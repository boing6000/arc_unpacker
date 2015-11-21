#include "fmt/entis/mio_audio_decoder.h"
#include "err.h"
#include "fmt/entis/audio/lossless.h"
#include "fmt/entis/audio/lossy.h"
#include "fmt/entis/common/enums.h"
#include "fmt/entis/common/sections.h"
#include "util/file_from_samples.h"
#include "util/format.h"

using namespace au;
using namespace au::fmt::entis;

static const bstr magic1 = "Entis\x1A\x00\x00"_b;
static const bstr magic2 = "\x00\x01\x00\x03\x00\x00\x00\x00"_b;
static const bstr magic3 = "Music Interleaved and Orthogonal transformed"_b;

static audio::MioHeader read_header(
    io::Stream &stream, common::SectionReader &section_reader)
{
    auto header_section = section_reader.get_section("Header");
    stream.seek(header_section.offset);
    common::SectionReader header_section_reader(stream);
    header_section = header_section_reader.get_section("SoundInf");
    stream.seek(header_section.offset);

    audio::MioHeader header;
    header.version = stream.read_u32_le();
    header.transformation
        = static_cast<common::Transformation>(stream.read_u32_le());
    header.architecture
        = static_cast<common::Architecture>(stream.read_u32_le());

    header.channel_count   = stream.read_u32_le();
    header.sample_rate     = stream.read_u32_le();
    header.blockset_count  = stream.read_u32_le();
    header.subband_degree  = stream.read_u32_le();
    header.sample_count    = stream.read_u32_le();
    header.lapped_degree   = stream.read_u32_le();
    header.bits_per_sample = stream.read_u32_le();
    return header;
}

static std::vector<audio::MioChunk> read_chunks(
    io::Stream &stream, common::SectionReader &section_reader)
{
    auto stream_section = section_reader.get_section("Stream");
    stream.seek(stream_section.offset);
    common::SectionReader chunk_section_reader(stream);
    std::vector<audio::MioChunk> chunks;
    for (auto &chunk_section : chunk_section_reader.get_sections("SoundStm"))
    {
        stream.seek(chunk_section.offset);
        audio::MioChunk chunk;
        chunk.version = stream.read_u8();
        chunk.initial = stream.read_u8() > 0;
        stream.skip(2);
        chunk.sample_count = stream.read_u32_le();
        chunk.data = stream.read(chunk_section.size - 8);
        chunks.push_back(chunk);
    }
    return chunks;
}

bool MioAudioDecoder::is_recognized_impl(File &file) const
{
    return file.stream.read(magic1.size()) == magic1
        && file.stream.read(magic2.size()) == magic2
        && file.stream.read(magic3.size()) == magic3;
}

std::unique_ptr<File> MioAudioDecoder::decode_impl(File &file) const
{
    file.stream.seek(0x40);

    common::SectionReader section_reader(file.stream);
    auto header = read_header(file.stream, section_reader);
    auto chunks = read_chunks(file.stream, section_reader);

    std::unique_ptr<audio::AudioDecoderImpl> impl;
    if (header.transformation == common::Transformation::Lossless)
        impl.reset(new audio::LosslessAudioDecoder(header));
    else if (header.transformation == common::Transformation::Lot)
        impl.reset(new audio::LossyAudioDecoder(header));
    else if (header.transformation == common::Transformation::LotMss)
        impl.reset(new audio::LossyAudioDecoder(header));
    else
    {
        throw err::NotSupportedError(util::format(
            "Transformation type %d not supported", header.transformation));
    }

    bstr samples;
    for (auto chunk : chunks)
        samples += impl->process_chunk(chunk);

    return util::file_from_samples(
        header.channel_count,
        header.bits_per_sample,
        header.sample_rate,
        samples,
        file.name);
}

static auto dummy = fmt::register_fmt<MioAudioDecoder>("entis/mio");

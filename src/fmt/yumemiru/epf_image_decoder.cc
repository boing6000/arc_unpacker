#include "fmt/yumemiru/epf_image_decoder.h"
#include "err.h"
#include "util/pack/lzss.h"

using namespace au;
using namespace au::fmt::yumemiru;

static const bstr magic = "yga\x00"_b;

bool EpfImageDecoder::is_recognized_impl(File &file) const
{
    file.stream.seek(0);
    return file.stream.read(magic.size()) == magic;
}

pix::Grid EpfImageDecoder::decode_impl(File &file) const
{
    file.stream.seek(magic.size());
    const auto width = file.stream.read_u32_le();
    const auto height = file.stream.read_u32_le();
    if (file.stream.read_u32_le() != 1)
        throw err::CorruptDataError("Expected '1'");
    const auto size_orig = file.stream.read_u32_le();
    const auto size_comp = file.stream.read_u32_le();
    const auto data = util::pack::lzss_decompress_bytewise(
        file.stream.read(size_comp), size_orig);
    return pix::Grid(width, height, data, pix::Format::BGRA8888);
}

static auto dummy = fmt::register_fmt<EpfImageDecoder>("yumemiru/epf");

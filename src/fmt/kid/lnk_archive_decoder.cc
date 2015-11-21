#include "fmt/kid/lnk_archive_decoder.h"
#include "err.h"
#include "fmt/kid/lnd_file_decoder.h"
#include "io/memory_stream.h"
#include "util/range.h"

using namespace au;
using namespace au::fmt::kid;

static const bstr magic = "LNK\x00"_b;

namespace
{
    struct ArchiveEntryImpl final : fmt::ArchiveEntry
    {
        bool compressed;
        size_t offset;
        size_t size;
    };
}

bool LnkArchiveDecoder::is_recognized_impl(File &arc_file) const
{
    return arc_file.stream.read(magic.size()) == magic;
}

std::unique_ptr<fmt::ArchiveMeta>
    LnkArchiveDecoder::read_meta_impl(File &arc_file) const
{
    arc_file.stream.seek(magic.size());
    auto meta = std::make_unique<ArchiveMeta>();
    auto file_count = arc_file.stream.read_u32_le();
    arc_file.stream.skip(8);
    auto file_data_start = arc_file.stream.tell() + (file_count << 5);
    for (auto i : util::range(file_count))
    {
        auto entry = std::make_unique<ArchiveEntryImpl>();
        entry->offset = arc_file.stream.read_u32_le() + file_data_start;
        u32 tmp = arc_file.stream.read_u32_le();
        entry->compressed = tmp & 1;
        entry->size = tmp >> 1;
        entry->name = arc_file.stream.read_to_zero(24).str();
        meta->entries.push_back(std::move(entry));
    }
    return meta;
}

std::unique_ptr<File> LnkArchiveDecoder::read_file_impl(
    File &arc_file, const ArchiveMeta &m, const ArchiveEntry &e) const
{
    auto entry = static_cast<const ArchiveEntryImpl*>(&e);
    auto output_file = std::make_unique<File>();
    output_file->name = entry->name;

    arc_file.stream.seek(entry->offset);
    auto data = arc_file.stream.read(entry->size);

    int key_pos = -1;
    if (output_file->has_extension(".wav"))
        key_pos = 0;
    else if (output_file->has_extension(".jpg"))
        key_pos = 0x1100;
    else if (output_file->has_extension(".scr"))
        key_pos = 0x1000;

    if (key_pos >= 0 && key_pos < static_cast<int>(entry->size))
    {
        u8 key = 0;
        for (u8 c : entry->name)
            key += c;

        for (size_t i = 0; i < 0x100 && key_pos + i < entry->size; i++)
        {
            data[key_pos + i] -= key;
            key = key * 0x6D - 0x25;
        }
    }
    output_file->stream.write(data);

    if (entry->compressed)
    {
        LndFileDecoder lnd_file_decoder;
        return lnd_file_decoder.decode(*output_file);
    }
    else
        return output_file;
}

std::vector<std::string> LnkArchiveDecoder::get_linked_formats() const
{
    return {"kid/cps", "kid/prt", "kid/waf"};
}

static auto dummy = fmt::register_fmt<LnkArchiveDecoder>("kid/lnk");

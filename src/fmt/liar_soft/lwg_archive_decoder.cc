#include "fmt/liar_soft/lwg_archive_decoder.h"
#include "fmt/liar_soft/wcg_image_decoder.h"
#include "util/encoding.h"
#include "util/range.h"

using namespace au;
using namespace au::fmt::liar_soft;

static const bstr magic = "LG\x01\x00"_b;

namespace
{
    struct ArchiveEntryImpl final : fmt::ArchiveEntry
    {
        size_t offset;
        size_t size;
    };
}

bool LwgArchiveDecoder::is_recognized_impl(File &arc_file) const
{
    return arc_file.stream.read(magic.size()) == magic;
}

std::unique_ptr<fmt::ArchiveMeta>
    LwgArchiveDecoder::read_meta_impl(File &arc_file) const
{
    arc_file.stream.seek(magic.size());
    size_t image_width = arc_file.stream.read_u32_le();
    size_t image_height = arc_file.stream.read_u32_le();

    size_t file_count = arc_file.stream.read_u32_le();
    arc_file.stream.skip(4);
    size_t table_size = arc_file.stream.read_u32_le();
    size_t file_data_start = arc_file.stream.tell() + table_size + 4;

    auto meta = std::make_unique<ArchiveMeta>();
    for (auto i : util::range(file_count))
    {
        auto entry = std::make_unique<ArchiveEntryImpl>();
        arc_file.stream.skip(9);
        entry->offset = file_data_start + arc_file.stream.read_u32_le();
        entry->size = arc_file.stream.read_u32_le();
        auto name_size = arc_file.stream.read_u8();
        entry->name = util::sjis_to_utf8(arc_file.stream.read(name_size)).str();
        meta->entries.push_back(std::move(entry));
    }
    return meta;
}

std::unique_ptr<File> LwgArchiveDecoder::read_file_impl(
    File &arc_file, const ArchiveMeta &m, const ArchiveEntry &e) const
{
    auto entry = static_cast<const ArchiveEntryImpl*>(&e);
    arc_file.stream.seek(entry->offset);
    auto data = arc_file.stream.read(entry->size);
    return std::make_unique<File>(entry->name, data);
}

std::vector<std::string> LwgArchiveDecoder::get_linked_formats() const
{
    return {"liar-soft/wcg", "liar-soft/lwg"};
}

static auto dummy = fmt::register_fmt<LwgArchiveDecoder>("liar-soft/lwg");

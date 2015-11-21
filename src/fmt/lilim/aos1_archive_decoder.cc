#include "fmt/lilim/aos1_archive_decoder.h"
#include "io/bit_reader.h"
#include "util/range.h"

using namespace au;
using namespace au::fmt::lilim;

namespace
{
    struct ArchiveEntryImpl final : fmt::ArchiveEntry
    {
        size_t offset;
        size_t size;
    };
}

bool Aos1ArchiveDecoder::is_recognized_impl(File &arc_file) const
{
    arc_file.stream.seek(0);
    return arc_file.has_extension("aos") && arc_file.stream.read_u32_le() > 0;
}

std::unique_ptr<fmt::ArchiveMeta>
    Aos1ArchiveDecoder::read_meta_impl(File &arc_file) const
{
    arc_file.stream.seek(0);
    auto meta = std::make_unique<ArchiveMeta>();
    while (!arc_file.stream.eof())
    {
        auto entry = std::make_unique<ArchiveEntryImpl>();
        const auto name = arc_file.stream.read_to_zero(0x10);
        if (!name.size())
            break;
        if (name[0] == 0xFF)
        {
            auto offset = arc_file.stream.read_u32_le();
            arc_file.stream.skip(12);
            arc_file.stream.skip(offset);
            continue;
        }
        entry->name = name.str();
        entry->offset = arc_file.stream.read_u32_le();
        entry->size = arc_file.stream.read_u32_le();
        arc_file.stream.skip(8);
        entry->offset += arc_file.stream.tell();
        meta->entries.push_back(std::move(entry));
    }
    return meta;
}

std::unique_ptr<File> Aos1ArchiveDecoder::read_file_impl(
    File &arc_file, const ArchiveMeta &m, const ArchiveEntry &e) const
{
    const auto entry = static_cast<const ArchiveEntryImpl*>(&e);
    const auto data = arc_file.stream.seek(entry->offset).read(entry->size);
    return std::make_unique<File>(entry->name, data);
}

std::vector<std::string> Aos1ArchiveDecoder::get_linked_formats() const
{
    return {"lilim/scr", "lilim/abm", "microsoft/bmp"};
}

static auto dummy = fmt::register_fmt<Aos1ArchiveDecoder>("lilim/aos1");

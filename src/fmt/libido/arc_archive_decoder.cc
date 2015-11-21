#include "fmt/libido/arc_archive_decoder.h"
#include <algorithm>
#include "util/pack/lzss.h"
#include "util/range.h"

using namespace au;
using namespace au::fmt::libido;

namespace
{
    struct ArchiveEntryImpl final : fmt::ArchiveEntry
    {
        size_t offset;
        size_t size_orig;
        size_t size_comp;
    };
}

bool ArcArchiveDecoder::is_recognized_impl(File &arc_file) const
{
    auto file_count = arc_file.stream.read_u32_le();
    if (file_count)
    {
        arc_file.stream.skip((file_count - 1) * 32 + 24);
        const auto last_file_size_comp = arc_file.stream.read_u32_le();
        const auto last_file_offset = arc_file.stream.read_u32_le();
        arc_file.stream.seek(last_file_size_comp + last_file_offset);
    }
    else
        arc_file.stream.skip(1);
    return arc_file.stream.eof();
}

std::unique_ptr<fmt::ArchiveMeta>
    ArcArchiveDecoder::read_meta_impl(File &arc_file) const
{
    auto meta = std::make_unique<ArchiveMeta>();
    u32 file_count = arc_file.stream.read_u32_le();
    for (auto i : util::range(file_count))
    {
        auto entry = std::make_unique<ArchiveEntryImpl>();
        auto tmp = arc_file.stream.read(20);
        for (auto i : util::range(tmp.size()))
            tmp[i] ^= tmp[tmp.size() - 1];
        entry->name = tmp.str(true);
        entry->size_orig = arc_file.stream.read_u32_le();
        entry->size_comp = arc_file.stream.read_u32_le();
        entry->offset = arc_file.stream.read_u32_le();
        meta->entries.push_back(std::move(entry));
    }
    return meta;
}

std::unique_ptr<File> ArcArchiveDecoder::read_file_impl(
    File &arc_file, const ArchiveMeta &m, const ArchiveEntry &e) const
{
    auto entry = static_cast<const ArchiveEntryImpl*>(&e);
    arc_file.stream.seek(entry->offset);
    auto data = arc_file.stream.read(entry->size_comp);
    data = util::pack::lzss_decompress_bytewise(data, entry->size_orig);
    return std::make_unique<File>(entry->name, data);
}

static auto dummy = fmt::register_fmt<ArcArchiveDecoder>("libido/arc");

// LWG archive
//
// Company:   Liar-soft
// Engine:    -
// Extension: .lwg
//
// Known games:
// - Souten No Celenaria - What a Beautiful World
// - Sekien no Inganock - What a Beautiful People
// - Shikkoku no Sharnoth - What a Beautiful Tomorrow

#include "fmt/liar_soft/lwg_archive.h"
#include "fmt/liar_soft/wcg_converter.h"
#include "util/encoding.h"
#include "util/range.h"

using namespace au;
using namespace au::fmt::liar_soft;

namespace
{
    struct TableEntry
    {
        std::string name;
        size_t offset;
        size_t size;
    };

    using Table = std::vector<std::unique_ptr<TableEntry>>;
}

static const std::string magic = "LG\x01\x00"_s;

static Table read_table(io::IO &arc_io)
{
    size_t file_count = arc_io.read_u32_le();
    arc_io.skip(4);
    size_t table_size = arc_io.read_u32_le();
    size_t file_start = arc_io.tell() + table_size + 4;

    Table table;
    table.reserve(file_count);
    for (auto i : util::range(file_count))
    {
        std::unique_ptr<TableEntry> entry(new TableEntry);
        arc_io.skip(9);
        entry->offset = file_start + arc_io.read_u32_le();
        entry->size = arc_io.read_u32_le();
        entry->name = util::sjis_to_utf8(arc_io.read(arc_io.read_u8()));
        table.push_back(std::move(entry));
    }
    size_t file_data_size = arc_io.read_u32_le();
    return table;
}

static std::unique_ptr<File> read_file(io::IO &arc_io, const TableEntry &entry)
{
    std::unique_ptr<File> file(new File);
    file->name = entry.name;
    arc_io.seek(entry.offset);
    file->io.write_from_io(arc_io, entry.size);
    return file;
}

struct LwgArchive::Priv
{
    WcgConverter wcg_converter;
};

LwgArchive::LwgArchive() : p(new Priv)
{
    add_transformer(&p->wcg_converter);
    add_transformer(this);
}

LwgArchive::~LwgArchive()
{
}

bool LwgArchive::is_recognized_internal(File &arc_file) const
{
    return arc_file.io.read(magic.size()) == magic;
}

void LwgArchive::unpack_internal(File &arc_file, FileSaver &file_saver) const
{
    arc_file.io.skip(magic.size());
    size_t image_width = arc_file.io.read_u32_le();
    size_t image_height = arc_file.io.read_u32_le();

    Table table = read_table(arc_file.io);
    for (auto &entry : table)
        file_saver.save(read_file(arc_file.io, *entry));
}

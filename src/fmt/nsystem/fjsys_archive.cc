// FJSYS archive
//
// Company:   -
// Engine:    NSystem
// Extension: none
//
// Known games:
// - Sono Hanabira ni Kuchizuke o 1
// - Sono Hanabira ni Kuchizuke o 2
// - Sono Hanabira ni Kuchizuke o 3
// - Sono Hanabira ni Kuchizuke o 4
// - Sono Hanabira ni Kuchizuke o 5
// - Sono Hanabira ni Kuchizuke o 6
// - Sono Hanabira ni Kuchizuke o 7
// - Sono Hanabira ni Kuchizuke o 8
// - Sono Hanabira ni Kuchizuke o 9
// - Sono Hanabira ni Kuchizuke o 10
// - Sono Hanabira ni Kuchizuke o 11

#include "fmt/nsystem/fjsys_archive.h"
#include "fmt/nsystem/mgd_converter.h"

using namespace au;
using namespace au::fmt::nsystem;

namespace
{
    typedef struct
    {
        size_t header_size;
        size_t file_names_size;
        size_t file_count;
    } Header;
}

static const std::string magic("FJSYS\x00\x00\x00", 8);

static std::unique_ptr<Header> read_header(io::IO &arc_io)
{
    std::unique_ptr<Header> header(new Header);
    header->header_size = arc_io.read_u32_le();
    header->file_names_size = arc_io.read_u32_le();
    header->file_count = arc_io.read_u32_le();
    arc_io.skip(64);
    return header;
}

static std::unique_ptr<File> read_file(io::IO &arc_io, const Header &header)
{
    std::unique_ptr<File> file(new File);
    size_t file_name_offset = arc_io.read_u32_le();
    size_t data_size = arc_io.read_u32_le();
    size_t data_offset = static_cast<size_t>(arc_io.read_u64_le());
    size_t old_pos = arc_io.tell();
    size_t file_names_start = header.header_size - header.file_names_size;

    arc_io.seek(file_name_offset + file_names_start);
    file->name = arc_io.read_until_zero();

    arc_io.seek(data_offset);
    file->io.write_from_io(arc_io, data_size);

    arc_io.seek(old_pos);
    return file;
}

struct FjsysArchive::Priv
{
    MgdConverter mgd_converter;
};

FjsysArchive::FjsysArchive() : p(new Priv)
{
    add_transformer(&p->mgd_converter);
}

FjsysArchive::~FjsysArchive()
{
}

bool FjsysArchive::is_recognized_internal(File &arc_file) const
{
    return arc_file.io.read(magic.size()) == magic;
}

void FjsysArchive::unpack_internal(File &arc_file, FileSaver &file_saver) const
{
    arc_file.io.skip(magic.size());

    std::unique_ptr<Header> header = read_header(arc_file.io);
    for (size_t i = 0; i < header->file_count; i++)
        file_saver.save(read_file(arc_file.io, *header));
}
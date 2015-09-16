#include "fmt/rpgmaker/rgssad_archive.h"
#include "test_support/archive_support.h"
#include "test_support/catch.hh"
#include "test_support/file_support.h"

using namespace au;
using namespace au::fmt::rpgmaker;

TEST_CASE("RpgMaker RGSSAD archives", "[fmt]")
{
    std::vector<std::shared_ptr<File>> expected_files
    {
        tests::stub_file("abc.txt", "123"_b),
        tests::stub_file("another.txt", "abcdefghij"_b),
    };

    RgssadArchive archive;
    auto actual_files = tests::unpack_to_memory(
        "tests/fmt/rpgmaker/files/rgssad/test.rgssad", archive);

    tests::compare_files(expected_files, actual_files, true);
}

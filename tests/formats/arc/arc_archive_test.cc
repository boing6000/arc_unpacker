#include "formats/arc/arc_archive.h"
#include "test_support/archive_support.h"

void test_arc_archive()
{
    std::vector<VirtualFile*> expected_files;
    std::unique_ptr<VirtualFile> file1(new VirtualFile);
    std::unique_ptr<VirtualFile> file2(new VirtualFile);
    file1->name = "abc.txt";
    file2->name = "another.txt";
    file1->io.write("123", 3);
    file2->io.write("abcdefghij", 10);
    expected_files.push_back(file1.get());
    expected_files.push_back(file2.get());

    std::string path = "tests/test_files/arc/arc/test.arc";
    std::unique_ptr<Archive> archive(new ArcArchive);
    auto output_files = unpack_to_memory(path, *archive);
    auto actual_files = output_files->get_saved();

    compare_files(expected_files, actual_files);
}

int main(void)
{
    test_arc_archive();
    return 0;
}
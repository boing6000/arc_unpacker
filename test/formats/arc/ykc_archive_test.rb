require 'lib/formats/arc/ykc_archive'
require 'test/test_helper'

# Unit tests for YkcArchive
class YkcArchiveTest < Test::Unit::TestCase
  def test
    TestHelper.generic_pack_and_unpack_test(YkcArchive)
  end

  def test_backslash
    input_files = InputFilesMock.new([
      { file_name: 'dir/test.txt', data: 'whatever' }])

    output_files = TestHelper.pack_and_unpack(YkcArchive, input_files)

    assert_equal('dir\\test.txt', output_files.files.first[:file_name])
  end
end
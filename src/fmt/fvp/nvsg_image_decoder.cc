#include "fmt/fvp/nvsg_image_decoder.h"
#include "err.h"
#include "util/pack/zlib.h"
#include "util/range.h"

using namespace au;
using namespace au::fmt::fvp;

static const bstr hzc1_magic = "hzc1"_b;
static const bstr nvsg_magic = "NVSG"_b;

bool NvsgImageDecoder::is_recognized_impl(File &file) const
{
    if (file.stream.read(hzc1_magic.size()) != hzc1_magic)
        return false;
    file.stream.skip(8);
    return file.stream.read(nvsg_magic.size()) == nvsg_magic;
}

pix::Grid NvsgImageDecoder::decode_impl(File &file) const
{
    file.stream.skip(hzc1_magic.size());
    size_t uncompressed_size = file.stream.read_u32_le();
    file.stream.skip(4); // nvsg header size
    file.stream.skip(nvsg_magic.size());
    file.stream.skip(2);
    size_t format = file.stream.read_u16_le();
    size_t width = file.stream.read_u16_le();
    size_t height = file.stream.read_u16_le();
    file.stream.skip(8);
    size_t image_count = file.stream.read_u32_le();
    file.stream.skip(8);

    bstr data = util::pack::zlib_inflate(file.stream.read_to_eof());

    pix::Format pixel_format;
    switch (format)
    {
        case 0:
            pixel_format = pix::Format::BGR888;
            break;

        case 1:
            pixel_format = pix::Format::BGRA8888;
            break;

        case 2:
            height *= image_count;
            pixel_format = pix::Format::BGRA8888;
            break;

        case 3:
            pixel_format = pix::Format::Gray8;
            break;

        case 4:
            for (auto i : util::range(data.size()))
                if (data.get<u8>()[i])
                    data.get<u8>()[i] = 255;
            pixel_format = pix::Format::Gray8;
            break;

        default:
            throw err::NotSupportedError("Unexpected pixel format");
    }

    return pix::Grid(width, height, data, pixel_format);
}

static auto dummy = fmt::register_fmt<NvsgImageDecoder>("fvp/nvsg");

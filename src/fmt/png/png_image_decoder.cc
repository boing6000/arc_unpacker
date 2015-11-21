#include "fmt/png/png_image_decoder.h"
#include <cstring>
#include <png.h>
#include "err.h"
#include "log.h"
#include "util/range.h"

using namespace au;
using namespace au::fmt::png;

static const bstr magic = "\x89PNG"_b;

static void error_handler(png_structp png_ptr, png_const_charp error_msg)
{
    throw err::CorruptDataError(error_msg);
}

static void warning_handler(png_structp png_ptr, png_const_charp warning_msg)
{
    Log.warn("libpng warning: %s\n", warning_msg);
}

static void read_handler(png_structp png_ptr, png_bytep output, png_size_t size)
{
    auto stream = reinterpret_cast<io::Stream*>(png_get_io_ptr(png_ptr));
    const auto input = stream->read(size);
    std::memcpy(output, input.get<u8>(), size);
}

static int custom_chunk_handler(png_structp png_ptr, png_unknown_chunkp chunk)
{
    const auto handler = reinterpret_cast<PngImageDecoder::ChunkHandler*>(
        png_get_user_chunk_ptr(png_ptr));
    const auto name = std::string(reinterpret_cast<const char*>(chunk->name));
    const auto data = bstr(chunk->data, chunk->size);
    (*handler)(name, data);
    return 1; // == handled
}

static pix::Grid decode(File &file, PngImageDecoder::ChunkHandler handler)
{
    png_structp png_ptr = png_create_read_struct(
        PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr)
        throw std::logic_error("Failed to create PNG read structure");

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        throw std::logic_error("Failed to create PNG info structure");

    png_set_error_fn(
        png_ptr,
        png_get_error_ptr(png_ptr),
        error_handler,
        warning_handler);

    png_set_read_user_chunk_fn(png_ptr, &handler, custom_chunk_handler);
    png_set_read_fn(png_ptr, &file.stream, &read_handler);
    png_read_png(
        png_ptr,
        info_ptr,
        PNG_TRANSFORM_GRAY_TO_RGB
            | PNG_TRANSFORM_STRIP_16
            | PNG_TRANSFORM_PACKING
            | PNG_TRANSFORM_BGR
            | PNG_TRANSFORM_EXPAND,
        nullptr);

    int color_type;
    int bits_per_channel;
    png_uint_32 width, height;
    png_get_IHDR(
        png_ptr, info_ptr,
        &width, &height,
        &bits_per_channel, &color_type,
        nullptr, nullptr, nullptr);
    if (bits_per_channel != 8)
        throw err::UnsupportedBitDepthError(bits_per_channel);

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    pix::Format format;
    if (color_type == PNG_COLOR_TYPE_RGB)
        format = pix::Format::BGR888;
    else if (color_type == PNG_COLOR_TYPE_RGBA)
        format = pix::Format::BGRA8888;
    else if (color_type == PNG_COLOR_TYPE_GRAY)
        format = pix::Format::Gray8;
    else
        throw err::NotSupportedError("Bad pixel format");

    bstr data;
    data.reserve(width * height * format_to_bpp(format));
    for (auto y : util::range(height))
        data += bstr(row_pointers[y], width * format_to_bpp(format));
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return pix::Grid(width, height, data, format);
}

bool PngImageDecoder::is_recognized_impl(File &file) const
{
    return file.stream.read(magic.size()) == magic;
}

pix::Grid PngImageDecoder::decode_impl(File &file) const
{
    return ::decode(file, [](const std::string &name, const bstr &data)
    {
        Log.warn("Ignoring unknown PNG chunk: %s\n", name.c_str());
    });
}

pix::Grid PngImageDecoder::decode(
    File &file, PngImageDecoder::ChunkHandler chunk_handler) const
{
    return ::decode(file, chunk_handler);
}

static auto dummy = fmt::register_fmt<PngImageDecoder>("png/png");

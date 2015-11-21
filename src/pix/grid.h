#pragma once

#include <memory>
#include "io/stream.h"
#include "pix/format.h"
#include "pix/palette.h"
#include "pix/pixel.h"

namespace au {
namespace pix {

    class Grid final
    {
    public:
        Grid(const Grid &other);
        Grid(size_t width, size_t height);
        Grid(size_t width, size_t height, const bstr &input, Format fmt);
        Grid(size_t width, size_t height, io::Stream &input_stream, Format fmt);
        Grid(size_t width, size_t height, const bstr &input,
            const Palette &palette);
        Grid(size_t width, size_t height, io::Stream &input_stream,
            const Palette &palette);
        ~Grid();

        size_t width() const;
        size_t height() const;
        Pixel &at(size_t x, size_t y);
        const Pixel &at(size_t x, size_t y) const;

        void flip_vertically();
        void flip_horizontally();
        void crop(size_t width, size_t height);
        void apply_mask(const Grid &other);
        void apply_palette(const Palette &palette);
        void paste(const Grid &other, const int target_x, const int target_y);

        Pixel *begin();
        Pixel *end();
        const Pixel *begin() const;
        const Pixel *end() const;

    private:
        struct Priv;
        std::unique_ptr<Priv> p;
    };

} }

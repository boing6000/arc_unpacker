#pragma once

#include "fmt/image_decoder.h"

namespace au {
namespace fmt {
namespace cronus {

    class GrpImageDecoder final : public ImageDecoder
    {
    public:
        GrpImageDecoder();
        ~GrpImageDecoder();
    protected:
        bool is_recognized_internal(File &) const override;
        pix::Grid decode_internal(File &) const override;
    private:
        struct Priv;
        std::unique_ptr<Priv> p;
    };

} } }
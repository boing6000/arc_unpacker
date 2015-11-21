#pragma once

#include <memory>
#include "io/stream.h"

namespace au {
namespace fmt {
namespace fc01 {
namespace common {

    class MrgDecryptor final
    {
    public:
        MrgDecryptor(const bstr &input);
        MrgDecryptor(const bstr &input, const size_t output_size);
        ~MrgDecryptor();
        bstr decrypt_without_key();
        bstr decrypt_with_key(const u8 key);
    private:
        struct Priv;
        std::unique_ptr<Priv> p;
    };

} } } }

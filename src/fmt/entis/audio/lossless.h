#pragma once

#include "fmt/entis/audio/common.h"
#include "fmt/entis/common/decoder.h"

namespace au {
namespace fmt {
namespace entis {
namespace audio {

    class LosslessAudioDecoder final : public AudioDecoderImpl
    {
    public:
        LosslessAudioDecoder(const MioHeader &header);
        ~LosslessAudioDecoder();

        bstr process_chunk(const MioChunk &chunk) override;

    private:
        struct Priv;
        std::unique_ptr<Priv> p;
    };

} } } }

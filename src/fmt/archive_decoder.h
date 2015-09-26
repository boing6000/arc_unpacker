#pragma once

#include "idecoder.h"

namespace au {
namespace fmt {

    class ArchiveDecoder : public IDecoder
    {
    public:
        virtual ~ArchiveDecoder();
        virtual FileNamingStrategy get_file_naming_strategy() const override;

        virtual void register_cli_options(ArgParser &) const override;
        virtual void parse_cli_options(const ArgParser &) override;

        virtual bool is_recognized(File &) const override;
        virtual void unpack(File &, FileSaver &, bool) const override;

    protected:
        virtual bool is_recognized_internal(File &) const = 0;
        virtual void unpack_internal(File &, FileSaver &) const = 0;
        void add_decoder(IDecoder *decoder);

    private:
        std::vector<IDecoder*> decoders;
    };

} }

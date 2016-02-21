#include "dec/mebius/koe_audio_decoder.h"

using namespace au;
using namespace au::dec::mebius;

KoeAudioDecoder::KoeAudioDecoder()
{
    plugin_manager.add(
        "snow",
        "Snow (full voice version)",
        {
            "\x16\x83\x0A\x4D\x6E\x39\xBF\xD8\x9C\x2B\x9E\x9F\xAE\x13\x8C\x63"
            "\xBE\x53\x95\x2E\x61\xB3\xFC\x26\x1C\xA5\xBF\x99\x69\x29\x3C\x99"
            "\xD7\x1E\x8B\xFD\xBD\x98\xC9\x12\x0E\x93\x5F\x59\x4E\x89\x7B\x26"
            "\xA7\x53\x50\xF1\xB6\x52\x5A\xA6\x6D\xCD\x20\xD9\xC3\x82\xCB\x21"
            "\xFD\x4D\x8B\xFA\x49\xEA\xC3\x7C\x81\x42\xEE\x38\xC3\xAB\xE0\x1A"
            "\xBD\x9F\xB4\x98\x4F\x59\x60\x8D\xEE\x41\x92\x87\xEB\x30\x2A\x66"
            "\xF4\x69\xA2\xA4\x0F\x53\xB6\x04\x4E\x4A\xB8\x9E\x8B\x23\xE0\xF8"
            "\xE6\xA2\x1F\xA4\x46\x9B\x34\x09\x33\xE3\x0B\x66\xB7\xCC\x1F\xA9"
            "\x1F\xEE\xF6\x1D\x42\x55\xE6\x19\x44\x61\xBA\xAE\x57\xFC\x6D\x08"
            "\xFE\x6B\x84\x5C\x69\x50\xD0\xCC\xC3\xBC\x92\x7C\x33\x59\x4D\x2D"
            "\x50\x00\x47\xCE\x4C\xDB\x7A\xB0\x25\x61\x07\x55\x8A\xAD\x50\x0B"
            "\xD3\x2D\x6C\xC9\x39\x94\x82\x0F\x9B\xF9\x45\x95\x1C\xBA\xA5\xB9"
            "\xD2\x60\xE3\xE3\xC7\x34\xAA\x43\x27\xC7\xC2\x3D\xBD\x8A\xA6\x4B"
            "\xA9\x3F\xEF\xBB\x6B\xE4\x6B\x89\x2A\xE9\xD1\xC0\xE5\x3A\xED\x1A"
            "\x61\xF9\xB3\xCC\x03\x0F\x82\xCD\x74\x36\x2A\xD8\x3E\x4E\xE0\x17"
            "\x37\x1B\x41\xC2\xE8\xA7\x81\x7C\xD3\x02\xFD\x51\xB4\x02\x43\x9E"
            ""_b,

            "\xCE\xC5\x94\xE8\xD5\x7F\xEB\xF4\x96\xCA\xAA\x80\xAC\x45\x60\x58"
            "\x71\x50\xDD\x72\x20\x39\x08\x73\xFE\x46\x07\xC5\x78\x77\xC0\x23"
            "\x49\x9F\xFC\xD1\x9A\x0F\x99\x7F\x3E\x7B\xAE\xF4\x66\xEE\x14\x94"
            "\x75\xD0\x0E\xD8\x64\x60\xB4\x3B\x40\x33\xC3\x4E\x40\x0E\xE4\x6C"
            "\x8D\x26\xBA\xB0\x17\xA5\x40\xB7\x27\x80\x79\x58\x92\xF8\x79\x3E"
            "\x2A\xDA\xC8\x29\xD3\x43\x66\xC0\xE5\x16\xAB\x25\x35\x68\x60\xC1"
            "\x77\x6E\x2B\x0E\x50\x58\xDC\xAE\xC5\x97\xE9\x27\xE1\xF3\x03\xA2"
            "\x43\x77\x13\xF0\xEC\x8C\x40\xB4\x7F\x62\x8B\x84\x40\x68\xAF\xD2"
            "\x10\xF2\xFE\x79\x3D\x63\x3D\xB4\x43\x65\xB8\x5F\x77\x13\x32\x56"
            "\xA4\x93\xC9\x3D\x9F\x89\xFE\x0B\xD0\x6C\x81\x2D\x3F\x94\xDD\x16"
            "\x1A\x12\x3A\x83\xC7\x26\xC3\xE0\xFE\xF1\xEC\x82\x6C\xAF\xA0\x30"
            "\xEB\xFD\x1A\xA1\xD0\xA9\xEC\x7A\x52\x6D\x83\xE4\x84\x97\x8F\x44"
            "\x89\x0E\xB7\xC1\x4F\xA1\x89\x8C\x09\xA6\xE5\x98\x4C\xC3\x7A\xCA"
            "\xE6\x6D\x06\xB7\x5B\x82\x6C\x02\x2E\x03\x57\xF3\xD6\x3D\x79\x5B"
            "\x87\x0E\xA2\x4E\xA6\xFE\xB8\x56\xA6\x55\xD3\x2B\x17\x6F\x7F\x84"
            "\x16\xF7\xE6\x99\x8A\x4E\x73\xDE\x45\x2E\x1A\xA6\xEF\x78\x67\x1A"
            ""_b,

            "\x40\xBA\x96\x7E\x07\xE1\x92\x95\x7E\x95\x17\x47\x3D\x1C\x08\x94"
            "\x02\xA5\x39\x7D\x95\xCB\xD8\x57\x09\x52\x67\xFD\x86\x57\xFD\x81"
            "\x04\xB9\x70\x54\x14\xC7\x8E\xA5\xA0\x11\xF5\xE2\xC5\x6E\xDB\x01"
            "\xA8\x8C\xA9\x25\xEB\x98\xD6\xBA\xAD\xD9\x62\x00\xAE\x50\xCA\x3E"
            "\x04\xAA\xF7\x98\xF9\x2C\xAE\xA4\x11\xCE\xF8\xCC\xAD\xB8\x07\xA5"
            "\xE8\xDF\x28\x2A\xA1\xE4\x81\x1F\x35\x7B\x4C\x7F\xFA\x04\x75\x31"
            "\x77\x0D\xD1\x79\xD3\x68\x2C\xDB\x16\x27\xBB\xD5\x2A\xFB\x2C\xBC"
            "\xB1\x70\xE2\x1C\xA8\xF6\x1E\x53\xDA\xA0\x89\xED\xB9\x25\x0A\x55"
            "\x08\x01\x37\xE7\x6B\xB4\xDB\x18\xE2\x13\x6B\x8E\x25\x98\x40\x05"
            "\xE7\x32\x1F\x4B\xA9\x7C\xC8\x24\x51\x54\x16\xFD\x6F\xC8\x67\x2B"
            "\xD2\xCD\x78\x18\xC2\xB0\xB6\xAA\x25\xB2\x4E\xCD\x3A\xD7\x0D\x43"
            "\x64\xBD\x35\x52\xFC\x07\x70\x67\xBE\x48\xFB\xA9\xD2\x67\xC3\xB8"
            "\x6A\xDC\x76\x04\x0E\xDD\xD3\xEB\x7A\x49\x39\xAC\xBD\xE5\x31\xBB"
            "\x71\xCC\x91\x8A\xB1\x09\x57\xF3\x39\xD2\x5E\xAB\x4F\x5F\x24\x86"
            "\xD5\x3D\xA8\xE7\x36\x23\x21\x32\x76\x3C\x98\x0A\x34\x51\x1E\xB8"
            "\x51\x40\x34\x93\x0B\x5C\x94\x24\x50\x6A\x72\x85\x04\xF1\xE5\x20"
            ""_b,
        });

    plugin_manager.add(
        "tomokoi",
        "Tomodachi Ijou Koibito Miman",
        {
            "\xB0\x6F\xA4\xD7\x8B\x81\xBD\xF3\x82\xAF\x95\x6B\x9D\x3E\x88\x73"
            "\xB8\xF9\xD8\x09\x31\xF3\x84\xDA\xCC\xAF\x54\x60\xFD\x97\x04\xA6"
            "\x05\x65\x20\x9A\xA7\x62\xD9\xD7\x5C\x98\x6F\x2D\x3A\x6E\x07\xF8"
            "\x86\x34\xF9\x05\xAB\x25\xF5\x70\x79\x64\x03\x7C\xF2\xF6\xBF\x9B"
            "\x91\xBB\x6B\x2A\xB3\xEB\xF2\x42\x39\x27\xD2\xF0\xEA\x00\x7A\x57"
            "\xAF\xB2\xCE\xEE\xBE\xCE\x1B\x87\x4E\x1F\xA4\xB0\xD1\x8E\x79\x9D"
            "\x6E\xC4\x26\xBF\x26\xDD\x39\x2D\x54\x49\x0B\xF6\x19\xDF\x3E\x19"
            "\x2F\xA2\x6A\x2A\x66\xAC\x68\x60\xA6\xEB\xB7\x24\xC0\x85\x5E\x40"
            "\xF8\x8B\xD8\x68\x78\xE8\x66\xA1\xAA\xA7\xC7\x4F\x2C\x6D\xD1\x5F"
            "\xC4\xE6\x46\x6F\x1B\x69\xF7\xD1\x23\x89\x1C\x53\x6E\x75\x41\xAF"
            "\x52\xCB\x6D\x03\x28\x38\xBE\x41\xFE\x99\x9D\xDF\x96\x7C\xD8\xDE"
            "\xF3\x95\x3E\x47\x5E\xA7\x05\x43\xA8\x6B\x96\x8C\x89\x6D\x16\x29"
            "\x60\x74\x31\x47\x36\xE2\x91\x3D\x57\xAD\x81\x63\xC8\xD5\x9A\x5F"
            "\x03\x7A\x14\x10\x32\x7B\xF1\x33\xDE\xBA\x52\x74\xC7\x6E\xF8\x7E"
            "\x4C\x2C\x58\x3B\xA9\x7A\x51\x5C\xFD\xA5\xCF\x67\xB8\x34\x85\x3D"
            "\x7D\x93\xE9\x7E\x9E\x6E\xC3\xB2\xB1\xD0\x5C\x83\x61\x6F\x27\x18"
            ""_b,

            "\x15\xEE\x1F\x83\x32\x20\xF8\x17\x53\xE3\x7B\xC0\x6A\x75\x93\xA5"
            "\x79\x32\x36\x7A\x76\xC5\xF4\x06\xC5\x08\xF5\x1E\xE4\xD5\xED\x72"
            "\x0B\xEC\x2A\x52\x6D\x87\xC3\x55\xD9\xC0\x07\x7A\x5E\x84\x35\x38"
            "\xB7\x0C\x17\x8A\x22\xB4\x17\xFB\xEE\xA1\x57\xAE\x51\x09\xF3\xE9"
            "\x65\x0F\x66\x3B\xD1\x91\x51\x0F\x08\x58\xC3\x75\x0D\x69\x3C\x65"
            "\xC4\x92\x1E\x27\x32\x69\x93\xD3\x19\xBA\xAF\x00\x87\x38\x79\xFB"
            "\x24\xEA\xAE\x4E\x4C\x1C\x06\xCF\xD9\xD7\x4E\x80\x2C\x27\xBF\x07"
            "\x38\xA6\x48\xF9\x43\x2E\x32\xD4\x13\x09\x7B\xBB\xAC\x92\x99\xF8"
            "\x70\xAC\xA1\xD0\x2A\x59\x8F\x17\xEF\xFE\x85\x9B\x53\x15\xDA\xE9"
            "\xC7\xBD\xD4\x64\x55\x9C\x42\x38\x4E\x55\x7D\x3D\xCB\x96\xF0\xA8"
            "\x14\x92\x21\x3E\xA1\xCC\xF0\xD9\x0F\xA1\x0B\x00\xFD\x5C\xAE\x4E"
            "\x53\x61\xC6\xF6\xCE\xA5\x91\x2C\x62\x01\x3A\x17\x53\x1A\xA1\x47"
            "\xFE\xF1\xD1\x42\x48\xD3\xBB\x7F\x1D\xA8\xC7\x96\x8E\xFC\x5E\xEA"
            "\x5A\xAD\xE8\xFB\x78\x8B\x76\xD2\x86\x7B\x79\x0B\x96\xC4\x51\x04"
            "\x43\x30\x20\x3F\x19\x19\x88\xE3\x27\x10\x65\xFE\xC8\x4A\x11\x67"
            "\x01\x55\x46\xEE\x80\x68\xC9\xC1\x1B\x4C\x49\x14\xC9\x95\xA9\x7F"
            ""_b,

            "\x06\xDE\xEF\x76\xD2\xDA\xE7\x95\x7A\x87\x6D\x7C\xF6\x17\x44\x9F"
            "\x08\xD2\xC5\x89\xDC\xDE\xA1\x0F\x2D\xCB\xCA\xB8\x6E\xBB\x7F\x8A"
            "\x9E\x63\x70\x58\xCC\xA8\x61\x34\x68\x98\xD8\xB3\x74\x18\x2C\x9B"
            "\x1F\x64\xFD\x28\xF4\x56\x8E\x80\x98\x06\x5C\x13\x38\x31\xFE\x62"
            "\xBD\x11\xBC\x05\x58\xF6\x38\xDD\x6A\x5A\x01\x4C\x03\xC1\x0A\xE0"
            "\x58\xA2\x88\x4E\xF6\x96\x1A\x2A\xA0\xA1\xA5\xAF\x04\x4E\x08\x99"
            "\xC8\xDA\x9B\x4C\xA4\xD2\x82\x51\xE2\xBB\x33\xFC\x23\xAF\xAD\x22"
            "\xB7\x98\x5D\x36\xD3\xE7\x8C\x54\x0C\x6A\xE6\x6D\x53\x28\xFA\xAE"
            "\xE7\x66\x36\x50\xE6\x40\xBA\xDF\xFA\xE2\xA3\xCC\xDB\x70\x89\x27"
            "\x88\x0A\x59\x6D\x81\x06\xD1\x5A\x65\x5E\xC3\x7F\x2F\xC7\x5D\xB2"
            "\x86\x91\x19\x0A\xD7\x33\xA8\xF0\x21\xA7\xE7\x19\xB5\x07\xB4\xCA"
            "\x59\xEA\xB8\xD4\xFB\x21\xF8\xAC\x7C\x2F\x45\xEA\x22\x2B\x58\x4A"
            "\x55\xEA\xB6\x45\x34\x96\xAE\xFD\x86\x97\xF9\x93\xBE\x6A\x6A\xFB"
            "\x7B\x65\x21\x24\x42\x5C\x37\x4F\x64\x45\x58\x0C\xBC\xC1\xB7\xAD"
            "\xC7\xB6\xE3\x21\xBB\xC8\xD2\x15\x1F\xF1\x39\x3F\x87\x86\x88\xBE"
            "\x84\xD7\x1A\x63\xD5\x51\x63\xDB\x74\x39\x4C\x12\x12\xF1\x6E\x2C"
            ""_b
        });

    add_arg_parser_decorator(
        plugin_manager.create_arg_parser_decorator(
            "Selects KOE decryption routine."));
}

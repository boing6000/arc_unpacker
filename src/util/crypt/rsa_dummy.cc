#include "err.h"
#include "util/crypt/rsa.h"

using namespace au;
using namespace au::util::crypt;

struct Rsa::Priv
{
};

Rsa::Rsa(const RsaKey &key)
{
    throw err::NotSupportedError(
        "RSA is unavailable - need to compile with OpenSSL.");
}

Rsa::~Rsa()
{
}

bstr Rsa::decrypt(const bstr &input) const
{
    return ""_b;
}

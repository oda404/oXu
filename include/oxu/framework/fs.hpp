
#pragma once

#include<string>

namespace oxu::framework::fs
{

#if defined(__linux__)
/* Canonicalizes the path but also resolves '~' to the user's home directory. */
std::string canonical(std::string path);
#endif

}

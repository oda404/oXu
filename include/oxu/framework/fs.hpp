
#pragma once

#include<string>

namespace oxu::framework::fs
{

#if defined(__linux__)
/* Resolves '~' to the user's home directory. */
std::string path_resolve_homedir(std::string path);
#endif

}

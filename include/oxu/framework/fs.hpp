
#pragma once

#include<string>

namespace oxu::framework::fs
{

#if defined(__linux__)
/* Canonicalizes the path but also resolves '~' to the user's home directory. */
std::string canonical(std::string path);
#endif

/**
 * Creates a given directory.
 * If it already exists it will not touch it and return true.
 * @return false if not privileged, true otherwise.
 */
bool dir_create(const std::string &path);

}

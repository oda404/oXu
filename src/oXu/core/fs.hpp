#pragma once

#include<string>

namespace oxu::fs
{
    bool is_config_dir_valid(const std::string &path);
    void validate_config_dir(const std::string &path);
}

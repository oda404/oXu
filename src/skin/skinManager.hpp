// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<experimental/filesystem>
#include<vector>
#include<string>

namespace fs = std::experimental::filesystem;

namespace oxu
{
    class SkinManager
    {
    private:
        std::vector<std::string> skins;

    public:
        void enumSkins();

        const std::string &getSkinPath(const int &index);
    };
}
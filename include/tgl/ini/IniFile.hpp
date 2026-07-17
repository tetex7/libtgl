/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/14/2026.
//

#pragma once
#ifndef LIBTGL_INIFILE_HPP
#define LIBTGL_INIFILE_HPP
#include <tgl/Object.hpp>
#include <tgl/String.hpp>
#include <filesystem>
#include <fstream>
#include <vector>

namespace tgl::ini
{
    class IniFile final : public Object
    {
    private:
        std::vector<String> lines;
        std::filesystem::path path;
        std::ifstream ifs;

    public:
        explicit IniFile(const std::filesystem::path& path);



        ~IniFile() override = default;
    };
}

#endif //LIBTGL_INIFILE_HPP

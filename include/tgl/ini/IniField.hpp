/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/18/2026.
//

#pragma once
#ifndef LIBTGL_INIFIELD_HPP
#define LIBTGL_INIFIELD_HPP

#include <tgl/ini/IniObjectType.hpp>
#include <tgl/Object.hpp>

namespace tgl::ini
{
    using IniIdentifier = String;

    class IniField : public Object
    {
        IniObjectType type;
    protected:
        explicit IniField(IniObjectType type);
    public:

        [[nodiscard]] IniObjectType getType() const;

        ~IniField() override = default;
    };
}

#endif //LIBTGL_INIFIELD_HPP

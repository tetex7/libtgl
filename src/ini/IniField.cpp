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
#include <tgl/ini/IniField.hpp>

namespace tgl::ini
{
    IniField::IniField(IniObjectType type)
    : type(type) {}

    IniObjectType IniField::getType() const
    {
        return this->type;
    }
}

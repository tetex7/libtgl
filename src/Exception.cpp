/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 06/30/2026.
//

#include <tgl/Exception.hpp>

#include "tgl/String.hpp"

namespace tgl
{
    const char* Exception::what() const noexcept
    {
        return message.c_str();
    }

    String Exception::toString() const
    {
        return String(this->getMessage());
    }

    const std::string& Exception::getMessage() const
    {
        return message;
    }
}

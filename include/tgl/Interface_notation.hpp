/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/05/2026.
//

#pragma once

#ifndef LIBTGL_INTERFACE_NOTATION_HPP
#define LIBTGL_INTERFACE_NOTATION_HPP
#include <tgl/Object.hpp>

#define TGL_INTERFACE_DECLARE(name) class name : public tgl::Object { \
    public: \
    virtual ~##name() = default; \
    private:

#define TGL_INTERFACE_METHOD(protection, signature) protection: virtual signature = 0

#define TGL_INTERFACE_DECLARE_END(name) };

#endif //LIBTGL_INTERFACE_NOTATION_HPP

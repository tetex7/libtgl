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
#ifndef LIBTGL_ISTREAM_HPP
#define LIBTGL_ISTREAM_HPP

#include <cstddef>
#include <functional>

namespace tgl
{
    /**
     * @brief DON'T USE WIP
     * @tparam T
     */
    template <typename T>
    class IStream
    {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

        using rref = value_type&&;

        using offset_t = size_t;
    protected:
        IStream() = default;
    public:



        virtual void seek(offset_t offset) = 0;

        virtual reference peek() = 0;
        virtual const_reference peek() const = 0;

        virtual


        virtual ~IStream() = default;
    };
}

#endif //LIBTGL_ISTREAM_HPP

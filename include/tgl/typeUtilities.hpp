/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/15/2026.
//

#pragma once
#ifndef LIBTGL_TYPEUTILITIES_HPP
#define LIBTGL_TYPEUTILITIES_HPP

#include <type_traits>
#include <concepts>

namespace tgl
{
    using hash_t = std::size_t;

    template <typename T>
    struct real_type
    {
        using type = std::remove_cvref_t<T>;
    };

    template <typename T>
    using real_type_t = typename real_type<T>::type;

    template <typename T>
    struct is_real_type : std::bool_constant<std::same_as<T, real_type_t<T>>>{};

    template <typename T>
    constexpr inline bool is_real_type_v = is_real_type<T>::value;

    template <typename T>
    concept RealType = is_real_type_v<T>;

    template <typename T>
    concept Pointer = std::is_pointer_v<T>;
}

static_assert(!tgl::RealType<const int>);
static_assert(!tgl::RealType<volatile int>);
static_assert(!tgl::RealType<int&>);
static_assert(!tgl::RealType<const int&>);

static_assert(tgl::RealType<int>);

#endif //LIBTGL_TYPEUTILITIES_HPP

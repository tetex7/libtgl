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

#pragma once
#ifndef LIBTGL_DYNACAST_HPP
#define LIBTGL_DYNACAST_HPP
#include <type_traits>
#include <concepts>
#include <expected>
#include <ranges>


#include <tgl/Object.hpp>

#include <tgl/BadCastException.hpp>

#include <tgl/export_defs.hpp>
#include <tgl/typeUtilities.hpp>


namespace tgl
{
    template <typename T>
    concept DynacastTarget = RealType<T> && TglObject<T>;

    namespace unsafe
    {
        //This is heresy and should be only used with an environments already constrained by concepts
        //Or other forms of type checking
        template<DynacastTarget To,  DynacastTarget From>
        constexpr inline To& uncheckedCast(From& from)
        {
            return static_cast<To&>(from);
        }

        template<DynacastTarget To,  DynacastTarget From>
        constexpr inline const To& uncheckedCast(const From& from)
        {
            return static_cast<const To&>(from);
        }

        /**
         * @brief This call is extremely dangerous Only use when absolutely needed 
         */
        template<DynacastTarget From>
        inline std::span<const uint8_t> uncheckedByteCast(const From& from)
        {
            return std::span<const uint8_t>(std::bit_cast<const uint8_t*>(&from), sizeof(From));
        }
    }

    template<DynacastTarget To, DynacastTarget From>
    inline std::expected<std::reference_wrapper<To>, BadCastException> exp_dynacast(From& from)
    {
        if constexpr (std::same_as<To, From>)
            return from;

        if (To* ptr = dynamic_cast<To*>(&from))
            return *ptr;

        return std::unexpected{BadCastException(typeid(from), typeid(To))};
    }

    template<DynacastTarget To, DynacastTarget From>
    inline std::expected<std::reference_wrapper<const To>, BadCastException> exp_dynacast(const From& from)
    {
        if constexpr (std::same_as<To, From>)
            return from;

        if (const To* ptr = dynamic_cast<const To*>(&from))
            return *ptr;

        return std::unexpected{BadCastException(typeid(from), typeid(To))};
    }

    template<DynacastTarget To, DynacastTarget From>
    inline To& dynacast(From& from)
    {
        if constexpr (std::same_as<To, From>)
            return from;

        auto exp = exp_dynacast<To, From>(from);

        if (exp.has_value())
        {
            return exp.value();
        }
        throw exp.error();
    }

    template<DynacastTarget To, DynacastTarget From>
    inline const To& dynacast(const From& from)
    {
        if constexpr (std::same_as<To, From>)
            return from;

        auto exp = exp_dynacast<To, From>(from);

        if (exp.has_value())
        {
            return exp.value();
        }
        throw exp.error();
    }

    template<DynacastTarget To, DynacastTarget From>
    inline To& super_cast(From& from)
    {
        return dynacast<To, From>(from);
    }

    template<DynacastTarget To, DynacastTarget From>
    inline const To& super_cast(const From& from)
    {
        return dynacast<To, From>(from);
    }
}

#endif //LIBTGL_DYNACAST_HPP

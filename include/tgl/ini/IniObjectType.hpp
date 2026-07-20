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

#ifndef LIBTGL_INIOBJECTTYPE_HPP
#define LIBTGL_INIOBJECTTYPE_HPP
#include <cstdint>

#include <tgl/typeUtilities.hpp>
#include <tgl/String.hpp>

namespace tgl::ini
{
    enum class IniObjectType : std::uint8_t
    {
        NONE = 0,
        BOOLEAN = sizeof(bool),
        INTEGER = sizeof(std::int64_t),
        DOUBLE,
        OBJECT,
        STRING,
    };

    inline bool operator==(const IniObjectType a, const std::uint8_t b)
    {
        return static_cast<std::uint8_t>(a) == b;
    }

    inline bool operator==(const std::uint8_t a, const IniObjectType b)
    {
        return a == static_cast<std::uint8_t>(b);
    }

    inline bool operator!=(const IniObjectType a, const std::uint8_t b)
    {
        return static_cast<std::uint8_t>(a) != b;
    }

    inline bool operator!=(const std::uint8_t a, const IniObjectType b)
    {
        return a != static_cast<std::uint8_t>(b);
    }

    inline const char* getIniObjectTypeAsString(const IniObjectType e)
    {
        switch (e)
        {
            case IniObjectType::NONE: return "NONE";
            case IniObjectType::OBJECT: return "OBJECT";
            case IniObjectType::INTEGER: return "INTEGER";
            case IniObjectType::BOOLEAN: return "BOOLEAN";
            case IniObjectType::STRING: return "STRING";
            case IniObjectType::DOUBLE: return "FLOAT";
            default: return "unknown";
        }
    }

    class IniObject;

    template <typename T>
    concept isIniObjectConpat = std::same_as<T, std::int64_t> ||
        std::same_as<T, double> ||
        std::same_as<T, bool> ||
        std::constructible_from<T, const IniObject&> ||
        std::same_as<T, String>;

    template <isIniObjectConpat T>
    constexpr IniObjectType getIniObjectType()
    {
        if constexpr (std::same_as<T, std::int64_t>)
        {
            return IniObjectType::INTEGER;
        }
        else if constexpr (std::same_as<T, bool>)
        {
            return IniObjectType::BOOLEAN;
        }
        else if constexpr (std::same_as<T, double>)
        {
            return IniObjectType::DOUBLE;
        }
        else if constexpr (std::same_as<T, Object>)
        {
            return IniObjectType::OBJECT;
        }
        else if constexpr (std::same_as<T, String>)
        {
            return IniObjectType::STRING;
        }
        return IniObjectType::NONE;
    }


    class IniIntField;
    class IniStringField;
    class IniBoolField;
    class IniDoubleField;


    template<RealType T>
    constexpr IniObjectType assumeIniFieldType()
    {
        if constexpr (std::same_as<T, IniIntField>)
        {
            return IniObjectType::INTEGER;
        }
        else if constexpr (std::same_as<T, IniBoolField>)
        {
            return IniObjectType::BOOLEAN;
        }
        else if constexpr (std::same_as<T, IniDoubleField>)
        {
            return IniObjectType::DOUBLE;
        }
        else if constexpr (std::same_as<T, IniStringField>)
        {
            return IniObjectType::STRING;
        }
        return IniObjectType::NONE;
    }

    template <isIniObjectConpat T>
    struct ini_field_type_selector{};

    template <>
    struct ini_field_type_selector<std::int64_t>
    {
        using type = IniIntField;
    };

    template <>
    struct ini_field_type_selector<bool>
    {
        using type = IniBoolField;
    };

    template <>
    struct ini_field_type_selector<double>
    {
        using type = IniDoubleField;
    };

    template <>
    struct ini_field_type_selector<String>
    {
        using type = IniStringField;
    };

    template <isIniObjectConpat T>
    using ini_field_type_selector_t = typename ini_field_type_selector<T>::type;

    template <RealType T>
    struct ini_field_actual_type{};

    template <>
    struct ini_field_actual_type<std::int64_t>
    {
        using type = IniIntField;
    };

    template <>
    struct ini_field_actual_type<bool>
    {
        using type = IniBoolField;
    };

    template <>
    struct ini_field_actual_type<double>
    {
        using type = IniDoubleField;
    };

    template <>
    struct ini_field_actual_type<String>
    {
        using type = IniStringField;
    };

    template <RealType T>
    using ini_field_actual_type_t = typename ini_field_actual_type<T>::type;
}

#endif //LIBTGL_INIOBJECTTYPE_HPP

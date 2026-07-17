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
        BOOLEAN = sizeof(bool),
        INTEGER = sizeof(std::int64_t),
        UNSIGNED = sizeof(std::uint64_t),
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
            case IniObjectType::OBJECT: return "OBJECT";
            case IniObjectType::INTEGER: return "INTEGER";
            case IniObjectType::BOOLEAN: return "BOOLEAN";
            case IniObjectType::STRING: return "STRING";
            case IniObjectType::FLOAT: return "FLOAT";
            default: return "unknown";
        }
    }

    class IniObject;



    template <RealType T>
    concept isIniObjectConpat = std::same_as<T, std::uint64_t> ||
        std::same_as<T, std::int64_t> ||
        std::same_as<T, double> ||
        std::same_as<T, bool> ||
        std::same_as<T, Object> ||
        std::same_as<T, String>;

    constexpr bool s = isIniObjectConpat<int>;
}

#endif //LIBTGL_INIOBJECTTYPE_HPP

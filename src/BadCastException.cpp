//
// Created by tete on 07/02/2026.
//
#include <format>
#include <tgl/BadCastException.hpp>

namespace tgl
{
    BadCastException::BadCastException(const std::type_info& from, const std::type_info& to)
    : Exception(std::format("failed to cast {} to {}", from.name(), to.name())),
    from(from),
    to(to) {}

    const std::type_info& BadCastException::getFromType() const
    {
        return from;
    }

    const std::type_info& BadCastException::getToType() const
    {
        return to;
    }
}

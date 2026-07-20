/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/13/2026.
//

#pragma once
#ifndef LIBTGL_OBJECTIDENTIFIER_HPP
#define LIBTGL_OBJECTIDENTIFIER_HPP

#include <array>
#include <cstdint>
#include <span>
#include <string>
#include <tgl/export_defs.hpp>

/**
 * Out of Model
 */
namespace tgl::oom
{
    class TGL_API ObjectIdentifier final
    {
    private:
        std::uint16_t prefix;
        std::uint16_t body;
        std::uint16_t suffix;
    public:
        ObjectIdentifier();

        ObjectIdentifier(std::uint16_t prefix, std::uint16_t body, std::uint16_t suffix);

        ObjectIdentifier(ObjectIdentifier&&) noexcept = default;
        ObjectIdentifier& operator=(ObjectIdentifier&&) noexcept = default;

        [[nodiscard]] std::array<std::uint8_t, 6> getByteArray() const;

        [[nodiscard]] std::span<const std::uint8_t> getByteView() const;

        [[nodiscard]] std::string asString() const;

        [[nodiscard]] std::uint16_t getPrefix() const;

        [[nodiscard]] std::uint16_t getBody() const;

        [[nodiscard]] std::uint16_t getSuffix() const;

        bool operator==(const ObjectIdentifier& b) const;
        bool operator!=(const ObjectIdentifier& b) const;

        ObjectIdentifier(const ObjectIdentifier&) = delete;
        ObjectIdentifier& operator=(const ObjectIdentifier&) = delete;
    };

    //static_assert(std::is_trivially_copyable_v<ObjectIdentifier>, "ObjectIdentifier is not trivially copyable");
}

template<>
struct std::formatter<tgl::oom::ObjectIdentifier> : formatter<std::string> { // NOLINT(*-dcl58-cpp)
    auto format(const tgl::oom::ObjectIdentifier& obj, std::format_context& ctx) const {
        return std::formatter<std::string>::format(
            obj.asString(),
            ctx
        );
    }
};

#endif //LIBTGL_OBJECTIDENTIFIER_HPP

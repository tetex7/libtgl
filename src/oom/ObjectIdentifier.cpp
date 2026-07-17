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

#include <bit>
#include <format>
#include <tgl/oom/ObjectIdentifier.hpp>
#include <random>

static std::mt19937& rng()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

namespace tgl::oom
{
    ObjectIdentifier::ObjectIdentifier()
        : prefix(std::uniform_int_distribution<std::uint16_t>(
              std::numeric_limits<std::uint16_t>::min()+25,
              std::numeric_limits<std::uint16_t>::max())(rng()))
        , body(std::uniform_int_distribution<std::uint16_t>(
              std::numeric_limits<std::uint16_t>::min()+7,
              std::numeric_limits<std::uint16_t>::max())(rng()))
        , suffix(std::uniform_int_distribution<std::uint16_t>(
              std::numeric_limits<std::uint16_t>::min()+5,
              std::numeric_limits<std::uint16_t>::max())(rng()))
    {}

    ObjectIdentifier::ObjectIdentifier(std::uint16_t prefix, std::uint16_t body, std::uint16_t suffix)
    : prefix(prefix), body(body), suffix(suffix) {}

    std::array<std::uint8_t, 6> ObjectIdentifier::getByteArray() const
    {
        static_assert(sizeof(std::array<std::uint8_t, 6>) == sizeof(ObjectIdentifier), "Object identifier cannot fit into this array");

        std::array<std::uint8_t, 6> result;
        std::memcpy(result.data(), this, sizeof(ObjectIdentifier));

        return result;
    }

    std::span<const std::uint8_t> ObjectIdentifier::getByteView() const
    {
        static_assert(sizeof(ObjectIdentifier) == 6, "Object identifier should be 6 bytes");
        return std::span(std::bit_cast<const std::uint8_t*>(this), 6);
    }

    std::string ObjectIdentifier::asString() const
    {
        return std::format("{{{:x}-{:x}-{:x}}}", prefix, body, suffix);
    }

    std::uint16_t ObjectIdentifier::getPrefix() const
    {
        return prefix;
    }

    std::uint16_t ObjectIdentifier::getBody() const
    {
        return body;
    }

    std::uint16_t ObjectIdentifier::getSuffix() const
    {
        return suffix;
    }

    bool ObjectIdentifier::operator==(const ObjectIdentifier& b) const
    {
        return std::memcmp(this, &b, sizeof(ObjectIdentifier)) == 0;
    }

    bool ObjectIdentifier::operator!=(const ObjectIdentifier& b) const
    {
        return !this->operator==(b);
    }
}

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

#include "tgl/Object.hpp"
#include "tgl/String.hpp"
#include "tgl/dynacast.hpp"

#include <cxxabi.h>
namespace tgl
{
    std::string Object::getGoodTypeName() const
    {
#ifndef _WIN32
        int status = -4; // Initialize to an unknown error status

        // Pass NULL for output_buffer so __cxa_demangle allocates memory for us
        char* demangled = abi::__cxa_demangle(this->getTypeInfo().name(), nullptr, nullptr, &status);

        if (status == 0 && demangled != nullptr) {
            std::string result(demangled);
            std::free(demangled); // Free the memory allocated by __cxa_demangle
            return result;
        }

        // Return original string if demangling fails
        return this->getTypeInfo().name();
#else
        return this->getTypeInfo().name();
#endif
    }

    const std::type_info& Object::getTypeInfo() const
    {
        return typeid(*this);
    }

    std::string Object::toStdString() const
    {
        if (instanceOf<String>(*this))
        {
            return unsafe::uncheckedCast<String>(*this).asStdString();
        }
        return this->toString().asStdString();
    }

    String Object::toString() const
    {
        return String(std::format("{}@{:p}", this->getGoodTypeName(), std::bit_cast<void*>(this)));
    }

    std::size_t Object::getHash() const
    {
        return std::hash<const void*>{}(this);
    }

    bool Object::equals(const Object& b) const
    {
        return this == std::addressof(b);
    }

    bool Object::operator==(const Object& b) const
    {
        return this->equals(b);
    }

    bool Object::operator!=(const Object& b) const
    {
        return !this->equals(b);
    }
}

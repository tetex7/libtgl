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

#ifndef LIBTGL_EXCEPTION_HPP
#define LIBTGL_EXCEPTION_HPP

#include <exception>
#include <tgl/Object.hpp>

namespace tgl
{
    //Yes I know multi inheritance from two whole not interface objects is heresy
    //Hypocrisy had to be done for backwards compatibility
    class TGL_API Exception : public std::exception, public Object
    {
    protected:
        std::string message;
    public:
        explicit Exception(const char* what) : std::exception(), message(what){}
        explicit Exception(const std::string& message) : std::exception(), message(message){}

        [[nodiscard]] const char* what() const noexcept override;

        String toString() const override;

        [[nodiscard]] virtual const std::string& getMessage() const;

        ~Exception() override = default;
    };
}

#endif //LIBTGL_EXCEPTION_HPP

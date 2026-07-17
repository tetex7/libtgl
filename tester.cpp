/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/05/2026.
//
#include <print>

#include <tgl/String.hpp>

#include <tgl/dynacast.hpp>
#include <tgl/BadCastException.hpp>

int main()
{
    tgl::String test = "ttty";
    test = test.append("fff");

    tgl::String g = "hf,bg,jh,bj";

    for (const tgl::String& s : test.split('y'))
    {
        std::println("{}", s);
    }

    if (test.endsWith("fff"))
    {
        std::println("tg");
    }

    for (const auto& it = tgl::dynacast<tgl::IIterable<char>>(test); const char& c : it)
    {
        std::println("{}", c);
    }

    try
    {
        const auto& g = tgl::exp_dynacast<tgl::Exception>(test);
        (void)g;
        throw g.error();
    }
    catch (tgl::Exception& e)
    {
        std::println("{}", e.getMessage());
    }

    std::println("{}", tgl::Object());
}

/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/19/2026.
//

#include <gtest/gtest.h>

#include "tgl/dynacast.hpp"
#include "tgl/Object.hpp"
#include "tgl/String.hpp"

TEST(TglDynacastTests, goodCast)
{
    tgl::String str;
    ASSERT_NO_THROW((void)tgl::dynacast<tgl::Object>(str));
}

TEST(TglDynacastTests, badCast)
{
    tgl::String str;
    ASSERT_ANY_THROW((void)tgl::dynacast<tgl::Exception>(str));
}

TEST(TglDynacastTests, expectedGoodCast)
{
    tgl::String str;
    auto expected = tgl::exp_dynacast<tgl::Object>(str);

    ASSERT_TRUE(expected.has_value());
}

TEST(TglDynacastTests, expectedBadCast)
{
    tgl::String str;
    auto expected = tgl::exp_dynacast<tgl::Exception>(str);

    ASSERT_FALSE(expected.has_value());
}
/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/17/2026.
//

#include <gtest/gtest.h>

#include "tgl/String.hpp"

TEST(TglStringTests, zeroSize)
{
    const tgl::String str = "";
    ASSERT_EQ(0, str.getLength());

    ASSERT_TRUE(str.isEmpty());
}

TEST(TglStringTests, split)
{
    const char* splitter = "a,b,c";

    const auto strs = tgl::String::of(splitter).split(',');

    ASSERT_EQ(strs.size(), 3);
    ASSERT_EQ(strs[0], "a");
    ASSERT_EQ(strs[1], "b");
    ASSERT_EQ(strs[2], "c");
}

TEST(TglStringTests, splitTwoSplitEdgeCase)
{
    const char* splitter = "a,b";

    const auto strs = tgl::String(splitter).split(',');

    ASSERT_EQ(strs.size(), 2);
    ASSERT_EQ(strs[0], "a");
    ASSERT_EQ(strs[1], "b");
}

TEST(TglStringTests, splitNoSplitEdgeCase)
{
    const char* splitter = "agh";

    const auto strs = tgl::String::of(splitter).split(',');

    ASSERT_EQ(strs.size(), 1);
    ASSERT_EQ(strs[0], splitter);
}


TEST(TglStringTests, formatPassThrough)
{
    const tgl::String str = tgl::String::format("{},{},{}", 'a', 'b', 'c');

    ASSERT_EQ(str, "a,b,c");
}
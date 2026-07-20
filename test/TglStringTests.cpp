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
#include <print>

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

    const auto strs = tgl::String::of(splitter).split(',');

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

TEST(TglStringTests, cliSplit)
{
    const char* splitter = R"(a "b\" c" d)";

    const auto strs = tgl::String::of(splitter).cliSplit();

    ASSERT_EQ(strs.size(), 3);
    ASSERT_EQ(strs[0], "a");
    ASSERT_EQ(strs[1], "\"b\" c\"");
    ASSERT_EQ(strs[2], "d");
}


TEST(TglStringTests, formatPassThrough)
{
    const tgl::String str = tgl::String::format("{},{},{}", 'a', 'b', 'c');

    ASSERT_EQ(str, "a,b,c");
}

TEST(TglStringTests, upperCase)
{
    const tgl::String str = "abc";

    ASSERT_EQ(str, "abc");

    const tgl::String up = str.toUpperCase();
    ASSERT_EQ(up, "ABC");
}

TEST(TglStringTests, lowerCase)
{
    const tgl::String str = "ABC";
    ASSERT_EQ(str, "ABC");

    const tgl::String low = str.toLowerCase();

    ASSERT_EQ(low, "abc");
}

TEST(TglStringTests, startsWith)
{
    const tgl::String starter = "(test chars)";

    const tgl::String str = "(test chars)test";

    ASSERT_TRUE(str.startsWith(starter));
}

TEST(TglStringTests, endsWith)
{
    const tgl::String ender = "(test chars)";

    const tgl::String str = "test(test chars)";

    ASSERT_TRUE(str.endsWith(ender));
}

TEST(TglStringTests, toNumber)
{
    const tgl::String str = "6969 test";

    const auto no  = str.toNumber<int>();

    ASSERT_TRUE(no.has_value());
    ASSERT_EQ(no.value(), 6969);
}

TEST(TglStringTests, toNumberFailState)
{
    const tgl::String str = "test";

    const auto no = str.toNumber<int>();

    ASSERT_FALSE(no.has_value());
}
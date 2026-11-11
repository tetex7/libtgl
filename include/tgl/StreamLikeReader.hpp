/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 9/21/26.
//

#pragma once

#ifndef LIBTGL_STREAMLIKEREADER_HPP
#define LIBTGL_STREAMLIKEREADER_HPP
#include <tgl/Object.hpp>

namespace tgl
{
    template<RealType T, RealType C = std::vector<T>> requires std::ranges::range<C>
    class StreamLikeReader : public Object
    {
    public:
        using value_type = T;
        using container_type = C;
        using const_iterator = std::const_iterator<C>;
    private:
        vector_type data;
        const_iterator ctx;
    public:


        ~StreamLikeReader() override = default;
    };
}

tgl::StreamLikeReader<int, >

#endif //LIBTGL_STREAMLIKEREADER_HPP

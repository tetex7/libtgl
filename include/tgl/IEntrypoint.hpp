/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/11/2026.
//

#ifndef LIBTGL_IENTRYPOINT_HPP
#define LIBTGL_IENTRYPOINT_HPP

namespace tgl
{
    class IEntrypoint
    {
    public:
        virtual void ctor() = 0;
        virtual int main(int argc, char* argv[]) = 0;
        virtual void dtor() = 0;

        virtual ~IEntrypoint() = default;
    };
}


#endif //LIBTGL_IENTRYPOINT_HPP

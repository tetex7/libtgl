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

#ifndef LIBTGL_IOUTOFMODELOBJECT_HPP
#define LIBTGL_IOUTOFMODELOBJECT_HPP

namespace tgl::oom
{
    class IOutOfModelObject
    {
    protected:
        IOutOfModelObject();
    public:
        virtual ~IOutOfModelObject();
    };
}

#endif //LIBTGL_IOUTOFMODELOBJECT_HPP

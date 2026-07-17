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

#include "tgl_runtime.hpp"

#include <tgl/IEntrypoint.hpp>

namespace tgl::runtime
{
    IEntrypoint* _tgl_entrypoint = nullptr; // NOLINT(*-reserved-identifier)
}

__attribute__((constructor))
void __tgl_constructor() // NOLINT(*-reserved-identifier)
{
    using tgl::runtime::_tgl_entrypoint;
    if (_tgl_entrypoint)
        _tgl_entrypoint->ctor();
}

__attribute__((destructor))
void __tgl_destructor() // NOLINT(*-reserved-identifier)
{
    using tgl::runtime::_tgl_entrypoint;
    if (_tgl_entrypoint)
        _tgl_entrypoint->dtor();
}


int main(int argc, char* argv[])
{
    using tgl::runtime::_tgl_entrypoint;

    if (_tgl_entrypoint)
    {
        return _tgl_entrypoint->main(argc, argv);
    }
    return 1;
}

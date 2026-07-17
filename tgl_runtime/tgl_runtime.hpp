//
// Created by tete on 07/11/2026.
//

#ifndef LIBTGL_TGL_RUNTIME_HPP
#define LIBTGL_TGL_RUNTIME_HPP
#include <type_traits>

#include "tgl/IEntrypoint.hpp"

namespace tgl::runtime
{
    extern IEntrypoint* _tgl_entrypoint; // NOLINT(*-reserved-identifier)

    template<typename T> requires std::is_base_of_v<IEntrypoint, T>
    inline int __tgl_set_main() // NOLINT(*-reserved-identifier)
    {
        static T g = T();
        _tgl_entrypoint = &g;
        return 0;
    }
}

#define TGL_ENTRYPOINT(entrypoint) volatile int __tgl_entrypoint_##entrypoint__ = tgl::runtime::__tgl_set_main<entrypoint>();
#endif //LIBTGL_TGL_RUNTIME_HPP

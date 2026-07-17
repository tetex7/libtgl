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

#ifndef LIBTGL_EXPORT_DEFS_HPP
#define LIBTGL_EXPORT_DEFS_HPP

#if defined(_WIN32) || defined(__CYGWIN__)
#   ifdef TGL_EXPORTS
#       define TGL_API __declspec(dllexport)
#       define TGL_INTERNAL
#   else
#       define TGL_API __declspec(dllimport)
#       define TGL_INTERNAL
#   endif
#elif __GNUC__ >= 4 || defined(__clang__)
#   define TGL_API __attribute__((visibility("default")))
#   define TGL_INTERNAL __attribute__((visibility("hidden")))
#else
#   define TGL_API
#   define TGL_INTERNAL
#endif

#endif //LIBTGL_EXPORT_DEFS_HPP

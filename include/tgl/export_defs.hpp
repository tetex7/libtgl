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

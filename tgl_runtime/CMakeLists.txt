#
# Copyright (c) 2026. Tetex7
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#

add_library(tgl_runtime STATIC
        tgl_runtime.cpp
        tgl_runtime.hpp
)

target_link_libraries(tgl_runtime PUBLIC libtgl)
target_include_directories(libtgl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tgl_runtime)
enable_warnings(tgl_runtime)
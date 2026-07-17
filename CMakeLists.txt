#
# Copyright (c) 2026. Tetex7
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#

cmake_minimum_required(VERSION 4.2)
project(libtgl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)

if (NOT MSVC)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif ()

function(enable_warnings target)
    if(MSVC)
        #target_compile_options(${target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target} PRIVATE
                -Wall
                -Wextra
                -Wpedantic
                -Werror
        )
    endif()
endfunction()

add_library(libtgl SHARED
        include/tgl/Object.hpp
        include/tgl/dynacast.hpp
        include/tgl/Exception.hpp
        src/Exception.cpp
        src/Object.cpp
        include/tgl/String.hpp
        include/tgl/BadCastException.hpp
        src/BadCastException.cpp
        include/tgl/SynchronizedObject.hpp
        src/SynchronizedObject.cpp
        src/String.cpp
        include/tgl/IIterable.hpp
        include/tgl/Interface_notation.hpp
        include/tgl/export_defs.hpp
        include/tgl/utilities.hpp
        src/utilities.cpp
        include/tgl/unsafe/DynamicFixedWidthBuffer.hpp
        include/tgl/IEntrypoint.hpp
        include/tgl/oom/ObjectIdentifier.hpp
        src/oom/ObjectIdentifier.cpp
        include/tgl/oom/IOutOfModelObject.hpp
        include/tgl/IStream.hpp
        include/tgl/ini/IniFile.hpp
        include/tgl/ini/IniObjectType.hpp
        src/ini/IniFile.cpp
        include/tgl/typeUtilities.hpp
)

if (NOT WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

target_compile_definitions(libtgl PRIVATE TGL_EXPORTS)
target_include_directories(libtgl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(libtgl PUBLIC cxx_std_20)

enable_warnings(libtgl)

add_subdirectory(tgl_runtime)

add_executable(tester tester.cpp)
enable_warnings(tester)
target_link_libraries(tester PUBLIC libtgl)

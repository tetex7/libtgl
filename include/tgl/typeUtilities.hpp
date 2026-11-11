/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/15/2026.
//

#pragma once
#ifndef LIBTGL_TYPEUTILITIES_HPP
#define LIBTGL_TYPEUTILITIES_HPP

#include <type_traits>
#include <concepts>
#include <optional>

namespace tgl
{
    using hash_t = std::size_t;

    struct IInterface { virtual ~IInterface() = default; };
    struct IAbstract { virtual ~IAbstract() = default; };
    struct IRecord;

    template <typename T> requires std::same_as<T, std::remove_reference_t<T>>
    using OptionalReference = std::optional<std::reference_wrapper<T>>;

    template <typename T>
    struct real_type
    {
        using type = std::remove_cvref_t<T>;
    };

    template <typename T>
    using real_type_t = typename real_type<T>::type;

    template <typename T>
    struct is_real_type : std::bool_constant<std::same_as<T, real_type_t<T>>>{};

    template <typename T>
    constexpr inline bool is_real_type_v = is_real_type<T>::value;

    template <typename T>
    concept RealType = is_real_type_v<T>;

    template <typename T>
    concept Pointer = std::is_pointer_v<T>;

    class Object;

    template <typename T>
    concept TglObject = std::is_base_of_v<Object, real_type_t<T>>;

    template<typename T>
    concept TglInterface = std::is_base_of_v<IInterface, real_type_t<T>> && !std::is_base_of_v<Object, real_type_t<T>>
    && std::is_abstract_v<T>;

    template <typename T>
    concept TglAbstract = std::is_base_of_v<IAbstract, real_type_t<T>> && !std::is_base_of_v<Object, real_type_t<T>>
    && std::is_abstract_v<T>;

    template <typename A, typename B>
    constexpr bool instanceOf(const B&)
    {
        return std::derived_from<A, real_type_t<B>> || std::same_as<A, real_type_t<B>>;
    }

    template <typename A, typename B>
    consteval bool instanceOf()
    {
        return std::derived_from<A, real_type_t<A>> || std::same_as<A, real_type_t<B>>;
    }


    template <bool condition, std::integral auto a, std::integral auto b>
    using value_if = std::conditional_t<
        condition,
        std::integral_constant<decltype(a), a>,
        std::integral_constant<decltype(b), b>
    >;

    template <bool condition, auto a, auto b>
    inline constexpr auto value_if_v = value_if<condition, a, b>::value;

    template <typename L, typename R, typename... Args>
    concept Callable = std::invocable<L, Args...> && std::same_as<R, std::invoke_result_t<L, Args...>>;

    template <typename L, typename C>
    struct function_signature : std::bool_constant<false> {};

    template <typename L, typename R, typename... Args>
    struct function_signature<L, R(Args...)> : std::bool_constant<Callable<L, R, Args...>> {};

    template <typename L, typename F>
    inline constexpr bool function_signature_v = function_signature<L, F>::value;

    template <typename L, typename F>
    concept FunctionSignature = function_signature_v<L, F>;

}
static_assert(tgl::value_if_v<true, 42, 7> == 42);
static_assert(tgl::value_if_v<false, 42, 7> == 7);
static_assert(!tgl::RealType<const int>);
static_assert(tgl::FunctionSignature<decltype([](int){}), void(int)>);
static_assert(!tgl::RealType<volatile int>);
static_assert(!tgl::RealType<int&>);
static_assert(!tgl::RealType<const int&>);

static_assert(tgl::RealType<int>);

#endif //LIBTGL_TYPEUTILITIES_HPP

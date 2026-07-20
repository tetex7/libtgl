/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/18/2026.
//

#ifndef LIBTGL_DYNAMICOBJECT_HPP
#define LIBTGL_DYNAMICOBJECT_HPP
#include <tgl/typeUtilities.hpp>
#include <tgl/Object.hpp>


namespace tgl::unsafe
{
    template <typename T> requires RealType<T> && TglObject<T>
    class DynamicObject final
    {
    public:
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;
        using move_reference = value_type&&;
    private:
        std::unique_ptr<value_type> dyn_object;
    public:
        DynamicObject() requires std::is_default_constructible_v<T>
        : dyn_object(std::make_unique<value_type>()) {}

        DynamicObject(DynamicObject&&) noexcept = default;

        // ReSharper disable once CppNonExplicitConvertingConstructor
        template <typename... Args> requires std::constructible_from<value_type, Args...>
        DynamicObject(Args&&... args)
        : dyn_object(std::make_unique<value_type>(std::forward<Args>(args)...)) {}

        [[nodiscard]] std::span<const std::uint8_t> getByteView() const
        {
            return std::span<const std::uint8_t>(std::bit_cast<const std::uint8_t*>(this->dyn_object.get()), sizeof(value_type));
        }

        const_pointer operator->() const
        {
            return dyn_object.get();
        }

        pointer operator->()
        {
            return dyn_object.get();
        }

        const_reference operator*() const
        {
            return *dyn_object;
        }

        reference operator*()
        {
            return *dyn_object;
        }

        explicit operator reference() const
        {
            return *dyn_object;
        }

        DynamicObject(const DynamicObject&) = delete;
        DynamicObject& operator=(const DynamicObject&) = delete;
        ~DynamicObject() = default;
    };
}

#endif //LIBTGL_DYNAMICOBJECT_HPP

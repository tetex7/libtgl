//
// Created by tete on 07/10/2026.
//

#ifndef LIBTGL_DYNAMICFIXEDWIDTHBUFFER_HPP
#define LIBTGL_DYNAMICFIXEDWIDTHBUFFER_HPP

#include <type_traits>
#include <concepts>
#include <memory>
#include <cstring>
#include <print>
#include <tgl/typeUtilities.hpp>

namespace tgl::unsafe
{
    template<typename T>
    concept FundamentalIntegerType =  std::integral<T> || tgl::Pointer<T>;

    template <RealType T>
    requires std::is_trivially_copyable_v<T>
    class DynamicFixedWidthBuffer final
    {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using pointer = std::add_pointer_t<value_type>;
        using const_pointer = std::add_pointer_t<std::add_const_t<value_type>>;
        using reference = std::add_lvalue_reference_t<value_type>;
        using const_reference = std::add_lvalue_reference_t<std::add_const_t<value_type>>;
        using smart_pointer = std::unique_ptr<value_type[]>;
    private:
        size_type size;
        smart_pointer data;
    public:
        explicit DynamicFixedWidthBuffer(size_type size)
        : size(size), data(new value_type[size])
        {
            if constexpr (FundamentalIntegerType<value_type>)
            {
                std::memset(this->get(), 0, this->size * sizeof(value_type));
            }
        }

        template <std::size_t _size>
        explicit DynamicFixedWidthBuffer(const std::array<value_type, _size>& data)
        : size(_size), data(new value_type[_size])
        {
            std::memcpy(this->get(), data.data(), _size * sizeof(value_type));
        }

        DynamicFixedWidthBuffer(const std::initializer_list<value_type>& list)
        : size(list.size()), data(new value_type[list.size()])
        {
            std::memcpy(this->get(), list.data(), this->size * sizeof(value_type));
        }

        DynamicFixedWidthBuffer(const_pointer data, size_type size)
        requires FundamentalIntegerType<value_type>
        : size(size), data(new value_type[size])
        {
            std::memcpy(this->get(), data, this->size * sizeof(value_type));
        }

        DynamicFixedWidthBuffer(const_pointer start, const_pointer end)
        : size(end - start), data(new value_type[end - start])
        {
            std::memcpy(this->get(), start, this->size * sizeof(value_type));
        }

        explicit DynamicFixedWidthBuffer()
        requires std::same_as<value_type, char>
        : size(1), data(new value_type[size] {'\0'}) {}

        explicit DynamicFixedWidthBuffer()
        : size(0), data(nullptr) {}

        // ReSharper disable once CppNonExplicitConvertingConstructor
        explicit DynamicFixedWidthBuffer(nullptr_t)
        : size(0), data(nullptr) {}

        DynamicFixedWidthBuffer(nullptr_t, size_type) = delete;

        explicit DynamicFixedWidthBuffer(size_type size, value_type initializer)
        requires FundamentalIntegerType<value_type>
        : size(size), data(new value_type[size])
        {
            for (size_type i = 0; i < size; i++)
                this->data[i] = initializer;
        }

        DynamicFixedWidthBuffer(DynamicFixedWidthBuffer&& buffer) noexcept
        : size(buffer.size), data(std::move(buffer.data)){}

        DynamicFixedWidthBuffer& operator=(DynamicFixedWidthBuffer&& buffer) noexcept
        {
            this->size = buffer.size;
            this->data = std::move(buffer.data);
            return *this;
        }

        [[nodiscard]] bool isValid() const noexcept
        {
            return this->data != nullptr;
        }

        pointer get() const noexcept
        {
            return this->data.get();
        }

        void set(pointer new_data, size_type size) noexcept
        {
            this->data.reset(new_data);
            this->size = size;
        }

        [[nodiscard]] size_type getSize() const
        {
            return this->size;
        }

        reference operator[](size_type index)
        {
            if (index >= this->size)
                throw std::out_of_range("index out of range");
            return this->data[index];
        }

        const_reference operator[](size_type index) const
        {
            if (index >= this->size)
                throw std::out_of_range("index out of range");
            return this->data[index];
        }

        DynamicFixedWidthBuffer copy() const noexcept
        {
            return DynamicFixedWidthBuffer(this->get(), this->size);
        }

        DynamicFixedWidthBuffer(const DynamicFixedWidthBuffer&) = delete;
        DynamicFixedWidthBuffer& operator=(const DynamicFixedWidthBuffer&) = delete;

        explicit operator const char*()
        requires std::same_as<value_type, char>
        {
            return this->data;
        }

        explicit operator bool() const noexcept
        {
            return this->isValid();
        }

        pointer begin()
        {
            return this->get();
        }

        [[nodiscard]] const_pointer begin() const
        {
            return this->get();
        }

        pointer end()
        {
            return this->get() + this->size;
        }

        [[nodiscard]] const_pointer end() const
        {
            return this->get() + this->size;
        }

        ~DynamicFixedWidthBuffer() = default;
    };
}

#endif //LIBTGL_DYNAMICFIXEDWIDTHBUFFER_HPP

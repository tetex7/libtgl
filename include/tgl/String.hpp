//
// Created by tete on 07/02/2026.
//

#pragma once

#ifndef LIBTGL_STRING_HPP
#define LIBTGL_STRING_HPP

#include <tgl/Object.hpp>
#include <tgl/IIterable.hpp>
#include <string>
#include <string_view>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <tgl/unsafe/DynamicFixedWidthBuffer.hpp>
#include <tgl/export_defs.hpp>

namespace tgl
{
    class TGL_API String final : public IIterable<char>
    {
    private:
        std::size_t length;
        unsafe::DynamicFixedWidthBuffer<char> data;

        //A convenience constructor to make things cheaper
        String(unsafe::DynamicFixedWidthBuffer<char>&& buff, std::size_t length) noexcept;

        static bool cmpHelper(const String& a, const String& b);
    public:
        static constexpr std::size_t npos = static_cast<std::size_t>(-1);

        String();

        // ReSharper disable once CppNonExplicitConvertingConstructor
        String(const char* c_str);

        String(const char* c_str, std::size_t size);

        explicit String(const std::string& std_str);
        String(const String& str);

        explicit String(const std::string_view& str_view);

        template <std::size_t _size>
        String(const std::array<char, _size>& array)
        : length(_size), data(array) {}

        String(String&& str) noexcept;

        // ReSharper disable once CppNonExplicitConvertingConstructor
        String(std::nullptr_t) = delete;

        String& operator=(const String& b);
        String& operator=(String&& b) noexcept;

        [[nodiscard]] unsafe::DynamicFixedWidthBuffer<char>& getBackingBuffer();

        [[nodiscard]] const unsafe::DynamicFixedWidthBuffer<char>& getBackingBuffer() const;

        char* begin() override;
        [[nodiscard]] const char* begin() const override;

        char* end() override;
        [[nodiscard]] const char* end() const override;

        char& getCharacterReference(std::size_t index);
        [[nodiscard]] const char& getCharacterReference(std::size_t index) const;

        const char& operator[](std::size_t index) const;
        char& operator[](std::size_t index);

        String operator+=(const String& str) const;
        String operator+(const String& str) const;

        [[nodiscard]] String append(const String& b) const;

        [[nodiscard]] std::string_view getView() const;
        [[nodiscard]] std::span<const char> getCharView() const;

        [[nodiscard]] String toLowerCase() const;
        [[nodiscard]] String toUpperCase() const;

        [[nodiscard]] bool startsWith(const String& b) const;
        [[nodiscard]] bool endsWith(const String& b) const;

        [[nodiscard]] const char* getCString() const;

        [[nodiscard]] String toString() const override;

        [[nodiscard]] std::string asStdString() const;

        [[nodiscard]] std::size_t getLength() const override;

        [[nodiscard]] String trim() const;

        std::vector<String> split(char delimiter) const;

        [[nodiscard]] std::size_t getNumberOfCharacter(char c, std::size_t offset = npos) const;

        [[nodiscard]] std::size_t getHash() const override;

        [[nodiscard]] bool equals(const Object& b) const override;

        bool operator==(const char* b) const;
        bool operator!=(const char* b) const;

        [[nodiscard]] bool equalsIgnoreCase(const String& b) const;

        template<std::integral T>
        std::optional<T> toNumber(int base = 10) const
        {
            try
            {
                T temp{};
                char* last = nullptr;
                if constexpr (std::is_unsigned_v<T>)
                {
                    temp = static_cast<T>(std::strtoull(this->getCString(), &last, base));
                }
                else
                {
                    temp = static_cast<T>(std::strtoll(this->getCString(), &last, base));
                }

                if (last == this->getCString())
                {
                    return std::nullopt;
                }
                return temp;
            }
            catch (std::exception& e)
            {
                return std::nullopt;
            }
        }

        ~String() override = default;

        // Utility statics

        template <typename... Args>
        static inline String format(const std::format_string<Args...> string, Args&&... args)
        {
            return String(std::vformat(string.get(), std::make_format_args(args...)));
        }

        template <typename T> requires std::constructible_from<String, T>
        static String of(T&& value)
        {
            return String(std::forward<T>(value));
        }

        // ReSharper disable once CppNonExplicitConversionOperator
        operator std::filesystem::path() const;
    };

    namespace literals
    {
        String operator""_S(const char* c_str, std::size_t size);
    }
}

#endif //LIBTGL_STRING_HPP

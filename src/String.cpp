/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/03/2026.
//
#include "tgl/String.hpp"
#include <cstring>

#include "tgl/dynacast.hpp"
#include "tgl/utilities.hpp"


namespace tgl
{
    String::String(unsafe::DynamicFixedWidthBuffer<char>&& buff, std::size_t length) noexcept
        : length(length), data(std::move(buff)) {}

    bool String::cmpHelper(const String& a, const String& b)
    {
        if (a.getLength() != b.getLength())
        {
            return false;
        }

        const std::size_t len = a.getLength() < b.getLength() ? a.getLength() : b.getLength();

        return std::strncmp(a.getCString(), b.getCString(), len) == 0;
    }

    String::String() : length(0) {}

    String::String(const char* c_str)
    : length(std::strlen(c_str)), data(c_str, length + 1){}

    String::String(const char* c_str, std::size_t size)
    : length(size), data(c_str, size + 1){}

    String::String(const std::string& std_str)
    : length(std_str.length()), data(std_str.c_str(), length + 1){}

    String::String(const String& str)
    : length(str.length), data(str.getBackingBuffer().copy()){}

    String::String(const std::string_view& str_view)
    : length(str_view.length()), data(str_view.data(), length + 1){}

    String::String(String&& str) noexcept
    : length(str.length), data(std::move(str.data)){}

    String& String::operator=(const String& b)
    {
        if (this != &b) return *this;

        char* const buffer = new char[b.getLength() + 1];

        std::memset(buffer, 0, b.getLength() + 1);
        std::memcpy(buffer, b.getCString(), b.getLength());

        this->data.set(buffer, length+1);
        this->length = b.getLength();

        return *this;
    }

    String& String::operator=(String&& b) noexcept
    {
        this->data = std::move(b.data);
        this->length = b.getLength();
        return *this;
    }

    unsafe::DynamicFixedWidthBuffer<char>& String::getBackingBuffer()
    {
        return this->data;
    }

    const unsafe::DynamicFixedWidthBuffer<char>& String::getBackingBuffer() const
    {
        return data;
    }

    char* String::begin()
    {
        return &data[0];
    }

    const char* String::begin() const
    {
        return &data[0];
    }

    char* String::end()
    {
        return &data[length];
    }

    const char* String::end() const
    {
        return &data[length];
    }

    char& String::getCharacterReference(std::size_t index)
    {
        if (index >= length)
            throw std::out_of_range("");

        return data[index];
    }

    const char& String::getCharacterReference(std::size_t index) const
    {
        if (index >= length)
            throw std::out_of_range("");

        return data[index];
    }

    const char& String::operator[](std::size_t index) const
    {
        return getCharacterReference(index);
    }

    char& String::operator[](std::size_t index)
    {
        return getCharacterReference(index);
    }

    String String::operator+=(const String& str) const
    {
        return this->append(str);
    }

    String String::operator+(const String& str) const
    {
        return this->append(str);
    }

    String String::append(const String& b) const
    {
        const std::size_t a_length = this->getLength();
        const std::size_t b_length = b.getLength();
        const std::size_t new_length = a_length + b_length;

        unsafe::DynamicFixedWidthBuffer<char> buffer = unsafe::DynamicFixedWidthBuffer<char>(new_length + 1, 0);

        std::memcpy(buffer.get(), this->getCString(), a_length);
        std::memcpy(buffer.get() + a_length, b.getCString(), b_length);

        return String(std::move(buffer), new_length);
    }

    std::string_view String::getView() const
    {
        return std::string_view(this->getCString(), this->getLength());
    }

    std::span<const char> String::getCharView() const
    {
        return std::span(this->getCString(), this->getLength());
    }

    String String::toLowerCase() const
    {
        String str(*this);

        for (char& c : str)
        {
            c = std::tolower(c);
        }

        return str;
    }

    String String::toUpperCase() const
    {
        String str(*this);

        for (char& c : str)
        {
            c = std::toupper(c);
        }

        return str;
    }

    bool String::startsWith(const String& b) const
    {
        return this->getView().starts_with(b.getView());
    }

    bool String::endsWith(const String& b) const
    {
        return this->getView().ends_with(b.getView());
    }

    //String String::trim() const
    //{
    //    std::unique_ptr<char[]> buffer(new char[length + 1]);

    //    std::memset(buffer.get(), 0, length + 1);
    //    std::memcpy(buffer.get(), data.get(), length);
    //    return String(std::move(buffer), length);
    //}

    const char* String::getCString() const
    {
        return data.get();
    }

    String String::toString() const
    {
        return String(*this);
    }

    std::string String::asStdString() const
    {
        return std::string(this->getCString(), length);
    }

    std::size_t String::getLength() const
    {
        return length;
    }

    String String::trim() const
    {
        if (length == 0)
        {
            return {};
        }

        std::size_t start = 0;
        while (start < length &&
               std::isspace(static_cast<unsigned char>(data[start])))
        {
            ++start;
        }

        if (start == length)
        {
            return {};
        }

        std::size_t end = length;
        while (end > start &&
               std::isspace(static_cast<unsigned char>(data[end - 1])))
        {
            --end;
        }

        return String(data.get() + start, end - start);
    }

    std::vector<String> String::split(char delimiter) const
    {
        std::vector<String> result;
        std::vector<char> temp;

        const auto close_out = [&]() -> void {
            temp.push_back(0);
            result.push_back(String(temp.data()));
        };

        const std::size_t num_do_split = this->getNumberOfCharacter(delimiter);

        std::size_t num_split = 0;
        for (const char& c : *this)
        {
            if (c == delimiter)
            {
                close_out();
                temp.clear();
                num_split++;
            }
            else
            {
                temp.push_back(c);
            }

        }

        if (num_split == 0 || num_split != num_do_split)
        {
            close_out();
        }

        return result;
    }

    std::size_t String::getNumberOfCharacter(char c, std::size_t offset) const
    {
        const std::size_t real_offset = offset == npos ? 0 : offset;

        std::size_t num = 0;

        for (std::size_t i = real_offset; i < real_offset; i++)
        {
            if (c == this->getCharacterReference(i))
            {
                num++;
            }
        }

        return num;
    }

    std::size_t String::getHash() const
    {
        return std::hash<std::string_view>{}(this->getView());
    }

    bool String::equals(const Object& b) const
    {
        if (this == &b)
            return true;

        if (const auto temp = exp_dynacast<String>(b); temp.has_value())
        {
            auto& str = temp.value();
            return cmpHelper(*this, str);
        }
        return Object::equals(b);
    }

    bool String::operator==(const char* b) const
    {
        return cmpHelper(*this, b);
    }

    bool String::operator!=(const char* b) const
    {
        return !cmpHelper(*this, b);
    }

    bool String::equalsIgnoreCase(const String& b) const
    {
        if (this->getLength() != b.getLength())
        {
            return false;
        }

        String t_a = this->toLowerCase();
        String t_b = b.toLowerCase();

        return t_a.equals(t_b);
    }

    String::operator std::filesystem::path() const
    {
        return std::filesystem::path(this->getCString());
    }

    namespace literals
    {
        String operator ""_S(const char* c_str, std::size_t size)
        {
            return String(c_str, size);
        }
    }
}

//
// Created by tete on 06/30/2026.
//

#include <tgl/Exception.hpp>

#include "tgl/String.hpp"

namespace tgl
{
    const char* Exception::what() const noexcept
    {
        return message.c_str();
    }

    String Exception::toString() const
    {
        return String(this->getMessage());
    }

    const std::string& Exception::getMessage() const
    {
        return message;
    }
}

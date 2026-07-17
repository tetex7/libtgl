//
// Created by tete on 06/30/2026.
//

#include "tgl/Object.hpp"
#include "tgl/String.hpp"

namespace tgl
{
    Object::Object(const Object&){}

    const oom::ObjectIdentifier& Object::getObjectID() const
    {
        return this->identifier;
    }

    const std::type_info& Object::getTypeInfo() const
    {
        return typeid(*this);
    }

    std::string Object::toStdString() const
    {
        return this->toString().asStdString();
    }

    String Object::toString() const
    {
        return String(std::format("{}@{:p}", identifier, std::bit_cast<void*>(this)));
    }

    std::size_t Object::getHash() const
    {
        return std::hash<const void*>{}(this);
    }

    bool Object::equals(const Object& b) const
    {
        return this == std::addressof(b);
    }

    bool Object::operator==(const Object& b) const
    {
        return this->equals(b);
    }

    bool Object::operator!=(const Object& b) const
    {
        return !this->equals(b);
    }

    Object& Object::operator=(Object&& other) noexcept
    {
        this->identifier = std::move(other.identifier);
        return *this;
    }
}

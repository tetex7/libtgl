//
// Created by tete on 06/30/2026.
//
#pragma once

#ifndef LIBTGL_OBJECT_HPP
#define LIBTGL_OBJECT_HPP
#include <string>
#include <typeinfo>
#include <utility>
#include <functional>
#include <format>
#include <tgl/export_defs.hpp>
#include <tgl/oom/ObjectIdentifier.hpp>

namespace tgl
{
    class Object;
    class String;

    template <typename T>
    concept TglObject = std::is_base_of_v<Object, std::remove_cvref_t<T>>;
    
    class TGL_API Object
    {
    private:
        oom::ObjectIdentifier identifier;
    public:
        template <typename T>
        constexpr static inline bool is_object = TglObject<T>;

        Object() = default;
        Object(const Object&);

        [[nodiscard]] const oom::ObjectIdentifier& getObjectID() const;

        [[nodiscard]] const std::type_info& getTypeInfo() const;

        [[nodiscard]] std::string toStdString() const;

        [[nodiscard]] virtual String toString() const;

        [[nodiscard]] virtual std::size_t getHash() const;

        [[nodiscard]] virtual bool equals(const Object& b) const;

        bool operator==(const Object& b) const;
        bool operator!=(const Object& b) const;

        Object& operator=(Object&& other) noexcept;

        virtual ~Object() = default;
    };
}

template <tgl::TglObject T>
struct std::hash<T> { // NOLINT(*-dcl58-cpp)
    std::size_t operator()(const T& obj) const noexcept {
        return static_cast<const tgl::Object&>(obj).getHash();
    }
};

template <tgl::TglObject T>
struct std::formatter<T> : formatter<std::string> { // NOLINT(*-dcl58-cpp)
    auto format(const T& obj, std::format_context& ctx) const {
        return std::formatter<std::string>::format(
            static_cast<const tgl::Object&>(obj).toStdString(),
            ctx
        );
    }
};


#endif //LIBTGL_OBJECT_HPP

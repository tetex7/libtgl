//
// Created by tete on 07/02/2026.
//

#ifndef LIBTGL_BADCASTEXCEPTION_HPP
#define LIBTGL_BADCASTEXCEPTION_HPP

#include <type_traits>

#include <tgl/Exception.hpp>

namespace tgl
{
    class TGL_API BadCastException : public Exception
    {
    private:
        const std::type_info& from;
        const std::type_info& to;
    public:
        BadCastException(const std::type_info& from, const std::type_info& to);

        [[nodiscard]] const std::type_info& getFromType() const;
        [[nodiscard]] const std::type_info& getToType() const;
    };
}

#endif //LIBTGL_BADCASTEXCEPTION_HPP

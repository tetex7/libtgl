//
// Created by tete on 07/04/2026.
//

#ifndef LIBTGL_IITERABLE_HPP
#define LIBTGL_IITERABLE_HPP


#include <tgl/Object.hpp>

#include <tgl/export_defs.hpp>

namespace  tgl
{
    template<typename T>
    class TGL_API IIterable : public Object
    {
    protected:
        IIterable() = default;
    public:
        virtual T* begin() = 0;
        virtual const T* begin() const = 0;

        virtual T* end() = 0;
        virtual const T* end() const = 0;

        [[nodiscard]] virtual std::size_t getLength() const = 0;

        ~IIterable() override = default;
    };
}

#endif //LIBTGL_IITERABLE_HPP

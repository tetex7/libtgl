//
// Created by tete on 07/11/2026.
//

#ifndef LIBTGL_IENTRYPOINT_HPP
#define LIBTGL_IENTRYPOINT_HPP

namespace tgl
{
    class IEntrypoint
    {
    public:
        virtual void ctor() = 0;
        virtual int main(int argc, char* argv[]) = 0;
        virtual void dtor() = 0;

        virtual ~IEntrypoint() = default;
    };
}


#endif //LIBTGL_IENTRYPOINT_HPP

//
// Created by tete on 07/02/2026.
//

#include <tgl/SynchronizedObject.hpp>

namespace tgl
{

    void SynchronizedObject::lock() const
    {
        _mutex.lock();
    }

    void SynchronizedObject::unlock() const noexcept
    {
        _mutex.unlock();
    }
}

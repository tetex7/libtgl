//
// Created by tete on 07/02/2026.
//

#ifndef LIBTGL_SYNCHRONIZEDOBJECT_HPP
#define LIBTGL_SYNCHRONIZEDOBJECT_HPP
#include <mutex>
#include <tgl/Object.hpp>


namespace tgl
{
    class SynchronizedObject;

    template <typename T>
    concept TglSynchronizedObject = std::derived_from<T, SynchronizedObject>;

    template <typename T>
    concept BasicLockableObject = requires(T obj)
    {
        obj.lock();
        obj.unlock();
    };

    class SynchronizedObject : public Object
    {
    private:
        using mutex_type = std::recursive_mutex;
        mutable mutex_type _mutex;
    protected:
        SynchronizedObject() = default;
    public:
        template <typename T>
        constexpr static inline bool is_synchronized_object = TglSynchronizedObject<T>;

        void lock() const;
        void unlock() const noexcept;

        ~SynchronizedObject() override = default;
    };

    static_assert(BasicLockableObject<SynchronizedObject>, "Synchronized object is no longer basic lockable (Broken implementation)");

    template <TglSynchronizedObject C>
    inline TGL_API void synchronized(C& self, std::function<void(C& obj)> function)
    {
        //We meet The standard's  BasicLockable's requirements
        //so yes
        std::lock_guard<C> guard(self);
        function(self);
    }

}

#endif //LIBTGL_SYNCHRONIZEDOBJECT_HPP

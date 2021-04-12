#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Storage.h"

#include <stddef.h>



template<typename T, size_t reserveSize = 1>
struct MapAllocator
{
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    Storage<T, reserveSize> storage;

    MapAllocator() = default;
    ~MapAllocator() = default;

    template<typename U>
    struct rebind 
    {
        using other = MapAllocator<U, reserveSize>;
    };

    template<typename U>
    MapAllocator(const MapAllocator<U, reserveSize> &)
    {
    }

    pointer allocate(size_t n)
    {
        return storage.allocate(n);
    }

    void deallocate(pointer p, size_t n)
    {
        storage.deallocate(p, n);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) 
    {
        new(p) U(std::forward<Args>(args)...);
    }

    static void destroy(T *p) 
    {
        p->~T();
    }
};

template<class T, class U, size_t reserveSize>
constexpr bool operator==(const MapAllocator<T, reserveSize>&, const MapAllocator<U, reserveSize>&) noexcept 
{
	return true;
}

template <class T, class U, size_t reserveSize>
constexpr bool operator!=(const MapAllocator<T, reserveSize>&, const MapAllocator<U, reserveSize>&) noexcept 
{
	return false;
}


#endif //ALLOCATOR_H
#ifndef STORAGE_H
#define STORAGE_H

#include <cstdlib>
#include <new>

template<typename T, const size_t reserveSize>
class Storage
{
    T* storage {nullptr}; 
    size_t memory_avaliable {0};
    size_t index_last {0};

public:
    Storage() = default;
    ~Storage() = default;

    T* allocate(size_t n)
    {
        if (n > reserveSize)
        {
            throw std::bad_alloc();
        }

        if (n <= memory_avaliable)
        {
            T *p = &storage[++index_last];
            --memory_avaliable;
            return p;
        }

        n *= reserveSize;
        storage = (T*) std::malloc((n + 1) * sizeof(T)); // надо добавить 1 для первой ноды (как я понял)
        if (!storage)
        {
            throw std::bad_alloc();
        }
        memory_avaliable = reserveSize;
        return &storage[index_last];
    }

    void deallocate(T *, size_t)
    {
        if (storage != nullptr)
        {
            free(storage);
            storage = nullptr;
        }
    }
};

#endif //STORAGE_H
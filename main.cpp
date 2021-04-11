#include "MapAllocator.h"
#include "Container.h"

#include <iostream>
#include <map>
//.

int factorial(const int n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n; 
}

template<typename T>
void print_map(const T &_map)
{
    for (const auto &one : _map)
    {
        std::cout << one.first << " " << one.second << std::endl;
    }
}

template<typename T>
void print_container(T &_container)
{
    for (const auto &one : _container)
    {
        std::cout << one.data << std::endl;
    }
}

int main (int, char **)
{
    static const int N = 10;

    // 1    
    std::map<int, int> std_allocator_map;
    for (int i = 0; i < N; ++i)    
    {
        std_allocator_map.insert(std::make_pair(i, factorial(i)));
    }

    // 2  
    std::map<int, int, std::less<int>, MapAllocator<std::pair<int, int>, N > > new_allocator_map;
    for (int i = 0; i < N; ++i)    
    {
        new_allocator_map.insert(std::make_pair(i, factorial(i)));
    }

    print_map(std_allocator_map);
    print_map(new_allocator_map);

    // 3
    Container<int> container;
    for (int i = 0; i < N; ++i)
    {
        container.append(i);
    }

    // 4
    Container<int, MapAllocator<int, N>> mapAllocator_container;
    for (int i = 0; i < N; ++i)
    {
        mapAllocator_container.append(i);
    }
    
    print_container(container);
    print_container(mapAllocator_container);

    return 0;
}

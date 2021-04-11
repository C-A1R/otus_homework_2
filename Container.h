#ifndef CONTAINER_H
#define CONTAINER_H

#include <memory>

template<typename T, typename A = std::allocator<T>>
class Container
{
public:
    struct Node
    {
        T data;
        Node *next {nullptr};
        Node (const T &_data) : data (_data)
        {
        }
        ~Node() = default;
    };

    Container(A _allocator = A()) : allocator(_allocator)
    {
    }
    ~Container()
    {
        auto ptr = first;
        while (ptr != nullptr)
        {
            auto next = ptr->next;
            destroy(ptr);
            ptr = next;
        }
    }

    void append(const T &data)
    {
        Node *newNode = nodeAllocator.allocate(1);
        allocator.construct(newNode, Node(data));
        if (last)
        {
            last->next = newNode;
        }
        last = newNode;
        if (!first)
        {
            first = newNode;
        }
    }

    class Iterator
    {
    public:
        Iterator(Container::Node *_ptr) : ptr(_ptr)
        {
        }

        void operator ++ ()
        {
            if (ptr != nullptr)
            {
                ptr = ptr->next;
            }
        }

        Container::Node& operator * ()
        {
            return *ptr;
        }

        bool operator != (const Iterator &other)
        {
            return this->ptr != other.ptr;
        }

    private:
        Container::Node* ptr;
    };

    Iterator begin()
    {
        return Iterator(first);
    }
    Iterator end()
    {
        return Iterator(last->next);
    }

private:
    Node *first {nullptr};
    Node *last {nullptr};

    A allocator;

    using RebindAllocNode = typename std::allocator_traits<A>::template rebind_alloc<Node>;
    RebindAllocNode nodeAllocator;

    void destroy(Node *node)
    {
        allocator.destroy(&node->data);
        nodeAllocator.deallocate(node, 1);
    }
};


#endif  //CONTAINER_H
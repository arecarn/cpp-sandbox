#include <array.hpp>
#include <utility> // std::forward
#include <cstdint>
#include <cassert>
#include <RingBuffer.hpp>

#ifndef OBJECT_POOL
#define OBJECT_POOL

template <typename T, uint32_t Count>
class ObjectPool
{
    private:
        using ObjectMemory = Array<char, sizeof(T)>;
        alignas(T) Array<ObjectMemory, Count> m_objects;
        RingBuffer<ObjectMemory*, Count> m_ptrs;

    public:
        ObjectPool()
        {
            for(auto& p : m_objects)
            {
                m_ptrs.push_back(&p);
            }
        }

        class UniquePtr
        {
            private:
                friend ObjectPool<T, Count>;

                ObjectPool<T, Count>* m_pool {nullptr};
                T* m_value {nullptr};


                template <typename... Args>
                UniquePtr(ObjectMemory* object, ObjectPool* pool, Args&&... args)
                : m_pool {pool}
                , m_value {new(object) T {std::forward<Args>(args)...}}
                {
                }

            public:
                UniquePtr() = default;
                UniquePtr(const UniquePtr&) = delete;
                UniquePtr& operator=(const UniquePtr&) = delete;

                UniquePtr(UniquePtr&& other) noexcept
                : m_pool {other.m_pool}
                , m_value {other.m_value}
                {
                    other.m_value = nullptr;
                    other.m_pool = nullptr;
                }

                UniquePtr& operator=(UniquePtr&& other) noexcept
                {
                    if (this != &other)
                    {
                        m_value = other.m_value;
                        m_pool = other.m_pool;
                        other.m_value = nullptr;
                        other.m_pool = nullptr;
                    }
                    return *this;
                }

                ~UniquePtr()
                {
                    if (m_value != nullptr)
                    {
                        m_value->~T();
                        m_pool->release(reinterpret_cast<ObjectMemory*>(m_value));
                        m_value = nullptr; // unnecessary?
                    }
                }

                operator bool() const
                {
                    return m_value == nullptr;
                }

                T* get()
                {
                    return m_value;
                }

                T& operator*()
                {
                    return *m_value;
                }

                T* operator->()
                {
                    return m_value;
                }
        };

        template <typename... Args>
        UniquePtr make_unique(Args&&... args)
        {
            while (true)
            {
                // get mutex here
                if (!m_ptrs.empty())
                {
                    auto result = UniquePtr{m_ptrs[0], this, std::forward<Args>(args)...};
                    m_ptrs.pop_front();
                    // release mutex here
                    return result;
                }
                // release mutex here
                // wait for non-zero semaphore here
            }
        }

    private:
        void release(ObjectMemory* ptr)
        {
            // get mutex
            assert(!m_ptrs.full());
            m_ptrs.push_front(ptr);
            // release mutex
            // put semaphore to notify
        }
};

#endif // header

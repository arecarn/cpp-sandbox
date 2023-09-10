#include <array>
#include <bitset>
#include <cstdint>
#include <cassert>
#include <limits>

#ifndef OBJECT_POOL
#define OBJECT_POOL

template <typename T, uint32_t Count>
class ObjectPool
{
    private:
        using ObjectMemory = std::array<char, sizeof(T)>;
        alignas(T) std::array<ObjectMemory, Count> m_objects;
        std::bitset<Count> m_in_use;

    public:
        ObjectPool() = default;

        class UniquePtr
        {
            private:
                friend ObjectPool<T, Count>;

                constexpr static size_t Dummy_Index = std::numeric_limits<size_t>::max();
                ObjectMemory* m_object {nullptr};
                size_t m_index {Dummy_Index};
                ObjectPool<T, Count>* m_pool {nullptr};
                T* m_value {nullptr};


                template <typename... Args>
                UniquePtr(ObjectMemory* object, size_t i, ObjectPool* p, Args&&... args)
                : m_object {object}
                , m_index {i}
                , m_pool {p}
                , m_value {new(m_object) T {std::forward<Args>(args)...}}
                {
                }


            public:

                UniquePtr() = default;

                UniquePtr(const UniquePtr&) = delete;

                UniquePtr(UniquePtr&& other) noexcept
                    : m_object {other.m_object}
                , m_index {other.m_index}
                , m_pool {other.m_pool}
                , m_value {other.m_value}
                {
                    other.m_object = nullptr;
                    other.m_index = Dummy_Index; // don't release
                    other.m_value = nullptr; // don't release
                    other.m_pool = nullptr;
                }

                UniquePtr& operator=(const UniquePtr&) = delete;

                UniquePtr& operator=(UniquePtr&& other) noexcept
                {
                    if (this != &other)
                    {
                        m_object = other.m_object;
                        m_index = other.m_index;
                        m_pool = other.m_pool;
                        other.m_index = Dummy_Index; // don't release
                    }
                    return *this;
                }

                ~UniquePtr()
                {
                    if (m_index != Dummy_Index)
                    {
                        m_value->~T();
                        m_pool->release(m_index);
                        m_index = Dummy_Index; // avoid double release

                    }
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
                // get mutex here
                while (true)
                {
                    for (size_t i = 0; i < m_objects.size(); i++)
                    {
                        if (!m_in_use[i])
                        {
                            m_in_use[i] = true;
                            return UniquePtr {&m_objects[i], i, this, std::forward<Args>(args)...};
                        }
                    }
                    // wait for non-zero semaphore here
                }
            }

    private:
        void release(size_t index)
        {
            // get mutex here
            assert(index < m_objects.size());
            assert(m_in_use[index]);
            m_in_use[index] = false;
            // put semaphore here
        }
};

#endif // header

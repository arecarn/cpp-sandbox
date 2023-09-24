#include <mutex>

template <typename T>
class Mailbox
{
    T m_data[2];
    std::mutex m_available[2];
    std::mutex m_mutex[2];

    public:
    Mailbox()
    {
        for (auto &m : m_available)
        {
            m.lock();
        }
    }

    void push(const T& data)
    {
        if (m_mutex[0].try_lock())
        {
            m_data[0] = data;
            m_available[0].unlock();
            m_available[1].try_lock(); // invalidate anything in second slot
            m_mutex[0].unlock();
            return;
        }

        if (m_mutex[1].try_lock())
        {
            m_data[1] = data;
            m_available[1].unlock();
            m_mutex[1].unlock();
            return;
        }
    }

    bool try_pop(T& data)
    {
        if (m_mutex[1].try_lock())
        {
            if (m_available[1].try_lock())
            {
                data = m_data[1];
                m_mutex[1].unlock();
                return true;
            }
            m_mutex[1].unlock();
        }
        if (m_mutex[0].try_lock())
        {
            if (m_available[0].try_lock())
            {
                data = m_data[0];
                m_mutex[0].unlock();
                return true;
            }
            m_mutex[0].unlock();
        }

        return false;
    }
};

#ifndef TODO_HPP
#define TODO_HPP

#include "uuid_v4.h"
#include <chrono>
#include <string>
#include <string_view>
#include <utility>

UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
UUIDv4::UUID uuid = uuidGenerator.getUUID();

class Todo
{
public:
    Todo(std::string text, std::time_t creation_time)
        : m_text {std::move(text)}
        , m_creation_time {creation_time}
    {
    }

    enum class State
    {
        Checked,
        Unchecked,
    };

    State state()
    {
        return m_state;
    }

    std::string_view text()
    {
        return m_text;
    }

    void text(std::string new_text)
    {
        m_text = std::move(new_text);
    }

    time_t creation_time() const
    {
        return m_creation_time;
    }

    void toggle()
    {
        if (m_state == State::Checked)
        {
            m_state = State::Unchecked;
        }
        else
        {
            m_state = State::Checked;
        }
    }

private:
    std::string m_text;
    std::time_t m_creation_time;
    State m_state = State::Unchecked;
};

#endif // header guard

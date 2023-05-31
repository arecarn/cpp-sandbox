#ifndef TODO_HPP
#define TODO_HPP

#include <string>
#include <string_view>

class Todo
{
public:
    Todo(const std::string& text)
        : m_text {text}
    {
    }
    enum class State
    {
        Checked,
        Unchecked,
    };
    State state() { return m_state; }
    std::string_view text()
    {
        return m_text;
    }

private:
    std::string m_text;

    State m_state = State::Unchecked;
};

#endif // header guard

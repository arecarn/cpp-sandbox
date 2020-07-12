#include "state_machine.hpp"

void StateMachine::queue(Value event)
{
    m_events.push(event);
}

void StateMachine::step()
{
    if (!m_events.empty())
    {
        m_state->handle(m_events[0]);
        m_events.pop();
    }

    m_state->step();
}

void State::handle(const Value& event)
{
    switch (event.tag())
    {
    case Value::Int:
        handle_int(*event.as_int());
        break;

    case Value::Float:
        handle_float(*event.as_float());
        break;
    }
}

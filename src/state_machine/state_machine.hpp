#ifndef STATE_MACHINE
#define STATE_MACHINE

#include "ringbuffer.hpp"
#include "tagged_union.hpp"
#include <cstdint>

class State
{
public:
    virtual uint32_t id() = 0;
    virtual void step() = 0;
    void handle(const Value& event);
    virtual void entry() {}
    virtual void exit() {}

private:
    virtual void handle_int(const int& i) = 0;
    virtual void handle_float(const float& f) = 0;
};

class StateMachine
{
public:
    void queue(Value event);
    void step();

private:
    static constexpr uint32_t Event_Queue_Size{10};
    ringbuffer<Value, Event_Queue_Size> m_events;
    State* m_state = nullptr;
};

#endif // STATE_MACHINE

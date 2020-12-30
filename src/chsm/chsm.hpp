#ifndef HIERARCHICAL_STATE_MACHINE
#define HIERARCHICAL_STATE_MACHINE

#include <cassert>
#include <cstdint>

constexpr uint8_t Max_State_Nesting = 255;

template <typename Event>
class Hsm;

template <typename Event>
class State;

using EventId = int32_t;
using StateId = int32_t;

[[maybe_unused]] constexpr EventId Event_Init {-1};
[[maybe_unused]] constexpr EventId Event_Entry {-2};
[[maybe_unused]] constexpr EventId Event_Exit {-3};

// Result
////////////////////////////////////////////////////////////////////////////////
class Unhandled
{
};

class Handled
{
};

template <typename Event>
class Transition
{
public:
    Transition() = default;

    explicit Transition(State<Event>& target)
        : m_target {&target}
    {
    }

    State<Event>* target() const
    {
        return m_target;
    }

private:
    State<Event>* const m_target {nullptr};
};

template <typename Event>
class Result
{
public:
    enum class State
    {
        Handled,
        Unhandled,
        Transition,
    };

    explicit Result(Unhandled /*unused*/)
        : m_state {State::Unhandled}
    {
    }

    explicit Result(Handled /*unused*/)
        : m_state {State::Handled}
    {
    }

    explicit Result(Transition<Event> transition)
        : m_state {State::Transition}
        , m_transition {transition}
    {
    }

    [[nodiscard]] bool event_was_handeled() const
    {
        return m_state == State::Handled || m_state == State::Transition;
    }

    [[nodiscard]] bool has_transition() const
    {
        return m_state == State::Transition;
    }

    [[nodiscard]] Transition<Event>& transition()
    {
        return m_transition;
    }

private:
    State m_state = State::Unhandled;
    Transition<Event> m_transition;
};

// EventHandler
////////////////////////////////////////////////////////////////////////////////
template <typename Event>
using EventHandler = Result<Event> (Hsm<Event>::*)(EventId id, const Event*);

// State
////////////////////////////////////////////////////////////////////////////////
template <typename Event>
class State
{
public:
    State(
        StateId id,
        State* super_state,
        EventHandler<Event> event_handler,
        State* inital_state = nullptr);

    [[nodiscard]] StateId id() const
    {
        return m_id;
    }
    Result<Event> on_event(Hsm<Event>* hsm, EventId id, Event const* event)
    {
        return (hsm->*m_event_handler)(id, event);
    }
    State* inital_state() const
    {
        return m_inital_state;
    }
    State* super_state() const
    {
        return m_super_state;
    }

private:
    State* const m_super_state;
    EventHandler<Event> m_event_handler;
    const StateId m_id;
    State* const m_inital_state;
};

template <typename Event>
State<Event>::State(
    StateId id,
    State* super_state,
    EventHandler<Event> event_handler,
    State* inital_state)
    : m_super_state(super_state)
    , m_event_handler(event_handler)
    , m_id(id)
    , m_inital_state(inital_state)
{
}

// Hierarchical State Machine
////////////////////////////////////////////////////////////////////////////////
template <typename Event>
class Hsm
{
public:
    explicit Hsm(State<Event>& inital);
    void on_start(); /// enter and start the top state
    void on_event(Event const* event);
    [[nodiscard]] StateId state() const
    {
        return m_current_state->id();
    }

private:
    uint8_t levels_to_lca(State<Event>* source, State<Event>* target);
    void exit_to_lca(State<Event>* source, uint8_t levels_to_lca);
    void enter_from_lca();
    void init_state();

    State<Event>* m_current_state; /// current state
    State<Event>* m_next_state = nullptr; /// the next state if transition taken otherwise a nullptr
    State<Event>* m_source_state = nullptr; /// source state during last transition
    State<Event>* m_entry_path[Max_State_Nesting];
};

/// HSM constructor
template <typename Event>
Hsm<Event>::Hsm(State<Event>& inital_state)
    : m_current_state {&inital_state}
{
}

/// enters and starts the top state
template <typename Event>
void Hsm<Event>::on_start()
{
    m_current_state->on_event(this, Event_Entry, nullptr);
    init_state();
}

template <typename Event>
void Hsm<Event>::init_state()
{
    // perform init events till there are no more transitions
    while (true)
    {
        m_current_state->on_event(this, Event_Init, nullptr);
        if (m_current_state->inital_state() != nullptr)
        {
            assert(m_next_state == nullptr);
            m_next_state = m_current_state->inital_state();
        }

        if (m_next_state != nullptr)
        {
            enter_from_lca();
        }
        else
        {
            break;
        }
    }
}

template <typename Event>
void Hsm<Event>::on_event(Event const* event)
{
    // try to handle events walking up the inheritance chain if not handled
    for (auto s = m_current_state; s != nullptr; s = s->super_state())
    {
        auto result = s->on_event(this, to_event_id(*event), event);
        if (result.event_was_handeled())
        {
            if (result.has_transition())
            {
                assert(m_next_state == nullptr);
                m_next_state = result.transition().target();
                auto levels = levels_to_lca(s, m_next_state);
                exit_to_lca(s, levels);
                enter_from_lca();
                init_state();
            }
            break;
        }
    }
}

template <typename Event>
void Hsm<Event>::enter_from_lca()
{
    State<Event>** trace = m_entry_path;
    *trace = nullptr;
    for (State<Event>* s = m_next_state; s != m_current_state; s = s->super_state())
    {
        ++trace;
        *trace = s; // record path to target
    }
    while (*trace != nullptr)
    {
        // retrace the entry
        (*trace)->on_event(this, Event_Entry, nullptr);
        --trace;
    }
    m_current_state = m_next_state;
    m_next_state = nullptr;
}

/// exit current states and all super states up to least common ancestor
template <typename Event>
void Hsm<Event>::exit_to_lca(State<Event>* source, uint8_t levels_to_lca)
{
    State<Event>* s = m_current_state;
    while (s != source)
    {
        s->on_event(this, Event_Exit, nullptr);
        s = s->super_state();
    }
    while (levels_to_lca != 0)
    {
        s->on_event(this, Event_Exit, nullptr);
        s = s->super_state();
        --levels_to_lca;
    }
    m_current_state = s;
}

template <typename Event>
uint8_t Hsm<Event>::levels_to_lca(State<Event>* source, State<Event>* target)
{
    State<Event>* s;
    State<Event>* t;
    uint8_t levels_to_lca = 0;
    if (source == target)
    {
        return 1;
    }
    for (s = source;
         s != nullptr;
         ++levels_to_lca, s = s->super_state())
    {
        for (t = target; t; t = t->super_state())
        {
            if (s == t)
            {
                return levels_to_lca;
            }
        }
    }
    return 0;
}

#endif // HIERARCHICAL_STATE_MACHINE

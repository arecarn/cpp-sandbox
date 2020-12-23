#ifndef HIERARCHICAL_STATE_MACHINE
#define HIERARCHICAL_STATE_MACHINE

#include <cassert>
#include <cstdint>

#define MAX_STATE_NESTING 8

using EventId = int32_t;
using StateId = int32_t;

template <typename Event>
class Unhandled
{
};

template <typename Event>
class Handled
{
};

template <typename Event>
class Transition;

template <typename Event>
class Result
{
public:
    enum class State
    {
        Handled,
        Unhandled,
    };

    explicit Result(Unhandled<Event> /*unused*/)
        : m_state {State::Unhandled}
    {
    }

    explicit Result(Handled<Event> /*unused*/)
        : m_state {State::Handled}
    {
    }

    explicit Result(Transition<Event>& transition)
        : m_state {State::Handled}
        , m_transition {&transition}
    {
    }

    [[nodiscard]] bool event_was_handeled() const
    {
        return m_state == State::Handled;
    }

    [[nodiscard]] bool has_transition() const
    {
        return m_transition != nullptr;
    }

    Transition<Event>& transition()
    {
        return *m_transition;
    }

private:
    State m_state = State::Unhandled;
    Transition<Event>* const m_transition = nullptr;
};

template <typename Event>
class Hsm;

template <typename Event>
using EventHandler = Result<Event> (Hsm<Event>::*)(EventId id, const Event*);

template <typename Event>
class State
{
    State* const m_super_state; /// pointer to superstate
    EventHandler<Event> m_event_handler; /// state's handler function
    const StateId m_id;
    State* const m_inital_state; /// initial state

public:
    State(
        StateId id,
        State* super,
        EventHandler<Event> handler,
        State* inital = nullptr);

    [[nodiscard]] StateId id() const
    {
        return m_id;
    }

private:
    Result<Event> on_event(Hsm<Event>* ctx, EventId id, Event const* event)
    {
        return (ctx->*m_event_handler)(id, event);
    }
    friend class Hsm<Event>;
};

// Hierarchical State Machine base class
template <typename Event>
class Hsm
{
    State<Event>* m_current_state; /// current state
    const State<Event>* m_inital_state;

protected:
    State<Event>* m_next_state; /// the next state if transition taken otherwise a nullptr
    State<Event>* m_source_state; /// source state during last transition
    State<Event> m_top_state; /// top-most state object
    State<Event>* m_entry_path[MAX_STATE_NESTING];

public:
    Hsm(StateId top_id, EventHandler<Event> top_hndlr, State<Event>* inital = nullptr);
    void on_start(); /// enter and start the top state
    void on_event(Event const* event); /// "state machine engine"
    [[nodiscard]] StateId state() const
    {
        return m_current_state->id();
    }

protected:
    unsigned char levels_to_lca(State<Event>* target);
    void exit_to_lca(unsigned char levels_to_lca);
    void enter_from_lca();
    State<Event>* current_state()
    {
        return m_current_state;
    }
    void init_state();

    template <typename T>
    friend class Transition;
};

template <typename Event>
class Transition
{
public:
    Transition(Hsm<Event>& hsm, State<Event>& target)
        : m_levels_to_lca {hsm.levels_to_lca(&target)}
        , m_target {target}
    {
    }

    [[nodiscard]] unsigned char levels_to_lca() const
    {
        return m_levels_to_lca;
    }

    State<Event>& target() const
    {
        return m_target;
    }

private:
    const unsigned char m_levels_to_lca;
    State<Event>& m_target;
};

[[maybe_unused]] constexpr EventId Event_Init {-1};
[[maybe_unused]] constexpr EventId Event_Entry {-2};
[[maybe_unused]] constexpr EventId Event_Exit {-3};

////////////////////////////////////////////////////////////////////////////////

/// State constructor
template <typename Event>
State<Event>::State(
    StateId id,
    State* super_state,
    EventHandler<Event> handler,
    State* inital_state)
    : m_super_state(super_state)
    , m_event_handler(handler)
    , m_id(id)
    , m_inital_state(inital_state)
{
}

/// HSM constructor
template <typename Event>
Hsm<Event>::Hsm(
    StateId top_id,
    EventHandler<Event> top_hndlr,
    State<Event>* inital)
    : m_current_state {&m_top_state}
    , m_next_state {nullptr}
    , m_top_state(top_id, nullptr, top_hndlr, inital)
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
        if (m_current_state->m_inital_state)
        {
            assert(m_next_state == nullptr);
            m_next_state = m_current_state->m_inital_state;
        }

        if (m_next_state)
        {
            enter_from_lca();
        }
        else
        {
            break;
        }
    }
}

/// state machine engine
template <typename Event>
void Hsm<Event>::on_event(Event const* event)
{
    State<Event>* s;
    // try to handle events walking up the inheritance chain if not handled
    for (s = m_current_state; s; s = s->m_super_state)
    {
        m_source_state = s; // level of outermost event handler
        auto result = s->on_event(this, to_event_id(*event), event);
        if (result.event_was_handeled())
        {
            if (result.has_transition())
            {
                auto& t = result.transition();
                assert(m_next_state == nullptr);
                exit_to_lca(t.levels_to_lca());
                m_next_state = &t.target();
                // the current state is the LCA of the source and target state
                // so enter the target state
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
    State<Event>* s;
    *trace = nullptr;
    for (s = m_next_state; s != m_current_state; s = s->m_super_state)
    {
        ++trace;
        *trace = s; // record path to target
    }
    while (*trace != nullptr)
    {
        // retrace the entry
        s = *trace;
        s->on_event(this, Event_Entry, nullptr);
        --trace;
    }
    m_current_state = m_next_state;
    m_next_state = nullptr;
}

/// exit current states and all superstates up to least common ancestor
template <typename Event>
void Hsm<Event>::exit_to_lca(unsigned char levels_to_lca)
{
    State<Event>* s = m_current_state;
    while (s != m_source_state)
    {
        s->on_event(this, Event_Exit, nullptr);
        s = s->m_super_state;
    }
    while (levels_to_lca != 0)
    {
        s->on_event(this, Event_Exit, nullptr);
        s = s->m_super_state;
        --levels_to_lca;
    }
    m_current_state = s;
}

template <typename Event>
unsigned char Hsm<Event>::levels_to_lca(State<Event>* target)
{
    State<Event>* s;
    State<Event>* t;
    unsigned char levels_to_lca = 0;
    if (m_source_state == target)
    {
        return 1;
    }
    for (s = m_source_state; s; ++levels_to_lca, s = s->m_super_state)
    {
        for (t = target; t; t = t->m_super_state)
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

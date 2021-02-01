#ifndef HIERARCHICAL_STATE_MACHINE
#define HIERARCHICAL_STATE_MACHINE

#include <cassert>
#include <cstdint>

constexpr uint8_t Max_State_Nesting = 255;

class Hsm;

class State;

using StateId = int32_t;

// Result
////////////////////////////////////////////////////////////////////////////////
class Unhandled
{
};

class Handled
{
};

class Transition
{
public:
    Transition() = default;

    explicit Transition(State& target)
        : m_target {&target}
    {
    }

    State* target() const
    {
        return m_target;
    }

private:
    State* const m_target {nullptr};
};

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

    explicit Result(Transition transition)
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

    [[nodiscard]] Transition& transition()
    {
        return m_transition;
    }

private:
    State m_state = State::Unhandled;
    Transition m_transition;
};

// EventHandler
////////////////////////////////////////////////////////////////////////////////
using EventHandler = Result (Hsm::*)();

using EntryHandler = void (Hsm::*)();

using InitHandler = void (Hsm::*)();

using ExitHandler = void (Hsm::*)();

// State
////////////////////////////////////////////////////////////////////////////////
class State
{
public:
    State(
        StateId id,
        State* super_state,
        EventHandler event_handler,
        EntryHandler init_handler,
        EntryHandler entry_handler,
        EntryHandler exit_handler,
        State* inital_state = nullptr);

    [[nodiscard]] StateId id() const
    {
        return m_id;
    }
    Result handle(Hsm* hsm)
    {
        return (hsm->*m_event_handler)();
    }

    void entry(Hsm* hsm)
    {
        if (m_entry_handler != nullptr)
        {
            (hsm->*m_entry_handler)();
        }
    }

    void init(Hsm* hsm)
    {
        if (m_init_handler != nullptr)
        {
            (hsm->*m_init_handler)();
        }
    }

    void exit(Hsm* hsm)
    {
        if (m_exit_handler != nullptr)
        {
            (hsm->*m_exit_handler)();
        }
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
    EventHandler m_event_handler;
    InitHandler m_init_handler;
    EntryHandler m_entry_handler;
    ExitHandler m_exit_handler;
    const StateId m_id;
    State* const m_inital_state;
};

State::State(
    StateId id,
    State* super_state,
    EventHandler event_handler,
    InitHandler init_handler,
    EntryHandler entry_handler,
    ExitHandler exit_handler,
    State* inital_state)
    : m_super_state(super_state)
    , m_event_handler(event_handler)
    , m_init_handler(init_handler)
    , m_entry_handler(entry_handler)
    , m_exit_handler(exit_handler)
    , m_id(id)
    , m_inital_state(inital_state)
{
}

// Hierarchical State Machine
////////////////////////////////////////////////////////////////////////////////
class Hsm
{
public:
    explicit Hsm(State& inital);
    void init(); /// enter and start the top state
    void handle();
    [[nodiscard]] StateId state_id() const
    {
        return m_current_state->id();
    }

private:
    uint8_t levels_to_lca(State* source, State* target);
    void exit_to_lca(State* source, uint8_t levels_to_lca);
    void enter_from_lca();
    void init_state();

    State* m_current_state; /// current state
    State* m_next_state = nullptr; /// the next state if transition taken otherwise a nullptr
    State* m_entry_path[Max_State_Nesting];
};

/// HSM constructor
Hsm::Hsm(State& inital_state)
    : m_current_state {&inital_state}
{
}

/// enters and starts the top state
void Hsm::init()
{
    m_current_state->entry(this);
    init_state();
}

void Hsm::init_state()
{
    // perform init events till there are no more transitions
    while (true)
    {
        m_current_state->init(this);
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

void Hsm::handle()
{
    // try to handle events walking up the inheritance chain if not handled
    for (auto s = m_current_state; s != nullptr; s = s->super_state())
    {
        auto result = s->handle(this);
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

void Hsm::enter_from_lca()
{
    State** trace = m_entry_path;
    *trace = nullptr;
    for (State* s = m_next_state; s != m_current_state; s = s->super_state())
    {
        ++trace;
        *trace = s; // record path to target
    }
    while (*trace != nullptr)
    {
        // retrace the entry
        (*trace)->entry(this);
        --trace;
    }
    m_current_state = m_next_state;
    m_next_state = nullptr;
}

/// exit current states and all super states up to least common ancestor
void Hsm::exit_to_lca(State* source, uint8_t levels_to_lca)
{
    State* s = m_current_state;
    while (s != source)
    {
        s->exit(this);
        s = s->super_state();
    }
    while (levels_to_lca != 0)
    {
        s->exit(this);
        s = s->super_state();
        --levels_to_lca;
    }
    m_current_state = s;
}

uint8_t Hsm::levels_to_lca(State* source, State* target)
{
    State* s;
    State* t;
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

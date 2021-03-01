#ifndef HIERARCHICAL_STATE_MACHINE
#define HIERARCHICAL_STATE_MACHINE

#include <cstdint>

constexpr uint8_t Max_State_Nesting = 255;

class Hsm;

class State;

using StateId = uint32_t;

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
        : m_target{&target} {}

              [[nodiscard]] State
        * target() const
    {
        return m_target;
    }

private:
    State* const m_target{nullptr};
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
        : m_state{State::Unhandled}
    {
    }

    explicit Result(Handled /*unused*/)
        : m_state{State::Handled}
    {
    }

    explicit Result(Transition transition)
        : m_state{State::Transition}
        , m_transition{transition} {}

              [[nodiscard]] bool event_was_handeled() const
    {
        return m_state == State::Handled || m_state == State::Transition;
    }

    [[nodiscard]] bool has_transition() const {
        return m_state == State::Transition;
    }

        [[nodiscard]] Transition& transition()
    {
        return m_transition;
    }

private:
    State m_state;
    Transition m_transition;
};

// EventHandler
////////////////////////////////////////////////////////////////////////////////
using EventHandler = Result (Hsm::*)();

template <typename T>
EventHandler event_handler(T member_function)
{
    return static_cast<EventHandler>(member_function);
}

using Handler = void (Hsm::*)();

template <typename T>
Handler entry_handler(T member_function)
{
    return static_cast<Handler>(member_function);
}

template <typename T>
Handler exit_handler(T member_function)
{
    return static_cast<Handler>(member_function);
}

template <typename T>
Handler init_handler(T member_function)
{
    return static_cast<Handler>(member_function);
}

// State
////////////////////////////////////////////////////////////////////////////////
class State
{
public:
    State(
        StateId id,
        State* super_state,
        EventHandler event_handler,
        Handler init_handler,
        Handler entry_handler,
        Handler exit_handler,
        State* inital_state = nullptr);

    [[nodiscard]] StateId id() const {
        return m_id;
    } Result handle(Hsm* hsm)
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

    [[nodiscard]] State* inital_state() const {
        return m_inital_state;
    }
        [[nodiscard]] State* super_state() const
    {
        return m_super_state;
    }

private:
    State* const m_super_state;
    EventHandler m_event_handler;
    Handler m_init_handler;
    Handler m_entry_handler;
    Handler m_exit_handler;
    const StateId m_id;
    State* const m_inital_state;
};

// Hierarchical State Machine
////////////////////////////////////////////////////////////////////////////////
class Hsm
{
public:
    explicit Hsm(State& inital_state);
    void init(); /// enter and start the top state
    void handle();
    [[nodiscard]] StateId state_id() const {
        return m_current_state->id();
    }

    private : static uint8_t levels_to_lca(State* source, State* target);
    void exit_to_lca(State* source, uint8_t levels_to_lca);
    void enter_from_lca();
    void init_state();

    State* m_current_state; /// current state
    State* m_next_state = nullptr; /// the next state if transition taken otherwise a nullptr
    State* m_entry_path[Max_State_Nesting] = {nullptr};
};

#endif // HIERARCHICAL_STATE_MACHINE

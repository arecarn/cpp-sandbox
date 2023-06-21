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
        : m_target {&target}
    {
    }

    [[nodiscard]] State* target() const
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
    State m_state;
    Transition m_transition;
};

// EventHandler
////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Param>
class HandlerType
{
public:
    template <typename P>
    explicit HandlerType(P v)
        : m_value {static_cast<T>(v)}
    {
    }

    HandlerType() = default;
    [[nodiscard]] const T& value() const
    {
        return m_value;
    }

private:
    T m_value = {}; // TODO(rcarney making this const seems like an issue)
};

using EventHandlerFunction = Result (Hsm::*)();
using EventHandler = HandlerType<EventHandlerFunction, struct EventHandlerParam>;

using HandlerFunction = void (Hsm::*)();
using InitHandler = HandlerType<HandlerFunction, struct InitHandlerParam>;
using EntryHandler = HandlerType<HandlerFunction, struct EntryHandlerParam>;
using ExitHandler = HandlerType<HandlerFunction, struct ExitHandlerParam>;
// State
////////////////////////////////////////////////////////////////////////////////

class State;

template <typename T, typename Param>
class StateType
{
public:
    explicit StateType(T v)
        : m_value {v}
    {
    }

    StateType() = default;
    [[nodiscard]] const T& value() const
    {
        return m_value;
    }

private:
    const T m_value = {};
};

using InitalState = StateType<State*, struct InitalStateParam>;
using SuperState = StateType<State*, struct SuperStateParam>;

struct Init
{
    InitHandler handler;
    InitalState state;
};

class State
{
public:
    State(
        StateId id,
        EventHandler event_handler,
        EntryHandler entry_handler = EntryHandler {},
        ExitHandler exit_handler = ExitHandler {},
        Init init = Init {},
        SuperState super_state = SuperState {});

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

    [[nodiscard]] State* inital_state() const
    {
        return m_inital_state;
    }
    [[nodiscard]] State* super_state() const
    {
        return m_super_state;
    }

private:
    State* const m_super_state;
    EventHandlerFunction m_event_handler;
    HandlerFunction m_init_handler;
    HandlerFunction m_entry_handler;
    HandlerFunction m_exit_handler;
    const StateId m_id;
    State* const m_inital_state;
};

// Hierarchical State Machine
////////////////////////////////////////////////////////////////////////////////
class Hsm
{
public:
    explicit Hsm(InitalState inital_state);
    void init(); /// enter and start the top state
    void handle();
    [[nodiscard]] StateId state_id() const
    {
        return m_current_state->id();
    }

private:
    static uint8_t levels_to_lca(State* source, State* target);
    void exit_to_lca(State* source, uint8_t levels_to_lca);
    void enter_from_lca();
    void init_state();

    State* m_current_state; /// current state
    State* m_next_state = nullptr; /// the next state if transition taken otherwise a nullptr
    State* m_entry_path[Max_State_Nesting] = {nullptr};
};

#endif // HIERARCHICAL_STATE_MACHINE

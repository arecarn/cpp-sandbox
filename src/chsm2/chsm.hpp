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

    [[nodiscard]] State* target() const { return m_target; }

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

    [[nodiscard]] Transition& transition() { return m_transition; }

private:
    State m_state;
    Transition m_transition;
};

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
    [[nodiscard]] const T& value() const { return m_value; }

private:
    const T m_value = {};
};

using InitalState = StateType<State*, struct InitalStateParam>;
using SuperState = StateType<State*, struct SuperStateParam>;
class Hsm;

class State
{
public:
    State(StateId id, InitalState inital_state = InitalState {}, SuperState super_state = SuperState {});
    virtual ~State() = default;
    virtual Result handle() = 0;
    virtual void entry() { }
    virtual void init() { }
    virtual void exit() { }
    [[nodiscard]] StateId id() const { return m_id; }
    [[nodiscard]] State* inital_state() const { return m_inital_state; }
    [[nodiscard]] State* super_state() const { return m_super_state; }

private:
    const StateId m_id;
    State* const m_super_state;
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
    [[nodiscard]] StateId state_id() const { return m_current_state->id(); }

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

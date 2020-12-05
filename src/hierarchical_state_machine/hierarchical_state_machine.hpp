#ifndef HIERARCHICAL_STATE_MACHINE
#define HIERARCHICAL_STATE_MACHINE

#include <cassert>

#define MAX_STATE_NESTING 8

using Event = int;
struct Msg
{
    Event evt;
};

class Hsm;
using EventHandler = const Msg* (Hsm::*)(const Msg*);

class State
{
    State* const m_super; /// pointer to superstate
    EventHandler m_handler; /// state's handler function
    char const* m_name;
    State* const m_inital; /// initial state

public:
    State(char const* name,
        State* super,
        EventHandler handler,
        State* inital = nullptr);

private:
    Msg const* on_event(Hsm* ctx, Msg const* msg)
    {
        return (ctx->*m_handler)(msg);
    }
    friend class Hsm;
};

class Hsm
{ // Hierarchical State Machine base class
    char const* m_name; // pointer to static name */
    State* m_current; /* current state */
    const State* m_inital;

protected:
    State* m_next; /* next state (non 0 if transition taken) */
    State* m_source; /* source state during last transition */
    State m_top; /* top-most state object */
    State* m_entry_path[MAX_STATE_NESTING];

public:
    Hsm(char const* name, EventHandler top_hndlr, State* inital = nullptr); /* Ctor */
    void on_start(); /* enter and start the top state */
    void on_event(Msg const* msg); /* "state machine engine" */
protected:
    unsigned char to_lca(State* target);
    void exit(unsigned char to_lca);
    void enter();
    State* current_state() { return m_current; }
    void init_state();

#define STATE_TRAN(TARGET)                     \
    {                                          \
        static Transition t {*this, (TARGET)}; \
        t();                                   \
    }

    friend class Transition;
};

class Transition
{
public:
    Transition(Hsm& hsm, State& target)
        : m_depth {hsm.to_lca(&target)}
        , m_target {target}
        , m_hsm {hsm}
    {
    }

    void operator()()
    {
        assert(m_hsm.m_next == nullptr);
        m_hsm.exit(m_depth);
        m_hsm.m_next = &m_target;
    }

private:
    const unsigned char m_depth;
    State& m_target;
    Hsm& m_hsm;
};

[[maybe_unused]] constexpr Event INIT_EVT {-1};
[[maybe_unused]] constexpr Event ENTRY_EVT {-2};
[[maybe_unused]] constexpr Event EXIT_EVT {-3};

#endif //HIERARCHICAL_STATE_MACHINE

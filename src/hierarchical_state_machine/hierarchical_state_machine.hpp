#ifndef HIERARCHICAL_STATE_MACHINE
#define HIERARCHICAL_STATE_MACHINE

#include <cassert>

using Event = int;
struct Msg
{
    Event evt;
};

class Hsm; /* forward declaration */
using EvtHndlr = const Msg* (Hsm::*)(const Msg*);

class State
{
    State* m_super; /* pointer to superstate */
    EvtHndlr m_hndlr; /* state's handler function */
    char const* m_name;

public:
    State(char const* name, State* super, EvtHndlr hndlr);

private:
    Msg const* on_event(Hsm* ctx, Msg const* msg)
    {
        return (ctx->*m_hndlr)(msg);
    }
    friend class Hsm;
};

class Hsm
{ /* Hierarchical State Machine base class */
    char const* m_name; /* pointer to static name */
    State* m_curr; /* current state */
protected:
    State* m_next; /* next state (non 0 if transition taken) */
    State* m_source; /* source state during last transition */
    State m_top; /* top-most state object */
public:
    Hsm(char const* name, EvtHndlr top_hndlr); /* Ctor */
    void on_start(); /* enter and start the top state */
    void on_event(Msg const* msg); /* "state machine engine" */
protected:
    unsigned char to_lca(State* target);
    void exit(unsigned char to_lca);
    State* state_curr() { return m_curr; }
    void state_start(State* target)
    {
        assert(m_next == 0);
        m_next = target;
    }
#define STATE_TRAN(target_)                \
    if (1)                                 \
    {                                      \
        static unsigned char depth = 0xFF; \
        assert(m_next == 0);               \
        if (depth == 0xFF)                 \
            depth = to_lca(target_);       \
        exit(depth);                       \
        m_next = (target_);                \
    }                                      \
    else                                   \
        ((void)0)
};

[[maybe_unused]] constexpr Event START_EVT {-1};
[[maybe_unused]] constexpr Event ENTRY_EVT {-2};
[[maybe_unused]] constexpr Event EXIT_EVT {-3};

#endif //HIERARCHICAL_STATE_MACHINE

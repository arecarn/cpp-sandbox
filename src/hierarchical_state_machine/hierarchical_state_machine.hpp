#ifndef HIERARCHICAL_STATE_MACHINE
#define HIERARCHICAL_STATE_MACHINE

#include <cassert>

#define MAX_STATE_NESTING 8

using EventId = int;
using StateId = int;

template <typename Event>
class Hsm;

template <typename Event>
using EventHandler = const Event* (Hsm<Event>::*)(EventId id, const Event*);

template <typename Event>
class State
{
    State* const m_super; /// pointer to superstate
    EventHandler<Event> m_handler; /// state's handler function
    const int m_id;
    State* const m_inital; /// initial state

public:
    State(StateId id,
        State* super,
        EventHandler<Event> handler,
        State* inital = nullptr);

    [[nodiscard]] StateId id() const
    {
        return m_id;
    }

private:
    Event const* on_event(Hsm<Event>* ctx, EventId id, Event const* event)
    {
        return (ctx->*m_handler)(id, event);
    }
    friend class Hsm<Event>;
};

// Hierarchical State Machine base class
template <typename Event>
class Hsm
{
    State<Event>* m_current; /// current state
    const State<Event>* m_inital;

protected:
    State<Event>* m_next; /// next state (non 0 if transition taken)
    State<Event>* m_source; /// source state during last transition
    State<Event> m_top; /// top-most state object
    State<Event>* m_entry_path[MAX_STATE_NESTING];

public:
    Hsm(StateId topId, EventHandler<Event> top_hndlr, State<Event>* inital = nullptr);
    void on_start(); /// enter and start the top state
    void on_event(Event const* event); /// "state machine engine"
    StateId state() const
    {
        return m_current->id();
    }

protected:
    unsigned char to_lca(State<Event>* target);
    void exit_to_lca(unsigned char to_lca);
    void enter_from_lca();
    State<Event>* current_state() { return m_current; }
    void init_state();

    template <typename T>
    friend class Transition;
};

template <typename Event>
class Transition
{
public:
    Transition(Hsm<Event>& hsm, State<Event>& target)
        : m_depth {hsm.to_lca(&target)}
        , m_target {target}
        , m_hsm {hsm}
    {
    }

    void operator()()
    {
        assert(m_hsm.m_next == nullptr);
        m_hsm.exit_to_lca(m_depth);
        m_hsm.m_next = &m_target;
    }

private:
    const unsigned char m_depth;
    State<Event>& m_target;
    Hsm<Event>& m_hsm;
};

[[maybe_unused]] constexpr EventId Event_Init {-1};
[[maybe_unused]] constexpr EventId Event_Entry {-2};
[[maybe_unused]] constexpr EventId Event_Exit {-3};

////////////////////////////////////////////////////////////////////////////////

/// State constructor
template <typename Event>
State<Event>::State(StateId id, State* s, EventHandler<Event> h, State* i)
    : m_super(s)
    , m_handler(h)
    , m_id(id)
    , m_inital(i)
{
}

/// HSM constructor
template <typename Event>
Hsm<Event>::Hsm(StateId topId, EventHandler<Event> top_hndlr, State<Event>* inital)
    : m_current {&m_top}
    , m_next {nullptr}
    , m_top(topId, nullptr, top_hndlr, inital)
{
}

/// enters and starts the top state
template <typename Event>
void Hsm<Event>::on_start()
{
    m_current->on_event(this, Event_Entry, nullptr);
    init_state();
}

template <typename Event>
void Hsm<Event>::init_state()
{
    // perform init events till there are no more transitions
    while (true)
    {
        m_current->on_event(this, Event_Init, nullptr);
        if (m_current->m_inital)
        {
            assert(m_next == nullptr);
            m_next = m_current->m_inital;
        }

        if (m_next)
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
    for (s = m_current; s; s = s->m_super)
    {
        m_source = s; // level of outermost event handler
        event = s->on_event(this, to_event_id(*event), event);
        if (event == nullptr) // the event was processed
        {
            if (m_next) // a state transition was initiated
            {
                // the current state is the LCA of the source and target state
                // so enter the target state
                enter_from_lca();
                init_state();
            }
            break; // event processed
        }
    }
}

template <typename Event>
void Hsm<Event>::enter_from_lca()
{
    State<Event>** trace = m_entry_path;
    State<Event>* s;
    *trace = nullptr;
    for (s = m_next; s != m_current; s = s->m_super)
    {
        *(++trace) = s; // record path to target
    }
    while ((s = *trace--))
    { // retrace the entry
        s->on_event(this, Event_Entry, nullptr);
    }
    m_current = m_next;
    m_next = nullptr;
}

/// exit current states and all superstates up to least common ancestor
template <typename Event>
void Hsm<Event>::exit_to_lca(unsigned char to_lca)
{
    State<Event>* s = m_current;
    while (s != m_source)
    {
        s->on_event(this, Event_Exit, nullptr);
        s = s->m_super;
    }
    while (to_lca--)
    {
        s->on_event(this, Event_Exit, nullptr);
        s = s->m_super;
    }
    m_current = s;
}

/// find number of levels to the least common ancestor
template <typename Event>
unsigned char Hsm<Event>::to_lca(State<Event>* target)
{
    State<Event>* s;
    State<Event>* t;
    unsigned char to_lca = 0;
    if (m_source == target)
    {
        return 1;
    }
    for (s = m_source; s; ++to_lca, s = s->m_super)
    {
        for (t = target; t; t = t->m_super)
        {
            if (s == t)
            {
                return to_lca;
            }
        }
    }
    return 0;
}

#endif //HIERARCHICAL_STATE_MACHINE

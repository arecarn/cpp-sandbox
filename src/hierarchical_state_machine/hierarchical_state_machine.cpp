#include "hierarchical_state_machine.hpp"

static Msg const Init_Msg = {INIT_EVT};
static Msg const Entry_Msg = {ENTRY_EVT};
static Msg const Exit_Msg = {EXIT_EVT};

/// State constructor
State::State(char const* n, State* s, EventHandler h, State* i)
    : m_super(s)
    , m_name(n)
    , m_handler(h)
    , m_inital(i)
{
}

/// HSM constructor
Hsm::Hsm(char const* n, EventHandler top_hndlr, State* inital)
    : m_name(n)
    , m_top("top", nullptr, top_hndlr, inital)
{
}

/// enters and starts the top state
void Hsm::on_start()
{
    m_current = &m_top;
    m_next = nullptr;
    m_current->on_event(this, &Entry_Msg);
    init_state();
}

void Hsm::init_state()
{
    // perform init events till there are no more transitions
    while (true)
    {
        m_current->on_event(this, &Init_Msg);
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
void Hsm::on_event(Msg const* msg)
{
    State* s;
    // try to handle events walking up the inheritance chain if not handled
    for (s = m_current; s; s = s->m_super)
    {
        m_source = s; // level of outermost event handler
        msg = s->on_event(this, msg);
        if (msg == nullptr) // the event was processed
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

void Hsm::enter_from_lca()
{
    State** trace = m_entry_path;
    State* s;
    *trace = nullptr;
    for (State* s = m_next; s != m_current; s = s->m_super)
    {
        *(++trace) = s; // record path to target
    }
    while ((s = *trace--))
    { // retrace the entry
        s->on_event(this, &Entry_Msg);
    }
    m_current = m_next;
    m_next = nullptr;
}

/// exit current states and all superstates up to least common ancestor
void Hsm::exit_to_lca(unsigned char to_lca)
{
    State* s = m_current;
    while (s != m_source)
    {
        s->on_event(this, &Exit_Msg);
        s = s->m_super;
    }
    while (to_lca--)
    {
        s->on_event(this, &Exit_Msg);
        s = s->m_super;
    }
    m_current = s;
}

/// find number of levels to the least common ancestor
unsigned char Hsm::to_lca(State* target)
{
    State* s;
    State* t;
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

#include "hierarchical_state_machine.hpp"

static Msg const Start_Msg = {START_EVT};
static Msg const Entry_Msg = {ENTRY_EVT};
static Msg const Exit_Msg = {EXIT_EVT};
#define MAX_STATE_NESTING 8

/* State Ctor...............................................................*/
State::State(char const* n, State* s, EvtHndlr h)
    : m_name(n)
    , m_super(s)
    , m_hndlr(h)
{
}

/* Hsm Ctor.................................................................*/
Hsm::Hsm(char const* n, EvtHndlr top_hndlr)
    : m_top("top", nullptr, top_hndlr)
    , m_name(n)
{
}

/* enter and start the top state............................................*/
void Hsm::on_start()
{
    m_curr = &m_top;
    m_next = nullptr;
    m_curr->on_event(this, &Entry_Msg);
    while (m_curr->on_event(this, &Start_Msg), m_next)
    {
        State* entry_path[MAX_STATE_NESTING];
        State** trace = entry_path;
        State* s;
        *trace = nullptr;
        for (s = m_next; s != m_curr; s = s->m_super)
        {
            *(++trace) = s; /* trace path to target */
        }
        while (s = *trace--)
        { /* retrace entry from source */
            s->on_event(this, &Entry_Msg);
        }
        m_curr = m_next;
        m_next = nullptr;
    }
}

/* state machine "engine"...................................................*/
void Hsm::on_event(Msg const* msg)
{
    State* entry_path[MAX_STATE_NESTING];
    State** trace;
    State* s;
    for (s = m_curr; s; s = s->m_super)
    {
        m_source = s; /* level of outermost event handler */
        msg = s->on_event(this, msg);
        if (msg == nullptr)
        { /* processed? */
            if (m_next)
            { /* state transition taken? */
                trace = entry_path;
                *trace = nullptr;
                for (s = m_next; s != m_curr; s = s->m_super)
                {
                    *(++trace) = s; /* trace path to target */
                }
                while (s = *trace--)
                { /* retrace entry from LCA */
                    s->on_event(this, &Entry_Msg);
                }
                m_curr = m_next;
                m_next = nullptr;
                while (m_curr->on_event(this, &Start_Msg), m_next)
                {
                    trace = entry_path;
                    *trace = nullptr;
                    for (s = m_next; s != m_curr; s = s->m_super)
                    {
                        *(++trace) = s; /* record path to target */
                    }
                    while (s = *trace--)
                    { /* retrace the entry */
                        s->on_event(this, &Entry_Msg);
                    }
                    m_curr = m_next;
                    m_next = nullptr;
                }
            }
            break; /* event processed */
        }
    }
}

/* exit current states and all superstates up to LCA .......................*/
void Hsm::exit(unsigned char to_lca)
{
    State* s = m_curr;
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
    m_curr = s;
}

/* find # of levels to Least Common Ancestor................................*/
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

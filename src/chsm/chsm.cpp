#include "chsm.hpp"

#include <cassert>

// State
////////////////////////////////////////////////////////////////////////////////

State::State(
    StateId id,
    EventHandler event_handler,
    EntryHandler entry_handler,
    ExitHandler exit_handler,
    Init init,
    SuperState super_state)
    : m_super_state {super_state.value()}
    , m_event_handler {event_handler.value()}
    , m_init_handler {init.handler.value()}
    , m_entry_handler {entry_handler.value()}
    , m_exit_handler {exit_handler.value()}
    , m_id {id}
    , m_inital_state {init.state.value()}
{
}

// Hierarchical State Machine
////////////////////////////////////////////////////////////////////////////////

/// HSM constructor
Hsm::Hsm(InitalState inital_state)
    : m_current_state {inital_state.value()}
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
    for (auto* s = m_current_state; s != nullptr; s = s->super_state())
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

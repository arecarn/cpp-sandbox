#include "hierarchical_state_machine.hpp"
#include <cassert>
#include <cstdio>

struct Event
{
    int id;
};

EventId id(const Event& msg)
{
    return msg.id;
}

class HsmTest : public Hsm<Event>
{
    int m_my_foo {0};

protected:
    State<Event> m_s1;
    State<Event> m_s11;
    State<Event> m_s2;
    State<Event> m_s21;
    State<Event> m_s211;

public:
    HsmTest();
    Event const* top_handler(EventId id, Event const* msg);
    Event const* s1_handler(EventId id, Event const* msg);
    Event const* s11_handler(EventId id, Event const* msg);
    Event const* s2_handler(EventId id, Event const* msg);
    Event const* s21_handler(EventId id, Event const* msg);
    Event const* s211_handler(EventId id, Event const* msg);
};

enum HsmTestEvents
{
    A_SIG,
    B_SIG,
    C_SIG,
    D_SIG,
    E_SIG,
    F_SIG,
    G_SIG,
    H_SIG
};

Event const* HsmTest::top_handler(EventId id, Event const* msg)
{
    switch (id)
    {
        case INIT_EVT:
            printf("top-INIT;");
            break;
        case ENTRY_EVT:
            printf("top-ENTRY;");
            break;
        case EXIT_EVT:
            printf("top-EXIT;");
            break;
        case E_SIG:
            printf("top-E;");
            {
                static Transition t(*this, m_s211);
                t();
            }
            break;
        default:
            return msg;
    }
    return nullptr;
}

Event const* HsmTest::s1_handler(EventId id, Event const* msg)
{
    switch (id)
    {
        case INIT_EVT:
            printf("s1-INIT;");
            break;
        case ENTRY_EVT:
            printf("s1-ENTRY;");
            break;
        case EXIT_EVT:
            printf("s1-EXIT;");
            break;
        case A_SIG:
            printf("s1-A;");
            {
                static Transition<Event> t(*this, m_s1);
                t();
            }
            break;
        case B_SIG:
            printf("s1-B;");
            {
                static Transition<Event> t(*this, m_s11);
                t();
            }
            break;
        case C_SIG:
            printf("s1-C;");
            {
                static Transition<Event> t(*this, m_s2);
                t();
            }
            break;
        case D_SIG:
            printf("s1-D;");
            {
                static Transition<Event> t(*this, m_top);
                t();
            }
            break;
        case F_SIG:
            printf("s1-F;");
            {
                static Transition<Event> t(*this, m_s211);
                t();
            }
            break;
        default:
            return msg;
    }
    return nullptr;
}

Event const* HsmTest::s11_handler(EventId id, Event const* msg)
{
    switch (id)
    {
        case ENTRY_EVT:
            printf("s11-ENTRY;");
            break;
        case EXIT_EVT:
            printf("s11-EXIT;");
            break;
        case G_SIG:
            printf("s11-G;");
            {
                static Transition<Event> t(*this, m_s211);
                t();
            }
            break;
        case H_SIG:
            if (m_my_foo)
            {
                printf("s11-H;");
                m_my_foo = 0;
            }
            break;
        default:
            return msg;
    }
    return nullptr;
}

Event const* HsmTest::s2_handler(EventId id, Event const* msg)
{
    switch (id)
    {
        case INIT_EVT:
            printf("s2-INIT;");
            break;
        case ENTRY_EVT:
            printf("s2-ENTRY;");
            break;
        case EXIT_EVT:
            printf("s2-EXIT;");
            break;
        case C_SIG:
            printf("s2-C;");
            {
                static Transition<Event> t(*this, m_s1);
                t();
            }
            break;
        case F_SIG:
            printf("s2-F;");
            {
                static Transition<Event> t(*this, m_s11);
                t();
            }
            break;
        default:
            return msg;
    }
    return nullptr;
}

Event const* HsmTest::s21_handler(EventId id, Event const* msg)
{
    switch (id)
    {
        case INIT_EVT:
            printf("s21-INIT;");
            break;
        case ENTRY_EVT:
            printf("s21-ENTRY;");
            break;
        case EXIT_EVT:
            printf("s21-EXIT;");
            break;
        case B_SIG:
            printf("s21-B;");
            {
                static Transition<Event> t(*this, m_s211);
                t();
            }
            break;
        case H_SIG:
            if (!m_my_foo)
            {
                printf("s21-H;");
                m_my_foo = 1;
                {
                    static Transition<Event> t(*this, m_s21);
                    t();
                }
            }
            break;
        default:
            return msg;
    }
    return nullptr;
}

Event const* HsmTest::s211_handler(EventId id, Event const* msg)
{
    switch (id)
    {
        case ENTRY_EVT:
            printf("s211-ENTRY;");
            break;
        case EXIT_EVT:
            printf("s211-EXIT;");
            break;
        case D_SIG:
            printf("s211-D;");
            {
                static Transition<Event> t(*this, m_s21);
                t();
            }
            break;
        case G_SIG:
            printf("s211-G;");
            {
                static Transition<Event> t(*this, m_top);
                t();
            }
            break;
        default:
            return msg;
    }
    return nullptr;
}

HsmTest::HsmTest()
    : Hsm {"HsmTest", static_cast<EventHandler<Event>>(&HsmTest::top_handler), &m_s1}
    , m_s1 {"s1", &m_top, static_cast<EventHandler<Event>>(&HsmTest::s1_handler), &m_s11}
    , m_s11 {"s11", &m_s1, static_cast<EventHandler<Event>>(&HsmTest::s11_handler)}
    , m_s2 {"s2", &m_top, static_cast<EventHandler<Event>>(&HsmTest::s2_handler), &m_s21}
    , m_s21 {"s21", &m_s2, static_cast<EventHandler<Event>>(&HsmTest::s21_handler), &m_s211}
    , m_s211 {"s211", &m_s21, static_cast<EventHandler<Event>>(&HsmTest::s211_handler)}
{
}

const Event HsmTestMsg[] = {
    {A_SIG},
    {B_SIG},
    {C_SIG},
    {D_SIG},
    {E_SIG},
    {F_SIG},
    {G_SIG},
    {H_SIG}};

int main()
{
    HsmTest hsm_test;
    hsm_test.on_start();
    for (;;)
    {
        int c;
        printf("\nEvent<-");
        c = getc(stdin);
        getc(stdin);
        if (c < 'a' || 'h' < c)
        {
            break;
        }
        hsm_test.on_event(&HsmTestMsg[c - 'a']);
    }
}

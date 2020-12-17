#include "hierarchical_state_machine.hpp"
#include <cstdio>
#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <string>

// object to help trace through state transitions for testing
class Trace
{
public:
    void operator()(const std::string& s)
    {
        m_trace.push(s);
    }

    std::string pop()
    {
        std::string result;
        if (!m_trace.empty())
        {
            result = m_trace.front();
            m_trace.pop();
        }
        return result;
    }

    bool empty()
    {
        return m_trace.empty();
    }

private:
    std::queue<std::string> m_trace;
};

Trace g_trace;

struct Event
{
    int id;
};

EventId to_event_id(const Event& msg)
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
    [[nodiscard]] int my_foo() const
    {
        return m_my_foo;
    }
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
            g_trace("top-INIT");
            break;
        case ENTRY_EVT:
            g_trace("top-ENTRY");
            break;
        case EXIT_EVT:
            g_trace("top-EXIT");
            break;
        case E_SIG:
            g_trace("top-E");
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
            g_trace("s1-INIT");
            break;
        case ENTRY_EVT:
            g_trace("s1-ENTRY");
            break;
        case EXIT_EVT:
            g_trace("s1-EXIT");
            break;
        case A_SIG:
            g_trace("s1-A");
            {
                static Transition<Event> t(*this, m_s1);
                t();
            }
            break;
        case B_SIG:
            g_trace("s1-B");
            {
                static Transition<Event> t(*this, m_s11);
                t();
            }
            break;
        case C_SIG:
            g_trace("s1-C");
            {
                static Transition<Event> t(*this, m_s2);
                t();
            }
            break;
        case D_SIG:
            g_trace("s1-D");
            {
                static Transition<Event> t(*this, m_top);
                t();
            }
            break;
        case F_SIG:
            g_trace("s1-F");
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
            g_trace("s11-ENTRY");
            break;
        case EXIT_EVT:
            g_trace("s11-EXIT");
            break;
        case G_SIG:
            g_trace("s11-G");
            {
                static Transition<Event> t(*this, m_s211);
                t();
            }
            break;
        case H_SIG:
            if (m_my_foo)
            {
                g_trace("s11-H");
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
            g_trace("s2-INIT");
            break;
        case ENTRY_EVT:
            g_trace("s2-ENTRY");
            break;
        case EXIT_EVT:
            g_trace("s2-EXIT");
            break;
        case C_SIG:
            g_trace("s2-C");
            {
                static Transition<Event> t(*this, m_s1);
                t();
            }
            break;
        case F_SIG:
            g_trace("s2-F");
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
            g_trace("s21-INIT");
            break;
        case ENTRY_EVT:
            g_trace("s21-ENTRY");
            break;
        case EXIT_EVT:
            g_trace("s21-EXIT");
            break;
        case B_SIG:
            g_trace("s21-B");
            {
                static Transition<Event> t(*this, m_s211);
                t();
            }
            break;
        case H_SIG:
            if (!m_my_foo)
            {
                g_trace("s21-H");
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
            g_trace("s211-ENTRY");
            break;
        case EXIT_EVT:
            g_trace("s211-EXIT");
            break;
        case D_SIG:
            g_trace("s211-D");
            {
                static Transition<Event> t(*this, m_s21);
                t();
            }
            break;
        case G_SIG:
            g_trace("s211-G");
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

enum StateDemoId : StateId
{
    Top,
    S1,
    S11,
    S2,
    S21,
    S211,
};

HsmTest::HsmTest()
    : Hsm {Top, static_cast<EventHandler<Event>>(&HsmTest::top_handler), &m_s1}
    , m_s1 {S1, &m_top, static_cast<EventHandler<Event>>(&HsmTest::s1_handler), &m_s11}
    , m_s11 {S11, &m_s1, static_cast<EventHandler<Event>>(&HsmTest::s11_handler)}
    , m_s2 {S2, &m_top, static_cast<EventHandler<Event>>(&HsmTest::s2_handler), &m_s21}
    , m_s21 {S21, &m_s2, static_cast<EventHandler<Event>>(&HsmTest::s21_handler), &m_s211}
    , m_s211 {S211, &m_s21, static_cast<EventHandler<Event>>(&HsmTest::s211_handler)}
{
}

class HsmTestFixture : public ::testing::Test
{
protected:
};

TEST_F(HsmTestFixture, t) // NOLINT(readability-function-size)
{
    Event a {A_SIG};
    Event b {B_SIG};
    Event c {C_SIG};
    Event d {D_SIG};
    Event e {E_SIG};
    Event f {F_SIG};
    Event g {G_SIG};
    Event h {H_SIG};
    HsmTest hsm_test;

    // Initial Transitions
    EXPECT_EQ(Top, hsm_test.state());
    hsm_test.on_start();
    EXPECT_EQ("top-ENTRY", g_trace.pop());
    EXPECT_EQ("top-INIT", g_trace.pop());
    EXPECT_EQ("s1-ENTRY", g_trace.pop());
    EXPECT_EQ("s1-INIT", g_trace.pop());
    EXPECT_EQ("s11-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-A
    hsm_test.on_event(&a);
    EXPECT_EQ("s1-A", g_trace.pop());
    EXPECT_EQ("s11-EXIT", g_trace.pop());
    EXPECT_EQ("s1-EXIT", g_trace.pop());
    EXPECT_EQ("s1-ENTRY", g_trace.pop());
    EXPECT_EQ("s1-INIT", g_trace.pop());
    EXPECT_EQ("s11-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-B
    hsm_test.on_event(&b);
    EXPECT_EQ("s1-B", g_trace.pop());
    EXPECT_EQ("s11-EXIT", g_trace.pop());
    EXPECT_EQ("s11-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-C
    hsm_test.on_event(&c);
    EXPECT_EQ("s1-C", g_trace.pop());
    EXPECT_EQ("s11-EXIT", g_trace.pop());
    EXPECT_EQ("s1-EXIT", g_trace.pop());
    EXPECT_EQ("s2-ENTRY", g_trace.pop());
    EXPECT_EQ("s2-INIT", g_trace.pop());
    EXPECT_EQ("s21-ENTRY", g_trace.pop());
    EXPECT_EQ("s21-INIT", g_trace.pop());
    EXPECT_EQ("s211-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S211, hsm_test.state());

    // s211-C
    hsm_test.on_event(&c);
    EXPECT_EQ("s2-C", g_trace.pop());
    EXPECT_EQ("s211-EXIT", g_trace.pop());
    EXPECT_EQ("s21-EXIT", g_trace.pop());
    EXPECT_EQ("s2-EXIT", g_trace.pop());
    EXPECT_EQ("s1-ENTRY", g_trace.pop());
    EXPECT_EQ("s1-INIT", g_trace.pop());
    EXPECT_EQ("s11-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-D
    hsm_test.on_event(&d);
    EXPECT_EQ("s1-D", g_trace.pop());
    EXPECT_EQ("s11-EXIT", g_trace.pop());
    EXPECT_EQ("s1-EXIT", g_trace.pop());
    EXPECT_EQ("top-INIT", g_trace.pop());
    EXPECT_EQ("s1-ENTRY", g_trace.pop());
    EXPECT_EQ("s1-INIT", g_trace.pop());
    EXPECT_EQ("s11-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-E
    hsm_test.on_event(&e);
    EXPECT_EQ("top-E", g_trace.pop());
    EXPECT_EQ("s11-EXIT", g_trace.pop());
    EXPECT_EQ("s1-EXIT", g_trace.pop());
    EXPECT_EQ("s2-ENTRY", g_trace.pop());
    EXPECT_EQ("s21-ENTRY", g_trace.pop());
    EXPECT_EQ("s211-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S211, hsm_test.state());

    // s211-D
    hsm_test.on_event(&d);
    EXPECT_EQ("s211-D", g_trace.pop());
    EXPECT_EQ("s211-EXIT", g_trace.pop());
    EXPECT_EQ("s21-INIT", g_trace.pop());
    EXPECT_EQ("s211-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S211, hsm_test.state());

    // s211-F
    hsm_test.on_event(&f);
    EXPECT_EQ("s2-F", g_trace.pop());
    EXPECT_EQ("s211-EXIT", g_trace.pop());
    EXPECT_EQ("s21-EXIT", g_trace.pop());
    EXPECT_EQ("s2-EXIT", g_trace.pop());
    EXPECT_EQ("s1-ENTRY", g_trace.pop());
    EXPECT_EQ("s11-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-F
    hsm_test.on_event(&e);
    EXPECT_EQ("top-E", g_trace.pop());
    EXPECT_EQ("s11-EXIT", g_trace.pop());
    EXPECT_EQ("s1-EXIT", g_trace.pop());
    EXPECT_EQ("s2-ENTRY", g_trace.pop());
    EXPECT_EQ("s21-ENTRY", g_trace.pop());
    EXPECT_EQ("s211-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S211, hsm_test.state());

    // s211-G
    hsm_test.on_event(&g);
    EXPECT_EQ("s211-G", g_trace.pop());
    EXPECT_EQ("s211-EXIT", g_trace.pop());
    EXPECT_EQ("s21-EXIT", g_trace.pop());
    EXPECT_EQ("s2-EXIT", g_trace.pop());
    EXPECT_EQ("top-INIT", g_trace.pop());
    EXPECT_EQ("s1-ENTRY", g_trace.pop());
    EXPECT_EQ("s1-INIT", g_trace.pop());
    EXPECT_EQ("s11-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-G
    hsm_test.on_event(&g);
    EXPECT_EQ("s11-G", g_trace.pop());
    EXPECT_EQ("s11-EXIT", g_trace.pop());
    EXPECT_EQ("s1-EXIT", g_trace.pop());
    EXPECT_EQ("s2-ENTRY", g_trace.pop());
    EXPECT_EQ("s21-ENTRY", g_trace.pop());
    EXPECT_EQ("s211-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S211, hsm_test.state());

    // s211-H
    EXPECT_EQ(0, hsm_test.my_foo());
    hsm_test.on_event(&h);
    EXPECT_EQ("s21-H", g_trace.pop());
    EXPECT_EQ(1, hsm_test.my_foo());
    EXPECT_EQ("s211-EXIT", g_trace.pop());
    EXPECT_EQ("s21-EXIT", g_trace.pop());
    EXPECT_EQ("s21-ENTRY", g_trace.pop());
    EXPECT_EQ("s21-INIT", g_trace.pop());
    EXPECT_EQ("s211-ENTRY", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S211, hsm_test.state());

    // transition to s11
    hsm_test.on_event(&g);
    while (!g_trace.empty())
    {
        g_trace.pop();
    }

    // s11-H
    EXPECT_EQ(S11, hsm_test.state());
    EXPECT_EQ(1, hsm_test.my_foo());
    hsm_test.on_event(&h);
    EXPECT_EQ("s11-H", g_trace.pop());
    EXPECT_EQ(0, hsm_test.my_foo());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());
}

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

EventId to_event_id(const Event& event)
{
    return event.id;
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
    Result<Event> top_handler(EventId event_id, Event const* event);
    Result<Event> s1_handler(EventId event_id, Event const* event);
    Result<Event> s11_handler(EventId event_id, Event const* event);
    Result<Event> s2_handler(EventId event_id, Event const* event);
    Result<Event> s21_handler(EventId event_id, Event const* event);
    Result<Event> s211_handler(EventId event_id, Event const* event);
};

enum HsmTestEvents
{
    Event_A,
    Event_B,
    Event_C,
    Event_D,
    Event_E,
    Event_F,
    Event_G,
    Event_H
};

Result<Event> HsmTest::top_handler(EventId event_id, Event const* event)
{
    switch (event_id)
    {
        case Event_Init:
        {
            g_trace("top-Init");
            break;
        }
        case Event_Entry:
        {
            g_trace("top-Entry");
            break;
        }
        case Event_Exit:
        {
            g_trace("top-Exit");
            break;
        }
        case Event_E:
        {
            g_trace("top-E");
            static Transition<Event> transition(*this, m_s211);
            return transition;
        }
        default:
            return Unhandled<Event> {event};
    }
    return Handled<Event> {};
}

Result<Event> HsmTest::s1_handler(EventId event_id, Event const* event)
{
    switch (event_id)
    {
        case Event_Init:
        {
            g_trace("s1-Init");
            break;
        }
        case Event_Entry:
        {
            g_trace("s1-Entry");
            break;
        }
        case Event_Exit:
        {
            g_trace("s1-Exit");
            break;
        }
        case Event_A:
        {
            g_trace("s1-A");
            static Transition<Event> transition(*this, m_s1);
            return transition;
        }
        case Event_B:
        {
            g_trace("s1-B");
            static Transition<Event> transition(*this, m_s11);
            return transition;
        }
        case Event_C:
        {
            g_trace("s1-C");
            static Transition<Event> transition(*this, m_s2);
            return transition;
        }
        case Event_D:
        {
            g_trace("s1-D");
            static Transition<Event> transition(*this, m_top);
            return transition;
        }
        case Event_F:
        {
            g_trace("s1-F");
            static Transition<Event> transition(*this, m_s211);
            return transition;
        }
        default:
            return Unhandled<Event> {event};
    }
    return Handled<Event> {};
}

Result<Event> HsmTest::s11_handler(EventId event_id, Event const* event)
{
    switch (event_id)
    {
        case Event_Entry:
        {
            g_trace("s11-Entry");
            break;
        }
        case Event_Exit:
        {
            g_trace("s11-Exit");
            break;
        }
        case Event_G:
        {
            g_trace("s11-G");
            static Transition<Event> transition(*this, m_s211);
            return transition;
        }
        break;
        case Event_H:
        {
            if (m_my_foo)
            {
                g_trace("s11-H");
                m_my_foo = 0;
            }
            break;
        }
        default:
            return Unhandled<Event> {event};
    }
    return Handled<Event> {};
}

Result<Event> HsmTest::s2_handler(EventId event_id, Event const* event)
{
    switch (event_id)
    {
        case Event_Init:
        {
            g_trace("s2-Init");
            break;
        }
        case Event_Entry:
        {
            g_trace("s2-Entry");
            break;
        }
        case Event_Exit:
        {
            g_trace("s2-Exit");
            break;
        }
        case Event_C:
        {
            g_trace("s2-C");
            static Transition<Event> transition(*this, m_s1);
            return transition;
        }
        case Event_F:
        {
            g_trace("s2-F");
            static Transition<Event> transition(*this, m_s11);
            return transition;
        }
        default:
            return Unhandled<Event> {event};
    }
    return Handled<Event> {};
}

Result<Event> HsmTest::s21_handler(EventId event_id, Event const* event)
{
    switch (event_id)
    {
        case Event_Init:
        {
            g_trace("s21-Init");
            break;
        }
        case Event_Entry:
        {
            g_trace("s21-Entry");
            break;
        }
        case Event_Exit:
        {
            g_trace("s21-Exit");
            break;
        }
        case Event_B:
        {
            g_trace("s21-B");
            static Transition<Event> transition(*this, m_s211);
            return transition;
        }
        case Event_H:
        {
            if (!m_my_foo)
            {
                g_trace("s21-H");
                m_my_foo = 1;
                {
                    static Transition<Event> transition(*this, m_s21);
                    return transition;
                }
            }
            break;
        }
        default:
            return Unhandled<Event> {event};
    }
    return Handled<Event> {};
}

Result<Event> HsmTest::s211_handler(EventId event_id, Event const* event)
{
    switch (event_id)
    {
        case Event_Entry:
        {
            g_trace("s211-Entry");
            break;
        }
        case Event_Exit:
        {
            g_trace("s211-Exit");
            break;
        }
        case Event_D:
        {
            g_trace("s211-D");
            static Transition<Event> transition(*this, m_s21);
            return transition;
        }
        case Event_G:
        {
            g_trace("s211-G");
            static Transition<Event> transition(*this, m_top);
            return transition;
        }
        default:
            return Unhandled<Event> {event};
    }
    return Handled<Event> {};
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
    const Event a {Event_A};
    const Event b {Event_B};
    const Event c {Event_C};
    const Event d {Event_D};
    const Event e {Event_E};
    const Event f {Event_F};
    const Event g {Event_G};
    const Event h {Event_H};
    HsmTest hsm_test;

    // Initial Transitions
    EXPECT_EQ(Top, hsm_test.state());
    hsm_test.on_start();
    EXPECT_EQ("top-Entry", g_trace.pop());
    EXPECT_EQ("top-Init", g_trace.pop());
    EXPECT_EQ("s1-Entry", g_trace.pop());
    EXPECT_EQ("s1-Init", g_trace.pop());
    EXPECT_EQ("s11-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-A
    hsm_test.on_event(&a);
    EXPECT_EQ("s1-A", g_trace.pop());
    EXPECT_EQ("s11-Exit", g_trace.pop());
    EXPECT_EQ("s1-Exit", g_trace.pop());
    EXPECT_EQ("s1-Entry", g_trace.pop());
    EXPECT_EQ("s1-Init", g_trace.pop());
    EXPECT_EQ("s11-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-B
    hsm_test.on_event(&b);
    EXPECT_EQ("s1-B", g_trace.pop());
    EXPECT_EQ("s11-Exit", g_trace.pop());
    EXPECT_EQ("s11-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-C
    hsm_test.on_event(&c);
    EXPECT_EQ("s1-C", g_trace.pop());
    EXPECT_EQ("s11-Exit", g_trace.pop());
    EXPECT_EQ("s1-Exit", g_trace.pop());
    EXPECT_EQ("s2-Entry", g_trace.pop());
    EXPECT_EQ("s2-Init", g_trace.pop());
    EXPECT_EQ("s21-Entry", g_trace.pop());
    EXPECT_EQ("s21-Init", g_trace.pop());
    EXPECT_EQ("s211-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S211, hsm_test.state());

    // s211-C
    hsm_test.on_event(&c);
    EXPECT_EQ("s2-C", g_trace.pop());
    EXPECT_EQ("s211-Exit", g_trace.pop());
    EXPECT_EQ("s21-Exit", g_trace.pop());
    EXPECT_EQ("s2-Exit", g_trace.pop());
    EXPECT_EQ("s1-Entry", g_trace.pop());
    EXPECT_EQ("s1-Init", g_trace.pop());
    EXPECT_EQ("s11-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-D
    hsm_test.on_event(&d);
    EXPECT_EQ("s1-D", g_trace.pop());
    EXPECT_EQ("s11-Exit", g_trace.pop());
    EXPECT_EQ("s1-Exit", g_trace.pop());
    EXPECT_EQ("top-Init", g_trace.pop());
    EXPECT_EQ("s1-Entry", g_trace.pop());
    EXPECT_EQ("s1-Init", g_trace.pop());
    EXPECT_EQ("s11-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-E
    hsm_test.on_event(&e);
    EXPECT_EQ("top-E", g_trace.pop());
    EXPECT_EQ("s11-Exit", g_trace.pop());
    EXPECT_EQ("s1-Exit", g_trace.pop());
    EXPECT_EQ("s2-Entry", g_trace.pop());
    EXPECT_EQ("s21-Entry", g_trace.pop());
    EXPECT_EQ("s211-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S211, hsm_test.state());

    // s211-D
    hsm_test.on_event(&d);
    EXPECT_EQ("s211-D", g_trace.pop());
    EXPECT_EQ("s211-Exit", g_trace.pop());
    EXPECT_EQ("s21-Init", g_trace.pop());
    EXPECT_EQ("s211-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S211, hsm_test.state());

    // s211-F
    hsm_test.on_event(&f);
    EXPECT_EQ("s2-F", g_trace.pop());
    EXPECT_EQ("s211-Exit", g_trace.pop());
    EXPECT_EQ("s21-Exit", g_trace.pop());
    EXPECT_EQ("s2-Exit", g_trace.pop());
    EXPECT_EQ("s1-Entry", g_trace.pop());
    EXPECT_EQ("s11-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-F
    hsm_test.on_event(&e);
    EXPECT_EQ("top-E", g_trace.pop());
    EXPECT_EQ("s11-Exit", g_trace.pop());
    EXPECT_EQ("s1-Exit", g_trace.pop());
    EXPECT_EQ("s2-Entry", g_trace.pop());
    EXPECT_EQ("s21-Entry", g_trace.pop());
    EXPECT_EQ("s211-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S211, hsm_test.state());

    // s211-G
    hsm_test.on_event(&g);
    EXPECT_EQ("s211-G", g_trace.pop());
    EXPECT_EQ("s211-Exit", g_trace.pop());
    EXPECT_EQ("s21-Exit", g_trace.pop());
    EXPECT_EQ("s2-Exit", g_trace.pop());
    EXPECT_EQ("top-Init", g_trace.pop());
    EXPECT_EQ("s1-Entry", g_trace.pop());
    EXPECT_EQ("s1-Init", g_trace.pop());
    EXPECT_EQ("s11-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S11, hsm_test.state());

    // s11-G
    hsm_test.on_event(&g);
    EXPECT_EQ("s11-G", g_trace.pop());
    EXPECT_EQ("s11-Exit", g_trace.pop());
    EXPECT_EQ("s1-Exit", g_trace.pop());
    EXPECT_EQ("s2-Entry", g_trace.pop());
    EXPECT_EQ("s21-Entry", g_trace.pop());
    EXPECT_EQ("s211-Entry", g_trace.pop());
    EXPECT_EQ(true, g_trace.empty());
    EXPECT_EQ(S211, hsm_test.state());

    // s211-H
    EXPECT_EQ(0, hsm_test.my_foo());
    hsm_test.on_event(&h);
    EXPECT_EQ("s21-H", g_trace.pop());
    EXPECT_EQ(1, hsm_test.my_foo());
    EXPECT_EQ("s211-Exit", g_trace.pop());
    EXPECT_EQ("s21-Exit", g_trace.pop());
    EXPECT_EQ("s21-Entry", g_trace.pop());
    EXPECT_EQ("s21-Init", g_trace.pop());
    EXPECT_EQ("s211-Entry", g_trace.pop());
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

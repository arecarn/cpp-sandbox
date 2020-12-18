#include "hierarchical_state_machine.hpp"
#include <cstdio>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <string>

class Actions
{
public:
    virtual void top_init() = 0;
    virtual void top_entry() = 0;
    virtual void top_exit() = 0;
    virtual void top_e() = 0;

    virtual void s1_init() = 0;
    virtual void s1_entry() = 0;
    virtual void s1_exit() = 0;
    virtual void s1_a() = 0;
    virtual void s1_b() = 0;
    virtual void s1_c() = 0;
    virtual void s1_d() = 0;
    virtual void s1_f() = 0;

    virtual void s11_entry() = 0;
    virtual void s11_exit() = 0;
    virtual void s11_g() = 0;
    virtual void s11_h() = 0;

    virtual void s2_init() = 0;
    virtual void s2_entry() = 0;
    virtual void s2_exit() = 0;
    virtual void s2_c() = 0;
    virtual void s2_f() = 0;

    virtual void s21_init() = 0;
    virtual void s21_entry() = 0;
    virtual void s21_exit() = 0;
    virtual void s21_b() = 0;
    virtual void s21_h() = 0;

    virtual void s211_entry() = 0;
    virtual void s211_exit() = 0;
    virtual void s211_d() = 0;
    virtual void s211_g() = 0;
    virtual ~Actions() = default;
};

class MockActions : public Actions
{
public:
    MOCK_METHOD(void, top_init, (), (override));
    MOCK_METHOD(void, top_entry, (), (override));
    MOCK_METHOD(void, top_exit, (), (override));
    MOCK_METHOD(void, top_e, (), (override));
    MOCK_METHOD(void, s1_init, (), (override));
    MOCK_METHOD(void, s1_entry, (), (override));
    MOCK_METHOD(void, s1_exit, (), (override));
    MOCK_METHOD(void, s1_a, (), (override));
    MOCK_METHOD(void, s1_b, (), (override));
    MOCK_METHOD(void, s1_c, (), (override));
    MOCK_METHOD(void, s1_d, (), (override));
    MOCK_METHOD(void, s1_f, (), (override));
    MOCK_METHOD(void, s11_entry, (), (override));
    MOCK_METHOD(void, s11_exit, (), (override));
    MOCK_METHOD(void, s11_g, (), (override));
    MOCK_METHOD(void, s11_h, (), (override));
    MOCK_METHOD(void, s2_init, (), (override));
    MOCK_METHOD(void, s2_entry, (), (override));
    MOCK_METHOD(void, s2_exit, (), (override));
    MOCK_METHOD(void, s2_c, (), (override));
    MOCK_METHOD(void, s2_f, (), (override));
    MOCK_METHOD(void, s21_init, (), (override));
    MOCK_METHOD(void, s21_entry, (), (override));
    MOCK_METHOD(void, s21_exit, (), (override));
    MOCK_METHOD(void, s21_b, (), (override));
    MOCK_METHOD(void, s21_h, (), (override));
    MOCK_METHOD(void, s211_entry, (), (override));
    MOCK_METHOD(void, s211_exit, (), (override));
    MOCK_METHOD(void, s211_d, (), (override));
    MOCK_METHOD(void, s211_g, (), (override));
};

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
    Actions& m_actions;

public:
    HsmTest(Actions& actions);
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
            m_actions.top_init();
            break;
        }
        case Event_Entry:
        {
            m_actions.top_entry();
            break;
        }
        case Event_Exit:
        {
            m_actions.top_exit();
            break;
        }
        case Event_E:
        {
            m_actions.top_e();
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
            m_actions.s1_init();
            break;
        }
        case Event_Entry:
        {
            m_actions.s1_entry();
            break;
        }
        case Event_Exit:
        {
            m_actions.s1_exit();
            break;
        }
        case Event_A:
        {
            m_actions.s1_a();
            static Transition<Event> transition(*this, m_s1);
            return transition;
        }
        case Event_B:
        {
            m_actions.s1_b();
            static Transition<Event> transition(*this, m_s11);
            return transition;
        }
        case Event_C:
        {
            m_actions.s1_c();
            static Transition<Event> transition(*this, m_s2);
            return transition;
        }
        case Event_D:
        {
            m_actions.s1_d();
            static Transition<Event> transition(*this, m_top);
            return transition;
        }
        case Event_F:
        {
            m_actions.s1_f();
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
            m_actions.s11_entry();
            break;
        }
        case Event_Exit:
        {
            m_actions.s11_exit();
            break;
        }
        case Event_G:
        {
            m_actions.s11_g();
            static Transition<Event> transition(*this, m_s211);
            return transition;
        }
        break;
        case Event_H:
        {
            if (m_my_foo)
            {
                m_actions.s11_h();
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
            m_actions.s2_init();
            break;
        }
        case Event_Entry:
        {
            m_actions.s2_entry();
            break;
        }
        case Event_Exit:
        {
            m_actions.s2_exit();
            break;
        }
        case Event_C:
        {
            m_actions.s2_c();
            static Transition<Event> transition(*this, m_s1);
            return transition;
        }
        case Event_F:
        {
            m_actions.s2_f();
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
            m_actions.s21_init();
            break;
        }
        case Event_Entry:
        {
            m_actions.s21_entry();
            break;
        }
        case Event_Exit:
        {
            m_actions.s21_exit();
            break;
        }
        case Event_B:
        {
            m_actions.s21_b();
            break;
            static Transition<Event> transition(*this, m_s211);
            return transition;
        }
        case Event_H:
        {
            if (!m_my_foo)
            {
                m_actions.s21_h();
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
            m_actions.s211_entry();
            break;
        }
        case Event_Exit:
        {
            m_actions.s211_exit();
            break;
        }
        case Event_D:
        {
            m_actions.s211_d();
            static Transition<Event> transition(*this, m_s21);
            return transition;
        }
        case Event_G:
        {
            m_actions.s211_g();
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

HsmTest::HsmTest(Actions& actions)
    : Hsm {Top, static_cast<EventHandler<Event>>(&HsmTest::top_handler), &m_s1}
    , m_s1 {S1, &m_top, static_cast<EventHandler<Event>>(&HsmTest::s1_handler), &m_s11}
    , m_s11 {S11, &m_s1, static_cast<EventHandler<Event>>(&HsmTest::s11_handler)}
    , m_s2 {S2, &m_top, static_cast<EventHandler<Event>>(&HsmTest::s2_handler), &m_s21}
    , m_s21 {S21, &m_s2, static_cast<EventHandler<Event>>(&HsmTest::s21_handler), &m_s211}
    , m_s211 {S211, &m_s21, static_cast<EventHandler<Event>>(&HsmTest::s211_handler)}
    , m_actions {actions}
{
}

TEST(HsmTestFixture, t) // NOLINT(readability-function-size)
{
    [[maybe_unused]] const Event a {Event_A};
    [[maybe_unused]] const Event b {Event_B};
    [[maybe_unused]] const Event c {Event_C};
    [[maybe_unused]] const Event d {Event_D};
    [[maybe_unused]] const Event e {Event_E};
    [[maybe_unused]] const Event f {Event_F};
    [[maybe_unused]] const Event g {Event_G};
    [[maybe_unused]] const Event h {Event_H};
    MockActions actions {};
    HsmTest hsm_test(actions);

    // Initial Transitions
    EXPECT_EQ(Top, hsm_test.state());
    EXPECT_CALL(actions, top_entry());
    EXPECT_CALL(actions, top_init());
    EXPECT_CALL(actions, s1_entry());
    EXPECT_CALL(actions, s1_init());
    EXPECT_CALL(actions, s11_entry());
    hsm_test.on_start();
    EXPECT_EQ(S11, hsm_test.state());

    // s11-A
    EXPECT_CALL(actions, s1_a());
    EXPECT_CALL(actions, s11_exit());
    EXPECT_CALL(actions, s1_exit());
    EXPECT_CALL(actions, s1_entry());
    EXPECT_CALL(actions, s1_init());
    EXPECT_CALL(actions, s11_entry());
    hsm_test.on_event(&a);
    EXPECT_EQ(S11, hsm_test.state());

    // s11-B
    EXPECT_CALL(actions, s1_b());
    EXPECT_CALL(actions, s11_exit());
    EXPECT_CALL(actions, s11_entry());
    hsm_test.on_event(&b);
    EXPECT_EQ(S11, hsm_test.state());

    // s11-C
    EXPECT_CALL(actions, s1_c());
    EXPECT_CALL(actions, s11_exit());
    EXPECT_CALL(actions, s1_exit());
    EXPECT_CALL(actions, s2_entry());
    EXPECT_CALL(actions, s2_init());
    EXPECT_CALL(actions, s21_entry());
    EXPECT_CALL(actions, s21_init());
    EXPECT_CALL(actions, s211_entry());
    hsm_test.on_event(&c);
    EXPECT_EQ(S211, hsm_test.state());

    // s211-C
    EXPECT_CALL(actions, s2_c());
    EXPECT_CALL(actions, s211_exit());
    EXPECT_CALL(actions, s21_exit());
    EXPECT_CALL(actions, s2_exit());
    EXPECT_CALL(actions, s1_entry());
    EXPECT_CALL(actions, s1_init());
    EXPECT_CALL(actions, s11_entry());
    hsm_test.on_event(&c);
    EXPECT_EQ(S11, hsm_test.state());

    // s11-D
    EXPECT_CALL(actions, s1_d());
    EXPECT_CALL(actions, s11_exit());
    EXPECT_CALL(actions, s1_exit());
    EXPECT_CALL(actions, top_init());
    EXPECT_CALL(actions, s1_entry());
    EXPECT_CALL(actions, s1_init());
    EXPECT_CALL(actions, s11_entry());
    hsm_test.on_event(&d);
    EXPECT_EQ(S11, hsm_test.state());

    // s11-E
    EXPECT_CALL(actions, top_e());
    EXPECT_CALL(actions, s11_exit());
    EXPECT_CALL(actions, s1_exit());
    EXPECT_CALL(actions, s2_entry());
    EXPECT_CALL(actions, s21_entry());
    EXPECT_CALL(actions, s211_entry());
    hsm_test.on_event(&e);
    EXPECT_EQ(S211, hsm_test.state());

    // s211-D
    EXPECT_CALL(actions, s211_d());
    EXPECT_CALL(actions, s211_exit());
    EXPECT_CALL(actions, s21_init());
    EXPECT_CALL(actions, s211_entry());
    hsm_test.on_event(&d);
    EXPECT_EQ(S211, hsm_test.state());

    // s211-F
    EXPECT_CALL(actions, s2_f());
    EXPECT_CALL(actions, s211_exit());
    EXPECT_CALL(actions, s21_exit());
    EXPECT_CALL(actions, s2_exit());
    EXPECT_CALL(actions, s1_entry());
    EXPECT_CALL(actions, s11_entry());
    hsm_test.on_event(&f);
    EXPECT_EQ(S11, hsm_test.state());

    // s11-F
    EXPECT_CALL(actions, top_e());
    EXPECT_CALL(actions, s11_exit());
    EXPECT_CALL(actions, s1_exit());
    EXPECT_CALL(actions, s2_entry());
    EXPECT_CALL(actions, s21_entry());
    EXPECT_CALL(actions, s211_entry());
    hsm_test.on_event(&e);
    EXPECT_EQ(S211, hsm_test.state());

    // s211-G
    EXPECT_CALL(actions, s211_g());
    EXPECT_CALL(actions, s211_exit());
    EXPECT_CALL(actions, s21_exit());
    EXPECT_CALL(actions, s2_exit());
    EXPECT_CALL(actions, top_init());
    EXPECT_CALL(actions, s1_entry());
    EXPECT_CALL(actions, s1_init());
    EXPECT_CALL(actions, s11_entry());
    hsm_test.on_event(&g);
    EXPECT_EQ(S11, hsm_test.state());

    // s11-G
    EXPECT_CALL(actions, s11_g());
    EXPECT_CALL(actions, s11_exit());
    EXPECT_CALL(actions, s1_exit());
    EXPECT_CALL(actions, s2_entry());
    EXPECT_CALL(actions, s21_entry());
    EXPECT_CALL(actions, s211_entry());
    hsm_test.on_event(&g);
    EXPECT_EQ(S211, hsm_test.state());

    // s211-H
    EXPECT_CALL(actions, s211_exit());
    EXPECT_CALL(actions, s21_exit());
    EXPECT_CALL(actions, s21_entry());
    EXPECT_CALL(actions, s21_init());
    EXPECT_CALL(actions, s211_entry());
    EXPECT_EQ(0, hsm_test.my_foo());
    EXPECT_CALL(actions, s21_h());
    hsm_test.on_event(&h);
    EXPECT_EQ(1, hsm_test.my_foo());
    EXPECT_EQ(S211, hsm_test.state());

    // s211-G
    EXPECT_CALL(actions, s211_g());
    EXPECT_CALL(actions, s211_exit());
    EXPECT_CALL(actions, s21_exit());
    EXPECT_CALL(actions, s2_exit());
    EXPECT_CALL(actions, top_init());
    EXPECT_CALL(actions, s1_entry());
    EXPECT_CALL(actions, s1_init());
    EXPECT_CALL(actions, s11_entry());
    hsm_test.on_event(&g);
    EXPECT_EQ(S11, hsm_test.state());

    // s11-H
    EXPECT_EQ(S11, hsm_test.state());
    EXPECT_EQ(1, hsm_test.my_foo());
    EXPECT_CALL(actions, s11_h());
    hsm_test.on_event(&h);
    EXPECT_EQ(0, hsm_test.my_foo());
    EXPECT_EQ(S11, hsm_test.state());
}

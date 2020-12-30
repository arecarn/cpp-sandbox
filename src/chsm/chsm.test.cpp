#include "chsm.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

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
    State<Event> m_top_state;
    State<Event> m_s1_state;
    State<Event> m_s11_state;
    State<Event> m_s2_state;
    State<Event> m_s21_state;
    State<Event> m_s211_state;
    Actions& m_actions;

public:
    explicit HsmTest(Actions& actions);
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

Result<Event> HsmTest::top_handler(EventId event_id, Event const* /*unused*/)
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
            return Result<Event> {Transition<Event> {m_s211_state}};
        }
        default:
            return Result<Event> {Unhandled {}};
    }
    return Result<Event> {Handled {}};
}

Result<Event> HsmTest::s1_handler(EventId event_id, Event const* /*unused*/)
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
            return Result<Event> {Transition<Event> {m_s1_state}};
        }
        case Event_B:
        {
            m_actions.s1_b();
            return Result<Event> {Transition<Event> {m_s11_state}};
        }
        case Event_C:
        {
            m_actions.s1_c();
            return Result<Event> {Transition<Event> {m_s2_state}};
        }
        case Event_D:
        {
            m_actions.s1_d();
            return Result<Event> {Transition<Event> {m_top_state}};
        }
        case Event_F:
        {
            m_actions.s1_f();
            return Result<Event> {Transition<Event> {m_s211_state}};
        }
        default:
            return Result<Event> {Unhandled {}};
    }
    return Result<Event> {Handled {}};
}

Result<Event> HsmTest::s11_handler(EventId event_id, Event const* /*unused*/)
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
            return Result<Event> {Transition<Event> {m_s211_state}};
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
            return Result<Event> {Unhandled {}};
    }
    return Result<Event> {Handled {}};
}

Result<Event> HsmTest::s2_handler(EventId event_id, Event const* /*unused*/)
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
            return Result<Event> {Transition<Event> {m_s1_state}};
        }
        case Event_F:
        {
            m_actions.s2_f();
            return Result<Event> {Transition<Event> {m_s11_state}};
        }
        default:
            return Result<Event> {Unhandled {}};
    }
    return Result<Event> {Handled {}};
}

Result<Event> HsmTest::s21_handler(EventId event_id, Event const* /*event*/)
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
            return Result<Event> {Transition<Event> {m_s211_state}};
        }
        case Event_H:
        {
            if (!m_my_foo)
            {
                m_actions.s21_h();
                m_my_foo = 1;
                {
                    return Result<Event> {Transition<Event> {m_s21_state}};
                }
            }
            break;
        }
        default:
            return Result<Event> {Unhandled {}};
    }
    return Result<Event> {Handled {}};
}

Result<Event> HsmTest::s211_handler(EventId event_id, Event const* /*event*/)
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
            return Result<Event> {Transition<Event> {m_s21_state}};
        }
        case Event_G:
        {
            m_actions.s211_g();
            return Result<Event> {Transition<Event> {m_top_state}};
        }
        default:
            return Result<Event> {Unhandled {}};
    }
    return Result<Event> {Handled {}};
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
    : Hsm {m_top_state}
    , m_top_state {Top, nullptr, static_cast<EventHandler<Event>>(&HsmTest::top_handler), &m_s1_state}
    , m_s1_state {S1, &m_top_state, static_cast<EventHandler<Event>>(&HsmTest::s1_handler), &m_s11_state}
    , m_s11_state {S11, &m_s1_state, static_cast<EventHandler<Event>>(&HsmTest::s11_handler)}
    , m_s2_state {S2, &m_top_state, static_cast<EventHandler<Event>>(&HsmTest::s2_handler), &m_s21_state}
    , m_s21_state {S21, &m_s2_state, static_cast<EventHandler<Event>>(&HsmTest::s21_handler), &m_s211_state}
    , m_s211_state {S211, &m_s21_state, static_cast<EventHandler<Event>>(&HsmTest::s211_handler)}
    , m_actions {actions}
{
}

constexpr Event A {Event_A};
constexpr Event B {Event_B};
constexpr Event C {Event_C};
constexpr Event D {Event_D};
constexpr Event E {Event_E};
constexpr Event F {Event_F};
constexpr Event G {Event_G};
constexpr Event H {Event_H};

class HsmTestFixtureS11 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_hsm_test = std::make_unique<HsmTest>(m_actions);

        // Initial Transitions
        EXPECT_EQ(Top, m_hsm_test->state());
        EXPECT_CALL(m_actions, top_entry());
        EXPECT_CALL(m_actions, top_init());
        EXPECT_CALL(m_actions, s1_entry());
        EXPECT_CALL(m_actions, s1_init());
        EXPECT_CALL(m_actions, s11_entry());
        m_hsm_test->on_start();
        EXPECT_EQ(S11, m_hsm_test->state());
    }

    testing::StrictMock<MockActions> m_actions;
    std::unique_ptr<HsmTest> m_hsm_test;
};

TEST_F(HsmTestFixtureS11, s11_A)
{
    EXPECT_CALL(m_actions, s1_a());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->on_event(&A);
    EXPECT_EQ(S11, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS11, s11_B)
{
    EXPECT_CALL(m_actions, s1_b());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->on_event(&B);
    EXPECT_EQ(S11, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS11, s11_C)
{
    EXPECT_CALL(m_actions, s1_c());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s2_entry());
    EXPECT_CALL(m_actions, s2_init());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->on_event(&C);
    EXPECT_EQ(S211, m_hsm_test->state());
}
TEST_F(HsmTestFixtureS11, s11_D)
{
    EXPECT_CALL(m_actions, s1_d());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, top_init());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->on_event(&D);
    EXPECT_EQ(S11, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS11, s11_E)
{
    EXPECT_CALL(m_actions, top_e());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s2_entry());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->on_event(&E);
    EXPECT_EQ(S211, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS11, s11_F)
{
    EXPECT_CALL(m_actions, s1_f());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s2_entry());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->on_event(&F);
    EXPECT_EQ(S211, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS11, s11_G)
{
    EXPECT_CALL(m_actions, s11_g());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s2_entry());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->on_event(&G);
    EXPECT_EQ(S211, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS11, s11_H)
{
    EXPECT_EQ(S11, m_hsm_test->state());
    EXPECT_EQ(0, m_hsm_test->my_foo());
    m_hsm_test->on_event(&H);
    EXPECT_EQ(0, m_hsm_test->my_foo());
    EXPECT_EQ(S11, m_hsm_test->state());
}

class HsmTestFixtureS211 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_hsm_test = std::make_unique<HsmTest>(m_actions);

        // Initial Transitions
        EXPECT_EQ(Top, m_hsm_test->state());
        EXPECT_CALL(m_actions, top_entry());
        EXPECT_CALL(m_actions, top_init());
        EXPECT_CALL(m_actions, s1_entry());
        EXPECT_CALL(m_actions, s1_init());
        EXPECT_CALL(m_actions, s11_entry());
        m_hsm_test->on_start();
        EXPECT_EQ(S11, m_hsm_test->state());

        // s1-C
        EXPECT_CALL(m_actions, s1_c());
        EXPECT_CALL(m_actions, s11_exit());
        EXPECT_CALL(m_actions, s1_exit());
        EXPECT_CALL(m_actions, s2_entry());
        EXPECT_CALL(m_actions, s2_init());
        EXPECT_CALL(m_actions, s21_entry());
        EXPECT_CALL(m_actions, s21_init());
        EXPECT_CALL(m_actions, s211_entry());
        m_hsm_test->on_event(&C);
        EXPECT_EQ(S211, m_hsm_test->state());
    }

    // void TearDown() override {}
    testing::StrictMock<MockActions> m_actions;
    std::unique_ptr<HsmTest> m_hsm_test;
};

TEST_F(HsmTestFixtureS211, s211_A)
{
    m_hsm_test->on_event(&A);
    EXPECT_EQ(S211, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS211, s211_B)
{
    EXPECT_CALL(m_actions, s21_b());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->on_event(&B);
    EXPECT_EQ(S211, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS211, s211_C)
{
    EXPECT_CALL(m_actions, s2_c());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->on_event(&C);
    EXPECT_EQ(S11, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS211, s211_D)
{
    EXPECT_CALL(m_actions, s211_d());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->on_event(&D);
    EXPECT_EQ(S211, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS211, s211_F)
{
    EXPECT_CALL(m_actions, s2_f());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->on_event(&F);
    EXPECT_EQ(S11, m_hsm_test->state());
}
TEST_F(HsmTestFixtureS211, s211_G)
{
    EXPECT_CALL(m_actions, s211_g());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, top_init());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->on_event(&G);
    EXPECT_EQ(S11, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS211, s211_H)
{
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    EXPECT_EQ(0, m_hsm_test->my_foo());
    EXPECT_CALL(m_actions, s21_h());
    m_hsm_test->on_event(&H);
    EXPECT_EQ(1, m_hsm_test->my_foo());
    EXPECT_EQ(S211, m_hsm_test->state());
}

TEST_F(HsmTestFixtureS211, my_foo)
{
    // set my_foo = 1
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    EXPECT_EQ(0, m_hsm_test->my_foo());
    EXPECT_CALL(m_actions, s21_h());
    m_hsm_test->on_event(&H);
    EXPECT_EQ(1, m_hsm_test->my_foo());
    EXPECT_EQ(S211, m_hsm_test->state());

    // transition to s11
    EXPECT_CALL(m_actions, s211_g());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, top_init());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->on_event(&G);

    // my_foo set to 0
    EXPECT_EQ(S11, m_hsm_test->state());
    EXPECT_EQ(1, m_hsm_test->my_foo());
    EXPECT_CALL(m_actions, s11_h());
    m_hsm_test->on_event(&H);
    EXPECT_EQ(0, m_hsm_test->my_foo());
    EXPECT_EQ(S11, m_hsm_test->state());
}

#include "chsm.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

class TopState;
class S1State;
class S11State;
class S2State;
class S21State;
class S211State;

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

enum TestHsmEvents : int
{
    Event_A,
    Event_B,
    Event_C,
    Event_D,
    Event_E,
    Event_F,
    Event_G,
    Event_H,
    Event_Invalid,
};

struct Event
{
    int id;
};

class TestHsm : public Hsm
{
    int m_foo {0};
    Event m_event {Event_Invalid};

protected:
    Actions& m_actions;

    TopState m_top_state;
    S1State m_s1_state;
    S11State m_s11_state;
    S2State m_s2_state;
    S21State m_s21_state;
    S211State m_s211_state;

public:
    friend TopState;
    friend S1State;
    friend S11State;
    friend S2State;
    friend S21State;
    friend S211State;

    explicit TestHsm(

        Actions actions);

    void dispatch(Event event)
    {
        m_event = event;
        handle();
    }

    [[nodiscard]] Event event() const { return m_event; }

    [[nodiscard]] int foo() const { return m_foo; }
};

// Top
////////////////////////////////////////////////////////////////////////////////
class TopState : public State
{
public:
    TopState(StateId id,
        TestHsm& hsm,
        InitalState inital_state,
        SuperState super_state = SuperState {})
        : State {id, inital_state, super_state}
        , m_hsm {hsm}
    {
    }

    Result handle() override
    {
        switch (m_hsm.event().id)
        {
            case Event_E:
            {
                m_hsm.m_actions.top_e();
                return Result {Transition {m_hsm.m_s211_state}};
            }
            default:
                return Result {Unhandled {}};
        }
        return Result {Handled {}};
    }

    void init() override { m_hsm.m_actions.top_init(); }

    void entry() override { m_hsm.m_actions.top_entry(); }

    void exit() override { m_hsm.m_actions.top_exit(); }

private:
    TestHsm& m_hsm;
};

// S1
////////////////////////////////////////////////////////////////////////////////
class S1State : public State
{
public:
    S1State(StateId id, InitalState inital_state, TestHsm& hsm,
        SuperState super_state = SuperState {})
        : State {id, inital_state, super_state}
        , m_hsm {hsm}
    {
    }

    Result handle() override
    {
        switch (m_hsm.event().id)
        {
            case Event_A:
            {
                m_hsm.m_actions.s1_a();
                return Result {Transition {m_hsm.m_s1_state}};
            }
            case Event_B:
            {
                m_hsm.m_actions.s1_b();
                return Result {Transition {m_hsm.m_s11_state}};
            }
            case Event_C:
            {
                m_hsm.m_actions.s1_c();
                return Result {Transition {m_hsm.m_s2_state}};
            }
            case Event_D:
            {
                m_hsm.m_actions.s1_d();
                return Result {Transition {m_hsm.m_top_state}};
            }
            case Event_F:
            {
                m_hsm.m_actions.s1_f();
                return Result {Transition {m_hsm.m_s211_state}};
            }
            default:
                return Result {Unhandled {}};
        }
        return Result {Handled {}};
    }

    void init() override { m_hsm.m_actions.s1_init(); }

    void entry() override { m_hsm.m_actions.s1_entry(); }

    void exit() override { m_hsm.m_actions.s1_exit(); }

private:
    TestHsm& m_hsm;
};

// S11
////////////////////////////////////////////////////////////////////////////////
class S11State : public State
{

    S11State(StateId id,
        TestHsm& hsm,
        InitalState inital_state,
        SuperState super_state = SuperState {})
        : State {id, inital_state, super_state}
        , m_hsm {hsm}
    {
    }

    Result handle() override
    {
        switch (m_hsm.event().id)
        {
            case Event_G:
            {
                m_hsm.m_actions.s11_g();
                return Result {Transition {m_hsm.m_s211_state}};
            }
            break;
            case Event_H:
            {
                if (m_hsm.m_foo)
                {
                    m_hsm.m_actions.s11_h();
                    m_hsm.m_foo = 0;
                }
                break;
            }
            default:
                return Result {Unhandled {}};
        }
        return Result {Handled {}};
    }

    void exit() override { m_hsm.m_actions.s11_exit(); }

    void entry() override { m_hsm.m_actions.s11_entry(); }

private:
    TestHsm& m_hsm;
};

// S2
////////////////////////////////////////////////////////////////////////////////
class S2State : public State
{
    S2State(StateId id,
        TestHsm& hsm,
        InitalState inital_state,
        SuperState super_state = SuperState {})
        : State {id, inital_state, super_state}
        , m_hsm {hsm}
    {
    }

    Result handle() override
    {
        switch (m_hsm.event().id)
        {
            case Event_C:
            {
                m_hsm.m_actions.s2_c();
                return Result {Transition {m_hsm.m_s1_state}};
            }
            case Event_F:
            {
                m_hsm.m_actions.s2_f();
                return Result {Transition {m_hsm.m_s11_state}};
            }
            default:
                return Result {Unhandled {}};
        }
        return Result {Handled {}};
    }

    void init() override { m_hsm.m_actions.s2_init(); }

    void entry() override { m_hsm.m_actions.s2_entry(); }

    void exit() override { m_hsm.m_actions.s2_exit(); }

private:
    TestHsm& m_hsm;
};

// S21
////////////////////////////////////////////////////////////////////////////////
class S21State : public State
{
    S21State(StateId id,
        TestHsm& hsm,
        InitalState inital_state,
        SuperState super_state = SuperState {})
        : State {id, inital_state, super_state}
        , m_hsm {hsm}
    {
    }
    Result handle() override
    {
        switch (m_hsm.event().id)
        {
            case Event_B:
            {
                m_hsm.m_actions.s21_b();
                return Result {Transition {m_hsm.m_s211_state}};
            }
            case Event_H:
            {
                if (!m_hsm.m_foo)
                {
                    m_hsm.m_actions.s21_h();
                    m_hsm.m_foo = 1;
                    {
                        return Result {Transition {m_hsm.m_s21_state}};
                    }
                }
                break;
            }
            default:
                return Result {Unhandled {}};
        }
        return Result {Handled {}};
    }

    void init() override { m_hsm.m_actions.s21_init(); }

    void entry() override { m_hsm.m_actions.s21_entry(); }

    void exit() override { m_hsm.m_actions.s21_exit(); }

private:
    TestHsm& m_hsm;
};

// S211
////////////////////////////////////////////////////////////////////////////////
class S211State : public State
{
    S211State(StateId id,
        TestHsm& hsm,
        InitalState inital_state,
        SuperState super_state = SuperState {})
        : State {id, inital_state, super_state}
        , m_hsm {hsm}
    {
    }
    Result handle() override
    {
        switch (m_hsm.event().id)
        {
            case Event_D:
            {
                m_hsm.m_actions.s211_d();
                return Result {Transition {m_hsm.m_s21_state}};
            }
            case Event_G:
            {
                m_hsm.m_actions.s211_g();
                return Result {Transition {m_hsm.m_top_state}};
            }
            default:
                return Result {Unhandled {}};
        }
        return Result {Handled {}};
    }

    void entry() override { m_hsm.m_actions.s211_entry(); }

    void exit() override { m_hsm.m_actions.s211_exit(); }

private:
    TestHsm& m_hsm;
};

enum StateDemoId : StateId
{
    Top_Id,
    S1_Id,
    S11_Id,
    S2_Id,
    S21_Id,
    S211_Id,
};

// clang-format off
TestHsm::TestHsm(Actions& actions)
    : Hsm {InitalState{&m_top_state}}
    , m_top_state {
        Top_Id,
        InitalState{&m_s1_state}
    }
        , m_s1_state {
            S1_Id,
            InitalState{&m_s11_state},
            SuperState{&m_top_state},
        }
            , m_s11_state {
                S11_Id,
                InitalState{},
                SuperState{&m_s1_state},
            }
        , m_s2_state {
            S2_Id,
            InitalState{&m_s21_state},
            SuperState{&m_top_state},
        }
            , m_s21_state {
                S21_Id,
                InitalState{&m_s211_state},
                SuperState{&m_s2_state},
            }
                , m_s211_state {
                    S211_Id,
                    InitalState {},
                    SuperState{&m_s21_state},
                }
    , m_actions {actions}
{
}
// clang-format on

// Test
////////////////////////////////////////////////////////////////////////////////

constexpr Event A {Event_A};
constexpr Event B {Event_B};
constexpr Event C {Event_C};
constexpr Event D {Event_D};
constexpr Event E {Event_E};
constexpr Event F {Event_F};
constexpr Event G {Event_G};
constexpr Event H {Event_H};

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

class TestHsmFixtureS11 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_hsm_test = std::make_unique<TestHsm>(m_actions);

        // Initial Transitions
        EXPECT_EQ(Top_Id, m_hsm_test->state_id());
        EXPECT_CALL(m_actions, top_entry());
        EXPECT_CALL(m_actions, top_init());
        EXPECT_CALL(m_actions, s1_entry());
        EXPECT_CALL(m_actions, s1_init());
        EXPECT_CALL(m_actions, s11_entry());
        m_hsm_test->init();
        EXPECT_EQ(S11_Id, m_hsm_test->state_id());
    }

    testing::StrictMock<MockActions> m_actions;
    std::unique_ptr<TestHsm> m_hsm_test;
};

TEST_F(TestHsmFixtureS11, s11_A)
{
    EXPECT_CALL(m_actions, s1_a());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(A);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS11, s11_B)
{
    EXPECT_CALL(m_actions, s1_b());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(B);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS11, s11_C)
{
    EXPECT_CALL(m_actions, s1_c());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s2_entry());
    EXPECT_CALL(m_actions, s2_init());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(C);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS11, s11_D)
{
    EXPECT_CALL(m_actions, s1_d());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, top_init());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(D);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS11, s11_E)
{
    EXPECT_CALL(m_actions, top_e());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s2_entry());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(E);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS11, s11_F)
{
    EXPECT_CALL(m_actions, s1_f());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s2_entry());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(F);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS11, s11_G)
{
    EXPECT_CALL(m_actions, s11_g());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s2_entry());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(G);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS11, s11_H)
{
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
    EXPECT_EQ(0, m_hsm_test->foo());
    m_hsm_test->dispatch(H);
    EXPECT_EQ(0, m_hsm_test->foo());
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

class TestHsmFixtureS211 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_hsm_test = std::make_unique<TestHsm>(m_actions);

        // Initial Transitions
        EXPECT_EQ(Top_Id, m_hsm_test->state_id());
        EXPECT_CALL(m_actions, top_entry());
        EXPECT_CALL(m_actions, top_init());
        EXPECT_CALL(m_actions, s1_entry());
        EXPECT_CALL(m_actions, s1_init());
        EXPECT_CALL(m_actions, s11_entry());
        m_hsm_test->init();
        EXPECT_EQ(S11_Id, m_hsm_test->state_id());

        // s1-C
        EXPECT_CALL(m_actions, s1_c());
        EXPECT_CALL(m_actions, s11_exit());
        EXPECT_CALL(m_actions, s1_exit());
        EXPECT_CALL(m_actions, s2_entry());
        EXPECT_CALL(m_actions, s2_init());
        EXPECT_CALL(m_actions, s21_entry());
        EXPECT_CALL(m_actions, s21_init());
        EXPECT_CALL(m_actions, s211_entry());
        m_hsm_test->dispatch(C);
        EXPECT_EQ(S211_Id, m_hsm_test->state_id());
    }

    // void TearDown() override {}
    testing::StrictMock<MockActions> m_actions;
    std::unique_ptr<TestHsm> m_hsm_test;
};

TEST_F(TestHsmFixtureS211, s211_A)
{
    m_hsm_test->dispatch(A);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS211, s211_B)
{
    EXPECT_CALL(m_actions, s21_b());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(B);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS211, s211_C)
{
    EXPECT_CALL(m_actions, s2_c());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(C);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS211, s211_D)
{
    EXPECT_CALL(m_actions, s211_d());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(D);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS211, s211_F)
{
    EXPECT_CALL(m_actions, s2_f());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(F);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS211, s211_G)
{
    EXPECT_CALL(m_actions, s211_g());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, top_init());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(G);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS211, s211_H)
{
    EXPECT_EQ(0, m_hsm_test->foo());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    EXPECT_CALL(m_actions, s21_h());
    m_hsm_test->dispatch(H);
    EXPECT_EQ(1, m_hsm_test->foo());
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS211, foo)
{
    // set foo = 1
    EXPECT_EQ(0, m_hsm_test->foo());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    EXPECT_CALL(m_actions, s21_h());
    m_hsm_test->dispatch(H);
    EXPECT_EQ(1, m_hsm_test->foo());
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());

    // transition to s11
    EXPECT_CALL(m_actions, s211_g());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, top_init());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(G);

    // foo set to 0
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
    EXPECT_EQ(1, m_hsm_test->foo());
    EXPECT_CALL(m_actions, s11_h());
    m_hsm_test->dispatch(H);
    EXPECT_EQ(0, m_hsm_test->foo());
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

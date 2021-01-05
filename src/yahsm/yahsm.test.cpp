#include "yahsm.hpp"
#include <cstdio>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// HSM
////////////////////////////////////////////////////////////////////////////////

// Implements the following state machine from Miro Samek's
// Practical Statecharts in C/C++
//
// |-init-----------------------------------------------------|
// |                           s0                             |
// |----------------------------------------------------------|
// |                                                          |
// |    |-init-----------|        |-------------------------| |
// |    |       s1       |---c--->|            s2           | |
// |    |----------------|<--c----|-------------------------| |
// |    |                |        |                         | |
// |<-d-| |-init-------| |        | |-init----------------| | |
// |    | |     s11    |<----f----| |          s21        | | |
// | /--| |------------| |        | |---------------------| | |
// | a  | |            | |        | |                     | | |
// | \->| |            |------g--------->|-init------|    | | |
// |    | |____________| |        | |-b->|    s211   |---g--->|
// |    |----b---^       |------f------->|           |    | | |
// |    |________________|        | |<-d-|___________|<--e----|
// |                              | |_____________________| | |
// |                              |_________________________| |
// |__________________________________________________________|

class Actions
{
public:
    virtual void top_init() = 0;

    virtual void s0_init() = 0;
    virtual void s0_entry() = 0;
    virtual void s0_exit() = 0;
    virtual void s0_e() = 0;

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

class TestHSM;

enum StateId : unsigned int
{
    Top_Id, // 0
    S0_Id, // 1
    S1_Id, // 2
    S11_Id, // 3
    S2_Id, // 4
    S21_Id, // 5
    S211_Id, // 6
};

// clang-format off
//                    <hsm,          id, parent state>
using Top  = CompState<TestHSM,  Top_Id     /*none*/>;
using S0   = CompState<TestHSM,   S0_Id,         Top>;
using S1   = CompState<TestHSM,   S1_Id,          S0>;
using S11  = LeafState<TestHSM,  S11_Id,          S1>;
using S2   = CompState<TestHSM,   S2_Id,          S0>;
using S21  = CompState<TestHSM,  S21_Id,          S2>;
using S211 = LeafState<TestHSM, S211_Id,         S21>;
// clang-format on

enum class Event
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    None,
};

template <>
inline void Top::init(TestHSM& h);

class TestHSM
{
public:
    explicit TestHSM(Actions& actions)
        : m_actions {actions}
    {
    }

    void init()
    {
        // enter initial state
        Top::init(*this);
    }

    void next(const TopState<TestHSM>& state)
    {
        m_state = &state;
    }

    [[nodiscard]] Event event() const
    {
        return m_event;
    }

    void dispatch(Event event)
    {
        m_event = event;
        m_state->handler(*this);
    }

    void foo(int i)
    {
        m_foo = i;
    }

    [[nodiscard]] int foo() const
    {
        return m_foo;
    }

    [[nodiscard]] unsigned int state_id() const
    {
        return m_state->id();
    }

    Actions& actions()
    {
        return m_actions;
    }

private:
    const TopState<TestHSM>* m_state {nullptr};
    Event m_event {Event::None};
    int m_foo;
    Actions& m_actions;
};

// Top
////////////////////////////////////////////////////////////////////////////////
template <>
inline void Top::init(TestHSM& h)
{
    h.foo(0);
    InitalStateSetup<S0> i(h);
    h.actions().top_init();
}

// S0
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename X>
inline void S0::handle(TestHSM& h, const X& x) const
{
    switch (h.event())
    {
        case Event::E:
        {
            Tran<X, This, S211> t(h);
            h.actions().s0_e();
            return;
        }
        default:
            break;
    }
    return Base::handle(h, x);
}

template <>
inline void S0::init(TestHSM& h)
{
    InitalStateSetup<S1> i(h);
    h.actions().s0_init();
}

template <>
inline void S0::entry(TestHSM& h)
{
    h.actions().s0_entry();
}

template <>
inline void S0::exit(TestHSM& h)
{
    h.actions().s0_exit();
}

// S1
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename X>
inline void S1::handle(TestHSM& h, const X& x) const
{
    switch (h.event())
    {
        case Event::A:
        {
            Tran<X, This, S1> t(h);
            h.actions().s1_a();
            return;
        }
        case Event::B:
        {
            Tran<X, This, S11> t(h);
            h.actions().s1_b();
            return;
        }
        case Event::C:
        {
            Tran<X, This, S2> t(h);
            h.actions().s1_c();
            return;
        }
        case Event::D:
        {
            Tran<X, This, S0> t(h);
            h.actions().s1_d();
            return;
        }
        case Event::F:
        {
            Tran<X, This, S211> t(h);
            h.actions().s1_f();
            return;
        }
        default:
            break;
    }
    return Base::handle(h, x);
}

template <>
inline void S1::init(TestHSM& h)
{
    InitalStateSetup<S11> i(h);
    h.actions().s1_init();
}

template <>
inline void S1::entry(TestHSM& h)
{
    h.actions().s1_entry();
}

template <>
inline void S1::exit(TestHSM& h)
{
    h.actions().s1_exit();
}

// S11
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename X>
inline void S11::handle(TestHSM& h, const X& x) const
{
    switch (h.event())
    {
        case Event::G:
        {
            Tran<X, This, S211> t(h);
            h.actions().s11_g();
            return;
        }
        case Event::H:
            if (h.foo())
            {
                h.actions().s11_h();
                h.foo(0);
                return;
            }
            break;
        default:
            break;
    }
    return Base::handle(h, x);
}

template <>
inline void S2::init(TestHSM& h)
{
    InitalStateSetup<S21> i(h);
    h.actions().s2_init();
}

template <>
inline void S11::entry(TestHSM& h)
{
    h.actions().s11_entry();
}

template <>
inline void S11::exit(TestHSM& h)
{
    h.actions().s11_exit();
}

// S2
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename X>
inline void S2::handle(TestHSM& h, const X& x) const
{
    switch (h.event())
    {
        case Event::C:
        {
            Tran<X, This, S1> t(h);
            h.actions().s2_c();
            return;
        }
        case Event::F:
        {
            Tran<X, This, S11> t(h);
            h.actions().s2_f();
            return;
        }
        default:
            break;
    }
    return Base::handle(h, x);
}

template <>
inline void S21::init(TestHSM& h)
{
    InitalStateSetup<S211> i(h);
    h.actions().s21_init();
}

template <>
inline void S2::entry(TestHSM& h)
{
    h.actions().s2_entry();
}

template <>
inline void S2::exit(TestHSM& h)
{
    h.actions().s2_exit();
}

// S21
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename X>
inline void S21::handle(TestHSM& h, const X& x) const
{
    switch (h.event())
    {
        case Event::B:
        {
            Tran<X, This, S211> t(h);
            h.actions().s21_b();
            return;
        }
        case Event::H:
            if (!h.foo())
            {
                Tran<X, This, S21> t(h);
                h.actions().s21_h();
                h.foo(1);
                return;
            }
            break;
        default:
            break;
    }
    return Base::handle(h, x);
}

template <>
inline void S21::entry(TestHSM& h)
{
    h.actions().s21_entry();
}

template <>
inline void S21::exit(TestHSM& h)
{
    h.actions().s21_exit();
}

// S211
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename X>
inline void S211::handle(TestHSM& h, const X& x) const
{
    switch (h.event())
    {
        case Event::D:
        {
            Tran<X, This, S21> t(h);
            h.actions().s211_d();
            return;
        }
        case Event::G:
        {
            Tran<X, This, S0> t(h);
            h.actions().s211_g();
            return;
        }
        default:
            break;
    }
    return Base::handle(h, x);
}

template <>
inline void S211::entry(TestHSM& h)
{
    h.actions().s211_entry();
}

template <>
inline void S211::exit(TestHSM& h)
{
    h.actions().s211_exit();
}

// Test
////////////////////////////////////////////////////////////////////////////////

class MockActions : public Actions
{
public:
    MOCK_METHOD(void, top_init, (), (override));

    MOCK_METHOD(void, s0_init, (), (override));
    MOCK_METHOD(void, s0_entry, (), (override));
    MOCK_METHOD(void, s0_exit, (), (override));
    MOCK_METHOD(void, s0_e, (), (override));

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

class HsmTestFixtureS11 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_hsm_test = std::make_unique<TestHSM>(m_actions);

        // Initial Transitions
        // EXPECT_EQ(S0_Id, m_hsm_test->state_id()); //TODO can't get state
        // before init this might be okay though
        EXPECT_CALL(m_actions, top_init());
        EXPECT_CALL(m_actions, s0_entry());
        EXPECT_CALL(m_actions, s0_init());
        EXPECT_CALL(m_actions, s1_entry());
        EXPECT_CALL(m_actions, s1_init());
        EXPECT_CALL(m_actions, s11_entry());
        m_hsm_test->init();
        EXPECT_EQ(S11_Id, m_hsm_test->state_id());
    }

    testing::StrictMock<MockActions> m_actions;
    std::unique_ptr<TestHSM> m_hsm_test;
};

TEST_F(HsmTestFixtureS11, s11_A)
{
    EXPECT_CALL(m_actions, s1_a());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(Event::A);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(HsmTestFixtureS11, s11_B)
{
    // TODO investigate difference chsm behavior
    EXPECT_CALL(m_actions, s1_b());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(Event::B);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
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
    m_hsm_test->dispatch(Event::C);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(HsmTestFixtureS11, s11_D)
{
    // TODO investigate chsm difference
    EXPECT_CALL(m_actions, s1_d());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s0_exit());
    EXPECT_CALL(m_actions, s0_entry());
    EXPECT_CALL(m_actions, s0_init());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(Event::D);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(HsmTestFixtureS11, s11_E)
{
    EXPECT_CALL(m_actions, s0_e());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s0_exit());
    EXPECT_CALL(m_actions, s0_entry());
    EXPECT_CALL(m_actions, s2_entry());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(Event::E);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(HsmTestFixtureS11, s11_F)
{
    EXPECT_CALL(m_actions, s1_f());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s2_entry());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(Event::F);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(HsmTestFixtureS11, s11_G)
{
    EXPECT_CALL(m_actions, s11_g());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s1_exit());
    EXPECT_CALL(m_actions, s2_entry());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(Event::G);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(HsmTestFixtureS11, s11_H)
{
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
    EXPECT_EQ(0, m_hsm_test->foo());
    m_hsm_test->dispatch(Event::H);
    EXPECT_EQ(0, m_hsm_test->foo());
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

class TestHSMFixtureS211 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_hsm_test = std::make_unique<TestHSM>(m_actions);

        // Initial Transitions
        // EXPECT_EQ(S0_Id, m_hsm_test->state_id()); // TODO can't inspect
        // initial state
        EXPECT_CALL(m_actions, top_init()); // investigate differences with chsm
        EXPECT_CALL(m_actions, s0_entry());
        EXPECT_CALL(m_actions, s0_init());
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
        m_hsm_test->dispatch(Event::C);
        EXPECT_EQ(S211_Id, m_hsm_test->state_id());
    }

    // void TearDown() override {}
    testing::StrictMock<MockActions> m_actions;
    std::unique_ptr<TestHSM> m_hsm_test;
};

TEST_F(TestHSMFixtureS211, s211_A)
{
    m_hsm_test->dispatch(Event::A);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHSMFixtureS211, s211_B)
{
    // TODO different than chsm
    EXPECT_CALL(m_actions, s21_b());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(Event::B);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHSMFixtureS211, s211_C)
{
    EXPECT_CALL(m_actions, s2_c());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(Event::C);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHSMFixtureS211, s211_D)
{
    // TODO different than chsm
    EXPECT_CALL(m_actions, s211_d());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    EXPECT_CALL(m_actions, s21_entry());
    m_hsm_test->dispatch(Event::D);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHSMFixtureS211, s211_F)
{
    EXPECT_CALL(m_actions, s2_f());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(Event::F);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHSMFixtureS211, s211_G)
{
    // TODO different than chsm
    EXPECT_CALL(m_actions, s211_g());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, s0_exit());
    EXPECT_CALL(m_actions, s0_init());
    EXPECT_CALL(m_actions, s0_entry());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(Event::G);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHSMFixtureS211, s211_H)
{
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    EXPECT_EQ(0, m_hsm_test->foo());
    EXPECT_CALL(m_actions, s21_h());
    m_hsm_test->dispatch(Event::H);
    EXPECT_EQ(1, m_hsm_test->foo());
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHSMFixtureS211, foo)
{
    // TODO different than chsm
    // set foo = 1
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    EXPECT_EQ(0, m_hsm_test->foo());
    EXPECT_CALL(m_actions, s21_h());
    m_hsm_test->dispatch(Event::H);
    EXPECT_EQ(1, m_hsm_test->foo());
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());

    // transition to s11
    EXPECT_CALL(m_actions, s211_g());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_exit());
    EXPECT_CALL(m_actions, s2_exit());
    EXPECT_CALL(m_actions, s0_exit());
    EXPECT_CALL(m_actions, s0_init());
    EXPECT_CALL(m_actions, s0_entry());
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(Event::G);

    // foo set to 0
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
    EXPECT_EQ(1, m_hsm_test->foo());
    EXPECT_CALL(m_actions, s11_h());
    m_hsm_test->dispatch(Event::H);
    EXPECT_EQ(0, m_hsm_test->foo());
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

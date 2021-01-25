#include "yahsm.hpp"
#include <cstdio>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Hsm
////////////////////////////////////////////////////////////////////////////////

// Implements the following state machine from Miro Samek's
// Practical Statecharts in C/C++
//
// |-init-----------------------------------------------------|
// |                          top                             |
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

class TestHsm;

enum StateId : unsigned int
{
    Top_Id, // 0
    S1_Id, // 1
    S11_Id, // 2
    S2_Id, // 3
    S21_Id, // 4
    S211_Id, // 5
};

// clang-format off
//                    <hsm,          id, parent state>
using Top   = CompState<TestHsm, Top_Id     /*none*/>;
using S1   = CompState<TestHsm,   S1_Id,          Top>;
using S11  = LeafState<TestHsm,  S11_Id,          S1>;
using S2   = CompState<TestHsm,   S2_Id,          Top>;
using S21  = CompState<TestHsm,  S21_Id,          S2>;
using S211 = LeafState<TestHsm, S211_Id,         S21>;
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
inline void Top::init(TestHsm& h);

class TestHsm
{
public:
    explicit TestHsm(Actions& actions)
        : m_actions {actions}
    {
    }

    void init()
    {
        // enter initial state
        Top::init(*this);
    }

    void next(const TopState<TestHsm>& state)
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
    const TopState<TestHsm>* m_state {nullptr};
    Event m_event {Event::None};
    int m_foo {0};
    Actions& m_actions;
};

// Top
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename Current>
inline void Top::handle(TestHsm& h, const Current& c) const
{
    switch (h.event())
    {
        case Event::E:
        {
            Tran<Current, This, S211> t(h);
            h.actions().top_e();
            return;
        }
        default:
            break;
    }
    return Base::handle(h, c);
}

template <>
inline void Top::init(TestHsm& h)
{
    h.actions().top_init();
    InitalStateSetup<S1> i(h);
}

// S1
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename Current>
inline void S1::handle(TestHsm& h, const Current& c) const
{
    switch (h.event())
    {
        case Event::A:
        {
            Tran<Current, This, S1> t(h);
            h.actions().s1_a();
            return;
        }
        case Event::B:
        {
            Tran<Current, This, S11> t(h);
            h.actions().s1_b();
            return;
        }
        case Event::C:
        {
            Tran<Current, This, S2> t(h);
            h.actions().s1_c();
            return;
        }
        case Event::D:
        {
            Tran<Current, This, Top> t(h);
            h.actions().s1_d();
            return;
        }
        case Event::F:
        {
            Tran<Current, This, S211> t(h);
            h.actions().s1_f();
            return;
        }
        default:
            break;
    }
    return Base::handle(h, c);
}

template <>
inline void S1::init(TestHsm& h)
{
    InitalStateSetup<S11> i(h);
    h.actions().s1_init();
}

template <>
inline void S1::entry(TestHsm& h)
{
    h.actions().s1_entry();
}

template <>
inline void S1::exit(TestHsm& h)
{
    h.actions().s1_exit();
}

// S11
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename Current>
inline void S11::handle(TestHsm& h, const Current& c) const
{
    switch (h.event())
    {
        case Event::G:
        {
            Tran<Current, This, S211> t(h);
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
    return Base::handle(h, c);
}

template <>
inline void S2::init(TestHsm& h)
{
    InitalStateSetup<S21> i(h);
    h.actions().s2_init();
}

template <>
inline void S11::entry(TestHsm& h)
{
    h.actions().s11_entry();
}

template <>
inline void S11::exit(TestHsm& h)
{
    h.actions().s11_exit();
}

// S2
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename Current>
inline void S2::handle(TestHsm& h, const Current& c) const
{
    switch (h.event())
    {
        case Event::C:
        {
            Tran<Current, This, S1> t(h);
            h.actions().s2_c();
            return;
        }
        case Event::F:
        {
            Tran<Current, This, S11> t(h);
            h.actions().s2_f();
            return;
        }
        default:
            break;
    }
    return Base::handle(h, c);
}

template <>
inline void S21::init(TestHsm& h)
{
    InitalStateSetup<S211> i(h);
    h.actions().s21_init();
}

template <>
inline void S2::entry(TestHsm& h)
{
    h.actions().s2_entry();
}

template <>
inline void S2::exit(TestHsm& h)
{
    h.actions().s2_exit();
}

// S21
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename Current>
inline void S21::handle(TestHsm& h, const Current& c) const
{
    switch (h.event())
    {
        case Event::B:
        {
            Tran<Current, This, S211> t(h);
            h.actions().s21_b();
            return;
        }
        case Event::H:
            if (!h.foo())
            {
                Tran<Current, This, S21> t(h);
                h.actions().s21_h();
                h.foo(1);
                return;
            }
            break;
        default:
            break;
    }
    return Base::handle(h, c);
}

template <>
inline void S21::entry(TestHsm& h)
{
    h.actions().s21_entry();
}

template <>
inline void S21::exit(TestHsm& h)
{
    h.actions().s21_exit();
}

// S211
////////////////////////////////////////////////////////////////////////////////
template <>
template <typename Current>
inline void S211::handle(TestHsm& h, const Current& c) const
{
    switch (h.event())
    {
        case Event::D:
        {
            Tran<Current, This, S21> t(h);
            h.actions().s211_d();
            return;
        }
        case Event::G:
        {
            Tran<Current, This, Top> t(h);
            h.actions().s211_g();
            return;
        }
        default:
            break;
    }
    return Base::handle(h, c);
}

template <>
inline void S211::entry(TestHsm& h)
{
    h.actions().s211_entry();
}

template <>
inline void S211::exit(TestHsm& h)
{
    h.actions().s211_exit();
}

// Test
////////////////////////////////////////////////////////////////////////////////

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
    EXPECT_CALL(m_actions, s1_entry());
    EXPECT_CALL(m_actions, s1_init());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(Event::A);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS11, s11_B)
{
    EXPECT_CALL(m_actions, s1_b());
    EXPECT_CALL(m_actions, s11_exit());
    EXPECT_CALL(m_actions, s11_entry());
    m_hsm_test->dispatch(Event::B);
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
    m_hsm_test->dispatch(Event::C);
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
    m_hsm_test->dispatch(Event::D);
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
    m_hsm_test->dispatch(Event::E);
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
    m_hsm_test->dispatch(Event::F);
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
    m_hsm_test->dispatch(Event::G);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS11, s11_H)
{
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
    EXPECT_EQ(0, m_hsm_test->foo());
    m_hsm_test->dispatch(Event::H);
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
        m_hsm_test->dispatch(Event::C);
        EXPECT_EQ(S211_Id, m_hsm_test->state_id());
    }

    // void TearDown() override {}
    testing::StrictMock<MockActions> m_actions;
    std::unique_ptr<TestHsm> m_hsm_test;
};

TEST_F(TestHsmFixtureS211, s211_A)
{
    m_hsm_test->dispatch(Event::A);
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS211, s211_B)
{
    EXPECT_CALL(m_actions, s21_b());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(Event::B);
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
    m_hsm_test->dispatch(Event::C);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS211, s211_D)
{
    EXPECT_CALL(m_actions, s211_d());
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s211_entry());
    m_hsm_test->dispatch(Event::D);
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
    m_hsm_test->dispatch(Event::F);
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
    m_hsm_test->dispatch(Event::G);
    EXPECT_EQ(S11_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS211, s211_H)
{
    EXPECT_CALL(m_actions, s211_exit());
    EXPECT_CALL(m_actions, s21_entry());
    EXPECT_CALL(m_actions, s21_init());
    EXPECT_CALL(m_actions, s211_entry());
    EXPECT_EQ(0, m_hsm_test->foo());
    EXPECT_CALL(m_actions, s21_h());
    m_hsm_test->dispatch(Event::H);
    EXPECT_EQ(1, m_hsm_test->foo());
    EXPECT_EQ(S211_Id, m_hsm_test->state_id());
}

TEST_F(TestHsmFixtureS211, foo)
{
    // set foo = 1
    EXPECT_CALL(m_actions, s211_exit());
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
    EXPECT_CALL(m_actions, top_init());
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

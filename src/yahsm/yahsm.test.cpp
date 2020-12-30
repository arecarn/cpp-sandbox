#include "yahsm.hpp"
#include "gtest/gtest.h"
#include <cstdio>

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

class TestHSM;

// clang-format off
//                    <hsm,    id, parent state>
using Top  = CompState<TestHSM, 0  /*none*/>;
using S0   = CompState<TestHSM, 1, Top>;
using S1   = CompState<TestHSM, 2, S0>;
using S11  = LeafState<TestHSM, 3, S1>;
using S2   = CompState<TestHSM, 4, S0>;
using S21  = CompState<TestHSM, 5, S2>;
using S211 = LeafState<TestHSM, 6, S21>;
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
    H
};

template <>
inline void Top::init(TestHSM& h)
{
    InitalStateSetup<S0> i(h);
    printf("Top-INIT;");
}

class TestHSM
{
public:
    TestHSM()
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

private:
    const TopState<TestHSM>* m_state;
    Event m_event;
    int m_foo;
};

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
            printf("s0-E;");
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
    printf("S0-INIT;");
}

template <>
inline void S0::entry(TestHSM& /*unused*/)
{
    printf("S0-ENTRY;");
}
template <>
inline void S0::exit(TestHSM& /*unused*/)
{
    printf("S0-EXIT;");
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
            printf("s1-A;");
            return;
        }
        case Event::B:
        {
            Tran<X, This, S11> t(h);
            printf("s1-B;");
            return;
        }
        case Event::C:
        {
            Tran<X, This, S2> t(h);
            printf("s1-C;");
            return;
        }
        case Event::D:
        {
            Tran<X, This, S0> t(h);
            printf("s1-D;");
            return;
        }
        case Event::F:
        {
            Tran<X, This, S211> t(h);
            printf("s1-F;");
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
    printf("S1-INIT;");
}

template <>
inline void S1::entry(TestHSM& /*unused*/)
{
    printf("S1-ENTRY;");
}

template <>
inline void S1::exit(TestHSM& /*unused*/)
{
    printf("S1-EXIT;");
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
            printf("s11-G;");
            return;
        }
        case Event::H:
            if (h.foo())
            {
                printf("s11-H");
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
    printf("S2-INIT;");
}

template <>
inline void S11::entry(TestHSM& /*unused*/)
{
    printf("S11-ENTRY;");
}

template <>
inline void S11::exit(TestHSM& /*unused*/)
{
    printf("S11-EXIT;");
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
            printf("s2-C");
            return;
        }
        case Event::F:
        {
            Tran<X, This, S11> t(h);
            printf("s2-F");
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
    printf("S21-INIT;");
}

template <>
inline void S2::entry(TestHSM& /*unused*/)
{
    printf("S2-ENTRY;");
}

template <>
inline void S2::exit(TestHSM& /*unused*/)
{
    printf("S2-EXIT;");
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
            printf("s21-B;");
            return;
        }
        case Event::H:
            if (!h.foo())
            {
                Tran<X, This, S21> t(h);
                printf("s21-H;");
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
inline void S21::entry(TestHSM& /*unused*/)
{
    printf("S21-ENTRY;");
}

template <>
inline void S21::exit(TestHSM& /*unused*/)
{
    printf("S21-EXIT;");
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
            printf("s211-D;");
            return;
        }
        case Event::G:
        {
            Tran<X, This, S0> t(h);
            printf("s211-G;");
            return;
        }
        default:
            break;
    }
    return Base::handle(h, x);
}

template <>
inline void S211::entry(TestHSM& /*unused*/)
{
    printf("S211-ENTRY;");
}
template <>
inline void S211::exit(TestHSM& /*unused*/)
{
    printf("S211-EXIT;");
}

// Test
////////////////////////////////////////////////////////////////////////////////

bool test_dispatch(char c)
{
    static TestHSM s_test;
    if (c < 'a' || 'h' < c)
    {
        return false;
    }
    printf("\nEvent<-%c: ", c);
    s_test.dispatch(static_cast<Event>(c - 'a'));
    printf("\n");
    return true;
}

TEST(basic, pizza)
{
    test_dispatch('a');
    test_dispatch('b');
    test_dispatch('d');
    test_dispatch('e');
    test_dispatch('i');
    test_dispatch('f');
    test_dispatch('i');
    test_dispatch('i');
    test_dispatch('f');
    test_dispatch('a');
    test_dispatch('b');
    test_dispatch('d');
    test_dispatch('d');
    test_dispatch('e');
    test_dispatch('g');
    test_dispatch('h');
    test_dispatch('h');
    test_dispatch('c');
    test_dispatch('g');
    test_dispatch('c');
    test_dispatch('c');
}

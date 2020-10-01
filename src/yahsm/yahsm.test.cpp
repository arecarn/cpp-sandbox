#include "yahsm.hpp"
#include "gtest/gtest.h"
#include <cstdio>

/* Implements the following state machine from Miro Samek's
 * Practical Statecharts in C/C++
 *
 * |-init-----------------------------------------------------|
 * |                           s0                             |
 * |----------------------------------------------------------|
 * |                                                          |
 * |    |-init-----------|        |-------------------------| |
 * |    |       s1       |---c--->|            s2           | |
 * |    |----------------|<--c----|-------------------------| |
 * |    |                |        |                         | |
 * |<-d-| |-init-------| |        | |-init----------------| | |
 * |    | |     s11    |<----f----| |          s21        | | |
 * | /--| |------------| |        | |---------------------| | |
 * | a  | |            | |        | |                     | | |
 * | \->| |            |------g--------->|-init------|    | | |
 * |    | |____________| |        | |-b->|    s211   |---g--->|
 * |    |----b---^       |------f------->|           |    | | |
 * |    |________________|        | |<-d-|___________|<--e----|
 * |                              | |_____________________| | |
 * |                              |_________________________| |
 * |__________________________________________________________|
 */

class TestHSM;

// clang-format off
//                    <hsm,    id, parent state>
using Top  = CompState<TestHSM, 0  /*None*/>;
using S0   = CompState<TestHSM, 1, Top>;
using S1   = CompState<TestHSM, 2, S0>;
using S11  = LeafState<TestHSM, 3, S1>;
using S2   = CompState<TestHSM, 4, S0>;
using S21  = CompState<TestHSM, 5, S2>;
using S211 = LeafState<TestHSM, 6, S21>;
// clang-format on

enum class Signal
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

#define HSMINIT(State, InitState)         \
    template <>                           \
    inline void State::init(TestHSM& h)   \
    {                                     \
        InitalStateSetup<InitState> i(h); \
        printf(#State "-INIT;");          \
    }

HSMINIT(Top, S0)
HSMINIT(S0, S1)
HSMINIT(S1, S11)
HSMINIT(S2, S21)
HSMINIT(S21, S211)

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

    [[nodiscard]] Signal get_sig() const
    {
        return m_sig;
    }

    void dispatch(Signal sig)
    {
        m_sig = sig;
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
    Signal m_sig;
    int m_foo;
};

bool test_dispatch(char c)
{
    static TestHSM s_test;
    if (c < 'a' || 'h' < c)
    {
        return false;
    }
    printf("\nSignal<-%c: ", c);
    s_test.dispatch(static_cast<Signal>(c - 'a'));
    printf("\n");
    return true;
}

#define HSMHANDLER(State) \
    template <>           \
    template <typename X> \
    inline void State::handle(TestHSM& h, const X& x) const

HSMHANDLER(S0)
{
    switch (h.get_sig())
    {
        case Signal::E:
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

HSMHANDLER(S1)
{
    switch (h.get_sig())
    {
        case Signal::A:
        {
            Tran<X, This, S1> t(h);
            printf("s1-A;");
            return;
        }
        case Signal::B:
        {
            Tran<X, This, S11> t(h);
            printf("s1-B;");
            return;
        }
        case Signal::C:
        {
            Tran<X, This, S2> t(h);
            printf("s1-C;");
            return;
        }
        case Signal::D:
        {
            Tran<X, This, S0> t(h);
            printf("s1-D;");
            return;
        }
        case Signal::F:
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

HSMHANDLER(S11)
{
    switch (h.get_sig())
    {
        case Signal::G:
        {
            Tran<X, This, S211> t(h);
            printf("s11-G;");
            return;
        }
        case Signal::H:
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

HSMHANDLER(S2)
{
    switch (h.get_sig())
    {
        case Signal::C:
        {
            Tran<X, This, S1> t(h);
            printf("s2-C");
            return;
        }
        case Signal::F:
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

HSMHANDLER(S21)
{
    switch (h.get_sig())
    {
        case Signal::B:
        {
            Tran<X, This, S211> t(h);
            printf("s21-B;");
            return;
        }
        case Signal::H:
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

HSMHANDLER(S211)
{
    switch (h.get_sig())
    {
        case Signal::D:
        {
            Tran<X, This, S21> t(h);
            printf("s211-D;");
            return;
        }
        case Signal::G:
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

#define HSMENTRY(State)                \
    template <>                        \
    inline void State::entry(TestHSM&) \
    {                                  \
        printf(#State "-ENTRY;");      \
    }

HSMENTRY(S0)
HSMENTRY(S1)
HSMENTRY(S11)
HSMENTRY(S2)
HSMENTRY(S21)
HSMENTRY(S211)

#define HSMEXIT(State)                \
    template <>                       \
    inline void State::exit(TestHSM&) \
    {                                 \
        printf(#State "-EXIT;");      \
    }

HSMEXIT(S0)
HSMEXIT(S1)
HSMEXIT(S11)
HSMEXIT(S2)
HSMEXIT(S21)
HSMEXIT(S211)

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

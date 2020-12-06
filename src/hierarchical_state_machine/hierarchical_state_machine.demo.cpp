#include "hierarchical_state_machine.hpp"
#include <cassert>
#include <cstdio>

class HsmTest : public Hsm
{
    int m_my_foo {0};

protected:
    State m_s1;
    State m_s11;
    State m_s2;
    State m_s21;
    State m_s211;

public:
    HsmTest();
    Msg const* top_handler(Msg const* msg);
    Msg const* s1_handler(Msg const* msg);
    Msg const* s11_handler(Msg const* msg);
    Msg const* s2_handler(Msg const* msg);
    Msg const* s21_handler(Msg const* msg);
    Msg const* s211_handler(Msg const* msg);
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

Msg const* HsmTest::top_handler(Msg const* msg)
{
    switch (msg->evt)
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
            STATE_TRAN(m_s211);
            break;
        default:
            return msg;
    }
    return nullptr;
}

Msg const* HsmTest::s1_handler(Msg const* msg)
{
    switch (msg->evt)
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
            STATE_TRAN(m_s1);
            break;
        case B_SIG:
            printf("s1-B;");
            STATE_TRAN(m_s11);
            break;
        case C_SIG:
            printf("s1-C;");
            STATE_TRAN(m_s2);
            break;
        case D_SIG:
            printf("s1-D;");
            STATE_TRAN(m_top);
            break;
        case F_SIG:
            printf("s1-F;");
            STATE_TRAN(m_s211);
            break;
        default:
            return msg;
    }
    return nullptr;
}

Msg const* HsmTest::s11_handler(Msg const* msg)
{
    switch (msg->evt)
    {
        case ENTRY_EVT:
            printf("s11-ENTRY;");
            break;
        case EXIT_EVT:
            printf("s11-EXIT;");
            break;
        case G_SIG:
            printf("s11-G;");
            STATE_TRAN(m_s211);
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

Msg const* HsmTest::s2_handler(Msg const* msg)
{
    switch (msg->evt)
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
            STATE_TRAN(m_s1);
            break;
        case F_SIG:
            printf("s2-F;");
            STATE_TRAN(m_s11);
            break;
        default:
            return msg;
    }
    return nullptr;
}

Msg const* HsmTest::s21_handler(Msg const* msg)
{
    switch (msg->evt)
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
            STATE_TRAN(m_s211);
            break;
        case H_SIG:
            if (!m_my_foo)
            {
                printf("s21-H;");
                m_my_foo = 1;
                STATE_TRAN(m_s21);
            }
            break;
        default:
            return msg;
    }
    return nullptr;
}

Msg const* HsmTest::s211_handler(Msg const* msg)
{
    switch (msg->evt)
    {
        case ENTRY_EVT:
            printf("s211-ENTRY;");
            break;
        case EXIT_EVT:
            printf("s211-EXIT;");
            break;
        case D_SIG:
            printf("s211-D;");
            STATE_TRAN(m_s21);
            break;
        case G_SIG:
            printf("s211-G;");
            STATE_TRAN(m_top);
            break;
        default:
            return msg;
    }
    return nullptr;
}

HsmTest::HsmTest()
    : Hsm {"HsmTest", static_cast<EventHandler>(&HsmTest::top_handler), &m_s1}
    , m_s1 {"s1", &m_top, static_cast<EventHandler>(&HsmTest::s1_handler), &m_s11}
    , m_s11 {"s11", &m_s1, static_cast<EventHandler>(&HsmTest::s11_handler)}
    , m_s2 {"s2", &m_top, static_cast<EventHandler>(&HsmTest::s2_handler), &m_s21}
    , m_s21 {"s21", &m_s2, static_cast<EventHandler>(&HsmTest::s21_handler), &m_s211}
    , m_s211 {"s211", &m_s21, static_cast<EventHandler>(&HsmTest::s211_handler)}
{
}

const Msg HsmTestMsg[] = {
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

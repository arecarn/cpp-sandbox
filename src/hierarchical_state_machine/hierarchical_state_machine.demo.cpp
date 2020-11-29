#include "hierarchical_state_machine.hpp" //.h "
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
    Msg const* top_hndlr(Msg const* msg);
    Msg const* s1_hndlr(Msg const* msg);
    Msg const* s11_hndlr(Msg const* msg);
    Msg const* s2_hndlr(Msg const* msg);
    Msg const* s21_hndlr(Msg const* msg);
    Msg const* s211_hndlr(Msg const* msg);
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

Msg const* HsmTest::top_hndlr(Msg const* msg)
{
    switch (msg->evt)
    {
        case START_EVT:
            printf("top-INIT;");
            state_start(&m_s1);
            return nullptr;
        case ENTRY_EVT:
            printf("top-ENTRY;");
            return nullptr;
        case EXIT_EVT:
            printf("top-EXIT;");
            return nullptr;
        case E_SIG:
            printf("top-E;");
            STATE_TRAN(&m_s211);
            return nullptr;
    }
    return msg;
}

Msg const* HsmTest::s1_hndlr(Msg const* msg)
{
    switch (msg->evt)
    {
        case START_EVT:
            printf("s1-INIT;");
            state_start(&m_s11);
            return nullptr;
        case ENTRY_EVT:
            printf("s1-ENTRY;");
            return nullptr;
        case EXIT_EVT:
            printf("s1-EXIT;");
            return nullptr;
        case A_SIG:
            printf("s1-A;");
            STATE_TRAN(&m_s1);
            return nullptr;
        case B_SIG:
            printf("s1-B;");
            STATE_TRAN(&m_s11);
            return nullptr;
        case C_SIG:
            printf("s1-C;");
            STATE_TRAN(&m_s2);
            return nullptr;
        case D_SIG:
            printf("s1-D;");
            STATE_TRAN(&m_top);
            return nullptr;
        case F_SIG:
            printf("s1-F;");
            STATE_TRAN(&m_s211);
            return nullptr;
    }
    return msg;
}

Msg const* HsmTest::s11_hndlr(Msg const* msg)
{
    switch (msg->evt)
    {
        case ENTRY_EVT:
            printf("s11-ENTRY;");
            return nullptr;
        case EXIT_EVT:
            printf("s11-EXIT;");
            return nullptr;
        case G_SIG:
            printf("s11-G;");
            STATE_TRAN(&m_s211);
            return nullptr;
        case H_SIG:
            if (m_my_foo)
            {
                printf("s11-H;");
                m_my_foo = 0;
                return nullptr;
            }
            break;
    }
    return msg;
}

Msg const* HsmTest::s2_hndlr(Msg const* msg)
{
    switch (msg->evt)
    {
        case START_EVT:
            printf("s2-INIT;");
            state_start(&m_s21);
            return nullptr;
        case ENTRY_EVT:
            printf("s2-ENTRY;");
            return nullptr;
        case EXIT_EVT:
            printf("s2-EXIT;");
            return nullptr;
        case C_SIG:
            printf("s2-C;");
            STATE_TRAN(&m_s1);
            return nullptr;
        case F_SIG:
            printf("s2-F;");
            STATE_TRAN(&m_s11);
            return nullptr;
    }
    return msg;
}

Msg const* HsmTest::s21_hndlr(Msg const* msg)
{
    switch (msg->evt)
    {
        case START_EVT:
            printf("s21-INIT;");
            state_start(&m_s211);
            return nullptr;
        case ENTRY_EVT:
            printf("s21-ENTRY;");
            return nullptr;
        case EXIT_EVT:
            printf("s21-EXIT;");
            return nullptr;
        case B_SIG:
            printf("s21-B;");
            STATE_TRAN(&m_s211);
            return nullptr;
        case H_SIG:
            if (!m_my_foo)
            {
                printf("s21-H;");
                m_my_foo = 1;
                STATE_TRAN(&m_s21);
                return nullptr;
            }
            break;
    }
    return msg;
}

Msg const* HsmTest::s211_hndlr(Msg const* msg)
{
    switch (msg->evt)
    {
        case ENTRY_EVT:
            printf("s211-ENTRY;");
            return nullptr;
        case EXIT_EVT:
            printf("s211-EXIT;");
            return nullptr;
        case D_SIG:
            printf("s211-D;");
            STATE_TRAN(&m_s21);
            return nullptr;
        case G_SIG:
            printf("s211-G;");
            STATE_TRAN(&m_top);
            return nullptr;
    }
    return msg;
}

HsmTest::HsmTest()
    : Hsm {"HsmTest", static_cast<EvtHndlr>(&HsmTest::top_hndlr)}
    , m_s1 {"s1", &m_top, static_cast<EvtHndlr>(&HsmTest::s1_hndlr)}
    , m_s11 {"s11", &m_s1, static_cast<EvtHndlr>(&HsmTest::s11_hndlr)}
    , m_s2 {"s2", &m_top, static_cast<EvtHndlr>(&HsmTest::s2_hndlr)}
    , m_s21 {"s21", &m_s2, static_cast<EvtHndlr>(&HsmTest::s21_hndlr)}
    , m_s211 {"s211", &m_s21, static_cast<EvtHndlr>(&HsmTest::s211_hndlr)}
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

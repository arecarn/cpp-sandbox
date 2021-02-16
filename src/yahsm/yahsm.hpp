#ifndef YAHSM_HPP
#define YAHSM_HPP

// This code based on the code from the following article:
// Yet Another Hierarchical State Machine
// by Stefan Heinzmann
// Overload issue 64 December 2004
// http://www.state-machine.com/resources/Heinzmann04.pdf

// This is a basic implementation of UML Statecharts. The key observation is
// that the machine can only be in a leaf state at any given time. The composite
// states are only traversed, never final. Only the leaf states are ever
// instantiated. The composite states are only mechanisms used to generate code.
// They are never instantiated.

// Top State, Composite State and Leaf State
////////////////////////////////////////////////////////////////////////////////

template <typename H>
struct TopState
{
    using Host = H;
    using Base = void;

    virtual void handler(Host&) const = 0;
    [[nodiscard]] virtual unsigned id() const = 0;
    virtual ~TopState() = default;
};

template <typename H, unsigned Id, typename B>
struct CompState;

template <typename H, unsigned Id, typename B = CompState<H, 0, TopState<H>>>
struct CompState : B
{
    using Base = B;
    using This = CompState<H, Id, Base>;

    template <typename Current>
    void handle(H& h, const Current& c) const { Base::handle(h, c); }

    static void init(H& /*unused*/); // no implementation
    static void entry(H& /*unused*/) { }
    static void exit(H& /*unused*/) { }
};

template <typename H>
struct CompState<H, 0, TopState<H>> : TopState<H>
{
    using Base = TopState<H>;
    using This = CompState<H, 0, Base>;

    template <typename Current>
    void handle(H& /*unused*/, const Current& /*unused*/) const { }

    static void init(H& /*unused*/); // no implementation
    static void entry(H& /*unused*/) { }
    static void exit(H& /*unused*/) { }
};

template <typename H, unsigned Id, typename B = CompState<H, 0, TopState<H>>>
struct LeafState : B
{
    using Host = H;
    using Base = B;
    using This = LeafState<H, Id, Base>;

    template <typename Current>
    void handle(H& h, const Current& c) const { Base::handle(h, c); }

    virtual void handler(H& h) const { handle(h, *this); }
    [[nodiscard]] virtual unsigned id() const { return Id; }
    static void init(H& h) { h.state(State); } // don't specialize this
    static void entry(H& /*unused*/) { }
    static void exit(H& /*unused*/) { }

    static const LeafState State; // only the leaf states have instances
};

template <typename H, unsigned Id, typename B>
const LeafState<H, Id, B> LeafState<H, Id, B>::State;

// Transition
////////////////////////////////////////////////////////////////////////////////

// A gadget from Herb Sutter's GotW #71 -- depends on SFINAE
template <class D, class B>
class IsDerivedFrom
{
private:
    class Yes
    {
        char m_a[1];
    };
    class No
    {
        char m_a[10];
    };
    static Yes test(B*); // undefined
    static No test(...); // undefined
public:
    static constexpr bool Value = (sizeof(test(static_cast<D*>(0))) == sizeof(Yes));
};

template <class T, class U>
struct IsSame
{
    static constexpr bool Value = false;
};

template <class T>
struct IsSame<T, T>
{
    static constexpr bool Value = true;
};

template <bool>
class Bool
{
};

template <typename Current, typename Source, typename Target>
struct Tran
{
    using Host = typename Current::Host;
    using CurrentBase = typename Current::Base;
    using CurrentBasesBase = typename Current::Base::Base;
    using SourceBase = typename Source::Base;
    using TargetBase = typename Target::Base;

    enum
    { // work out when to terminate template recursion
        Source_Is_Target = IsSame<Source, Target>::Value,
        Source_Derives_From_Target = IsDerivedFrom<Source, Target>::Value,
        Source_Derives_From_Current = IsDerivedFrom<Source, Current>::Value,
        Source_Derives_From_CurrentBase = IsDerivedFrom<Source, CurrentBase>::Value,
        TargetBase_Derives_From_CurrentBase = IsDerivedFrom<TargetBase, CurrentBase>::Value,
        CurrentBaseBase_Derives_From_Target = IsDerivedFrom<CurrentBasesBase, Target>::Value,

        Exit_Stop = TargetBase_Derives_From_CurrentBase
            || (Source_Derives_From_Target
                && !Source_Is_Target
                && !CurrentBaseBase_Derives_From_Target),

        // When Current starts as the Target, determine where the entry
        // functions should begin
        Entry_Stop = Source_Derives_From_Current
            || Source_Derives_From_CurrentBase,

        Entry_Start = Source_Derives_From_Target
            && !Source_Is_Target
    };

    // overloading is used to stop recursion. The more natural template
    // specialization method would require to specialize the inner template
    // without specializing the outer one, which is forbidden.
    static void exit_actions(Host& /*unused*/, Bool<true> /*unused*/) { }

    static void exit_actions(Host& h, Bool<false> /*unused*/)
    {
        Current::exit(h);
        Tran<CurrentBase, Source, Target>::exit_actions(h, Bool<Exit_Stop>());
    }

    static void entry_actions(Host& /*unused*/, Bool<true> /*unused*/) { }

    static void entry_actions(Host& h, Bool<false> /*unused*/)
    {
        Tran<CurrentBase, Source, Target>::entry_actions(h, Bool<Entry_Stop>());
        Current::entry(h);
    }

    Tran(Host& h)
        : m_host(h)
    {
        exit_actions(m_host, Bool<false>());
    }

    ~Tran()
    {
        Tran<Target, Source, Target>::entry_actions(m_host, Bool<Entry_Start>());
        Target::init(m_host);
    }

    Host& m_host;
};

// InitalStateSetup
////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct InitalStateSetup
{
    using Host = typename T::Host;
    InitalStateSetup(Host& h)
        : m_host(h)
    {
    }
    ~InitalStateSetup()
    {
        T::entry(m_host);
        T::init(m_host);
    }

private:
    Host& m_host;
};

// Hsm
////////////////////////////////////////////////////////////////////////////////

template <typename DerivedHsm, typename InitialState>
class Hsm
{
public:
    void state(const TopState<DerivedHsm>& state)
    {
        m_state = &state;
    }

    [[nodiscard]] unsigned int state_id() const
    {
        return m_state->id();
    }

    void handle()
    {
        m_state->handler(*static_cast<DerivedHsm*>(this));
    }

    void init()
    {
        InitalStateSetup<InitialState> i {*static_cast<DerivedHsm*>(this)};
    }

private:
    const TopState<DerivedHsm>* m_state {nullptr};
};

#endif // YAHSM_HPP

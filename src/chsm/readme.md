# About
Based on the code from "State Oriented Programming Hierarchical State Machines
in C/C++" by Miro Samek and Paul Y. Montgomery May 13, 2000.

# Demo State Diagram

```plantuml
[*] --> Top
state Top {
    Top -> S211: E
    [*] --> S1

    state S1 {
        S1 --> S1: A
        S1 --> S11: B
        S1 --> S2: C
        S1 --> Top: D
        S1 --> S221: F

        [*] ---> S11
        state S11 {
            S11: on H / if foo: foo = 0
            S11 --> S211: G
        }
    }

    state S2 {
        [*] ---> S21
        S2 --> S1: C
        S2 --> S11: F
        state S21 {
            [*] ---> S211
            S21 -> S21: B / if !foo: foo = 1
            state S211 {
                S211 -u-> Top: G
                S211 -u-> S21: D
            }
        }
    }
}
```


# Implementation Notes/Thoughts


- state machine should be fed by queue so states themselves can emit events
    - instead of this should there be some context object that is passed into
      states that holds a handle to data the state may want to modify/access.
      This might include a handle to the queue that feeds the state mahcine.

- States should not be modifying the state machine i.e. the
  Transition objects shouldn't poke at the Hsm object. This is
  mixing code that should not be there.
    - if states could be their own unique classes then they
      could pre-calculate all their transition data at
      construction time using multiple transition object members

- states need to be able to reference other state instances to
  initiate transitions. This is achieve in the original
  implementation by making all the handler functions member
  functions of the HSM object, then binding those to states.

- on_event handlers need to be able to reference extended
  state data so it can modify it, right now this is acheived by making the
  state handler's functions member functions of the derivedHSM
    - could use CRTP DerivedHsm: Hsm<DerivedHsm> to ensure that some info specified
      in the DerivedHsm is used in the base state machine
        - examples:
        - passing DerivedHsm pointer to on_event handlers

- input events -> state machine -> output actions
- The implementation of the actions performed by a state machine (excluding
  modifications to extended state) should be decoupled from the state machine
  code. This is both the state machine and the actions
  themselves can be independently tested.
    - an actions object could be passed into the state machine as an interface,
      and for testing it could be mocked out.

- Should there be some way to inject the current state (including the extended
  state) into the state machine, to aid in testing? It sure does make testing
  easier.
    - this could be part of the state machine's constructor
    - this could be member functions that modify the state machines state



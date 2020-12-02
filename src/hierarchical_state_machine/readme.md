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
        S2 --> S1: C
        S2 --> S11: F
        state S21 {
            S21 -> S21: B / if !foo: foo = 1
        }
        state S211 {
            S211 -u-> Top: G
        }
    }
}
```

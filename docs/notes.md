# How does the Internet Work
* what happens after you hit enter on the URL bar
* DNS
* UDP/TCP/IP

--------------------------------------------------------------------------------

# Algorithms

## Recursive

## Backtracking
* constraint solving

## Sorting

## Binary Search

## Divide and Conquer

## Permutations / Combinations


## Dynamic Programming / Memozation
Prefix Sum
* exclusive_scan
* inclusive_scan

--------------------------------------------------------------------------------

# Data Structures

## Trie
Big O



## Sorted Vector

| Algorithm            | Average    | Worst case   |
| -------------------- | ---------- | ------------ |
| Space                | O(n)       | O(n)         |
| Search               | O(log(n))  | O(log(n))    |
| Insert               | O(n)       | O(n)         |
| Find min/max         | O(1)       | O(1)         |
| Delete middle/front  | O(n)       | O(n)         |
| Delete back          | O(1)       | O(1)         |

## Stack
LIFO

## Queue
FIFO

## Binary Heap

### Description


can be a min or max heap

  `std::priority_queue<T>`

### Complexity
| Algorithm      | Average  | Worst case |
|----------------|----------|------------|
| Space          | O(n)     | O(n)       |
| Search         | O(n)     | O(n)       |
| Insert         | O(1)     | O(log n)   |
| Find min/max   | O(1)     | O(1)       |
| Delete min/max | O(log n) | O(log n)   |


## Hash Set


## Hash Table / Set
### Implementations
* open addressing: array with probing to detect and avoid collisions
    * must store key with value to verify correct value given a collision
    * deleting values can be tricky

* chained
    * uses some structure (often a linked list) to collect all values that collide
    * vector could provide better cache locality

## Trees

### B-Tree
generalized tree

### Binary Trees

Implementations
    * red black tree

* often helpful to use a stack
* binary tree's aren't ordered unless they are binary search trees

### Traversals
    * Depth First Search
        * implemented using stack (LIFO) / recursion
        * in-order: left, root, right
            * traverses a binary search tree in accenting order
        * out-order: right, root, left
            * traverses a binary search tree in descending order
        * post-order
            * left, right, root
        * pre-order
            * root, left, right

    Breadth First Search
        * implemented using a queue (FIFO)
        * AKA level order



##  Graphs

* Made up of edges (connections), and vertexes (nodes)
* edges can be weighted
* edges can be directed
* can contain cycles


* Implementations
    * Adjacency list: e.g. array of sets, where the contents of each set specifies
    * Adjacency matrix: 2-D array where rows/columns represent vertexes, and their intersections are their connections



Depth First Search
Breadth First Search
* AKA level order for a tree

## Linked List

* reverse linked list
    * pointer to prev (initially nullptr)
    * pointer to curr (initially head)
    * pointer to next  curr->next
    * while current

```cpp
Node* reverse(Node* l);
{
    Node* prev = nullptr;
    Node* curr = l;
    Node* next = nullptr

    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

return prev;
}
```






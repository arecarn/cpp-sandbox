# Algorithms

## Recursive

## Backtracking
* constraint solving

## Sorting
* heap sort
* merge sort
* quick sort
* insertion sort
* bubble sort

## Binary Search

## Divide and Conquer
* merge sort

## Permutations / Combinations

## Hashing
* perfect hash

## Dynamic Programming / Memozation
Prefix Sum
* exclusive_scan
* inclusive_scan

## Path Finding

--------------------------------------------------------------------------------


# Data Structures

## Trie



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

## Deque / Queue / Stack

### Stack
FIFO

### Queue
LIFO

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


## Hash Table/Set

### Implementations
* open addressing: array with probing to detect and avoid collisions
    * must store key with value to verify correct value given a collision
    * deleting values can be tricky

* chained
    * uses some structure (often a linked list) to collect all values that collide
    * vector could provide better cache locality

## B-Tree
generalized tree

## Binary Tree

## Binary Search Trees

Implementations
    * red black tree

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

## Graph

### Graph - Adjacency List

* Made up of edges (connections), and vertexes (nodes)
* edges can be weighted
* edges can be directed
* can contain cycles

### Graph - Adjacency Matrix

* Implementations
    * Adjacency list: e.g. array of sets, where the contents of each set specifies
    * Adjacency matrix: 2-D array where rows/columns represent vertexes, and their intersections are their connections


Depth First Search
Breadth First Search
* AKA level order for a tree

## Linked List
Techniques:
* reverse linked list
    * pointer to prev (initially nullptr)
    * pointer to curr (initially head)
    * pointer to next  curr->next
    * while current
* fast pointer slow pointer
    * find cycles
    * find midway point

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

--------------------------------------------------------------------------------


--------------------------------------------------------------------------------

# Internet / Networking

### What happens when you open a browser and enter a URL then hit enter

* Our browser sends an HTTP request which gets routed through a local
  modem/router and gets sent to a name server for its URL extension.
* That name server routes the request to the correct IP address, which will
  resolve to some sort of web server.
* That server will serve up either some static files, or run some backed code
  in order to generate a resource (probably an HTML page).
* When the HTML page is returned, your browser will parse it, which will
  likely generate more requests, and the cycle will repeat.

  Also see this: https://softwareengineering.stackexchange.com/a/211201/337536


### How does Internet Search Work

### TCP/IP as it relates to the OSI Model

| OSI Layer Name                                   | TCP/IP Layer      | TCP/IP Protocol Examples                       |
| ------------------------------------------------ | ----------------- | ---------------------------------------------- |
| Application (7), Session (6), Presentation (5)   | Application (4)   | NFS, DNS, Telnet, SSH, FTP, rlogin,            |
|                                                  |                   | RSH, RCP, RIP, RDISC, SNMP, HTTP(S)            |
| Transport (4)                                    | Transport (3)     | TCP, UDP                                       |
| Network (3)                                      | Internet (2)      | IPv4, IPv6, ARP, ICMP, IGMP, ENC, IPsec        |
| Data link (2)                                    | Link (2)          | WiFi, Ethernet, PPP, IEEE 802.2                |
| Physical (1)                                     | N/A               | Ethernet Physical Layer,  Token Ring, RS-232   |

Network Access layer (1):
On this layer, physical connections and data framing happen. Sending an
Ethernet or Wi-Fi packet are examples of layer 1 concerns.

Internet layer (2):
This layer deals with the concerns of addressing packets and routing them over
multiple interconnection networks. It's at this layer that an IP address is
defined.

Transport layer (3):
The host-to-host layer provides two protocols, TCP and UDP, which we will
discuss in the next few chapters. These protocols address concerns such as data
order, data segmentation, network congestion, and error correction.

Process/Application layer (4):
The process/application layer is where protocols such as HTTP, SMTP, and FTP
are implemented. Most of the programs that feature in this book could be
considered to take place on this layer while consuming functionality provided
by our operating system's implementation of the lower layers.

--------------------------------------------------------------------------------

# Data Bases
## Relational (SQL)
## Key Value Store
## Wide Column
## Block Store

# Operating Systems
## Processes
## Threads
## Bootloader
## Scheduler
## Services

# Linux


# System Design
* horizontal scaling
* vertical scaling
* data size
* bandwidth
* data partitioning
* caching

# High Performance Computing
* memory map files
* don't do too much in loops to keep registers well utilized registers
* offload work from the CPU to accelerators or other peripherals
* CPU cache considerations
* minimize paging of virtual memory
* minimize thread/process context switching
* pin processes/threads to CPUs
* minimize application memory allocations
* minimize application copying
* distribute processing across multiple nodes
* 

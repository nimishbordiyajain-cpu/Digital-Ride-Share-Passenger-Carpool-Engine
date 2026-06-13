# PoolRide Carpool Engine

### DSA-I End Semester Project (C++)

---

# 2.1 Project Title

**PoolRide – Digital Ride-Share Passenger Carpool Engine**

A C++ based ride-sharing and carpool management system that uses multiple Data Structures and Algorithms to efficiently manage users, ride requests, vehicle allocation, route optimization, toll minimization, and passenger location tracking.

---

# 2.2 Problem Statement

PoolRide is a carpooling feature for a ride-sharing application that matches multiple passengers heading in the same direction into a single vehicle, calculates fair multi-stop routes, and dynamically adjusts pricing.

The existing system suffers from several limitations:

* Large user databases are inefficient for quick access.
* Price surge updates cannot be rolled back.
* Ride requests are not processed in submission order.
* Passenger location lookup is slow.
* Vehicles cannot be efficiently ranked by seat availability.
* No city street network model exists.
* Multi-stop route optimization is unavailable.
* Toll costs are ignored during route planning.

The objective is to design and implement an optimized carpool system using appropriate Data Structures and Algorithms to overcome these challenges.

---

# 2.3 Objectives

The primary objectives of the project are:

1. Store and manage user records efficiently.
2. Support dynamic surge pricing with rollback functionality.
3. Process ride requests in FIFO order.
4. Perform fast passenger location lookups.
5. Allocate vehicles based on available seating capacity.
6. Model a city street network using graphs.
7. Find shortest travel-time routes.
8. Minimize toll expenses during route planning.
9. Demonstrate practical applications of DSA concepts in ride-sharing systems.
10. Simulate real-world features similar to Uber Pool and Ola Share.

---

# 2.4 System Overview / Architecture

```text
+------------------------------------------------+
|              PoolRide Main System              |
+------------------------------------------------+
                     |
     ----------------------------------------
     |        |        |        |           |
     V        V        V        V           V

 User     Price    Ride      Location   Vehicle
Directory  Log     Queue      Finder    Manager
(B-Tree) (Stack) (Queue)   (Hash Map) (Max Heap)

                     |
                     V

              Street Network
                 (Graph)

               /          \
              /            \
             V              V

     Route Optimizer   Toll Optimizer
        (Dijkstra)   (Modified Dijkstra)
```

### Workflow

1. User records are stored in a B-Tree.
2. Ride requests enter a FIFO queue.
3. Passenger locations are tracked using a hash table.
4. Vehicles are prioritized using a max heap.
5. Routes are generated using graph algorithms.
6. Cheapest toll paths are calculated separately.
7. Surge prices are maintained through a stack.

---

# 2.5 Data Structures and Algorithms Used

| Module             | Data Structure / Algorithm | Purpose                                          |
| ------------------ | -------------------------- | ------------------------------------------------ |
| User Directory     | B-Tree                     | Efficient storage and retrieval of user accounts |
| Price Log          | Stack                      | Rollback surge pricing updates                   |
| Ride Request Queue | Queue                      | FIFO request processing                          |
| Location Finder    | Hash Table (unordered_map) | Fast passenger lookup                            |
| Capacity Sorter    | Max Heap                   | Vehicle prioritization                           |
| Street Network     | Graph (Adjacency List)     | Road network modeling                            |
| Route Optimizer    | Dijkstra Algorithm         | Shortest path calculation                        |
| Toll Optimizer     | Modified Dijkstra          | Minimum toll path calculation                    |

### Why These Structures?

#### B-Tree

Optimized for large datasets and disk-based storage.

#### Stack

Supports LIFO rollback operations for surge pricing.

#### Queue

Ensures fair ride request handling.

#### Hash Table

Provides near O(1) search performance.

#### Max Heap

Efficiently selects vehicles with maximum seat availability.

#### Graph

Represents city roads and locations naturally.

#### Dijkstra Algorithm

Finds shortest travel-time routes.

#### Modified Dijkstra

Finds minimum-cost toll routes.

---

# 2.6 Implementation Approach

The project is implemented using modular C++ programming.

### Module 1: User Directory

* Implemented using B-Tree.
* Stores user information and frequent routes.
* Supports insertion and searching.

### Module 2: Price Log

* Implemented using linked-list stack.
* Stores surge pricing history.
* Allows rollback of previous surge updates.

### Module 3: Ride Request Queue

* Implemented using linked-list queue.
* Processes ride requests in FIFO order.

### Module 4: Location Finder

* Implemented using unordered_map.
* Searches passenger locations using IDs.

### Module 5: Capacity Sorter

* Implemented using Max Heap.
* Prioritizes vehicles with highest available seats.

### Module 6: Street Network

* Implemented using Graph (Adjacency List).
* Represents city roads and travel connections.

### Module 7: Route Optimizer

* Uses Dijkstra Algorithm.
* Finds shortest travel-time routes.

### Module 8: Toll Optimizer

* Uses Modified Dijkstra Algorithm.
* Finds lowest toll-cost routes.

---

# 2.7 Time and Space Complexity Analysis

| Operation         | Complexity       |
| ----------------- | ---------------- |
| B-Tree Search     | O(log n)         |
| B-Tree Insert     | O(log n)         |
| Stack Push        | O(1)             |
| Stack Pop         | O(1)             |
| Queue Enqueue     | O(1)             |
| Queue Dequeue     | O(1)             |
| Hash Search       | O(1) Average     |
| Heap Insert       | O(log n)         |
| Heap Extract Max  | O(log n)         |
| Graph Edge Insert | O(1)             |
| Dijkstra          | O((V + E) log V) |
| Modified Dijkstra | O((V + E) log V) |

### Space Complexity

| Structure  | Complexity |
| ---------- | ---------- |
| B-Tree     | O(n)       |
| Stack      | O(n)       |
| Queue      | O(n)       |
| Hash Table | O(n)       |
| Heap       | O(n)       |
| Graph      | O(V + E)   |

---

# 2.8 Execution Steps

### Prerequisites

* C++ Compiler (g++)
* Windows/Linux/macOS

### Compile

```bash
g++ main.cpp -o PoolRide
```

### Run

```bash
./PoolRide
```

### Execution Flow

1. Launch application.
2. System loads sample data.
3. Main menu is displayed.
4. Select any module.
5. Perform desired operation.
6. View results.
7. Exit application.

---

# 2.9 Sample Inputs and Outputs

## Example 1: User Search

### Input

```text
Enter User ID: 1004
```

### Output

```text
User Found
ID: 1004
Name: Sneha Patil
Route: Vashi -> Kurla
```

---

## Example 2: Ride Request Queue

### Input

```text
Process Next Ride Request
```

### Output

```text
Request Processed Successfully
Passenger Assigned To Driver
```

---

## Example 3: Route Optimization

### Input

```text
Source: Andheri
Destination: Lower Parel
```

### Output

```text
Shortest Route:
Andheri -> Bandra -> Lower Parel

Travel Time: 30 Minutes
```

---

## Example 4: Toll Optimization

### Input

```text
Source: Thane
Destination: BKC
```

### Output

```text
Cheapest Toll Route Found

Total Toll Cost: Rs.40
```

---

# 2.10 Screenshots

Include the following screenshots in the GitHub repository:

### Screenshot 1

Application Startup Screen

### Screenshot 2

Main Menu

### Screenshot 3

User Directory Module

### Screenshot 4

Price Log Module

### Screenshot 5

Ride Request Queue Module

### Screenshot 6

Location Finder Module

### Screenshot 7

Capacity Sorter Module

### Screenshot 8

Street Network Graph

### Screenshot 9

Route Optimizer Output

### Screenshot 10

Toll Optimizer Output

---

# 2.11 Results and Observations

### Results

* User records are efficiently managed using B-Trees.
* Surge pricing rollback is achieved using stacks.
* Ride requests are processed fairly through queues.
* Passenger lookup is significantly faster using hashing.
* Vehicle allocation becomes more efficient using heaps.
* Graph structures accurately model road networks.
* Dijkstra successfully computes shortest travel routes.
* Modified Dijkstra effectively reduces toll expenses.

### Observations

* Different data structures solve different real-world problems.
* Algorithm selection greatly impacts system efficiency.
* Graph algorithms are essential for route optimization.
* Hash tables provide the fastest lookup operations.
* Priority-based allocation improves carpool utilization.

---

# 2.12 Conclusion

The **PoolRide Carpool Engine** successfully demonstrates the practical implementation of fundamental Data Structures and Algorithms in a real-world ride-sharing environment.

The system integrates B-Trees, Stacks, Queues, Hash Tables, Heaps, Graphs, Dijkstra's Algorithm, and Modified Dijkstra's Algorithm to efficiently manage users, requests, locations, vehicles, routes, and toll costs.

This project showcases how DSA concepts can be applied to solve complex transportation and carpooling challenges similar to modern platforms such as Uber Pool and Ola Share. The implementation achieves efficient performance, modularity, scalability, and ease of maintenance while meeting all requirements specified in the problem statement.

---

## Developed For

**DSA-I End Semester Project**
**ITM Skills University**
**Project Title: PoolRide – Digital Ride-Share Passenger Carpool Engine**
**Language: C++**
**Concepts Covered: B-Tree, Stack, Queue, Hash Table, Heap, Graph, Dijkstra, Modified Dijkstra**

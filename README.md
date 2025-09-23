# Research on Search Algorithms in C++

This repository contains my final project for my Data Structures course. The goal of this project was to implement several search Abstract Data Types (ADTs) from scratch in C++, and then conduct a performance analysis to compare their efficiency.

I implemented and benchmarked three distinct data structures—a Linked List, an AVL Tree, and a Hash Table—to observe how their underlying architecture impacts real-world performance on large datasets for insertion, search, and deletion operations. This with different dataset sizes from 10k to 100k. (for uploading purposes the data set included in this repository is only the 10k dataset)

-----

## Data Structures I Implemented

My primary role in the group was to implement the core logic for the more complex data structures and their drivers. Each structure was built to be tested against a dataset of 10,000 random integers.

### 1\. AVL Tree

A self-balancing binary search tree that maintains a logarithmic height. This was a challenging but rewarding structure to build, as it required a deep understanding of tree rotations to maintain balance. This was mostly done by Jane Nim with some help debuging and reformating of mine.

  * **Core Logic (`AVLTree.h`):**
      * Implemented the node structure, including height tracking.
      * Wrote the insertion and deletion methods that trigger rebalancing checks.
      * Coded the four rotation cases (Left, Right, Left-Right, and Right-Left) that are the cornerstone of the AVL algorithm.
  * **Key Feature:** Guarantees **O(log n)** time complexity for search, insertion, and deletion, which my performance analysis confirmed was significantly faster than a linear search.

### 2\. Hash Table

A highly efficient data structure that maps keys to values for near-constant time access. I chose a specific combination of hashing and collision resolution to optimize performance. This was completely done by me in the project.

  * **Core Logic (`hashtable.h`):**
      * **Fibonacci Hashing:** I implemented a Fibonacci hashing function (`(key * A) % tableSize` where A is the golden ratio). I chose this method because it's known for its excellent key distribution, which helps minimize collisions.
      * **Chaining for Collision Resolution:** To handle cases where two keys hash to the same index, I used separate chaining with `std::list`. Each bucket in the table is a linked list of values that hashed to that location.
  * **Key Feature:** Achieves an average time complexity of **O(1)** for all operations, making it the fastest structure in my tests, especially for search and insertion.

### 3\. Linked List

This implementation served as our baseline to provide a clear comparison against the more advanced data structures. This was also completely done by me in the project

  * **Core Logic (`linked_list_imp.h`):**
      * Utilized the standard C++ `std::list` to perform operations.
      * The search algorithm is a simple linear scan through the list.
  * **Key Feature:** Demonstrates **O(n)** time complexity, which, as expected, was significantly slower and effectively highlights the advantages of the AVL and Hash Table structures.

-----

## Performance Analysis and Results

To benchmark the data structures, I wrote driver programs (`*-driver.cpp`) that timed bulk operations using the `<chrono>` library. Each structure was subjected to the same test:

1.  **Insert:** Insert 10,000 unique random integers from `random_values_10k.txt`.
2.  **Search:** Search for 10,000 integers from `search_values_10k.txt`.
3.  **Delete:** Delete 10,000 integers from `delete_values_10k.txt`.

The results clearly aligned with theoretical Big O notation, providing a practical demonstration of why choosing the right data structure is critical.

| Data Structure  | Insert Time (ms) | Search Time (ms) | Delete Time (ms) |
| :-------------- | :--------------: | :--------------: | :--------------: |
| **Linked List** |        2         |        28        |        42        |
| **AVL Tree** |        10        |        4         |        5         |
| **Hash Table** |        4         |        1         |        2         |

*Table: Execution time for 10,000 operations.*

As shown, the **Hash Table** was the clear winner in terms of raw speed for search and delete, while the **AVL Tree** also offered a massive performance improvement over the Linked List.

-----

## How to Compile and Run

Each data structure has its own driver and can be compiled and run independently.

**Prerequisites:**

  * A C++ compiler that supports C++11 or later (e.g., g++).
  * The `.txt` data files in the same directory as the executable.
  * Un-comment the respecive .cpp files when using each different search algorithm.

**1. Compile an Implementation:**
Open a terminal and use the following commands:

```bash
# To compile the AVL Tree
g++ -std=c++11 -o avl_test avl-driver.cpp

# To compile the Hash Table
g++ -std=c++11 -o hash_test hash-driver.cpp

# To compile the Linked List
g++ -std=c++11 -o list_test list-driver.cpp
```

**2. Run the Executable:**
Run the compiled program and follow the on-screen menu prompts to load, search, delete, and print data.

```bash
# Example for AVL Tree
./avl_test
```

You will be prompted to enter the filenames for the datasets (`random_values_10k.txt`, etc.).

-----

## My Contributions to the Project

As documented in our group's project report, I was responsible for:

  * Developing the complete C++ implementation for the **Linked list Tree**.
  * Developing the C++ implementation for the **Hash Table** using the Fibonacci hashing method.
  * Writing the main driver programs for both the AVL Tree and Hash Table to enable user interaction and testing.
  * Conducting comprehensive testing and benchmarking on all three data structures to gather the performance data.
  * Explaining the technical details of the Fibonacci hashing method for our final report.

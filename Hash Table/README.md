# Hash Table Project

## Overview

This project is a demonstration of a Hash Table implementation in C++. It includes functionalities such as adding, removing, searching for, and displaying bids from a dataset. The Hash Table uses chaining as a method to resolve collisions, ensuring efficient data management even in scenarios of high collision.

The project parses auction data from CSV files and provides a user-friendly console interface to interact with the data through a hash table. This implementation showcases the core concepts of data structures and algorithms, particularly focusing on hash tables, linked lists, and collision resolution techniques.

## Features

- **Load Bids**: Import auction data from a CSV file into the hash table.
- **Display All Bids**: List all bids stored in the hash table.
- **Find Bid**: Search for a bid by its ID.
- **Remove Bid**: Delete a bid from the hash table.

## How to Run

1. Clone this repository to your local machine.
2. Ensure you have a C++ compiler installed.
3. Compile the source code. For example, if you are using `g++`, you can compile with:
   ```
   g++ HashTable.cpp -o HashTable
   ```
4. Run the compiled program, optionally passing the path to a CSV file as an argument:
   ```
   ./HashTable path/to/your/csvfile.csv
   ```

## Development

This project was developed incrementally, starting from basic data structure designs to implementing complex functionalities like collision resolution through chaining. One of the significant challenges was managing pointers within the hash table and ensuring efficient memory management to prevent leaks. Additionally, creating an effective hash function that minimizes collisions and distributes data evenly was crucial for the performance of the hash table.

Through careful testing, debugging, and optimization, this project demonstrates a practical implementation of a hash table in managing and querying auction data efficiently.
/**
// ============================================================================
// Name        : HashTable2.cpp
// Author      : Ryan Hatch
// Version     : 1.0.2
// Copyright   : Copyright © 2024
// Description : Hash Table implementation in C++
// ============================================================================
**/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"
#include <WinUser.h>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node *next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) : Node() {
            bid = aBid;
        }

        // initialize with a bid and a key
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    vector<Node*> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    // unsigned int hash(int key);
public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    unsigned int hash(std::string bidId);
};

/**
 * Default constructor
 */
HashTable::HashTable() : tableSize(404) {
    nodes.resize(tableSize, nullptr);    // Resize nodes to tableSize and initialize with nullptr
}
/** ^^FIX ME^^ (1): Initialize the structures used to hold bids and initialize node structure by resizing tableSize. */

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) : tableSize(size) {
    nodes.resize(tableSize); // Resize nodes to the specified tableSize
}

/**
 * Destructor
 */
HashTable::~HashTable() {
    for (unsigned int i = 0; i < tableSize; ++i) {
        Node* current = nodes[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
}

/***    // ^^FIX ME (2):^^ Implement logic to free storage when class is destroyed and then is to erase nodes beginning  */
/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
// unsigned int HashTable::hash(int key) {
//     return key % tableSize;
// }

unsigned int HashTable::hash(std::string bidId) {
unsigned int hashValue = 0;
for (char c : bidId) {
    hashValue = hashValue * 31 + c;
    }
return hashValue % tableSize;
}
/**    // ^^FIX ME (3):^^ Implement logic to calculate a hash value and to return key tableSize.    */

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {   
    unsigned int key = hash(bid.bidId);
    Node* newNode = new Node(bid, key);

    if (nodes[key] == nullptr) {
        nodes[key] = newNode;
    } else {
        Node* temp = nodes[key];
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
/**    // FIX ME (4): Implement logic to insert a bid, create the key for the given bid, retrieve node using key. If no entry found for the key, assign this node to the key position. Else if node is not used. Passing old node key to UNIT_MAX, set to key, set old node to bid and old node next to null pointer. Else find the next open node, then add new newNode to end   */

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    for (unsigned int i = 0; i < tableSize; ++i) {
        Node* node = nodes[i];
        while (node != nullptr) {
            cout << "Key " << node->key << ": " << node->bid.bidId << " | "
                 << node->bid.title << " | " << node->bid.amount << " | "
                 << node->bid.fund << endl;
            node = node->next;
        }
    }
}
/**    // FIXME (5): Implement logic to print all bids. For node begin to end iterate. If key not equal to UINT_MAx then output key, bidID, title, amount and fund. Node is equal to next iter. while node not equal to nullptr then output key, bidID, title, amount and fund. Node is equal to next node. */

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    unsigned int key = hash(bidId); 
    Node* node = nodes[key];
    Node* prev = nullptr;
    while (node->next != nullptr) {
        if (node->next->bid.bidId == bidId) {
            Node* temp = node->next;
            node->next = node->next->next;
            delete temp;
            break;
        }
        prev = node;
        node = node->next;
    }
}
/**    // FIXME (6): Implement logic to remove a bid. Then set key equal to hash atoi bidID cstring and then erase node begin and key. */

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    unsigned int key = hash(bidId);

    Node* node = nodes[key];
    Node* prev = nullptr;
    while (node != nullptr) {
        if (node->bid.bidId == bidId) {
            return node->bid;
        }
        node = node->next;
    }

    Bid bid; // Declare a variable named bid of type "Bid"
    return bid;
}
/**    // FIXME (7): Implement logic to search for and return a bid. Create the key for the given bid. if entry found for the key then return node bid.If no entry found for the key then return bid. While node is not equal to nullptr then if the current node matches, return node bid. If not equal to nullptr, set node equal to next node. */

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;
    bidTable = new HashTable();
    
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

// unsigned int HashTable::hash(std::string bidId)
// {
//     return 0;
// }

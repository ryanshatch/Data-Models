//============================================================================
// Name        : LinkedList.cpp
// Author      : Ryan Hatch
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <string>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

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
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    //Internal structure for list entries, housekeeping variables
    struct Node {
        Bid bid;
        Node *next;

        // default constructor
        Node() {
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) {
            bid = aBid;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size = 0;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);       /** append adds a new node to the end of the list **/
    void Prepend(Bid bid);      /** prepend adds a new node to the beginning of the list **/
    void PrintList();           /** printList displays all nodes in the list **/
    void Remove(string bidId);  /** remove deletes a node from the list **/
    Bid Search(string bidId);   /** search finds a node in the list **/
    int Size();                 /** size returns the number of nodes in the list **/
};

/**
 * FIX ME (1): Initialize housekeeping variables
 * set head and tail equal to null
**/

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    head = nullptr; /** head is the first node in the list **/
    tail = nullptr; /** tail is the last node in the list **/
    size = 0;       /** size is the number of nodes in the list **/
}


/**
 * Destructor
 */
LinkedList::~LinkedList() {
    // start at the head
    Node* current = head;
    Node* temp;

    // loop over each node, detach from list then delete
    while (current != nullptr) {
        temp = current; // hang on to current node
        current = current->next; // make current the next node
        delete temp; // delete the orphan node
    }
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // FIX ME (2): Implement append logic
    //Create new node
    //if there is nothing at the head...
            // new node becomes the head and the tail
    //else 
        // make current tail node point to the new node
        // and tail becomes the new node
    //increase size count

    if (head == nullptr) {
        /** This is the first node in the list **/
        head = new Node;
        tail = new Node;
    } else {
        /** If the list is not empty, add the new node to the end of the list **/
        tail->next = new Node;   /** make the current tail node point to the new node **/
        tail = new Node;         /** and make the new node the tail **/
    }

    size++; /** increase the size count **/
}


/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // FIX ME (3): Implement prepend logic
    // Create new node
    Node* newNode = new Node(bid);
    
    // if there is already something at the head...
        // new node points to current head as its next node
    if (head != nullptr) {
        newNode->next = head;
    } else {
        // if the list is empty, the new node becomes the tail
        tail = newNode;
    }
    // head now becomes the new node
    head = newNode;
    //increase size count
    size++;
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // FIXME (4): Implement print logic
    // start at the head
    Node* current = head;

    // while loop over each node looking for a match
    while (current != nullptr) {
        // Output current bidID, title, amount, and fund
        cout << current->bid.bidId << ": " << current->bid.title << " | " 
             << current->bid.amount << " | " << current->bid.fund << endl;

        //set current equal to next
        current = current->next;
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // FIX ME (5): Implement remove logic
    // Special case if matching node is the head
    if (head != nullptr && head->bid.bidId == bidId) {
        Node* temp = head;   // Hold onto the current head
        head = head->next;   // Make head point to the next node
        delete temp;         // Free up memory held by the old head
        size--;              // Decrease size count
        return;
    }

    // Start at the head
    Node* current = head;

    // While loop over each node looking for a match
    while (current != nullptr && current->next != nullptr) {
        // If the next node's bidID is equal to the current bidID
        if (current->next->bid.bidId == bidId) {
            Node* temp = current->next;      // Hold onto the next node temporarily
            current->next = current->next->next;  // Make current node point beyond the next node

            // If the node to be removed is the tail, update the tail
            if (temp == tail) {
                tail = current;
            }

            delete temp;    // Now free up memory held by temp
            size--;         // Decrease size count
            return;
        }

        // Current node is equal to the next node
        current = current->next;
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // FIX ME (6): Implement search logic

    // special case if matching node is the head
        // make head point to the next node in the list
        //decrease size count
        //return
        
    // Start at the head of the list
    Node* current = head;

    // Keep searching until the end is reached
    while (current != nullptr) {
        // If the current node matches, return it
        if (current->bid.bidId == bidId) {
            return current->bid;
        }

        // Else, the current node is equal to the next node
        current = current->next;
    }

    // Return an empty bid if not found
    return Bid();
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
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
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
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

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

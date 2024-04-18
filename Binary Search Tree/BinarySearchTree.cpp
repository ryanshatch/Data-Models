//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Ryan Hatch
// Version     : 1.2
// Copyright   : Copyright © 2017
// Description : Working with Data Structures using Binary Search Trees (BST)
//============================================================================

#include <algorithm> 
#include <iostream>
#include <time.h>
#include <windows.h>

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

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // // initialize with a bid
    // Node(Bid aBid) :
    //         Node() {
    //     bid = aBid;
    // }
    // initialize with a bid
    Node(Bid aBid) {
        bid = aBid;
        left = nullptr;
        right = nullptr;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root; // root of the tree set to null at start
    Node* nullPtr; // null pointer set to null at start
    Node* current; // current node set to null at start

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);
    int size = 0;   // node count in the tree set to be empty at start

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    // void PostOrder();
    // void PreOrder();
    void Insert(Bid bid);   // insert a bid into the tree
    void Remove(string bidId);  // remove a bid from the tree
    Bid Search(string bidId);   // search for a bid in the tree
    int Size(); // Used to return the size of the tree
    Node* findMin();    // find the minimum value in the tree
    Node* findMax();    // find the maximum value in the tree
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    // root = nullptr;
    this->root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (2): In order root
    // call inOrder fuction and pass root
    inOrder(root); 
}

/**
 * Traverse the tree in post-order
 *
 * void BinarySearchTree::PostOrder() {
 *     implementation of post-order traversal
 * }
 */

/**
 * Traverse the tree in pre-order
 *
//void BinarySearchTree::PreOrder() {
   // FixMe (4): Pre order root
   // preOrder root
*/

// void BinarySearchTree::Insert(Bid bid) {
    // FIXME (5) Implement inserting a bid into the tree
        // if root equal to null ptr
            // root is equal to new node bid
        // else
            // add Node root and bid

            // Create a new node with the bid
    // Node* newNode = new Node(bid);

    // Node* current = root; // set the current node to the root of the tree

    // If the tree is empty, the new node becomes the root
void BinarySearchTree::Insert(Bid bid) {
    Node* newNode = new Node(bid); // Create a new node with the bid
    if (root == nullptr) {
        root = newNode; // Set the root to the new node if the tree is empty
    } else {
        Node* current = root; // Start from the root
        while (true) {
            if (bid.bidId < current->bid.bidId) {
                // Go to the left subtree
                if (current->left == nullptr) {
                    current->left = newNode; // Insert the new node here
                    break;
                } else {
                    current = current->left; // Move to the left child
                }
            } else {
                // Go to the right subtree
                if (current->right == nullptr) {
                    current->right = newNode; // Insert the new node here
                    break;
                } else {
                    current = current->right; // Move to the right child
                }
            }
        }
    }
}

// Node* BinarySearchTree::findMin() {
//     Node* current = root;
//     while (current && current->left != nullptr) {
//         current = current->left;
//     }
//     return current;
// }


Node* BinarySearchTree::findMax() {
    Node* current = root;
    // Traverse the right sub-tree until you reach the node with the largest value
    while (current && current->right != nullptr) {
        current = current->right;
    }

    return current;
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(std::string bidId) {
    Node* parent = nullptr;
    Node* current = root;
    while (current != nullptr) {
        if (current->bid.bidId == bidId) {
            // Node found, now remove it

            // Case 1: Node has no children
            if (current->left == nullptr && current->right == nullptr) {
                if (parent == nullptr) {
                    root = nullptr;
                } else if (parent->left == current) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
                delete current;
            }
            // Case 2: Node has one child
            else if (current->left == nullptr || current->right == nullptr) {
                Node* child = (current->left != nullptr) ? current->left : current->right;
                if (parent == nullptr) {
                    root = child;
                } else if (parent->left == current) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
                delete current;
            }
            // Case 3: Node has two children
            else {
                // Find the successor (smallest node in the right subtree)
                Node* successorParent = current;
                Node* successor = current->right;
                while (successor->left != nullptr) {
                    successorParent = successor;
                    successor = successor->left;
                }

                // Replace the current node's bid with the successor's bid
                current->bid = successor->bid;

                // Remove the successor node
                if (successorParent->left == successor) {
                    successorParent->left = successor->right;
                } else {
                    successorParent->right = successor->right;
                }
                delete successor;
            }
        }
    }
}
    

// void BinarySearchTree::Remove(string bidId) {
//     // FIXME (6) Implement removing a bid from the tree
//     // remove node root bidID
//     Node* parent = nullptr;
//     Node* current = root;
//     while (current != nullptr) {
//         if (current->bid.bidId.compare(bidId) == 0) {
//             // Node found, now remove it

//             // Case 1: Node has no children
//             if (current->left == nullptr && current->right == nullptr) {
//                 if (parent == nullptr) {
//                     root = nullptr;
//                 } else if (parent->left == current) {
//                     parent->left = nullptr;
//                 } else {
//                     parent->right = nullptr;
//                 }
//                 delete current;
//             }
//             // Case 2: Node has one child
//             else if (current->left == nullptr || current->right == nullptr) {
//                 Node* child = (current->left != nullptr) ? current->left : current->right;
//                 if (parent == nullptr) {
//                     root = child;
//                 } else if (parent->left == current) {
//                     parent->left = child;
//                 } else {
//                     parent->right = child;
//                 }
//                 delete current;
//             }
//             // Case 3: Node has two children
//             else {
//                 Node* successor = (current->right);
//                 findMin; current->bid = successor->bid;
//                 current->right = removeNode(current->right, successor->bid.bidId);
//             }
//             return;
//         } else if (bidId < current->bid.bidId) {
//             parent = current;
//             current = current->left;
//         } else {
//             parent = current;
//             current = current->right;
//         }
//     }
//     cout << "Bid not found" << endl;
// }

/**
 * Search for a bid in the tree

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
// FIXME (7) Implement searching the tree for a bid
// set current node equal to root

// keep looping downwards until bottom reached or matching bidId found
    // if match found, return current bid

    // if bid is smaller than current node then traverse left
    // else larger so traverse right
Node* current = root; // set the current node to the root of the tree
while (current != nullptr) {
    // If the bid ID matches the current node's bid ID, return the bid.
    if (current->bid.bidId.compare(bidId) == 0) {
        return current->bid;
    }
    // If the bid ID is less than the current node's bid ID, move to the left child.
    if (bidId.compare(current->bid.bidId) < 0) {
        current = current->left;
    }
    // If the bid ID is greater than the current node's bid ID, move to the right child.
    else {
        current = current->right;
    }
// Bid bid;
// return bid;
}
}
/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (8) Implement inserting a bid into the tree
        // if node is larger then add to left
            // if no left node
                // this node becomes left
            // else recurse down the left node
                // else
        // if no right node
            // this node becomes right
        //else
    // recurse down the left node
    // Add the bid to the left side of the tree if the bid ID is less than the current node's bid ID
    if (node->bid.bidId.compare(bid.bidId) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(bid);
        } else {
            this->addNode(node->left, bid);
        }
    }
    // Add the bid to the right side of the tree if the bid ID is greater than or equal to the current node's bid ID
    else {
        if (node->right == nullptr) {
            node->right = new Node(bid);
        } else {
            this->addNode(node->right, bid);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
      // FixMe (9): Pre order root
      //if node is not equal to null ptr
      //InOrder not left
      //output bidID, title, amount, fund
      //InOder right
    if (node == nullptr) {
        return;
    }
    inOrder(node->left);    // recurse down the left node to the bottom of the tree.
    std::cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << std::endl; // output the bid details.
    inOrder(node->right);   // recurse down the right node to the bottom of the tree.
}


// void BinarySearchTree::postOrder(Node* node) {
      // FixMe (10): Pre order root
      //if node is not equal to null ptr
      //postOrder left
      //postOrder right
      //output bidID, title, amount, fund

//     Bid bid;
//     Node* current = nullptr; // set the current node to the root of the tree
//       // if node is not equal to nullptr
//         if (node != nullptr) {
//             // recurse down the left node to the bottom of the tree.
//             postOrder(node->left);
//             // recurse down the right node to the bottom of the tree.
//             postOrder(node->right);
//             // output the bid details.
//             cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
//         }

// }

// void BinarySearchTree::preOrder(Node* node) {
      // FixMe (11): Pre order root
      //if node is not equal to null ptr
      //output bidID, title, amount, fund
      //postOrder left
      //postOrder right      
// }

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    std::cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    std::cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        std::cout << c << " | ";
    }
    std::cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
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

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

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
            loadBids(csvPath, bst);

            // cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

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
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
#ifndef OPENHASHUNSORTEDLIST_H
#define OPENHASHUNSORTEDLIST_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "Metrics.h"

using namespace std;

// Class for Open Hashing with Unsorted Linked List
class OpenHashUnsortedList
{
private:
    // Node structure for linked list
    struct Node
    {
        int key;                               // Key for hashing
        string word;                           // Word stored in the node
        Node *next;                            // Pointer to next node
        Node(int k) : key(k), next(nullptr) {} // Constructor
    };

    std::vector<Node *> table; // Hash table storing pointers to Nodes

    int size; // Size (hash table)

    // Hash function for generating index
    int hashFunction(int key) const;

public:
    // Constructor
    OpenHashUnsortedList(int size);

    // Destructor
    ~OpenHashUnsortedList();

    Metrics metrics; // for tracking operations

    // Insert
    void insert(const std::string &token);

    // Search
    bool search(const std::string &token);

    // Remove
    void remove(const string &token);

    // Print the hash table for debugging purposes
    void printTable() const;
};

#endif

#ifndef OPENHASHSORTEDLIST_H
#define OPENHASHSORTEDLIST_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "Metrics.h"

using namespace std;

class OpenHashSortedList
{
private:
    // Node structure
    struct Node
    {
        int key;                               // Key for hashing
        string word;                           // Word associated with the key
        Node *next;                            // Pointer to the next node in the list
        Node(int k) : key(k), next(nullptr) {} // Constructor
    };

    std::vector<Node *> table; // Hash table storing pointers to nodes

    int size; // Size of the hash table

    int hashFunction(int key) const; // Hash function for computing index

    void insertSorted(Node *&head, int key, const string &word); // Insert node into sorted linked list

public:
    OpenHashSortedList(int size); // Constructor
    ~OpenHashSortedList();        // Destructor
    Metrics metrics;              // for tracking operations

    void insert(const std::string &token); // Insert a word into the hash table

    bool search(const std::string &token); // Search for a word in the hash table

    void insertByKeys(int key); // Insert node by key (for internal use)

    void remove(const string &token); // Remove a word from the hash table

    void printTable() const; // Print the hash table for debugging purposes
};

#endif // OPENHASHSORTEDLIST_H

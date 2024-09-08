#ifndef CLOSEDHASHING_H
#define CLOSEDHASHING_H

#include <string>
#include <vector>
#include "Metrics.h"

class ClosedHashing
{
private:
    std::vector<std::string> table; // Hash table to store strings
    std::vector<bool> isOccupied;   // Occupancy status for each slot
    int tableSize;                  // Size of the hash table

    int hashFunction(int key) const; // Hash function

public:
    Metrics metrics; // for operation tracking

    ClosedHashing(int size); // Constructor:

    void insert(const std::string &token); // Insert a token into the hash table

    bool search(const std::string &token); // Search for a token in the hash table

    void remove(const std::string &token); // Remove a token from the hash table

    void printTable() const; // Print the contents of the hash table
};

#endif

#include "ClosedHashing.h"
#include "TokenKeyGenerator.h"
#include <cmath>
#include <iostream>
using namespace std;

// Constructor: Initializes the table and occupancy vector
ClosedHashing::ClosedHashing(int size) : tableSize(size)
{
    table.resize(size, "");
    isOccupied.resize(size, false);
}

// Hash function:
int ClosedHashing::hashFunction(int key) const
{
    const double GOLDEN_RATIO = (sqrt(5.0) - 1) / 2;
    double product = GOLDEN_RATIO * key;
    double fraction = product - floor(product);
    double hashValue = tableSize * fraction;
    return static_cast<int>(floor(hashValue));
}

// Insert a word into the hash table
void ClosedHashing::insert(const string &word)
{
    metrics.incrementInsertOpr();            // Increment insert operations
    string token = convertWordToToken(word); // Convert word to token
    int key = generateKeys(token);
    int index = hashFunction(key); // Compute initial index
    int i = 0;
    while (i < tableSize) // Linear probing
    {
        metrics.incrementInsertProbes(); // Increment probe count
        if (!isOccupied[index])          // Check if slot is free
        {
            table[index] = word;
            isOccupied[index] = true; // Insert word & Mark slot as occupied
            return;
        }
        index = (index + 1) % tableSize; // Move to next index
        i++;
    }
    throw runtime_error("Table is full"); // Throw exception if table is full
}

// Search for a word in the hash table
bool ClosedHashing::search(const std::string &word)
{
    string token = convertWordToToken(word);
    int key = generateKeys(token);
    int index = hashFunction(key); // Compute initial index
    int i = 0;
    int probeCount = 0;
    while (i < tableSize) // Linear probing
    {
        probeCount++;
        if (table[index] == word) // Check if word matches
        {
            metrics.incrementSuccessSearchOpr();              // Increment successful search operations
            metrics.incrementSuccessSearchProbes(probeCount); // Increment successful search probes
            return true;
        }
        index = (index + 1) % tableSize; // Move to next index if word not found
        i++;
    }
    metrics.incrementUnsuccessSearchOpr();              // Increment unsuccessful search operations
    metrics.incrementUnsuccessSearchProbes(probeCount); // Increment unsuccessful search probes
    return false;                                       // Word not found
}

// Remove a word from the hash table
void ClosedHashing::remove(const std::string &word)
{
    string token = convertWordToToken(word); // Convert word to token
    int key = generateKeys(token);
    int index = hashFunction(key); // Compute initial index
    int i = 0;
    int probeCount = 0;
    while (i < tableSize) // Linear probing
    {
        probeCount++;             // Increment probe count
        if (table[index] == word) // Check if word matches
        {
            table[index] = "";                                // Clear the slot
            isOccupied[index] = false;                        // Mark slot as free
            metrics.incrementSuccessRemoveOpr();              // Increment successful remove operations
            metrics.incrementSuccessRemoveProbes(probeCount); // Increment successful remove probes
            return;
        }
        index = (index + 1) % tableSize; // Move to next index
        i++;
    }
    metrics.incrementUnsuccessRemoveOpr();              // Increment unsuccessful remove operations
    metrics.incrementUnsuccessRemoveProbes(probeCount); // Increment unsuccessful remove probes
}

// Print the contents of the hash table
void ClosedHashing::printTable() const
{
    for (int i = 0; i < tableSize; i++)
    {
        cout << i << ": ";
        if (isOccupied[i])
        {
            cout << table[i];
        }
        cout << endl;
    }
}

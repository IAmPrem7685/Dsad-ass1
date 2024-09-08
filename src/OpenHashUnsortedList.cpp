#include "OpenHashUnsortedList.h"
#include "TokenKeyGenerator.h"
#include <cmath>
#include <iostream>
using namespace std;

// Constructor: Initializes the hash table with a given size
OpenHashUnsortedList::OpenHashUnsortedList(int size) : size(size)
{
    table.resize(size, nullptr);
}

// Destructor: Cleans up allocated memory for each node in the table
OpenHashUnsortedList::~OpenHashUnsortedList()
{
    for (int i = 0; i < size; i++)
    {
        Node *current = table[i];
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }
}

// Hash function using the golden ratio
int OpenHashUnsortedList::hashFunction(int key) const
{
    const double GOLDEN_RATIO = (sqrt(5.0) - 1) / 2;
    double product = GOLDEN_RATIO * key;
    double fraction = product - floor(product);
    double hashValue = size * fraction;
    return static_cast<int>(floor(hashValue));
}

// Inserts a word into the hash table
// void OpenHashUnsortedList::insert(const string &word)
// {
//     metrics.incrementInsertOpr();    // Increment operation count
//     metrics.incrementInsertProbes(); // Increment probe count
//     string token = convertWordToToken(word);
//     int key = generateKeys(token);
//     int index = hashFunction(key); // Compute hash index
//     Node *newNode = new Node(key);
//     newNode->word = word;         // Set word in new node
//     newNode->next = table[index]; // Insert node at head of list
//     table[index] = newNode;
// }
void OpenHashUnsortedList::insert(const string &word)
{
    metrics.incrementInsertOpr(); // Increment operation count

    string token = convertWordToToken(word);
    int key = generateKeys(token);
    int index = hashFunction(key); // Compute hash index

    Node *newNode = new Node(key);
    newNode->word = word;    // Set word in new node
    newNode->next = nullptr; // The new node will be the last, so next is nullptr

    if (table[index] == nullptr)
    {                                    // If the linked list at this index is empty
        table[index] = newNode;          // Insert the new node as the first and only element
        metrics.incrementInsertProbes(); // Only one probe if no traversal is needed
    }
    else
    {
        Node *current = table[index];

        metrics.incrementInsertProbes(); // Increment probe count
        while (current->next != nullptr)
        { // Traverse to the end of the list
            current = current->next;
            metrics.incrementInsertProbes(); // Increment probe count with each step
        }
        current->next = newNode; // Append the new node at the end
        // Increment by the total probe count
    }
}

// Searches for a word in the hash table
bool OpenHashUnsortedList::search(const string &word)
{
    string token = convertWordToToken(word);
    int key = generateKeys(token);
    int index = hashFunction(key); // Compute hash index
    Node *current = table[index];
    int probeCount = 0; // Count probes
    if (current == nullptr)
    {
        probeCount++;
    }
    while (current != nullptr)
    {
        probeCount++;
        if (current->word == word) // Found the word
        {
            metrics.incrementSuccessSearchOpr();              // Increment success operation count
            metrics.incrementSuccessSearchProbes(probeCount); // Increment success probe count
            return true;
        }
        current = current->next; // Move to next node
    }
    metrics.incrementUnsuccessSearchOpr();              // Increment unsuccessful operation count
    metrics.incrementUnsuccessSearchProbes(probeCount); // Increment unsuccessful probe count
    return false;
}

// Removes a word from the hash table
void OpenHashUnsortedList::remove(const string &word)
{
    string token = convertWordToToken(word);
    int key = generateKeys(token);
    int index = hashFunction(key); // Compute hash index
    Node *current = table[index];
    Node *prev = nullptr;
    int probeCount = 0; // Count probes
    if (current == nullptr)
    {
        probeCount++;
    }
    while (current != nullptr)
    {
        probeCount++;
        if (current->word == word) // Found the word
        {
            if (prev == nullptr) // Remove node at head
            {
                table[index] = current->next;
            }
            else
            {
                prev->next = current->next; // Remove node from list
            }

            metrics.incrementSuccessRemoveOpr();              // Increment success operation count
            metrics.incrementSuccessRemoveProbes(probeCount); // Increment success probe count
            delete current;                                   // Free memory
            return;
        }

        prev = current;
        current = current->next; // Move to next node
    }
    metrics.incrementUnsuccessRemoveOpr();              // Increment unsuccessful operation count
    metrics.incrementUnsuccessRemoveProbes(probeCount); // Increment unsuccessful probe count
}

// Prints the hash table for debugging
void OpenHashUnsortedList::printTable() const
{
    for (int i = 0; i < size; i++)
    {
        cout << i << ": ";
        Node *current = table[i];
        while (current != nullptr)
        {
            cout << current->word << current->key << " ";
            current = current->next;
        }
        cout << endl;
    }
}

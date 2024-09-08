#include "OpenHashSortedList.h"
#include "TokenKeyGenerator.h"
#include <cmath>
#include <iostream>
using namespace std;

// Constructor: Initializes table with given size
OpenHashSortedList::OpenHashSortedList(int size) : size(size)
{
    table.resize(size, nullptr);
}

// Destructor: Cleans up allocated nodes
OpenHashSortedList::~OpenHashSortedList()
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

// Hash function
int OpenHashSortedList::hashFunction(int key) const
{
    const double GOLDEN_RATIO = (sqrt(5.0) - 1) / 2;
    double product = GOLDEN_RATIO * key;
    double fraction = product - floor(product);
    double hashValue = size * fraction;
    return static_cast<int>(floor(hashValue));
}

// Helper function to insert a node into a sorted linked list
void OpenHashSortedList::insertSorted(Node *&head, int key, const string &word)
{
    metrics.incrementInsertOpr(); // Increment operation count

    Node *newNode = new Node(key);
    newNode->word = word;
    if (head == nullptr || head->key > key)
    {
        metrics.incrementInsertProbes(); // Increment probe count
        newNode->next = head;
        head = newNode;
    }
    else
    {
        Node *current = head;
        metrics.incrementInsertProbes(); // Increment probe count
        while (current->next != nullptr && current->next->key < key)
        {
            metrics.incrementInsertProbes(); // Increment probe count
            current = current->next;
        }
        metrics.incrementInsertProbes(); // Increment probe count

        newNode->next = current->next;
        current->next = newNode;
    }
}

// Insert a word into the hash table
void OpenHashSortedList::insert(const string &word)
{
    string token = convertWordToToken(word);
    int key = generateKeys(token);
    int index = hashFunction(key);         // Compute hash index
    insertSorted(table[index], key, word); // Insert node into sorted list
}

// Search for a word in the hash table
bool OpenHashSortedList::search(const string &word)
{
    string token = convertWordToToken(word);
    int key = generateKeys(token);
    int index = hashFunction(key); // Compute hash index
    Node *current = table[index];
    int probCount = 0;
    if (current == nullptr)
    {
        probCount++; // Increment unsuccessful operation count
    }
    while (current != nullptr)
    {
        probCount++;
        if (current->key > key)
        {
            break; // Stop if key is greater than current
        }
        if (current->word == word)
        {
            metrics.incrementSuccessSearchOpr();             // Increment success operation count
            metrics.incrementSuccessSearchProbes(probCount); // Increment probe count
            return true;
        }
        current = current->next;
    }
    metrics.incrementUnsuccessSearchOpr();             // Increment unsuccessful operation count
    metrics.incrementUnsuccessSearchProbes(probCount); // Increment probe count
    return false;
}

// Remove a word from the hash table
void OpenHashSortedList::remove(const string &word)
{
    string token = convertWordToToken(word);
    int key = generateKeys(token);
    int index = hashFunction(key); // Compute hash index
    Node *current = table[index];
    Node *prev = nullptr;
    int probCount = 0;
    while (current != nullptr)
    {
        probCount++;
        if (current->key > key)
        {
            break; // Stop if key is greater than current
        }
        if (current->word == word)
        {
            if (prev == nullptr)
            {
                metrics.incrementSuccessRemoveOpr();             // Increment success operation count
                metrics.incrementSuccessRemoveProbes(probCount); // Increment probe count
                table[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current; // Delete the node
            return;
        }
        metrics.incrementUnsuccessRemoveOpr();             // Increment unsuccessful operation count
        metrics.incrementUnsuccessRemoveProbes(probCount); // Increment probe count
        prev = current;
        current = current->next;
    }
}

// Print the hash table for debugging purposes
void OpenHashSortedList::printTable() const
{
    for (int i = 0; i < size; i++)
    {
        Node *current = table[i];
        cout << i << ": ";
        while (current != nullptr)
        {
            cout << current->word << " ";
            current = current->next;
        }
        cout << endl;
    }
}

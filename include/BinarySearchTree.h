#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <string>
#include "Metrics.h"
using namespace std;

class BinarySearchTree
{
private:
    // Structure representing a node in the binary search tree
    struct Node
    {
        int key;
        string word;
        Node *left;
        Node *right;

        // Constructor for creating a node with a key and word
        Node(int v, const string &word) : key(v), word(word), left(nullptr), right(nullptr) {}
    };

    Node *root; // Pointer to the root node of the BST

    // Helper functions for recursive operations
    Node *insert(Node *node, int key, const string &word); // Recursive insertion
    Node *search(Node *node, int key, int &probeCount);    // Recursive search
    Node *remove(Node *node, int key, int &probeCount);    // Recursive deletion
    Node *findMin(Node *node);                             // Find the minimum node in the subtree
    void destroyTree(Node *node);                          // Recursive function to delete the tree
    void inorderTraversal(Node *node);                     // Recursive inorder traversal
    void visualTraversal(Node *node, int depth);           // Recursive visual traversal (tree view)

public:
    // Constructor and Destructor
    BinarySearchTree();
    ~BinarySearchTree();

    Metrics metrics; // for tracking operations and probes

    void insert(string word); // Insert a word into the BST
    bool search(string word); // Search for a word in the BST
    void remove(string word); // Remove a word from the BST
    void inorderTraversal();  // inorder traversal of the BST for debugging
    void visualTraversal();   // Visual representation of the BST for debugging
};

#endif

#include "BinarySearchTree.h"
#include "TokenKeyGenerator.h"
#include <iostream>
#include <string>
using namespace std;

// Constructor:
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

// Destructor:
BinarySearchTree::~BinarySearchTree()
{
    destroyTree(root);
}

// Recursively delete nodes in the subtree rooted at node
void BinarySearchTree::destroyTree(Node *node)
{
    if (node != nullptr)
    {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Recursively insert a new node into the tree
BinarySearchTree::Node *BinarySearchTree::insert(Node *node, int key, const string &word)
{
    if (node == nullptr)
    {
        metrics.incrementInsertProbes(); // Increment probes for insertion
        return new Node(key, word);
    }
    metrics.incrementInsertProbes();
    if (key < node->key) // Insert into the left subtree if key is smaller
    {
        node->left = insert(node->left, key, word);
    }
    else // Insert into the right subtree if key is larger
    {
        node->right = insert(node->right, key, word);
    }

    return node;
}

// Recursively search for a node by its key and count probes
BinarySearchTree::Node *BinarySearchTree::search(Node *node, int key, int &probeCount)
{
    if (node == nullptr || node->key == key)
    {
        probeCount++; // Final probe for finding or confirming absence of key
        return node;  // Return node if found or null if not
    }

    probeCount++;
    if (key < node->key) // Search in left subtree
    {
        return search(node->left, key, probeCount);
    }
    else // Search in right subtree
    {
        return search(node->right, key, probeCount);
    }
}

// Recursively remove a node from the tree by key
BinarySearchTree::Node *BinarySearchTree::remove(Node *node, int key, int &probeCount)
{
    if (node == nullptr)
    {
        probeCount++;
        return node;
    }

    probeCount++;
    if (key < node->key) // Search in the left subtree  to remove
    {
        node->left = remove(node->left, key, probeCount);
    }
    else if (key > node->key) // Search in the right subtree to remove
    {
        node->right = remove(node->right, key, probeCount);
    }
    else // Node found
    {
        if (node->left == nullptr) // Case 1: Node has no left child
        {
            Node *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) // Case 2: Node has no right child
        {
            Node *temp = node->left;
            delete node;
            return temp;
        }

        // Case 3: Node has two children, replace with minimum node in the right subtree
        Node *temp = findMin(node->right);
        node->key = temp->key; 
        node->right = remove(node->right, temp->key, probeCount); 
    }

    return node;
}

// Find the node with the minimum key in a subtree
BinarySearchTree::Node *BinarySearchTree::findMin(Node *node)
{
    while (node && node->left != nullptr)
    {
        node = node->left; 
    }
    return node;
}

// Perform an inorder traversal of the tree
void BinarySearchTree::inorderTraversal(Node *node)
{
    if (node != nullptr)
    {
        inorderTraversal(node->left);
        std::cout << node->key << "|" << node->word << " "; // Print the key and word
        inorderTraversal(node->right);
    }
}

// Public method to insert a word into the tree
void BinarySearchTree::insert(string word)
{
    metrics.incrementInsertOpr(); // Increment the insert operation count
    string token = convertWordToToken(word);
    int key = generateKeys(token);
    root = insert(root, key, word); // Insert the word by its key
}

// Public method to search for a word in the tree
bool BinarySearchTree::search(string word)
{
    string token = convertWordToToken(word);
    int key = generateKeys(token);
    int probeCount = 0;
    Node *result = search(root, key, probeCount);

    if (result != nullptr)
    {
        metrics.incrementSuccessSearchOpr(); // Increment successful search count
        metrics.incrementSuccessSearchProbes(probeCount); // Track probes for successful search
        return true;
    }
    else
    {
        metrics.incrementUnsuccessSearchOpr(); // Increment unsuccessful search count
        metrics.incrementUnsuccessSearchProbes(probeCount); // Track probes for unsuccessful search
        return false;
    }
}

// Public method to remove a word from the tree
void BinarySearchTree::remove(string word)
{
    string token = convertWordToToken(word);
    int key = generateKeys(token);
    int probeCount = 0;
    Node *result = search(root, key, probeCount);

    if (result != nullptr)
    {
        metrics.incrementSuccessRemoveOpr(); // Increment successful remove count
        metrics.incrementSuccessRemoveProbes(probeCount); // Track probes for successful remove
        root = remove(root, key, probeCount);
    }
    else
    {
        metrics.incrementUnsuccessRemoveOpr(); // Increment unsuccessful remove count
        metrics.incrementUnsuccessRemoveProbes(probeCount); // Track probes for unsuccessful remove
    }
}

// Public method to start an inorder traversal
void BinarySearchTree::inorderTraversal()
{
    inorderTraversal(root);
    std::cout << std::endl;
}

// Visual traversal of the tree: Print the tree structure
void BinarySearchTree::visualTraversal(Node *node, int depth)
{
    if (node != nullptr)
    {
        visualTraversal(node->right, depth + 1); // Print right subtree with indentation

        // Indent based on depth level
        for (int i = 0; i < depth; ++i) 
        {
            cout << "    "; // Four spaces for each level
        }

        cout << "(" << node->key << ", " << node->word << ")" << endl; // Print current node

        visualTraversal(node->left, depth + 1); // Print left subtree
    }
}

// Public method to initiate visual traversal from the root
void BinarySearchTree::visualTraversal()
{
    visualTraversal(root, 0);
}

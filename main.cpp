#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "ClosedHashing.h"
#include "OpenHashUnsortedList.h"
#include "OpenHashSortedList.h"
#include "BinarySearchTree.h"
#include "TokenKeyGenerator.h"

using namespace std;

int main()
{
    // Declare variables for user input
    vector<int> m = {1000};                        // Hash table sizes
    int n = 400;                                   // Number of initial insertions
    vector<int> methods = {1, 2, 4, 3};            // Methods to evaluate
    string inputFile = "input/testcase_large.txt"; // Input text file
    // string operationInput = "10220001112221010";   // Radix-3 string for operations
    string operationInput = "12";

    // OpenHashSortedList hashTable(10);
    // hashTable.insert("ab");
    // hashTable.insert("ba");
    // hashTable.insert("c");
    // hashTable.insert("d");
    // hashTable.search("a");
    // hashTable.search("b");
    // hashTable.search("c");
    // hashTable.search("d");
    // cout << hashTable.metrics.getAverageSuccessSearchProbes() << endl;
    // cout << hashTable.metrics.getAverageUnsuccessSearchProbes() << endl;
    // cout << hashTable.metrics.getAverageInsertProbes() << endl;

    // Get user input for hash table sizes
    // cout << "Enter hash table sizes (space-separated, e.g., 500 200 70000 1000): ";
    // string mInput;
    // getline(cin, mInput);
    // istringstream mStream(mInput);
    // int mVal;
    // while (mStream >> mVal)
    // {
    //     m.push_back(mVal);
    // }

    // // Get user input for number of initial insertions
    // cout << "Enter number of initial insertions: ";
    // cin >> n;

    // // Get user input for methods to evaluate
    // cout << "Enter methods to evaluate (space-separated, e.g., 1 2 3 4): ";
    // string methodInput;
    // cin.ignore(); // Ignore leftover newline
    // getline(cin, methodInput);
    // istringstream methodStream(methodInput);
    // int methodVal;
    // while (methodStream >> methodVal)
    // {
    //     methods.push_back(methodVal);
    // }

    // // Get user input for Radix-3 string for operations
    // cout << "Enter Radix-3 string for operations (e.g., 0000000000): ";
    // cin >> operationInput;

    // Generate tokens from the input file
    vector<string> tokens;
    tokens = generateWords(inputFile);

    // Print performance metrics header
    cout << "Performance Metrics for Hash Tables" << endl;
    cout << "|------------------------|-----------|-------------------------------|--------------------------------|" << endl;
    cout << "| Data Structure         |           | Avg. Search Probes            | Avg. Remove Probes             |" << endl;
    cout << "|------------------------|Avg. Insert|-------------------------------|-----------|--------------------|" << endl;
    cout << "|                        |    Probes |Success   |Unsuccess |  Total  |Success   |Unsuccess |   Total  |" << endl;
    cout << "|------------------------|-----------|----------|----------|---------|----------|----------|----------|" << endl;

    // Loop through each method and hash table size
    for (int method : methods)
    {
        for (int m : m)
        {

            // Open Hash with Unsorted List
            if (method == 1)
            {
                OpenHashUnsortedList hashTable(m);
                // Initial insertions
                for (int i = 0; i < n; i++)
                {
                    hashTable.insert(tokens[i]);
                }

                // Perform operations as per operationInput
                for (int i = n; i < tokens.size(); i++)
                {
                    for (char op : operationInput)
                    {
                        if (op == '0')
                        {
                            hashTable.search(tokens[i]); // Search operation
                        }
                        else if (op == '1')
                        {
                            hashTable.insert(tokens[i]); // Insert operation
                        }
                        else if (op == '2')
                        {
                            hashTable.remove(tokens[i]); // Remove operation
                        }
                    }
                }

                // Output metrics for this method and hash table size
                cout << "|Open Hash Unsorted(" << m << ") | " << std::fixed << std::setprecision(6)
                     << hashTable.metrics.getAverageInsertProbes() << " | "
                     << hashTable.metrics.getAverageSuccessSearchProbes() << " | "
                     << hashTable.metrics.getAverageUnsuccessSearchProbes() << " | "
                     << hashTable.metrics.getAverageTotalSearchProbes() << " | "
                     << hashTable.metrics.getAverageSuccessRemoveProbes() << " | "
                     << hashTable.metrics.getAverageUnsuccessRemoveProbes() << " |"
                     << hashTable.metrics.getAverageTotalRemoveProbes() << "|" << endl;

                // cout << hashTable.metrics.insertMetrics.first << " " << hashTable.metrics.insertMetrics.second << endl;
                // hashTable.printTable();
            }
            // Open Hash with Sorted List
            else if (method == 2)
            {
                OpenHashSortedList hashTable(m);
                for (int i = 0; i < n; i++)
                {
                    hashTable.insert(tokens[i]);
                }

                for (int i = n; i < tokens.size(); i++)
                {
                    for (char op : operationInput)
                    {
                        if (op == '0')
                        {
                            hashTable.search(string(tokens[i]));
                        }
                        else if (op == '1')
                        {
                            hashTable.insert(tokens[i]);
                        }
                        else if (op == '2')
                        {
                            hashTable.remove(tokens[i]);
                        }
                    }
                }
                cout << "| Open Hash Sorted(" << m << ")   | " << std::setprecision(6)
                     << hashTable.metrics.getAverageInsertProbes() << " | "
                     << hashTable.metrics.getAverageSuccessSearchProbes() << " | "
                     << hashTable.metrics.getAverageUnsuccessSearchProbes() << " | "
                     << hashTable.metrics.getAverageTotalSearchProbes() << " | "
                     << hashTable.metrics.getAverageSuccessRemoveProbes() << " | "
                     << hashTable.metrics.getAverageUnsuccessRemoveProbes() << " |"
                     << hashTable.metrics.getAverageTotalRemoveProbes() << " |" << endl;
            }
            // Closed Hashing
            else if (method == 3)
            {
                ClosedHashing hashTable(m);
                for (int i = 0; i < n; i++)
                {
                    hashTable.insert(tokens[i]);
                }

                for (int i = n; i < tokens.size(); i++)
                {
                    for (char op : operationInput)
                    {
                        if (op == '0')
                        {
                            hashTable.search(string(tokens[i]));
                        }
                        else if (op == '1')
                        {
                            hashTable.insert(tokens[i]);
                        }
                        else if (op == '2')
                        {
                            hashTable.remove(tokens[i]);
                        }
                    }
                }
                cout << "| Closed Hashing(" << m << ")     | " << std::setprecision(6)
                     << hashTable.metrics.getAverageInsertProbes() << " | "
                     << hashTable.metrics.getAverageSuccessSearchProbes() << " | "
                     << hashTable.metrics.getAverageUnsuccessSearchProbes() << " | "
                     << hashTable.metrics.getAverageTotalSearchProbes() << " | "
                     << hashTable.metrics.getAverageSuccessRemoveProbes() << " | "
                     << hashTable.metrics.getAverageUnsuccessRemoveProbes() << " |"
                     << hashTable.metrics.getAverageTotalRemoveProbes() << " |" << endl;
            }
        }
        // Binary Search Tree
        if (method == 4)
        {
            BinarySearchTree hashTable;
            for (int i = 0; i < n; i++)
            {
                hashTable.insert(tokens[i]);
            }

            for (int i = n; i < tokens.size(); i++)
            {
                for (char op : operationInput)
                {
                    if (op == '0')
                    {
                        hashTable.search(string(tokens[i]));
                    }
                    else if (op == '1')
                    {
                        hashTable.insert(tokens[i]);
                    }
                    else if (op == '2')
                    {
                        hashTable.remove(tokens[i]);
                    }
                }
            }
            cout << "| Binary Search Tree| " << std::fixed << std::setprecision(6)
                 << hashTable.metrics.getAverageInsertProbes() << " | "
                 << hashTable.metrics.getAverageSuccessSearchProbes() << " | "
                 << hashTable.metrics.getAverageUnsuccessSearchProbes() << " | "
                 << hashTable.metrics.getAverageTotalSearchProbes() << " | "
                 << hashTable.metrics.getAverageSuccessRemoveProbes() << " | "
                 << hashTable.metrics.getAverageUnsuccessRemoveProbes() << " |"
                 << hashTable.metrics.getAverageTotalRemoveProbes() << " |" << endl;
        }
    }

    return 0;
}

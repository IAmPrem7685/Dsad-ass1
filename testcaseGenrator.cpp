#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to generate a random token of length 10
string generateRandomString(int minLength, int maxLength)
{
    // Characters allowed in the random string (letters, digits, and symbols)
    const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=<>?";

    // Generate a random length between minLength and maxLength
    int length = minLength + rand() % (maxLength - minLength + 1);

    // Generate the random string
    string randomString = "";
    for (int i = 0; i < length; ++i)
    {
        randomString += chars[rand() % chars.size()];
    }
    return randomString;
}

// Function to write random tokens to a file
void generateTestFile(const string &filename, int numTokens)
{
    ofstream file(filename);
    for (int i = 0; i < numTokens; ++i)
    {
        file << generateRandomString(1, 12) << endl;
    }
    file.close();
}

int main()
{
    srand(time(0)); // Seed for random number generation

    // Test case 1: Small dataset
    generateTestFile("input/testcase_small.txt", 50);

    // Test case 2: Medium dataset
    generateTestFile("input/testcase_medium.txt", 200);

    // Test case 3: Large dataset with forced collisions
    generateTestFile("input/testcase_large.txt", 1000);

    cout << "Test files generated!" << endl;
    return 0;
}

#include "TokenKeyGenerator.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Function to read a file and generate a list of words by tokenizing the input text
vector<string> generateWords(const std::string &path)
{
    ifstream file(path); // Open the file
    stringstream buffer;
    buffer << file.rdbuf(); // Read file contents into buffer & Convert buffer to string
    string input = buffer.str();
    file.close();

    vector<string> words; // Store the words
    string word;

    // Iterate through the input string and extract words based on delimiters
    for (char c : input)
    {
        if (c == ',' || c == '.' || c == ' ' || c == '\n')
        {
            if (!word.empty())
            {
                words.push_back(word); // Add the word to the vector if it's not empty
                word.clear();          // Clear the word for the next iteration
            }
        }
        else
        {
            word += c; // Append the character to the current word
        }
    }

    // Add the last word if there's any
    if (!word.empty())
    {
        words.push_back(word);
    }

    return words;
}

// Convert a word to a token of exactly 10 characters
string convertWordToToken(string word)
{
    string token;

    // word length < 10 characters, append '*' to make it 10 characters long
    if (word.length() < 10)
    {
        token = word.append(10 - word.length(), '*');
    }
    // word length > 10 characters, truncate it to the first 10 characters
    else if (word.length() > 10)
    {
        token = word.substr(0, 10);
    }

    return token;
}

// Generate a unique key based on the ASCII values of the characters in the token
int generateKeys(string token)
{
    int key = 0;

    for (int i = 0; i < token.length(); i++)
    {
        key += static_cast<int>(token[i]); // Add the ASCII value of the character to the key
    }
    return key;
}

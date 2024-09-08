#ifndef TOKENKEYGENERATOR_H
#define TOKENKEYGENERATOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Function to generate a list of words by reading a file from the given path
std::vector<std::string> generateWords(const std::string &path);

// Function to convert a word into a token of exactly 10 characters
std::string convertWordToToken(std::string words);

// Function to generate a key from the given token by summing ASCII values
int generateKeys(std::string token);

#endif

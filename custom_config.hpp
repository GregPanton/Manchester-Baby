#ifndef CUSTOM_CONFIGURATION_HPP
#define CUSTOM_CONFIGURATION_HPP

#include <string>
#include <iostream>
#include <fstream>
#include "custom_error_handling.hpp"
using namespace std;

int customInstructionCount = 8;
int customMemoryLocationCount = 32;
int customBitsNotUserAfterLineNo = 8;
int customBitsNotUsedAfterFunctionNumber = 15;
int customBitsUsedForLineNo = 5;
int customBitsUsedForFunctionNo = 4;
int customJumpFunctionNumber = 0;

void updateCustomConfiguration(const string& customConfigFile) {
    ifstream configFileReader(customConfigFile);  // Open file

    // Check if the file opened correctly
    if (!configFileReader) {
        cout << "Error opening custom configuration file" << endl;
        throw FILE_IO_ERROR;
    }

    string line;
    while (getline(configFileReader, line)) { // Read file line by line
        // Temporary variables to hold strings as they're being formed
        string option = "";
        string newValue = "";
        bool optionFormed = false;

        // This loop splits up each line into the option and the value
        for (auto &c : line) {
            if (c == ';') { // Semicolons are used for comments, so anything at and after the semicolon can be ignored
                break;
            } else if (c != ':' && !optionFormed) {
                option += c;
            } else if (c == ':') { // Use colon to split the option and the value
                optionFormed = true;
            } else {
                if (isdigit(c)) {
                    newValue += c;
                }
            }
        }

        if (!option.empty()) {
            // Check if the option exists and then assign the new value if it does
            if (option == "customInstructionCount") {
                customInstructionCount = stoi(newValue);
            } else if (option == "customMemoryLocationCount") {
                customMemoryLocationCount = stoi(newValue);
            } else if (option == "customBitsNotUserAfterLineNo") {
                customBitsNotUserAfterLineNo = stoi(newValue);
            } else if (option == "customBitsNotUsedAfterFunctionNumber") {
                customBitsNotUsedAfterFunctionNumber = stoi(newValue);
            } else if (option == "customBitsUsedForLineNo") {
                customBitsUsedForLineNo = stoi(newValue);
            } else if (option == "customBitsUsedForFunctionNo") {
                customBitsUsedForFunctionNo = stoi(newValue);
            } else if (option == "customJumpFunctionNumber") {
                customJumpFunctionNumber = stoi(newValue);
            }
        }
    }
    configFileReader.close(); // Close the custom configuration text file
}

#endif

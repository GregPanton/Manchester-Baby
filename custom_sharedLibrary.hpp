#ifndef CUSTOM_SHARED_LIBRARY_HPP
#define CUSTOM_SHARED_LIBRARY_HPP

#include <bitset>
#include <algorithm>
#include "custom_error_handling.hpp"


string toBinary(long longInput) {
    return bitset<32>(longInput).to_string();
}


string instructionToBinary(int inputInt) {
    if (inputInt > 7) {
        throw INPUT_TOO_BIG_ERROR;
    }
    return bitset<3>(inputInt).to_string();
}


string memoryLocationToBinary(int inputInt) {
    if (inputInt > 31) {
        throw INPUT_TOO_BIG_ERROR;
    }
    return bitset<5>(inputInt).to_string();
}


string intToBinary(int inputInt) {
    string binary = bitset<32>(inputInt).to_string();
    bool hitAOne = false;
    string finalOutput = "";
    // This loop removes any trailing 0s
    for (auto &digit : binary) {
        if (digit != '0') { // We wait until we get a digit that's a 1 before doing anything
            finalOutput += digit;
            hitAOne = true;
        } else if (hitAOne) { // We accept all 1/0 after we hit the first 1
            finalOutput += digit;
        }
    }
    return finalOutput;
}


string reverseString(string stringIn) {
    string temp = stringIn;
    reverse(temp.begin(), temp.end()); // Reverses string
    return temp;
}

#endif

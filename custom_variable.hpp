#ifndef CUSTOM_VARIABLE_HPP
#define CUSTOM_VARIABLE_HPP

#include <string>
#include <utility>
#include "custom_error_handling.hpp"
#include "custom_config.hpp"

using namespace std;

class custom_variable {
    string variableName; // Stores the name of the variable
    long variableValue; // Stores the value of the variable
    int memoryLocation; // Stores the memory location it will be placed in after assembling;
    
public:
    custom_variable(); // Default constructor
    custom_variable(string, long); // Constructor allowing variable name and value to be set
    string getVariableName() const; // Getter
    long getVariableValue() const; // Getter
    int getMemoryLocation() const; // Getter
    void setVariableName(string x); // Setter
    void setVariableValue(long); // Setter
    void setMemoryLocation(int); // Setter
    void assign(string, long); // Assigner
    void assign(string, long, int); // Assigner
};


custom_variable::custom_variable() {
    this->variableValue = 0;
    this->variableName = "";
    this->memoryLocation = -1;
}


custom_variable::custom_variable(string inputString, long inputLong) {
    // Check if the input number is too big
    if (inputLong > 4294967295) {
        throw LARGE_VALUE_ERROR;
    }
    this->variableName = std::move(inputString);
    this->variableValue = inputLong;
    this->memoryLocation = -1;
}


void custom_variable::setMemoryLocation(int inputMemory) {
    // Check if the memory location you want to set is within the range
    if (inputMemory > (customMemoryLocationCount - 1) || inputMemory < 0) {
        throw OUT_OF_MEMORY_RANGE_ERROR;
    } else {
        this->memoryLocation = inputMemory;
    }
}


void custom_variable::setVariableValue(long inputLong) {
    // Check if the input number is too big
    if (inputLong > 4294967295) {
        throw LARGE_VALUE_ERROR;
    } else {
        this->variableValue = inputLong;
    }
}

void custom_variable::assign(string inputString, long inputLong, int inputMemory) {
    // Check if the memory location you want to set is within the range
    if (inputMemory > (customMemoryLocationCount - 1) || inputMemory < 0) {
        throw OUT_OF_MEMORY_RANGE_ERROR;
    }
    // Check if the input number is too big
    if (inputLong > 4294967295) {
        throw LARGE_VALUE_ERROR;
    }
    this->variableName = std::move(inputString);
    this->variableValue = inputLong;
    this->memoryLocation = inputMemory;
}

void custom_variable::assign(string inputString, long inputLong) {
    // Check if the input number is too big
    if (inputLong > 4294967295) {
        throw LARGE_VALUE_ERROR;
    }
    this->variableName = std::move(inputString);
    this->variableValue = inputLong;
}

// Getter implementations
string custom_variable::getVariableName() const {
    return variableName;
}

long custom_variable::getVariableValue() const {
    return variableValue;
}

int custom_variable::getMemoryLocation() const {
    return memoryLocation;
}

// Setter implementations
void custom_variable::setVariableName(string x) {
    this->variableName = std::move(x);
}

#endif

// File written by: Viktor Bratov
//
#ifndef CUSTOM_INSTRUCTION_HPP
#define CUSTOM_INSTRUCTION_HPP

#include <string>
#include <utility>
#include "error_handling.hpp"
#include "common_variables.hpp"

using namespace std;

class CustomInstruction {
    string variableName;
    string instructionLabel;
    int functionCode;
    int memoryLocation;

public:
    CustomInstruction();
    explicit CustomInstruction(int functionCode);
    CustomInstruction(string variable, int functionCode);
    CustomInstruction(string variable, int functionCode, string label);
    void setData(string variable, int functionCode);
    void setFunctionCode(int functionCode);
    void setMemoryLocation(int memoryLocation);
    void setVariableName(string variableNameInput) { this->variableName = std::move(variableNameInput); }
    void setInstructionLabel(string labelInput) { this->instructionLabel = std::move(labelInput); }
    int getFunctionCode();
    int getMemoryLocation();
    string getInstructionLabel() { return this->instructionLabel; }
    string getVariableName() { return this->variableName; }
};


CustomInstruction::CustomInstruction() {
    this->variableName = "";
    this->functionCode = -1;
    this->memoryLocation = -1;
    this->instructionLabel = "";
}


CustomInstruction::CustomInstruction(int functionCodeInput) {
    // Checks whether the function code that is being set exists
    if (functionCodeInput < 0 || functionCodeInput > customInstructionCount) {
        throw INSTRUCTION_DOES_NOT_EXIST_ERROR;
    }
    this->variableName = "";
    this->functionCode = functionCodeInput;
    this->memoryLocation = -1;
}


CustomInstruction::CustomInstruction(string variableNameInput, int functionCodeInput) {
    // Checks whether the function code that is being set exists
    if (functionCodeInput < 0 || functionCodeInput > customInstructionCount) {
        throw INSTRUCTION_DOES_NOT_EXIST_ERROR;
    }
    this->variableName = std::move(variableNameInput);
    this->functionCode = functionCodeInput;
    this->memoryLocation = -1;
    this->instructionLabel = "";
}

CustomInstruction::CustomInstruction(string variableNameInput, int functionCodeInput, string labelInput) {
    // Checks whether the function code that is being set exists
    if (functionCodeInput < 0 || functionCodeInput > customInstructionCount) {
        throw INSTRUCTION_DOES_NOT_EXIST_ERROR;
    }
    this->variableName = std::move(variableNameInput);
    this->functionCode = functionCodeInput;
    this->memoryLocation = -1;
    this->instructionLabel = std::move(labelInput);
}


void CustomInstruction::setFunctionCode(int functionCodeInput) {
    // Checks whether the function code that is being set exists
    if (functionCodeInput < 0 || functionCodeInput > customInstructionCount) {
        throw INSTRUCTION_DOES_NOT_EXIST_ERROR;
    }
    this->functionCode = functionCodeInput;
}


int CustomInstruction::getFunctionCode() {
    return this->functionCode;
}


void CustomInstruction::setData(string variableNameInput, int functionCodeInput) {
    // Checks whether the function code that is being set exists
    if (functionCodeInput < 0 || functionCodeInput > customMemoryLocationCount) {
        throw INSTRUCTION_DOES_NOT_EXIST_ERROR;
    }
    this->variableName = std::move(variableNameInput);
    this->functionCode = functionCodeInput;
}


void CustomInstruction::setMemoryLocation(int memoryLocationInput) {
    // Check if the set memory location is within range
    if (memoryLocationInput > (customMemoryLocationCount - 1) || memoryLocationInput < 0) {
        throw OUT_OF_MEMORY_RANGE_ERROR;
    }
    this->memoryLocation = memoryLocationInput;
}

int CustomInstruction::getMemoryLocation() {
    return this->memoryLocation;
}

#endif

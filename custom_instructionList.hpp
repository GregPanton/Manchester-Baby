#ifndef CUSTOM_INSTRUCTION_LIST_HPP
#define CUSTOM_INSTRUCTION_LIST_HPP

#include "custom_instruction.hpp"
#include <utility>
#include <vector>
#include "custom_error_handling.hpp"
#include "custom_config.hpp"

using namespace std;

class CustomInstructionList {
    vector<CustomInstruction> instructionList;

public:
    bool doesLabelExist(string label);
    long getInstructionListSize() { return instructionList.size(); } // returns size of vector
    CustomInstruction getItemInInstructionList(int);
    void addInstructions(string variableName, int functionCode, const string& label);
    void addInstructions(string variableName, int functionCode);
    void addInstructions(int functionCode);
    void bulkSetMemoryLocation(int fromMemoryLocation);
    void printInstructionList();
    CustomInstruction getInstructionViaLabel(string label);
};


CustomInstruction CustomInstructionList::getItemInInstructionList(int vectorLocation) {
    // Check whether the location is valid for the vector
    if (vectorLocation > static_cast<int>(instructionList.size()) || vectorLocation < 0) {
        throw OUTSIDE_OF_VECTOR_RANGE_ERROR;
    }
    return instructionList.at(vectorLocation);
}


void CustomInstructionList::addInstructions(string variableName, int functionCode) {
    // Creates object and places it into the vector
    CustomInstruction temp(std::move(variableName), functionCode);
    instructionList.push_back(temp);
}


void CustomInstructionList::addInstructions(int functionCode) {
    // Creates object and places it into the vector
    CustomInstruction temp(functionCode);
    instructionList.push_back(temp);
}


void CustomInstructionList::bulkSetMemoryLocation(int fromMemoryLocation) {
    // Checks if we have enough memory locations to allocate to all variables
    if ((customMemoryLocationCount - fromMemoryLocation) < static_cast<int>(instructionList.size())) {
        throw NOT_ENOUGH_MEMORY_ERROR;
    } else {
        int memoryLocationBeingSet = fromMemoryLocation;
        // For each instruction, we set the memory location then increment the instruction by one
        for (auto &i : instructionList) { // For each object in the vector
            i.setMemoryLocation(memoryLocationBeingSet); // Set memory address
            memoryLocationBeingSet++; // Increment memory by one
        }
        return;
    }
}


void CustomInstructionList::printInstructionList() {
    cout << "==========================" << endl;
    cout << "Instruction Vector List" << endl;
    for (auto &i : instructionList) { // For each object in the vector
        cout << "Function Code: " << i.getFunctionCode() << " | Variable Used: " << i.getVariableName() << " | Memory Address: " << i.getMemoryLocation() << " | Label: " << i.getInstructionLabel() << endl;
    }
    cout << "==========================" << endl;
}


bool CustomInstructionList::doesLabelExist(string labelInput) {
    for (auto &item : instructionList) { // For each object in the vector
        if (item.getInstructionLabel() == labelInput && !item.getInstructionLabel().empty()) { // If we get a match and the label isn't empty
            return true;
        }
    }
    return false;
}


void CustomInstructionList::addInstructions(string variableName, int functionCode, const string& labelInput) {
    // Checks if an item with the same label exists already
    if (doesLabelExist(labelInput)) {
        throw LABEL_ALREADY_EXISTS_ERROR;
    }
    // Creates object and places it into the vector
    CustomInstruction temp(variableName, functionCode, labelInput);
    instructionList.push_back(temp);
}


CustomInstruction CustomInstructionList::getInstructionViaLabel(string label) {
    // We check if the label exists, if it doesn't we throw an error
    if (!doesLabelExist(label)) {
        throw INSTRUCTION_DOES_NOT_EXIST_ERROR;
    }
    for (auto &item : instructionList) { // Looks through each object in the vector
        if (item.getInstructionLabel() == label) { // If we find the label matching
            return item; // Return the object
        }
    }
    throw INSTRUCTION_DOES_NOT_EXIST_ERROR; // Throw an error if we can't find a matching object
}

#endif // CUSTOM_INSTRUCTION_LIST_HPP


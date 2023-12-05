#ifndef CUSTOM_VARIABLE_LIST_HPP
#define CUSTOM_VARIABLE_LIST_HPP

#include <vector>
#include "custom_variable.hpp"
#include "custom_error_handling.hpp"
#include "custom_config.hpp"

using namespace std;

class custom_variableList {
    vector<custom_variable> variableContainer; // Contains the variables
public:
    bool containsName(const string& variableName);
    void addVariable(string variableName, long variableLong);
    void updateVariable(string variableName, long variableLong);
    void setMemoryLocation(string variableName, int memoryLocation);
    void bulkSetMemoryLocation(int fromMemoryLocation);
    long getVariableData(string variableName);
    int getMemoryLocation(string variableName);
    int sizeOfVariableList();
    void printVariableList();
    custom_variable getVariable(int vectorLocation);
};

bool custom_variableList::containsName(const string& variableName) {
    for (auto& variable : variableContainer) {
        if (variable.getVariableName() == variableName) {
            return true;
        }
    }
    return false;
}

void custom_variableList::addVariable(string variableName, long variableLong) {
    if (!containsName(variableName)) {
        custom_variable temp;
        temp.assign(variableName, variableLong);
        variableContainer.push_back(temp);
    } else {
        throw VARIABLE_NAME_PRESENT_ERROR;
    }
}

void custom_variableList::updateVariable(string variableName, long variableLong) {
    if (containsName(variableName)) {
        for (auto& variable : variableContainer) {
            if (variable.getVariableName() == variableName) {
                variable.setVariableValue(variableLong);
                return;
            }
        }
    } else {
        throw VARIABLE_DOES_NOT_EXIST_ERROR;
    }
}

void custom_variableList::setMemoryLocation(string variableName, int memoryLocation) {
    if (containsName(variableName)) {
        for (auto& variable : variableContainer) {
            if (variable.getVariableName() == variableName) {
                variable.setMemoryLocation(memoryLocation);
                return;
            }
        }
    } else {
        throw VARIABLE_DOES_NOT_EXIST_ERROR;
    }
}

void custom_variableList::bulkSetMemoryLocation(int fromMemoryLocation) {
    if ((customMemoryLocationCount - fromMemoryLocation) < (int)variableContainer.size()) {
        throw NOT_ENOUGH_MEMORY_ERROR;
    } else {
        int memoryLocationBeingSet = fromMemoryLocation;
        for (auto& variable : variableContainer) {
            variable.setMemoryLocation(memoryLocationBeingSet);
            memoryLocationBeingSet++;
            if (memoryLocationBeingSet == customMemoryLocationCount) {
                memoryLocationBeingSet = 0;
            }
        }
        return;
    }
}

long custom_variableList::getVariableData(string variableName) {
    if (!containsName(variableName)) {
        throw VARIABLE_DOES_NOT_EXIST_ERROR;
    } else {
        for (auto& variable : variableContainer) {
            if (variable.getVariableName() == variableName) {
                return variable.getVariableValue();
            }
        }
    }
    throw VARIABLE_DOES_NOT_EXIST_ERROR;
}

int custom_variableList::getMemoryLocation(string variableName) {
    if (!containsName(variableName)) {
        throw VARIABLE_DOES_NOT_EXIST_ERROR;
    } else {
        for (auto& variable : variableContainer) {
            if (variable.getVariableName() == variableName) {
                return variable.getMemoryLocation();
            }
        }
    }
    throw VARIABLE_DOES_NOT_EXIST_ERROR;
}

int custom_variableList::sizeOfVariableList() {
    return (int)variableContainer.size();
}

void custom_variableList::printVariableList() {
    cout << "Variable List" << endl;
    for (auto& variable : variableContainer) {
        cout << "Variable Name: " << variable.getVariableName() << " | Variable Value: " << variable.getVariableValue() << " | Memory Address: " << variable.getMemoryLocation() << endl;
    }
}

custom_variable custom_variableList::getVariable(int vectorLocation) {
    if (vectorLocation > (int)variableContainer.size() || vectorLocation < 0) {
        throw OUTSIDE_OF_VECTOR_RANGE_ERROR;
    }
    return variableContainer.at(vectorLocation);
}

#endif // CUSTOM_VARIABLE_LIST_HPP


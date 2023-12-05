// File written by: Viktor Bratov

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <limits>
#include <cstring>
#include "error_handling.hpp"
#include "custom_variableList.hpp"
#include "custom_instructionList.hpp"
#include "common_variables.hpp"

using namespace std;

vector<vector<string>> processedInput; // Holds the input file after it's cleaned up
custom_variableList variableContainer; // Holds all the variables used in the assembly file AKA Symbol table
CustomInstructionList instructionContainer; // Holds all the instructions states in the assembly file
const string arrayMnemonics[8] = {"JMP", "JRP", "LDN", "STO", "SUB", "CMP", "STP", "MTP"};
const int arrayFunctionNo[8] = {0, 1, 2, 3, 4, 6, 7, 8};

vector<string> mnemonics;
vector<int> functionNumbers;


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

void setup() {
    //places the mnemonic and function Numbers from their arrays into their vectors
    for (auto &item : arrayMnemonics) { // for each item in array
        mnemonics.push_back(item); //place that ite into the vector
    }
    for (auto &item : arrayFunctionNo) { // for each item in array
        functionNumbers.push_back(item); //place that ite into the vector
    }
}


int mnemonicToInt(const string &mnemonic) {

    // for each item in the mnemonics vector
    for (int loc = 0; loc < (int) mnemonics.size(); loc++) {
        // if the mnemonic we're looking for is in the mnemonics vector
        if (mnemonics.at(loc) == mnemonic) {
            // return the corresponding function number
            return functionNumbers.at(loc);
        }
    }

    // If we're gone through the whole loop with out find the mnemonics
    // it means it doesn't exist and we throw an error
    throw INSTRUCTION_DOES_NOT_EXIST_ERROR;
}


void processInputFiles(const string &txtFile) {
    cout << "reading input file" << endl;

    ifstream reader(txtFile);

    //if nothing is passed in, we didn't get a valid input
    if (txtFile.empty()) {
        throw INVALID_INPUT_ERROR;
    }

    if (!reader) {
        cout << "Error opening input file" << endl;
        throw FILE_IO_ERROR;
    }

    string line;
    while (getline(reader, line)) {
        string chunk = ""; //Used to temp hold chars as we process them
        vector<string> tempVector; // creates a temp vector for holding strings
        for (char &l : line) { //
            if (l == ' ' && !chunk.empty()) {
                tempVector.push_back(chunk);
                chunk = "";
            } else if (l == ';') { // we break if we hit a comment as the semi-collon and anything after is a comment
                break;
            } else if (l != ':' && l != ' ') {
                chunk += l;
            }
        }
        if(!chunk.empty()){
            tempVector.push_back(chunk); //push the last item if there is one into the vector
        }
        // If the tempory vector for the line we just processed isn't empty we push it to the vector
        if (!tempVector.empty()) {
            processedInput.push_back(tempVector);
        }
    }
    reader.close(); // close the reader

    // Check if we have data to process.
    if (processedInput.empty()) {
        throw INPUT_PROCESS_FAILED_ERROR;
    }

    cout << "Read file Successful" << endl;
}


void processAssembly() {

    // check if there's stuff to process
    if (processedInput.empty()) {
        throw NO_INSTRUCTION_TO_PROCESS_ERROR;
    }

    for (auto &line : processedInput) { // for each line in assembly
        vector<string> vectorTemp = line; // This variable is a temp holding locations for the line we're processing at the time.
        // temp strings to hold the data while we fetch it
        string variableName = "";
        string mnemonicName = "";
        string label = "";
        string varValue = "";

        if (find(mnemonics.begin(), mnemonics.end(), vectorTemp.at(0)) != mnemonics.end()) {
            // If we find a mnemonic in the first work
            if (1 < (int) vectorTemp.size()) {
                variableName = vectorTemp.at(1);
            }
            if (!vectorTemp.empty()) {
                mnemonicName = vectorTemp.at(0);
            }
            instructionContainer.addInstructions(variableName, mnemonicToInt(mnemonicName)); // place instruction
        } else if ((int) vectorTemp.size() > 1) {
            if (vectorTemp.at(1) == "VAR") {
                // if we find a variable
                if (2 < (int) vectorTemp.size()) {
                    varValue = vectorTemp.at(2);
                }
                if (!vectorTemp.empty()) {
                    mnemonicName = vectorTemp.at(0);
                }
                // if line contains variable
                variableContainer.addVariable(mnemonicName, stoi(varValue)); // add variables
            } else if (find(mnemonics.begin(), mnemonics.end(), vectorTemp.at(1)) != mnemonics.end()) {
                //if we find a mnemonic with a label
                if (2 < (int) vectorTemp.size()) {
                    variableName = vectorTemp.at(2);
                }
                if (1 < (int) vectorTemp.size()) {
                    mnemonicName = vectorTemp.at(1);
                }
                if (!vectorTemp.empty()) {
                    label = vectorTemp.at(0);
                }
                instructionContainer.addInstructions(variableName, mnemonicToInt(mnemonicName), label); // place instruction
            }
        }
    }

    // This assigns the memory locations of the instructions.
    instructionContainer.bulkSetMemoryLocation(1); // this is set to 1 as the MB starts its IC from 1 instead of 0
    // This assigns the memory locations of the variables, from the last instructions
    // We bulk set the variable locations from the location after the instructions that will the size of the instruction Container +1
    variableContainer.bulkSetMemoryLocation((int) instructionContainer.getInstructionListSize() + 1);
    cout << "outputting machine-code successful" << endl;
}


void outputMachineCode(const string &writeFile) {
    if (variableContainer.sizeOfVariableList() == 0 || instructionContainer.getInstructionListSize() == 0) {
        throw INPUT_PROCESS_FAILED_ERROR;
    }
    //if nothing is passed in, we didn't get a valid input
    if (writeFile.empty()) {
        throw INVALID_INPUT_ERROR;
    }

    //opens file to write to it
    ofstream outputFile(writeFile);
    // we check if we opened the file correctly
    if (!outputFile.is_open()) {
        cout << "Error opening input file" << endl;
        throw FILE_IO_ERROR;
    }

    string stringBuilder = ""; // holds string to place into machine code output

    // if the variables and instruction to output to machine code are
    // less than the number of memory locations we start the first line as a 0s
    if ((int) variableContainer.sizeOfVariableList() + (int) instructionContainer.getInstructionListSize() <
        customMemoryLocationCount - 1) {
        // we do a for loop for the total width of the memory
        int total = customBitsNotUserAfterLineNo+customBitsNotUsedAfterFunctionNumber+customBitsUsedForLineNo+customBitsUsedForFunctionNo;
        for(int i = 0; i < total; i++){
            stringBuilder+='0';
        }
        outputFile << stringBuilder << endl; // output string to txt file
        stringBuilder = "";
    }


    // for each instruction in the Instruction Container
    for (int i = 0; i < (int) instructionContainer.getInstructionListSize(); i++) {
        CustomInstruction tempInstruct = instructionContainer.getItemInInstructionList(i);
        stringBuilder = ""; // holds string to place into machine code output
        // Isn't a jump we process like normal
        int lineNo = 0;
        if(tempInstruct.getFunctionCode() == customJumpFunctionNumber){
            lineNo = instructionContainer.getInstructionViaLabel(tempInstruct.getVariableName()).getMemoryLocation();
        }else{
            try {
                lineNo = variableContainer.getMemoryLocation(tempInstruct.getVariableName());
            } catch (...) {
                //This try catch is to catch any time we looks for a variable that doesn't exist,
                //like when the string is blank, e.g. STP command
                if (tempInstruct.getFunctionCode() > 7 || tempInstruct.getFunctionCode() < 6 ) { // we check if it's the stp function
                    throw VARIABLE_USED_BUT_NOT_DEFINED_ERROR;
                }
            }
        }

        // get the line number and work out the binary version
        string binaryLineNo = intToBinary(lineNo);
        if ((int) binaryLineNo.length() > customBitsUsedForLineNo) {
            throw LINE_NUMBER_TOO_LARGE_FOR_BITS_DEFINED_ERROR;
        }
        stringBuilder += reverseString(binaryLineNo); // places line number into the line output string
        // This for loop places the spacing between the line number and function number
        int spacingNeeded = (customBitsUsedForLineNo + customBitsNotUserAfterLineNo) - (int) binaryLineNo.length();
        // This actually places the 0s into the string
        for (int x = 0; x < spacingNeeded; x++) {
            stringBuilder += '0';
        }

        // get the function number and output it into the line output string
        string binaryFunctionNo = intToBinary(tempInstruct.getFunctionCode());
        stringBuilder += reverseString(binaryFunctionNo);
        if ((int) binaryFunctionNo.length() > customBitsUsedForLineNo) {
            throw FUNCTION_NUMBER_TOO_LARGE_FOR_BITS_DEFINED_ERROR;
        }
        spacingNeeded = (customBitsUsedForFunctionNo + customBitsNotUsedAfterFunctionNumber) - (int) binaryFunctionNo.length();
        // This actually places the 0s into the string
        for (int x = 0; x < spacingNeeded; x++) {
            stringBuilder += '0';
        }

        outputFile << stringBuilder << endl; //output line to file
    }

    // for each variable in variable container
    for (int i = 0; i < variableContainer.sizeOfVariableList(); i++) {
        string stringBuilder = reverseString(toBinary(variableContainer.getVariable(i).getVariableValue()));
        outputFile << stringBuilder << endl;//output line to file
    }

}

int main(int argc, char *argv[]){
    setup();
    if(argc < 3){
        cout << "You need a min of 2 arguments" << endl;
        return -1;
    }
    string inputFile = argv[1];
    string outFile = argv[2];
    try {
        processInputFiles(inputFile);
        processAssembly();
        outputMachineCode(outFile);
        return 0;
    }catch(int& e){
        cout << "exception code: " << e << endl;
        explainCustomError(e);
        return 0;
    }catch(exception& e){
        cout << "Probably the assembler's programmer's fauly" << endl;
        cout << e.what() << endl;
        return 0;
    }
    return 0;
}

// File written by: Viktor Bratov
//
#ifndef CUSTOM_ERROR_HANDLING_HPP
#define CUSTOM_ERROR_HANDLING_HPP

#include <string>
#include <iostream>
using namespace std;

#define LARGE_VALUE_ERROR -101 // When the Long is > 32 bits large
#define OUT_OF_MEMORY_RANGE_ERROR -102 // When the memory location is outside the bank of 32 locations
#define VARIABLE_NAME_PRESENT_ERROR -103 // When a variable already exists with the same name
#define VARIABLE_DOES_NOT_EXIST_ERROR -104 // When a variable doesn't exist
#define NOT_ENOUGH_MEMORY_ERROR -105 // If there isn't enough memory locations to be allocated to all variables

#define INSTRUCTION_DOES_NOT_EXIST_ERROR  -201 // Instruction does not exist in instruction Set
#define OUTSIDE_OF_VECTOR_RANGE_ERROR -202 // When an item is requested from an invalid vector location
#define LABEL_ALREADY_EXISTS_ERROR -203 // When you try to assign an instruction with a label that is already used
#define INPUT_TOO_BIG_ERROR -204 // When the input int/long is too large

#define NO_INSTRUCTION_TO_PROCESS_ERROR -301 // No instructions in vector to process
#define UNABLE_TO_FIND_START_OR_END_ERROR -302 // Unable to find mnemonics START or/and END
#define INPUT_PROCESS_FAILED_ERROR -303 // Some error with processing the input of split variables
#define INVALID_INPUT_ERROR -304 // Invalid parameter given
#define FILE_IO_ERROR -305 // Can't open file
#define VARIABLE_USED_BUT_NOT_DEFINED_ERROR -306 // When a variable is used but not defined in the assembly
#define MISMATCHED_VECTOR_ERROR -307 // When the lines configuring the mnemonics and function numbers aren't the same length
#define LINE_NUMBER_TOO_LARGE_FOR_BITS_DEFINED_ERROR -308 // When the line number takes more bits than the number of bits allocated in it in custom_config.hpp
#define FUNCTION_NUMBER_TOO_LARGE_FOR_BITS_DEFINED_ERROR -309 // When the function number takes more bits than the number of bits allocated in it in custom_config.hpp
#define INVALID_CHAR_IN_CONFIG_ERROR -310 // When there's an invalid character in the config file, e.g., when you have a non-decimal number when defining the function numbers
#define MISMATCHED_CONFIG_DETAILS_ERROR -311 // When parts of config don't match, mainly customInstructionCount and the number of mnemonics stated


void explainCustomError(int errorCode) {
    switch (errorCode) {
        case LARGE_VALUE_ERROR:
            cout << "Value too big for the memory size" << endl;
            cout << "Value passed through is too big to fit in the available memory size." << endl;
            break;
        case OUT_OF_MEMORY_RANGE_ERROR:
            cout << "Out of Memory Range" << endl;
            cout << "Requested data from a memory location that doesn't exist" << endl;
            break;
        case VARIABLE_NAME_PRESENT_ERROR:
            cout << "Variable Name Present" << endl;
            cout << "You've defined a variable already, and you try to define it again" << endl;
            break;
        case VARIABLE_DOES_NOT_EXIST_ERROR:
            cout << "Variable Doesn't Exist" << endl;
            cout << "You use a variable with an instruction that you haven't defined" << endl;
            break;
        case NOT_ENOUGH_MEMORY_ERROR:
            cout << "Not Enough Memory" << endl;
            cout << "When there isn't enough memory locations for the number of variables and instructions." << endl;
            break;
        case INSTRUCTION_DOES_NOT_EXIST_ERROR:
            cout << "Instruction Doesn't Exist" << endl;
            cout << "Assembler used an instruction that doesn't exist in the instruction Set" << endl;
            break;
        case OUTSIDE_OF_VECTOR_RANGE_ERROR:
            cout << "Vector Out of Range" << endl;
            cout << "Assembler looked at a non-existent vector location" << endl;
            cout << "This is likely the programmer's fault" << endl;
            break;
        case LABEL_ALREADY_EXISTS_ERROR:
            cout << "Label Already Exists" << endl;
            cout << "You've used a label on an instruction/assembly line twice" << endl;
            break;
        case INPUT_TOO_BIG_ERROR:
            cout << "Input too big" << endl;
            cout << "Input int/long is too big for the function" << endl;
            break;
        case NO_INSTRUCTION_TO_PROCESS_ERROR:
            cout << "No Instruction to process" << endl;
            cout << "Assembler can't find instructions to process in the assembly file" << endl;
            break;
        case UNABLE_TO_FIND_START_OR_END_ERROR:
            cout << "Unable to find START or END markers" << endl;
            cout << "Can't find the `START` or/and `END` markers in the assembly file" << endl;
            cout << "This error was deprecated in commit: d3ecd1616640e4163a91aeaf2d334c55b978d2c6" << endl;
            break;
        case INPUT_PROCESS_FAILED_ERROR:
            cout << "Input Process Failed" << endl;
            cout << "Assembler failed to input your assembly file into its data structure" << endl;
            break;
        case INVALID_INPUT_ERROR:
            cout << "Invalid Input" << endl;
            cout << "Invalid parameter given" << endl;
            break;
        case FILE_IO_ERROR:
            cout << "File IO Error" << endl;
            cout << "There was an error opening your text file." << endl;
            break;
        case VARIABLE_USED_BUT_NOT_DEFINED_ERROR:
            cout << "Variable used but not defined" << endl;
            cout << "When one of your instructions in your assembly file is used but not defined" << endl;
            break;
        case MISMATCHED_VECTOR_ERROR:
            cout << "Mis-Matched vectors" << endl;
            cout << "When your custom mnemonics and functionNumbers in your config text file don't have the same number of items in each to match up." << endl;
            break;
        case LINE_NUMBER_TOO_LARGE_FOR_BITS_DEFINED_ERROR:
            cout << "Line number too large for bits defined" << endl;
            cout << "When the line number of a variable is too large for the number of bits defined to hold the bits in machine code." << endl;
            break;
        case FUNCTION_NUMBER_TOO_LARGE_FOR_BITS_DEFINED_ERROR:
            cout << "Function Number too large for bits defined" << endl;
            cout << "When the function number of a variable is too large for the number of bits defined to hold the bits in machine code." << endl;
            break;
        case INVALID_CHAR_IN_CONFIG_ERROR:
            cout << "Invalid char in config file" << endl;
            cout << "When there's an invalid char in the config file, e.g., when you have a non-decimal number when defining the function numbers" << endl;
            break;
        case MISMATCHED_CONFIG_DETAILS_ERROR:
            cout << "Mis-matched config details" << endl;
            cout << "When parts of config don't match, mainly customInstructionCount and the number of mnemonics stated" << endl;
            break;
        default:
            cout << "Not a standard error code " << endl;
            break;
    }
}

#endif

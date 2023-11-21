using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

int STORE[4096][32]; // A 2D array of integers (1's and 0's) that represent the store, it in initialized to the largest possible value
int ACCUMULATOR[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // A 32 long integer array that represents a binary number the baby stores outside of the store
int CI = 0; // Current Instruction, controls what line is currently being read
bool endProgram = false; // A boolean to keep track if a stop instruction has been reached 
int STORE_LENGTH = 32; // An integer value that stores how many lines long the store is, it is initially set to the default value 32
int MEMORY_LENGTH = 5; // An integer value that stores the number of bits that a memory location can be

void setsize() // Asks the user to input how large they want the memory addresses of the store to be
{
    bool validInput = false;

    while(!validInput)
    {
        //--PROMPT USER FOR INPUT--//
        cout << "Enter a number from 1 - 12 to choose the size of the store" << endl;
        cout << "-----" << endl;
        cout << "1 - 2 lines" << endl;
        cout << "2 - 4 Lines" << endl;
        cout << "3 - 8 Lines" << endl;
        cout << "4 - 16 Lines" << endl;
        cout << "5 - 32 Lines" << endl;
        cout << "6 - 64 Lines" << endl;
        cout << "7 - 128 Lines" << endl;
        cout << "8 - 256 Lines" << endl;
        cout << "9 - 512 Lines" << endl;
        cout << "10 - 1024 Lines" << endl;
        cout << "11 - 2048 Lines" << endl;
        cout << "12 - 4096 Lines" << endl;

        cin >> MEMORY_LENGTH; // Read input from user and store it to MEMORY_LENGTH

        if(MEMORY_LENGTH > 0 && MEMORY_LENGTH < 13) // If number is between 1 and 12
        {
            STORE_LENGTH = pow(2 , MEMORY_LENGTH); // Store length is 2 to the power of the memory length
            validInput = true; // The input was valid
        }
        else // If the value of MEMORY_LENGTH falls out of the specified range
        {
            cout << "Invalid input" << endl; // Display to the user that their choice was invalid
        }
    }
}

int readInstructionFromLine() // Reads the instruction stored at the current line being read
{
    int instructionNum = 0; // A number that stores the current instruction number
    int instructionCounter = 1; // A counter that keeps track of the current binary value

    for(int i = 13; i < 16; i++) // Loop over the 3 bits that store the instruction number
    {
        if(STORE[CI][i] == 1) // If the bit is 1
        {
            if(instructionCounter == 1) // If the instruction counter is 1
            {
                instructionNum++; // add 1 to the instruction counter
            }
            else
            {
                instructionNum += instructionCounter; // Add the instruction counter to the instruction number
            }
        }
        instructionCounter += instructionCounter; // Double the instruction counter as the next iteration will read the next binary position
    }

    return instructionNum; // Return this instruction number
}

void displayStore() // Display the store to the user
{
    for(int i = 0; i < 33; i++) // Top of store
    {
       cout << " ~ "; 
    }
    cout << endl;
    for(int i = 0; i < STORE_LENGTH; i++) // Store length is used as the number of lines in the store is determined at the program start
    {
        cout << "| ";
        for(int j = 0; j < 32; j++) // Every line is 32 bits long
        {
            //--PRINT VALUES ON SCREEN--//
            if(STORE[i][j] == 0)
            {
                cout << " 0 ";
            }
            else
            {
                cout << " 1 ";
            }
            
        }
        cout << " |" << endl;
    }
    for(int i = 0; i < 33; i++) // Bottom of store
    {
       cout << " ~ "; 
    }
    cout << endl;
}

void readFileIntoArray(string filename) // Reads in an input file and stores it to the STORE array
{
    ifstream file{filename}; // Create a file input stream for the file we want to read from
    char ch; // A character that will store the current character being read from the file
    
    
    if (!file.is_open()) // if the file is not open
    {
        cout << "Error opening file" << endl; // Display error to user
        return; // Return as nothing can be read
    }

    for(int i = 0; i< STORE_LENGTH; i++) // Store length is used as the number of lines in the store is determined at the program start
    {
        for(int j = 0; j< 32; j++) // Every line is 32 bits long
        {
            if(file.get(ch)) // If statement that checks if the character is successfully read, the value read is stored to ch
            {
                if(ch == '0') // If the character is a 0
                {
                    STORE[i][j] = 0; // Store the number 0 to the store
                }
                else // If the character is anything else
                {
                    STORE[i][j] = 1; // Store the number 1 to the store
                }
            }
        }
        file.get(ch); // After 32 bits have been read, read in the next character to 'eat' the \n
    }

    file.close(); // Close the file once completed
}

void saveToFile() // Reads the STORE array and saves it to a text file called 'output.txt', will override the current 'output.txt'
{
    ofstream outputFile("output.txt"); // Create a file output stream that will print to 'output.txt'
    if(!outputFile.is_open()) // If the file could not be opened
    {
        cout << "File could not be opened" << endl; // Print error message to the user
        return; // Return as file cannot be written to
    }

    for(int i = 0; i < STORE_LENGTH; i++) // Store length is used as the number of lines in the store is determined at the program start
    {
        for(int j = 0; j < 32; j++) // Every line is 32 bits long
        {
            outputFile << STORE[i][j]; // Add the current value of the array to the next space in the text file
        }
        outputFile << endl; // After 32 iterations, end the line
    }

    outputFile.close(); // CLose the file once done
}

int readMemoryLocation(int line[32]) // Reads the first nth bits from a line to find the memory location the function of that line is accessing
{
    int memoryLocation = 0; // An integer value that will represent the memory location being referred to
    int memoryCounter = 1; // A counter that iterates as the program moves to the next binary location
    for(int i = 0; i < MEMORY_LENGTH; i++) // Memory length is used as the size of memory locations is defined at program start
    {
        if(line[i] == 0) // If the current value is 0
        {
            // Do nothing
        }
        else // If the current value is anything else
        {
            if(memoryCounter == 1) // And the memory counter is 1
            {
                memoryLocation++; // Add 1 to the memory location
            }
            else // If the memory counter is not 1
            {
                memoryLocation += memoryCounter; // Add the memory counter to the memory location
            }
        }
        memoryCounter += memoryCounter; // Double the memory counter as the next iteration will read the next binary position
    }

    return memoryLocation; // Return the memory location
}

int readLineNum(int line[32]) // Reads the passed line and converts the 32 bits from binary to decimal
{
    int totalNumber = 0; // The value of the line in decimal format
    int memoryCounter = 1; // A counter that iterates as the program moves to the next binary location
    for(int i = 0; i < 32; i++) // Every line is 32 bits long
    {
        if(line[i] == 0) // If the value of the current bit is 0
        {
            // Do nothing
        }
        else // If the value is anything else
        {
            if(memoryCounter == 1) // And the memory counter is 1
            {
                totalNumber++; // Add 1 to the total number
            }
            else // If the memory counter is not 1
            {
                totalNumber += memoryCounter;  // Add the memory counter to the memory location
            }
        }
        memoryCounter += memoryCounter; // Double the memory counter as the next iteration will read the next binary position
    }

    return totalNumber; // Return the total number
}


void JMP() // Performs an absolute jump
{
    int lineNum; // An integer representation of the line number JMP wants to read
    lineNum = readMemoryLocation(STORE[CI]); // Set the line number to the memory location stored at the current line
    CI = readLineNum(STORE[lineNum]); // set CI to the numberical value stored at the memory address reffered to in the current line
}
void JRP() // Performs a relative jump
{
    int lineNum; // An integer representation of the line number JMP wants to read
    CI += readLineNum(STORE[readMemoryLocation(STORE[CI])]);// set CI to CI plus the numberical value stored at the memory address reffered to in the current line
}
void ACCN() // Uses two's compliment to convert the accumulator to negative
{
    int carry = 1; // An integer that keeps track of if there is still a binary number to be added to the current binary number
    for(int i = 0; i < 32; i++) // Every line is 32 bits long
    {
        if(ACCUMULATOR[i] == 0) // If the current bit is 0
        {
            ACCUMULATOR[i] = 1; // Change the bit to 1
        }
        else // If the current bit is not 0
        {
            ACCUMULATOR[i] = 0; // Change the bit to 0
        }
    }

   for (int i = 0; i < 32; ++i) // Every line is 32 bits long
   {
        int sum = ACCUMULATOR[i] + carry; // This will become 1 if current bit is 0, and if current bit is 2 if 1
        ACCUMULATOR[i] = sum % 2; // Update the current bit to 0 if sum is 2, 1 if sum is 1
        carry = sum / 2; // Update carry to 0 if sum is 1, 1 if sum is 2
    }
}
void LDN() // Loads a specified number in it's negative form into the accumulator using two's compliment
{
    int lineNum; // An integer representation of the line number JMP wants to read
    lineNum = readMemoryLocation(STORE[CI]); // Set the line number to the memory location stored at the current line
    
    for(int i = 0; i < 32; i++) // Every line is 32 bits long
    {
        ACCUMULATOR[i] = STORE[lineNum][i]; // Set the accumulator to the same binary value as the number stored on the specified line
    }
    ACCN(); // Set the accumulator to negative
}
void STO() // Stores the accumulators value to a specified memory address
{
    int lineNum; // An integer representation of the line number JMP wants to read
    lineNum = readMemoryLocation(STORE[CI]); // Set the line number to the memory location stored at the current line

    for(int i = 0; i < 32; i++) // Every line is 32 bits long
    {
        STORE[lineNum][i] = ACCUMULATOR[i]; // set the specified memory address of the store to the accumulator
    }
}

void SUB() // Subtracts a specified number from the accumulator using twos compliment
{
    ACCN(); // Flip the accumulator
    int lineNum; // An integer representation of the line number JMP wants to read
    int carry = 0; // An integer that keeps track of if there is still a binary number to be added to the current binary number, set to 0 as we are not simply adding 1
    lineNum = readMemoryLocation(STORE[CI]); // Set the line number to the memory location stored at the current line

    //--ADD THE NUMBERS WITH ONE NEGATED TO SUBTRACT--//
    for(int i = 0; i < 32; i++) // Every line is 32 bits long
    {
        int newNum = ACCUMULATOR[i] + STORE[lineNum][i] + carry; // This will become 1 if current bit is 0, and if current bit is 2 if 1
        ACCUMULATOR[i] = newNum % 2; // Update the current bit to 0 if sum is 2, 1 if sum is 1
        carry = newNum / 2; // Update carry to 0 if sum is 1, 1 if sum is 2
    }
    ACCN(); // Reset the accumulator so the correct value is stored
}

void CMP() // Assesses the accumulator and skips the next instruction if the value is negative
{
    CI += ACCUMULATOR[31]; // The final bit will only be 1 if the value is negative
}
void STP() // Halts the program
{
    endProgram = true; // Set the endProgram bool to true
}

void instructionSelect(int instructionNum) // compares a passed integer value to select the correct function
{
    switch (instructionNum) // Passes the number into a switch statament to be compared
    {
        //--CHECK IF THE NUMBER IS 0 - 7--//
        case 0: // If the number is 0
            JMP();
            break;

        case 1: // If the number is 1
            JRP();
            break;

        case 2: // If the number is 2
            LDN();
            break;

        case 3: // If the number is 3
            STO();
            break;

        case 4: // 4 and 5 both perform the subtract function
        case 5:
            SUB();
            break;

        case 6: // If the number is 6
            CMP();
            break;

        case 7: // If the number is 7
            STP();
            break;

        default: // If the number is not between 0 and 7
            cout << "ERROR, NUMBER NOT RECOGNISED" << endl;
            break;
    }
}

int main()
{
    //--WELCOME MESSAGE--//
    cout << "Welcome to the Manchester Baby" << endl;
    setsize(); // Set the number of memory addresses the store will contain
    cout << "Input file" << endl;
    cout << "----------------------------------------" << endl;
    readFileIntoArray("input.txt"); // Read the input file into the array
    displayStore(); // Display the store 
    while(!endProgram) // Whule the endProgram bool is false
    {
        CI++; // Increment the CI variable by 1
        instructionSelect(readInstructionFromLine()); // Call the instruction select by reading the instruction on the current line defined by CI
    }
    //--EXIT MESSAGE--//
    cout << "Output file answered" << endl;
    cout << "----------------------------------------" << endl;
    displayStore(); // Display the store
    cout << "Output saved to output.txt in folder" << endl;
    saveToFile(); // Save the new store to 'output.txt'
}

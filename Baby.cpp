using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

int STORE[4096][32];
int ACCUMULATOR[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CI = 0;
bool endProgram = false;
int STORE_LENGTH = 32;
int MEMORY_LENGTH = 5;

void setsize()
{
    bool validInput = false;

    while(!validInput)
    {
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

        cin >> MEMORY_LENGTH;

        if(MEMORY_LENGTH > 0 && MEMORY_LENGTH < 13)
        {
            STORE_LENGTH = pow(2 , MEMORY_LENGTH);
            validInput = true;
        }
        else
        {
            cout << "Invalid input" << endl;
        }
    }
}

int readInstructionFromLine()
{
    int instructionNum = 0;
    int instructionCounter = 1;

    for(int i = 13; i < 16; i++)
    {
        if(STORE[CI][i] == 1)
        {
            if(instructionCounter == 1)
            {
                instructionNum++;
            }
            else
            {
                instructionNum += instructionCounter;
            }
        }
        instructionCounter += instructionCounter;
    }

    return instructionNum;
}

void displayStore()
{
    for(int i = 0; i < 33; i++)
    {
       cout << " ~ "; 
    }
    cout << endl;
    for(int i = 0; i < STORE_LENGTH; i++)
    {
        cout << "| ";
        for(int j = 0; j < 32; j++)
        {
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
    for(int i = 0; i < 33; i++)
    {
       cout << " ~ "; 
    }
    cout << endl;
}

void readFileIntoArray(string filename) 
{
    ifstream file{filename};
    char ch;
    
    // Check if the file is open
    if (!file.is_open()) 
    {
        cout << "Error opening file" << endl;
        return; 
    }

    for(int i = 0; i< STORE_LENGTH; i++)
    {
        for(int j = 0; j< 32; j++)
        {
            if(file.get(ch))
            {
                if(ch == '0')
                {
                    STORE[i][j] = 0;
                }
                else
                {
                    STORE[i][j] = 1;
                }
            }
        }
        file.get(ch);
    }

    file.close();
}

void saveToFile()
{
    ofstream outputFile("output.txt");
    if(!outputFile.is_open())
    {
        return;
    }

    for(int i = 0; i < STORE_LENGTH; i++)
    {
        for(int j = 0; j < 32; j++)
        {
            outputFile << STORE[i][j];
        }
        outputFile << endl;
    }

    outputFile.close();
}

int readMemoryLocation(int line[32])
{
    int memoryLocation = 0;
    int memoryCounter = 1;
    for(int i = 0; i < MEMORY_LENGTH; i++)
    {
        if(line[i] == 0)
        {
            
        }
        else
        {
            if(memoryCounter == 1)
            {
                memoryLocation++;
            }
            else
            {
                memoryLocation += memoryCounter;
            }
        }
        memoryCounter += memoryCounter;
    }

    return memoryLocation;
}

int readLineNum(int line[32])
{
    int totalNumber = 0;
    int memoryCounter = 1;
    for(int i = 0; i < 32; i++)
    {
        if(line[i] == 0)
        {
            
        }
        else
        {
            if(memoryCounter == 1)
            {
                totalNumber++;
            }
            else
            {
                totalNumber += memoryCounter;
            }
        }
        memoryCounter += memoryCounter;
    }

    return totalNumber;
}


void JMP()
{
    int lineNum;
    lineNum = readMemoryLocation(STORE[CI]);
    CI = readLineNum(STORE[lineNum]);
}
void JRP()
{
    int lineNum;
    CI += readLineNum(STORE[readMemoryLocation(STORE[CI])]);
}
void ACCN()
{
    int carry = 1;
    bool added = false;
    for(int i = 0; i < 32; i++)
    {
        if(ACCUMULATOR[i] == 0)
        {
            ACCUMULATOR[i] = 1;
        }
        else
        {
            ACCUMULATOR[i] = 0;
        }
    }

   for (int i = 0; i < 32; ++i) 
   {
        int sum = ACCUMULATOR[i] + carry;
        ACCUMULATOR[i] = sum % 2; // Update the current bit
        carry = sum / 2;
    }
}
void LDN()
{
    bool added = false;
    int lineNum;
    lineNum = readMemoryLocation(STORE[CI]);
    
    for(int i = 0; i < 32; i++)
    {
        if(STORE[lineNum][i] == 0)
        {
            ACCUMULATOR[i] = 1;
        }
        else
        {
            ACCUMULATOR[i] = 0;
        }
    }

    for(int i = 0; i < 32; i++)
    {
        if(!added)
        {
            if(ACCUMULATOR[i] == 0)
            {
                ACCUMULATOR[i] = 1;
                added = true;
            }
            else
            {

            }
        }
    }
}
void STO()
{
    int lineNum;
    lineNum = readMemoryLocation(STORE[CI]);

    for(int i = 0; i < 32; i++)
    {
        STORE[lineNum][i] = ACCUMULATOR[i];
    }
}

void SUB()
{
    ACCN();
    int lineNum;
    int carry = 0;
    lineNum = readMemoryLocation(STORE[CI]);

    for(int i = 0; i < 32; i++)
    {
        int newNum = ACCUMULATOR[i] + STORE[lineNum][i] + carry;
        ACCUMULATOR[i] = newNum % 2;
        carry = newNum / 2;
    }
    ACCN();
}

void CMP()
{
    CI += ACCUMULATOR[32];
}
void STP()
{
    endProgram = true;
}

void instructionSelect(int instructionNum)
{
    switch (instructionNum)
    {
        case 0:
            JMP();
            cout << "0" << endl;
            break;

        case 1:
            cout << "1" << endl;
            JRP();
            break;

        case 2:
            cout << "2" << endl;
            LDN();
            break;

        case 3:
            cout << "3" << endl;
            STO();
            break;

        case 4:
        case 5:
            cout << "4" << endl;
            SUB();
            break;

        case 6:
            cout << "6" << endl;
            CMP();
            break;

        case 7:
            cout << "7" << endl;
            STP();
            break;
    }
}

int main()
{
    cout << "Welcome to the Manchester Baby" << endl;
    setsize();
    cout << "Input file" << endl;
    cout << "----------------------------------------" << endl;
    readFileIntoArray("input.txt");
    displayStore();
    while(!endProgram)
    {
        CI++;
        instructionSelect(readInstructionFromLine());
        cout << CI << endl;
    }
    cout << "Output file answered" << endl;
    cout << "----------------------------------------" << endl;
    displayStore();
    cout << "Output saved to output.txt in folder" << endl;
    saveToFile();
}
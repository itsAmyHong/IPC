/*
    In order to compartmentalize different operations, the code is split into several 
    classes and functions. This file defines the functions used in the main file.
*/

#include "functions.h"
using namespace std;

memory::memory(){
    pointer = 0;
}

// Returns integer at memory address
int memory::read(int address, char* buffer){
    if(address >= 2000) return -1;

    cout << "System: Reading " << address << " " << mem[address]<< endl;
    return 1;
}

// Writes to memory value at address specified
void memory::write(int address, int value){
    cout << "System: Writing " << address << " " << value << endl;
    mem[address] = value;
}

// Loads program instructions into memory from address 0
bool memory::loadProgram(string filename){
    ifstream file;
    file.open(filename);  

    // check if file is open
    if(!file.is_open()){
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }

    //Read in file line by line
    string line;
    int line_length = 0;

    //Read each line from file and extract the commands/jumps
    int mem_ptr = USER;

    while (!file.eof()){
        char temp[8] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',};
        int temp_ptr = 0;

        file >> line;
        line_length = line.length();

        if(line[0] == '.'){
            temp[temp_ptr] = '.';
            temp_ptr++;
        }

        for(int i = 0; i < line_length; i++){
            if(isdigit(line[i])){
                temp[temp_ptr] = line[i];
                temp_ptr++;
            }
        }

        if (temp[0] == '.'){
            for (int i = 0; i < 8; i++)
                temp[i] = temp[i + 1];
            temp[8] = '\0';
            mem_ptr = atoi(temp);
        }
        else if (isdigit(temp[0])){
            mem[mem_ptr] = atoi(temp);
            //cout << "System: wrote at " << mem_ptr << "  ::  " << mem[mem_ptr] << endl;
            mem_ptr++;
        }	
	}
    return true;
}

// Executes instruction specified
bool cpu::execute(int instruction){
    cout << "System: Executing " << instruction << endl;
    switch(instruction){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 50:
        default: return false;
    };
}


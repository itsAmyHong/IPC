/*
    In order to compartmentalize different operations, the code is split into several 
    classes and functions. This file defines the functions used in the main file.
*/
#include "functions.h"
using namespace std;

/// @brief write value to memory at address
/// @param value 
void memory::write(int address, int value){
    mem[address] = value;
}

/// @brief read to memory at address
/// @param address 
int memory::read(int address){
    return mem[address];
}

/// @brief loads program from file to memory
/// @param filename
bool memory::loadProgram(string filename){
    ifstream file;
    file.open(filename);

    if(!file){
        cout << "ERROR: " << filename << " does not exist!" << endl;
    }
    else if(!file.is_open()){
        cout << "ERROR: " << filename << " could not be opened!" << endl;
    }

    int ptr=0;
    int val=0;
    
    while(!file.eof()){
        // load line from file
        string newline;
        getline(file,newline);
        
        // parse out comments 
        int i=0;
        string line = "";
        while(i<newline.length() && (isdigit(newline[i]) || (newline[i] == '.'))){
            line += newline[i];
            i++;
        }

        // store instruction to memory
        if(line[0] != '\0'){
            if(line[0] == '.'){
                line = line.substr(1);
                ptr = stoi(line);  
            }
            else{
                val = stoi(line);
                mem[ptr]=val;
                ptr++;
            }
        }
    }
    file.close();
    return true;
}

/// @brief defines the message sent to memory 
/// @param command either read or write
/// @param address address to retreive from memory
void cpu::send(char command, int address){
    int c;
    if(command == 'r'){
        c = 0;
    }
    if(command == 'w'){
        c = 1;
    }
    buffer[0] = c;
    buffer[1] = address;
}

/// @brief defines the message sent to memory 
/// @param command either read or write
/// @param address address in memory
/// @param value data which to put into memory at address
void cpu::send(char command, int address, int value){
    send(command, address);
    buffer[2] = value;
}
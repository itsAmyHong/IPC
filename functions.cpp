#include "functions.h"
using namespace std;

int memory::read(int address){
    cout << "System: Reading " << address << " " << memory[address]<< endl;
    return memory[address];
}

void memory::write(int address, int value){
    cout << "System: Writing " << address << " " << value << endl;
    memory[address] = value;
}

bool cpu::loadProgram(string filename){
    ofstream file;
    file.open(filename);  
    return true;
}

bool cpu::execute(int instruction){
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
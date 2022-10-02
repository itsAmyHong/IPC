/*
    In order to compartmentalize different operations, the code is split into several 
    classes and functions. This file defines classes and initializes functions used in the main file.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/// @brief memory object stores memory array
class memory{
    private:
        int mem[2000]{};
    
    public:
        bool loadProgram(string filename);
        void write(int address, int value);
        int read(int address);
};

/// @brief cpu object defines communication to and from cpu
class cpu{
    public:
        int buffer[3] = {0, 0, 0};
        void send(char command, int pc);
        void send(char command, int pc, int value);
};



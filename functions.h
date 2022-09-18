/*
    In order to compartmentalize different operations, the code is split into several 
    classes and functions. This file defines classes and initializes functions used in the main file.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class memory{
    private:
        int mem[2000];
        int pointer;
    
    public:
        memory();

        const int USER = 0;
        const int SYSTEM = 1000;

        int read(int address, char *buffer);
        void write(int address, int value);

        bool loadProgram(string filename);
};

class cpu{
    public:
        //Registers
		int pc;
		int sp;
		int ir;
		int ac;
		int x;
		int y;

        // kernal mode switch
        bool kernalMode;

        bool execute(int instruction);

};



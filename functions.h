#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class memory{
    private:
        int memory[2000];
    public:
        int read(int address);
        void write(int address, int value);
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

        bool loadProgram(string filename);
        bool execute(int instruction);
};



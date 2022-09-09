#include <iostream>
using namespace std;

class Memory{
    private:
        int memory[2000];

    public:
        int read(int address);
        void write(int address, int value);
};

int Memory::read(int address){
    cout << "System: Reading " << address << " " << memory[address]<< endl;
    return memory[address];
}

void Memory::write(int address, int value){
    cout << "System: Writing " << address << " " << value << endl;
    memory[address] = value;
}
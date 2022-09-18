#include <iostream>
#include <unistd.h>
#include <string>
#include "functions.h"

using namespace std;

// Global one-way pipes for communication (0 - read, 1 - write)
int m2c[2]; // Pipe where CPU reads,  Memory writes
int c2m[2]; // Pupe where CPU writes, Memory reads

string filename = "test.txt";

// Initializes and runs two processes simulating the memory, cpu, and interrupts
int main(){

    pid_t child;
    char buffer[1024];

    cpu processor;
    int program_counter;

    pipe(c2m);
    pipe(m2c);

    child = fork();
    if(child == 0) {
        // In Memory process
        memory mem = memory();

        close(m2c[0]); // m2c close memory read 
        close(c2m[1]); // c2m close memory write

        mem.loadProgram(filename);
        
    } else {
        // In CPU process
        close(m2c[1]); // m2c close cpu write
        close(c2m[0]); // c2m close cpu read

        char temp_buff[5];
        write(c2m[1], &temp_buff, sizeof(temp_buff));

        int program_counter = 0;
        

    }
}

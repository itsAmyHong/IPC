#include <iostream>
#include <unistd.h>
#include <string>
#include "functions.h"

using namespace std;

memory m;
cpu processor;

// Global one-way pipes for communication (0 - read, 1 - write)
int rpipe[2]; // Pipe where CPU reads,  Memory writes
int wpipe[2]; // Pupe where CPU writes, Memory reads

string filename = "test.txt";

// Initializes and runs two processes simulating the memory, cpu, and interrupts
int main(){

    pid_t child;
    char buffer;

    pipe(rpipe);
    pipe(wpipe);

    child = fork();
    if(child == 0) {
        cout << "System: in Memory" << endl;

        close(rpipe[0]);    
        close(wpipe[1]);

        processor.loadProgram(filename);
          
        

    } else {
        cout << "System: in CPU" << endl;
        close(rpipe[1]);
        close(wpipe[0]); 

        cpu processor;
    }
}

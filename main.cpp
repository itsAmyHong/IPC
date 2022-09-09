#include <iostream>
#include <unistd.h>
#include <memory.cpp>
using namespace std;

int main(){

    pid_t child;

    // initialize one-way pipes for communication
    // 0 - read, 1 - write
    int rpipe[2]; // CPU reads, Memory writes
    int wpipe[2]; // CPU writes, Memory reads

    pipe(rpipe);
    pipe(wpipe);
    char buf;

    // create child processes
    child = fork();
    if(child == 0) {
        cout << "hello, I'm Memory" << endl;
        close(rpipe[0]); // Memory cannot read into rpipe
        close(wpipe[1]); // Memory cannot write into wpipe
        Memory m;
        

    } else {
        cout << "hello, I'm CPU" << endl;
        close(rpipe[1]); // CPU cannot write into rpipe
        close(wpipe[0]); // CPU cannot read into wpipe
    }

}

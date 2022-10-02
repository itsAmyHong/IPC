#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "functions.h"
using namespace std;

int main(int argc, char** argv){
    // check for correct number of arguments
    if (argc < 3){
        cout << "ERROR: This program requires input file name  and timer as arguments to operate." << endl;
        exit(0);
    }
    else if (argc > 3) {
        cout << "ERROR: This program only requires input file name and time as arguments" << endl;
        exit(0);
    }

    // define two one way pipes
    int c2m[2]; 
    int m2c[2];

    pipe(c2m);
    pipe(m2c);

    // Memory as child process, cpu as parent process
    int child = fork();
        if(child < 0){
            cout << "ERROR: Failed to fork" << endl;
            exit(0);
        }
        if(child == 0){  
            memory mem;

            // load program from file to memory
            string filename = argv[1];
            mem.loadProgram(filename);

            int buffer[3];
            int temp;
            string line;

            // continue to read commands from cpu
            while (true){
                read(c2m[0], &buffer, 12);
                int command = buffer[0];
                
                // if command is 0, read from cpu and write value at address
                if(command == 0){
                    temp = mem.read(buffer[1]);
                    write(m2c[1],&temp,4);
                } 
                // if command is 1, write value to memory
                else if(command==1){
                    mem.write(buffer[1],buffer[2]);
                } 
                // otherwise exit program
                else{
                    exit(0);
                }
            }
        }
        else{
            // Registers 
            int pc=0;
            int sp=1000;
            int ir=0;
            int ac=0;
            int x=0;
            int y=0;

            int TIMER = stoi(argv[2]);
            int timer = TIMER;
            bool user_mode = true;

            // fetch-execute cycle
            while(true){
                cpu cpu; 
                int temp;

                // check timer
                if(timer<=0 && user_mode){
                    user_mode = false;

                    // save pc and sp to system stack
                    cpu.send('w', 1999, sp);
                    write(c2m[1], &cpu.buffer, 12);

                    cpu.send('w', 1998, pc);
                    write(c2m[1], &cpu.buffer, 12);
                    
                    // set pc to system memory
                    timer += TIMER-1;
                    pc = 1000;
                    sp = 1998;
                }

                // fetch instruction from memory
                cpu.send('r', pc);
                write(c2m[1], &cpu.buffer, 12);
                read(m2c[0], &ir, 4);

                // execute instruction
                switch(ir){
                    case 1: // Load value into ac
                        pc++;
                        cpu.send('r', pc);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &ac, 4);
                        break;
                    case 2: // Load address
                        pc++;
                        cpu.send('r', pc);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &temp, 4);
                        
                        if(temp > 999 && user_mode){
                            cout << "Memory violation: accessing system address " << temp << " in user_mode mode." << endl;
                        } else{
                            cpu.send('0', temp);
                            write(c2m[1], &cpu.buffer, 12);
                            read(m2c[0], &ac, 4);
                        }
                        break;
                    case 3: // LoadInd addr
                        pc++;
                        cpu.send('r', pc);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &temp, 4);

                        if(temp > 999 && user_mode){
                            cout << "Memory violation: accessing system address " << temp << " in user_mode mode." << endl;
                        } else{
                            cpu.send('r', temp);
                            write(c2m[1], &cpu.buffer, 12);
                            read(m2c[0], &temp, 4);

                            if(temp > 999 && user_mode){
                                cout << "Memory violation: accessing system address " << temp << " in user_mode mode." << endl;
                            } else{
                                cpu.send('r', temp);
                                write(c2m[1], &cpu.buffer, 12);
                                read(m2c[0], &ac, 4);
                            }
                        }
                        break;
                    case 4: //LoadIdxX addr
                        pc++;
                        cpu.send('r', pc);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &temp, 4);

                        if(x+temp > 999 && user_mode){
                            cout << "Memory violation: accessing system address " << temp << " in user_mode mode." << endl;
                        } else{
                            cpu.send('r', temp+x);
                            write(c2m[1], &cpu.buffer, 12);
                            read(m2c[0], &ac, 4);
                        }
                        break;
                    case 5: // LoadIdxY address
                        pc++;
                        cpu.send('r', pc);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &temp, 4);

                        if(y+temp > 999 && user_mode){
                            cout << "Memory violation: accessing system address " << temp << " in user_mode mode." << endl;
                        } else{
                            cpu.send('r', temp+y);
                            write(c2m[1], &cpu.buffer, 12);
                            read(m2c[0], &ac, 4);
                        }
                        break;
                    case 6: // LoadSpX
                        if(sp+x > 999){
                                cout << "Memory violation: accessing system address " << temp << " in user_mode mode." << endl;
                        } else{
                            cpu.send('r', sp+x);
                            write(c2m[1], &cpu.buffer, 12);
                            read(m2c[0], &ac, 4); 
                        }
                        break;
                    case 7: // Store addr
                        pc++;
                        cpu.send('r', pc);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &temp, 4);

                        cpu.send('w', temp, ac);
                        write(c2m[1], &cpu.buffer, 12);
                        break;
                    case 8: // Get
                        ac = (rand()%10) + 1;
                        break;
                    case 9: // Put port
                        pc++;
                        cpu.send('r', pc);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0],&temp,4);
                        if(temp==1){
                            cout << ac;
                        }
                        if(temp==2){
                            cout << (char)ac;
                        }
                    case 10: ac+=x; break;
                    case 11: ac+=y; break;
                    case 12: ac-=x; break;
                    case 13: ac-=y; break;
                    case 14: x=ac; break;
                    case 15: ac=x; break;
                    case 16: y=ac; break;
                    case 17: ac=y; break;
                    case 18: sp=ac; break;
                    case 19: ac=sp; break;
                    case 20: // Jump addr
                        pc++;
                        cpu.send('r', pc);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &pc, 4);
                        pc--;
                        break;
                    case 21: // JumpIfEqual addr
                        pc++;
                        if(ac==0){
                            cpu.send('r', pc);
                            write(c2m[1], &cpu.buffer, 12);
                            read(m2c[0], &pc, 4);
                        }
                        break;
                    case 22: // JumpIfNotEqual addr
                        if(ac!=0){
                            cpu.send('r', pc+1);
                            write(c2m[1], &cpu.buffer, 12);
                            read(m2c[0], &pc, 4);
                            pc--;
                        }
                        else {
                            pc++;
                        }
                        break;
                    case 23: // Call addr
                        sp--;
                        cpu.send('w', sp, pc+1);
                        write(c2m[1], &cpu.buffer, 12);

                        cpu.send('r', pc+1);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &pc, 4);
                        pc--;
                        break;
                    case 24: // Ret
                        cpu.send('r', sp);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &pc, 4);
                        sp++;
                        break;
                    case 25: x++; break;
                    case 26: x--; break;
                    case 27: // Push
                        sp--;
                        cpu.send('w', sp, ac);
                        write(c2m[1], &cpu.buffer, 12);
                        break;
                    case 28: // Pop
                        cpu.send('r', sp);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &ac, 4);
                        sp++;
                        break;
                    case 29: // Int
                        user_mode = false;
                        cpu.send('w', 1999, sp);
                        write(c2m[1], &cpu.buffer, 12);
                        
                        cpu.send('w', 1998, pc+1);
                        write(c2m[1], &cpu.buffer, 12);

                        pc = 1499;
                        sp = 1998;
                        break;
                    case 30: // IRet
                        user_mode = true;
                        sp++;
                        cpu.send('r', 1998);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &pc, 4);
                        
                        sp++;
                        cpu.send('r', 1999);
                        write(c2m[1], &cpu.buffer, 12);
                        read(m2c[0], &sp, 4);
                        pc--;
                        break;
                    case 50: // End
                        cpu.buffer[0] = -1;
                        write(c2m[1], &cpu.buffer, 12);
                        exit(0);
                        break;
                }
                pc++;
                timer--;
            }
        }
}




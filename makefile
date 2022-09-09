PROG = ipc
SRCS = main.o functions.o

CXX = g++
CFLAGS  = -g -Wall

all: $(PROG)

$(PROG): $(SRCS)
	$(CXX) $(SRCS) -o $@

main.o: main.cpp 
	g++ -c main.cpp $<

functions.o: functions.cpp 
	g++ -c functions.cpp $<

clean:
	rm -f $(SRCS) $(PROG)
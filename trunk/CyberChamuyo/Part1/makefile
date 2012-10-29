target = tp1

all: $(target)
	g++ -o $(target) *.o

$(target): *.o
	g++ -std=c++0x -o tp1 *.o

*.o: source/*.cpp
	g++ -c -std=c++0x source/*.cpp 

all: main

CXX = g++

LINKFLAGS = -pedantic -Wall -fomit-frame-pointer -funroll-all-loops -O3

main: main.o b_tree.o database.o legal.o cluster.o macro_abcuas.o macro_place.o tetris.o
	$(CXX) $(LINKFLAGS) main.o b_tree.o database.o legal.o cluster.o macro_abcuas.o macro_place.o tetris.o -o main
main.o: main.cpp
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"`date`\"" main.cpp -c
b_tree.o: b_tree.cpp b_tree.h
	$(CXX) $(LINKFLAGS) b_tree.cpp -c
database.o: database.cpp database.h
	$(CXX) $(LINKFLAGS) database.cpp -c
legal.o: legal.cpp legal.h
	$(CXX) $(LINKFLAGS) legal.cpp -c
cluster.o: cluster.cpp cluster.h
	$(CXX) $(LINKFLAGS) cluster.cpp -c
macro_abcuas.o: macro_abcuas.cpp macro_abcuas.h
	$(CXX) $(LINKFLAGS) macro_abcuas.cpp -c
macro_place.o: macro_place.cpp macro_place.h
	$(CXX) $(LINKFLAGS) macro_place.cpp -c
tetris.o: tetris.cpp tetris.h
	$(CXX) $(LINKFLAGS) tetris.cpp -c
clean:
	rm -rf *.o *.gch main



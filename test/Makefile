all: Solver

Solver: Solver.o Maze.o
	gcc -o Solver -g Solver.o Maze.o

Solver.o: Solver.c Solver.h 
	gcc -Wall -pedantic -c -g Solver.c Solver.h

Maze.o: Maze.c Maze.h
	gcc -Wall -pedantic -c -g Maze.c Maze.h

clean: 
	rm -f *.o *.gch Solver

new: 
	make clean
	make


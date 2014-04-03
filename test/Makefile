
Maze: Maze.o mylib.o 
	gcc -o Maze -g Maze.o mylib.o

Maze.o: Maze.c mylib.c
	gcc -Wall -pedantic -c -g Maze.c

mylib.o: mylib.c mylib.h
	gcc -Wall -pedantic -c -g mylib.c


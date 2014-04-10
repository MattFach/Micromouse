#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "Maze.h"

void dummyfunc() {

}

int main (int argc, char ** argv) {


	Maze * my_maze;
	int opt;
	//int command;

	set_debug_off();

	// Checks for the debug flag x in command line argument
	while((opt = getopt(argc, argv, "x")) != EOF) 
		if(opt == 'x')
			set_debug_on();

	// Initialize new maze
	my_maze = new_Maze();
	
	print_map(my_maze);



	delete_Maze(&my_maze);

//	newline(stdout);	
//	writeline ("Please enter Horiz. wall #: ", stdout); /* prompt user input */
//    horiz_wall = decin();   /* Read in from user input */
//    clrbuf(horiz_wall);     /* get rid of extra input */
//    newline(stdout);	
//	writeline ("Please enter Vert. wall #: ", stdout); /* prompt user input */
//    vert_wall = decin();   /* Read in from user input */
//    clrbuf(vert_wall);     /* get rid of extra input */
//	newline(stdout);	


//	newline(stdout);	
	return 1;
}



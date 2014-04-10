
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Maze.h"

void dummyfunc() {

}

int main () {


	Maze * my_Maze = new_Maze();
	
	print_map(my_Maze);

	delete_Maze(&my_Maze);

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



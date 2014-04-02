
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


// Constants
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define SIZE 6

//========================================================================
//
//  struct Node
//
//  Description: 
//
//  Data fields
//
//  Node Functions
//
//========================================================================
typedef struct Node { 

	/* data */
	int distance;
	char section;

	int row;
	int column;
	int floodval;

	bool traveled_to;
	bool traced;

	/* pointers to neighbors */
	struct node * up;
	struct node * down;
	struct node * left;
	struct node * right;
} Node;

typedef struct Maze {

	Node map [SIZE][SIZE];	
	/* 
	struct Node map [SIZE][SIZE]; 
	*/

} Maze;


struct Maze * new_Maze ();
void init_map (Maze * this_maze);
void print_map (Maze * this_maze);


static bool debug_on = FALSE;	/* debug messages flag */
static long maze_counter = 0;	/* number of lists allocated so far */

/* Debug Mode - Setting Functions */

/*-----------------------------------------------------------------------
Function Name:      set_debug_on
Purpose:            To enable Debug Mode
Description:        Sets the class variable debug_on to TRUE
Input:              None
Result:             Debug messages will be displayed while running
                    the driver programs. No return value.
-----------------------------------------------------------------------*/
void set_debug_on (void) {
    
    /* debug mode will be turned on */
    debug_on = TRUE;
}

/*-----------------------------------------------------------------------
Function Name:      set_debug_of
Purpose:            To disable Debug Mode
Description:        Sets the class variable debug_on to FALSE
Input:              None
Result:             Debug messages will not be displayed while running
                    the driver programs. No return value.
-----------------------------------------------------------------------*/
void set_debug_off (void) {

    /* debug mode will be turned off */
    debug_on = FALSE;
}


Maze * new_Maze () {

	Maze * this_maze = (Maze *) malloc(sizeof(Maze));

	init_map(this_maze);

	return this_maze;
}

void init_map (Maze * this_maze) {

	int i, j, reference;
	int halfsize = SIZE / 2;

	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {

			this_maze->map[i][j].traveled_to = false;
			this_maze->map[i][j].traced = false;
			this_maze->map[i][j].row = i;
			this_maze->map[i][j].traveled_to = j;


			// Right now the initialization of flood value only works when SIZE is even
			if (i < halfsize && j < halfsize)
				this_maze->map[i][j].floodval = (halfsize - 1 - i) + (halfsize - 1 - j) ;

			else if (i < halfsize && j >= halfsize)
				this_maze->map[i][j].floodval = (halfsize - 1 - i) + (j - halfsize) ;
			
			else if (i >= halfsize && j < halfsize)
				this_maze->map[i][j].floodval = (i - halfsize) + (halfsize - 1 - j) ;

			else
				this_maze->map[i][j].floodval = (i - halfsize) + (j - halfsize) ;

		}
	}
}

void print_map (Maze * this_maze) {

	int i, j;
	char wallsym;

	printf("\n%s\n\n", "CURRENT MAP VALUES: ");

	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {


			printf("%c%2d", ' ', this_maze->map[i][j].floodval);

		} 
		printf("\n");
	}

	printf("\n");

}

int main () {

	Maze * my_Maze = new_Maze();

	print_map(my_Maze);

	return 1;
}



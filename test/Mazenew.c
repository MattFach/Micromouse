
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mylib.h"
#include "stack.h"


// Constants

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define SIZE 6


// Directions
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// Shortcut Constants
#define MAPIJ this_maze->map[i][j]
#define LEFT this_node->left
#define RIGHT this_node->right
#define UP this_node->up
#define DOWN this_node->down



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
	int floodval;

	//int distance;
	//char section;

	int row;
	int column;

	bool traveled_to;
	bool traced;

	/* pointers to neighbors */
	struct Node * left;
	struct Node * right;
	struct Node * up;
	struct Node * down;
	
} Node;

// Node Functions
struct Node * new_Node ();
bool update_floodval (Node * this_node);
bool update_walls (Node * this_node, bool west_wall, bool east_wall, bool north_wall, bool south_wall);


typedef struct Maze {

	Node * map [SIZE][SIZE];	

} Maze;

// Maze Functions
struct Maze * new_Maze ();
void init_map (Maze * this_maze);
void print_map (Maze * this_maze);


// Constructors

Node * new_Node () {

	Node * this_Node = (Node *) malloc(sizeof(Node));

	return this_Node;
}

Maze * new_Maze () {

	Maze * this_maze = (Maze *) malloc(sizeof(Maze));

	init_map(this_maze);

	return this_maze;
}

void init_map (Maze * this_maze) {

	int i, j;
	int halfsize = SIZE / 2;

	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {

			// Allocate a new Node at this coordinate
			MAPIJ = new_Node ();

			// Initiaize the Node fields
			MAPIJ->traveled_to = false;
			MAPIJ->traced = false;
			MAPIJ->row = i;
			MAPIJ->traveled_to = j;


			// Initializing the floodval at this coord
			// NOTE : Right now this only works when SIZE is even
			if (i < halfsize && j < halfsize)
				MAPIJ->floodval = (halfsize - 1 - i) + (halfsize - 1 - j) ;

			else if (i < halfsize && j >= halfsize)
				MAPIJ->floodval = (halfsize - 1 - i) + (j - halfsize) ;
			
			else if (i >= halfsize && j < halfsize)
				MAPIJ->floodval = (i - halfsize) + (halfsize - 1 - j) ;

			else
				MAPIJ->floodval = (i - halfsize) + (j - halfsize) ;


			// Initializing the pointers to neighboring Nodes
			// By Default, all of the neighbors will be accessible 
			// i.e. no inner walls
			MAPIJ->left = (i == 0) ? NULL : (this_maze->map[i-1][j]);
			MAPIJ->right = (i == SIZE-1) ? NULL : (this_maze->map[i+1][j]);
			MAPIJ->up = (j == 0) ? NULL : (this_maze->map[i][j-1]);
			MAPIJ->down = (j == SIZE-1) ? NULL : (this_maze->map[i][j+1]);

		}
	}
}

// Node Functions


int getLinearNum (Node * this_node) {

	return 16 * (this_node->row) + (this_node->column);
}

Node * getNodeFromNum (Maze * this_maze, int popped_num) {

	int i = popped_num / SIZE;
	int j = popped_num % SIZE;

	return MAPIJ;
}

int getSmallestNeighbor (Node * this_node) {

	// The Node's floodval will be 1 higher than the neigboring cell
	int smallestneighbor = -1;

	// NOTE: LEFT, RIGHT, etc, are substituting:
	// this_node->left, this_node->right, etc.

	if (LEFT != NULL && LEFT->floodval > smallestneighbor)
		smallestneighbor = LEFT->floodval;

	if (RIGHT != NULL && RIGHT->floodval > smallestneighbor)
		smallestneighbor = RIGHT->floodval;	

	if (UP != NULL && UP->floodval > smallestneighbor)
		smallestneighbor = UP->floodval;

	if (DOWN != NULL && DOWN->floodval > smallestneighbor)
		smallestneighbor = DOWN->floodval;

	return smallestneighbor;
}

long floodValCheck(Node * this_node) {

	if (getSmallestNeighbor (this_node) + 1 == this_node->floodval)
		// return true indicating this Node is 1 + min to adj cell.
		return TRUE;

	else 
		return FALSE;
}

bool update_floodval (Node * this_node) {

	this_node->floodval = getSmallestNeighbor (this_node) + 1;

	return true;

}

void push_neighbors (Stack * main_Stack, Node * this_node) {

	int pushed_num;

	if (LEFT != NULL) {

		pushed_num = getLinearNum(LEFT);
		push (main_Stack, pushed_num);
	}

	if (RIGHT != NULL) {

		pushed_num = getLinearNum(RIGHT);
		push (main_Stack, pushed_num);
	}

	if (UP != NULL) {

		pushed_num = getLinearNum(UP);
		push (main_Stack, pushed_num);
	}

	if (DOWN != NULL) {

		pushed_num = getLinearNum(DOWN);
		push (main_Stack, pushed_num);
	}

}


void flood_fill (Maze * this_maze, Node * this_node) {

	Stack * main_Stack = 0;
	Node * working_Node = 0;
	long status;
	int pushed_num;
	//int popped_num;
	long popped_num;

	// Allocate and initialize Stack
	unsigned long amount = SIZE * SIZE;
	main_Stack = new_Stack(amount);

	// Push cell (linearnum) to Stack
	pushed_num = getLinearNum(this_node);
	status = push (main_Stack, pushed_num);

	// While Stack is not empty
	while (!isempty_Stack (main_Stack)) {

		// Pop cell from Stack
		status = pop (main_Stack, &popped_num);
		working_Node = getNodeFromNum (this_maze, popped_num);
	
		// is the cell (1 + minumum OPEN adjascent cell) ?
		status = floodValCheck(working_Node);

		// if YES, keep going until stack empty
		if (status)
			continue;
		
		// if no, change current cell to 1 + minimum adjascent open cell
		// Then push open neighbors to the stack.
		else {

			update_floodval (working_Node);
			push_neighbors (main_Stack, working_Node);	// Push adj open neighbors to stack

		}

	} // end while
		
	// deallocate Stack
	delete_Stack (&main_Stack);

}




bool update_walls (Node * this_node, bool west_wall, bool east_wall, bool north_wall, bool south_wall) {

	// if any of the boolean flags are on, it means that there is a wall in that direction.
	// therefore the pointer to the neighbor should be NULLed

	// NOTE: LEFT, RIGHT, etc, are substituting:
	// this_node->left, this_node->right, etc.

	if (west_wall)
		LEFT = NULL;

	if (east_wall)
		RIGHT = NULL;

	if (north_wall)
		UP = NULL;

	if (south_wall)
		DOWN = NULL;

	return true;
}


// Maze Functions

void print_map (Maze * this_maze) {

	int i, j;
	//char wallsym;

	printf("\n%s\n\n", "CURRENT MAP VALUES: ");

	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {


			printf("%s%2d", "  ", MAPIJ->floodval);

		} 
		printf("\n\n");
	}

	printf("\n");
}



// Main

int main () {

/* This stuff below is for testing Maze code */

	Maze * my_Maze = new_Maze();
	int horiz_wall, vert_wall;
	print_map(my_Maze);

	newline(stdout);	
	writeline ("Please enter Horiz. wall #: ", stdout); /* prompt user input */
    horiz_wall = decin();   /* Read in from user input */
    clrbuf(horiz_wall);     /* get rid of extra input */
    newline(stdout);	
	writeline ("Please enter Vert. wall #: ", stdout); /* prompt user input */
    vert_wall = decin();   /* Read in from user input */
    clrbuf(vert_wall);     /* get rid of extra input */
	newline(stdout);	

	

	newline(stdout);	
	return 1;
}



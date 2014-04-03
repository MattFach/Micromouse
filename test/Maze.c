
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mylib.h"


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
#define FLOODVAL this_node->floodval
#define ROW this_node->row
#define COL this_node->column
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

typedef struct Maze {

	Node * map [SIZE][SIZE];	
	int size;

} Maze;


// Node Functions
struct Node * new_Node ();
void flood_fill (Node * this_node);
void set_wall (Maze * this_maze, Node * this_node, int dir, int set_on);

// Floodfill Helper Functions
int get_smallest_neighbor (Node * this_node);
int floodval_check(Node * this_node) ;
void update_floodval (Node * this_node);
void recurse_neighbors (Node * this_node) ;


// Maze Functions
struct Maze * new_Maze ();
void print_map (const Maze * this_maze);



// Constructors

Node * new_Node (Maze * this_maze, int i, int j) {

	Node * this_node = (Node *) malloc(sizeof(Node));

	int halfsize = this_maze->size / 2;

	this_node->traveled_to = false;
	this_node->traced = false;
	this_node->row = i;
	this_node->column = j;

	// Initializing the floodval at this coord
	// NOTE : Right now this only works when SIZE is even
	if (i < halfsize && j < halfsize)
		FLOODVAL = (halfsize - 1 - i) + (halfsize - 1 - j) ;
			
	else if (i < halfsize && j >= halfsize)
		FLOODVAL = (halfsize - 1 - i) + (j - halfsize) ;
			
	else if (i >= halfsize && j < halfsize)
		FLOODVAL = (i - halfsize) + (halfsize - 1 - j) ;

	else
		FLOODVAL = (i - halfsize) + (j - halfsize) ;


	// Initializing the pointers to neighboring Nodes
	// By Default, all of the neighbors will be accessible 
	// i.e. no inner walls. outer walls are implied and constructed
	LEFT = (i == 0) ? NULL : (this_maze->map[i-1][j]);
	RIGHT = (i == SIZE-1) ? NULL : (this_maze->map[i+1][j]);
	UP = (j == 0) ? NULL : (this_maze->map[i][j-1]);
	DOWN = (j == SIZE-1) ? NULL : (this_maze->map[i][j+1]);

	return this_node;
}

Maze * new_Maze () {

	Maze * this_maze = (Maze *) malloc(sizeof(Maze));

	int i, j;

	this_maze->size = SIZE;

	for (i = 0; i < SIZE; ++i) 
		for (j = 0; j < SIZE; ++j) 
			// Allocate a new Node at this coordinate
			MAPIJ = new_Node (this_maze, i, j);

	return this_maze;
}


// Node Functions


int get_smallest_neighbor (Node * this_node) {

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

int floodval_check(Node * this_node) {

	if (get_smallest_neighbor (this_node) + 1 == this_node->floodval)
		// return true indicating this Node is 1 + min to adj cell.
		return TRUE;

	else 
		return FALSE;
}

void update_floodval (Node * this_node) {

	this_node->floodval = get_smallest_neighbor (this_node) + 1;

}

void recurse_neighbors (Node * this_node) {

	// A NULL neighbor represents a wall
	// If neighbor is accessible, call floodfill w/neighbor @ param

	if (LEFT != NULL) 
		flood_fill (LEFT);

	if (RIGHT != NULL) 
		flood_fill (RIGHT);

	if (UP != NULL) 
		flood_fill (UP);

	if (DOWN != NULL) 
		flood_fill (DOWN);

}

void flood_fill (Node * this_node) {

	int status;  // Flag for valid floodval
	
	// is the cell (1 + minumum OPEN adjascent cell) ?
	status = floodval_check (this_node);

	// if no, change current cell to 1 + minimum adjascent open cell
	// Then push open neighbors to the recursive stack.
	if (!status) {

		update_floodval (this_node); // Update floodval to 1 + min open neighbor
		recurse_neighbors(this_node); // Recursive call to neighbors
	}
	
}

void set_wall (Maze * this_maze, Node * this_node, int dir, int set_on) {

	switch (dir) {
		case EAST : 
			if (ROW != SIZE - 1)
				LEFT = (set_on) ? NULL : this_maze->map[ROW+1][COL];
			break;

		case WEST :
			if (ROW != 0) 
				RIGHT = (set_on) ? NULL : this_maze->map[ROW-1][COL];
			break;

		case NORTH :
			if (COL != 0)
				UP = (set_on) ? NULL : this_maze->map[ROW][COL-1];	
			break;

		case SOUTH :
			if (COL != SIZE -1)
				DOWN = (set_on) ? NULL : this_maze->map[ROW][COL+1];
			break; 
	}
}

//void update_node (Node * this_node){



//}


// Maze Functions

void print_map (const Maze * this_maze) {

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



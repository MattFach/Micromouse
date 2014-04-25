
#include <stdlib.h>
#include <stdio.h>
#include "Maze.h"

static int debug_on = FALSE;    /* debug flag */

// Debug Statement Functions

void set_debug_on () {
    
    /* Debug Statements turned on */
    debug_on = TRUE;
}


void set_debug_off () {

    /* Debug Statements turned off */
    debug_on = FALSE;
}


// Constructors

Node * new_Node (Maze * this_maze, int i, int j) {

	if (debug_on)
		printf("allocating %d, %d\n", i, j);

	Node * this_node = (Node *) malloc(sizeof(Node));

	int halfsize = this_maze->size / 2;

	this_node->traveled_to = FALSE;
	this_node->traced = FALSE;
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
	/*
	LEFT = (j == 0) ? NULL : (this_maze->map[i][j-1]);
	RIGHT = (j == SIZE-1) ? NULL : (this_maze->map[i][j+1]);
	UP = (i == 0) ? NULL : (this_maze->map[i-1][j]);
	DOWN = (i == SIZE-1) ? NULL : (this_maze->map[i+1][j]);
*/
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


	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			MAPIJ->left = (j == 0) ? NULL : (this_maze->map[i][j-1]);
			MAPIJ->right = (j == SIZE-1) ? NULL : (this_maze->map[i][j+1]);
			MAPIJ->up = (i == 0) ? NULL : (this_maze->map[i-1][j]);
			MAPIJ->down = (i == SIZE-1) ? NULL : (this_maze->map[i+1][j]);
		}


	return this_maze;
}


// Destructors
void delete_Node (Node ** npp) {

	if (debug_on) 
		printf("deallocating %d, %d\n", (*npp)->row, (*npp)->column);

	free (*npp);
	*npp = 0;
}


void delete_Maze (Maze ** mpp) {

	int i, j;

	for (i = 0; i < (*mpp)->size; i++) {

		for (j = 0; j < (*mpp)->size; j++) {
			delete_Node (&((*mpp)->map[i][j])); 
		}
	}

	free(*mpp);
	*mpp = 0;
}


// Node Functions


int get_smallest_neighbor (Node * this_node) {

	printf("In get_smallest_neighbor\n");

	// The Node's floodval will be 1 higher than the neigboring cell
	int smallestneighbor = 255;

	// NOTE: LEFT, RIGHT, etc, are substituting:
	// this_node->left, this_node->right, etc.

	if (LEFT != NULL && (LEFT->floodval) < smallestneighbor)
		smallestneighbor = LEFT->floodval;

	if (RIGHT != NULL && (RIGHT->floodval) < smallestneighbor)
		smallestneighbor = RIGHT->floodval;	

	if (UP != NULL && (UP->floodval) < smallestneighbor)
		smallestneighbor = UP->floodval;

	if (DOWN != NULL && (DOWN->floodval) < smallestneighbor)
		smallestneighbor = DOWN->floodval;

	return smallestneighbor;
}


// Return the next direction that the solver would go
int get_smallest_neighbor_dir (Node * this_node, int preferred_dir) {

	printf("In get_smallest_neighbor_dir\n");

	// get the smallest neighboring flood_val;
	int smallestval = get_smallest_neighbor(this_node);
	int pathcount = 0;

    printf("preferred_dir: %d\n", preferred_dir);
    printf("smallestval: %d\n", smallestval);

    printf("neighboring floodvals:\n");
    if (UP != NULL)
    	printf("UP: %d\n", UP->floodval);
    if (RIGHT != NULL)
    	printf("RIGHT: %d\n", RIGHT->floodval);
    if (DOWN != NULL)
    	printf("DOWN: %d\n", DOWN->floodval);
    if (LEFT != NULL)
    	printf("LEFT: %d\n", LEFT->floodval);

	if ((UP != NULL) && (UP->floodval == smallestval)) {
    	printf("NORTH cell reachable\n");
    	pathcount++;
    }
  	if ((RIGHT != NULL) && (RIGHT->floodval == smallestval)) {
    	printf("EAST cell reachable\n");
    	pathcount++;
  	}
  	if ((DOWN != NULL) && (DOWN->floodval == smallestval)) {
    	printf("SOUTH cell reachable\n");
    	pathcount++;
    }
  	if ((LEFT != NULL) && (LEFT->floodval == smallestval)) {
    	printf("WEST cell reachable\n");
    	pathcount++;
	}

    printf("pathcount: %d\n", pathcount);

    if (pathcount > 1)
    	return preferred_dir;

    else {
    	
		if ((UP != NULL) && (UP->floodval == smallestval))
		   return NORTH;
  		else if ((RIGHT != NULL) && (RIGHT->floodval == smallestval))
    		return EAST;
  		else if ((DOWN != NULL) && (DOWN->floodval == smallestval))
    		return SOUTH;
  		else //if ((LEFT != NULL) && (LEFT->floodval) == smallestval)
    		return WEST;
	}
}


int floodval_check(Node * this_node) {

	//printf("In floodval_check\n");

	if (get_smallest_neighbor (this_node) + 1 == this_node->floodval)
		// return true indicating this Node is 1 + min to adj cell.
		return TRUE;

	else 
		return FALSE;
}

void update_floodval (Node * this_node) {

	//printf("In update_floodval\n");

	this_node->floodval = get_smallest_neighbor (this_node) + 1;

}

void recurse_neighbors (Node * this_node) {

	//printf("In recurse_neighbors\n");

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

	printf("In flood_fill\n");

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

// We really do not need to pass Maze * this_maze, 
// but it is done here for the set_off option
// where set_off being 0 will "erase" the wall... which is here for now.
void set_wall (Maze * this_maze, Node * this_node, int dir, int set_on) {

	switch (dir) {

		case NORTH :
			if (ROW != 0) {
				printf("NORTH Wall Set\n");
				//UP = (set_on) ? NULL : NULL;//this_maze->map[ROW-1][COL];	
				UP = NULL;
			}
			break;

		case SOUTH :
			if (ROW != SIZE -1) {
				printf("SOUTH Wall Set\n");
				DOWN = NULL;
				//DOWN = (set_on) ? NULL : NULL; //this_maze->map[ROW+1][COL];
			}
			break; 

		case EAST : 
			if (COL != SIZE - 1) {
				printf("EAST Wall Set\n");
				RIGHT = NULL;
				//LEFT = (set_on) ? NULL : NULL; //this_maze->map[ROW][COL+1];
			}
			break;

		case WEST :
			if (COL != 0) { 
				printf("WEST Wall Set\n");
				LEFT = NULL;
				//RIGHT = (set_on) ? NULL : NULL; //this_maze->map[ROW][COL-1];
			}
			break;

	}
}


// Visit cell = Updates a node
void visit_node (Maze * this_maze, Node * this_node){

	this_node->traveled_to = TRUE;

	// Use sensors to obtain wall information...
	// Call(s) to set_wall(this_maze, this_node, ...) to update wall info

	flood_fill (this_node);

}


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



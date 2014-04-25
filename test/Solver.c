#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "Maze.h"

void dummyfunc() {

}

void check_goal_reached (int * x, int * y, int * found_goal) {

  printf("In check_goal_reached\n");

  if (*x == SIZE / 2 || *x == SIZE / 2 - 1)
    if (*y == SIZE / 2 || *y == SIZE / 2 - 1) {
      *(found_goal) = TRUE; 
    }

}

void move_dir(Maze * this_maze, int * x, int * y, int * dir) {

  // When the parameters are passed, 
  // x, y are current positions, dir is current directions

  printf("In move_dir\n");
  printf("preffered_dir: %d\n", *dir );
  printf("current coords: %d,%d\n", *x, *y);

  Node * this_node = this_maze->map[(*x)][(*y)];
  int next_dir = get_smallest_neighbor_dir(this_node, *dir);
  printf("%d\n", next_dir);

  if (next_dir == NORTH) 
    (*x) = (*x) - 1;
  else if (next_dir == EAST) 
    (*y) = (*y) + 1;
  else if (next_dir == SOUTH) 
    (*x) = (*x) + 1;
  else if (next_dir == WEST) 
    (*y) = (*y) - 1;

  (*dir) = next_dir;



}

void visit_Node(Maze * this_Maze, int x, int y, int wallval) {

  int northwall, eastwall, southwall, westwall;
  Node * this_Node = this_Maze->map[x][y];

  northwall = eastwall = southwall = westwall = 0;

  printf("In visit_Node\n");
  printf("wallval: %d\n", wallval);

  if (wallval / 8 == TRUE) {
    westwall = TRUE;
    wallval -= 8;
  }

  if (wallval / 4 == TRUE) {
    southwall = TRUE;
    wallval -= 4;
  }

  if (wallval / 2 == TRUE) {
    eastwall = TRUE;
    wallval -= 2;
  }

  if (wallval / 1 == TRUE) {
    northwall = TRUE;
  }

  printf("N,E,S,W : %d, %d, %d, %d\n", northwall, eastwall, southwall, westwall);

  if (northwall) 
    set_wall(this_Maze, this_Node, NORTH, TRUE);
  if (eastwall)
    set_wall(this_Maze, this_Node, EAST, TRUE);
  if (southwall)
    set_wall(this_Maze, this_Node, SOUTH, TRUE);
  if (westwall)
    set_wall(this_Maze, this_Node, WEST, TRUE);

  flood_fill(this_Node);


}


int getVal(char c)
{
  
  int rtVal = 0;

  if(c >= '0' && c <= '9')
      rtVal = c - '0';
  
  else
    rtVal = c - 'a' + 10;
  
  return rtVal;

}


int main (int argc, char ** argv) {

  int found_goal;
	int direction;
	int x;
	int y;

	int Walls[SIZE][SIZE];
	int i, j;

	Maze * my_maze;
	int opt;
	char ch;
	char file_name[25];
	FILE *fp;
	//int command;

	set_debug_off();

	// Checks for the debug flag x in command line argument
	while((opt = getopt(argc, argv, "x")) != EOF) 
		if(opt == 'x')
			set_debug_on();

	// Initialize new maze
	my_maze = new_Maze();
	
	print_map(my_maze);

	// Open File and Read walls
	printf("Enter the name of maze file: ");
	gets(file_name);

	fp = fopen(file_name, "r");

	if (fp == NULL) {
		perror("Error while opening file");
		exit(EXIT_FAILURE);
	}


  // Reads Values and store them to appropriate array 

  for (j = 0; j < SIZE; j++) {
    for (i = SIZE-1; i >= 0; i--) {
    	if((ch = fgetc(fp)) != EOF) {
    		if (ch == ' ' || ch == '\n') {
    			i++;
    			continue;
    		}
    		int val = getVal(ch) * 16 + getVal(fgetc(fp));
    		Walls[i][j] = val;
    	}  		
    }
  }

  fclose(fp);


  // Prints the wall values... 
  // Status of each cell's walls is represented by an integer, between 0 and 15
/*
			 _1
		8	I_I 2
			  4
	
		Basically, if North Wall on : 1
				   if East Wall on  : 2
				   if South Wall on : 4
				   if West Wall on  : 8

*/

  printf("\n");
  for (i = 0; i < SIZE; i++) {
   	for (j = 0; j < SIZE; j++) {
   		printf("  %2d  ", Walls[i][j]);
    }
    printf("\n\n");
  }
  printf("\n\n");


	// Begin Solving!
  x = 15;
  y = 0;
  direction = NORTH;
  found_goal = FALSE;

  while (!found_goal) {
    printf("%d, %d\n", x, y);
    visit_Node(my_maze, x, y, Walls[x][y]);
    move_dir(my_maze, &x, &y, &direction);
    print_map(my_maze);
    check_goal_reached(&x, &y, &found_goal);
    if (x < 0 || y < 0) {
      printf("NEGATIVE COORD: ERROR\n");
      return 0;
    }
    printf("press any key to continue...\n");
    getchar();
  }

  // Deallocate the Maze
  delete_Maze(&my_maze);

	return 1;
}



#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "Maze.h"

void check_start_reached (int * x, int * y, int * found_goal) {

  if (*x == 15 && *y == 0) {
    *found_goal = TRUE;
    printf("Goal Coorinates Reached: %d, %d\n", *x, *y);
  }

}

void check_goal_reached (int * x, int * y, int * found_goal) {

  //printf("In check_goal_reached\n");

  if (*x == SIZE / 2 || *x == SIZE / 2 - 1)
    if (*y == SIZE / 2 || *y == SIZE / 2 - 1) {
      *(found_goal) = TRUE;
      printf("Goal Coordinates Reached: %d, %d\n", *x, *y); 
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

void visit_Node(Maze * this_maze, Stack * this_stack, int x, int y, int wallval) {

  int northwall, eastwall, southwall, westwall;
  Node * this_node = this_maze->map[x][y];

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

  if (northwall) {
    if (this_node->row != 0)
      push (this_stack, MAP[ROW-1][COL]);
    set_wall(this_maze, this_node, NORTH, TRUE);
  }
  if (eastwall) {
    if (this_node->column != SIZE-1)
      push (this_stack, MAP[ROW][COL+1]);
    set_wall(this_maze, this_node, EAST, TRUE);
  }
  if (southwall) {
    if (this_node->row != SIZE-1)
      push (this_stack, MAP[ROW+1][COL]);
    set_wall(this_maze, this_node, SOUTH, TRUE);
  }
  if (westwall) {
    if (this_node->column != 0)
      push (this_stack, MAP[ROW][COL-1]);
    set_wall(this_maze, this_node, WEST, TRUE);
  }

  push(this_stack, this_node);

  while (!is_empty_Stack(this_stack)) {
    pop(this_stack, &this_node);
    flood_fill(this_node, this_stack);
  }

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

  Stack * my_stack;
  //Node * temp;

	set_debug_off();

	// Checks for the debug flag x in command line argument
	while((opt = getopt(argc, argv, "x")) != EOF) 
		if(opt == 'x')
			set_debug_on();

	// Initialize new maze
	my_maze = new_Maze();

  // Initialize new stack
  my_stack = new_Stack();

	
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
    visit_Node(my_maze, my_stack, x, y, Walls[x][y]);
    move_dir(my_maze, &x, &y, &direction);
    printf("\nCurrent Location: %d,%d", x, y);
    print_map(my_maze);
    check_goal_reached(&x, &y, &found_goal);
    if (x < 0 || y < 0) {
      printf("NEGATIVE COORD: ERROR\n");
      return 0;
    }
    if (found_goal)
      printf("press enter to end simulation...\n");
    else
      printf("press enter to continue...\n");
    while(getchar() == 13);
    
  }

  /* read the walls around goal */
  /*
  for (int i = 0, i < 4, i++) {



  }
  */

  /* reset found_goal for returning to start */
  //found_goal = FALSE;

  /* set goal to 0, then reflood maze */
  /*
  set_value(my_maze->map[15][0], 0);
  push_open_neighbors (my_maze->map[15][0], my_stack);
  while (!is_empty_Stack(my_stack)) {
    pop(my_stack, &temp);
    flood_fill(temp, my_stack);
  }

  while (!found_goal) {
    printf("%d, %d\n", x, y);
    visit_Node(my_maze, my_stack, x, y, Walls[x][y]);
    move_dir(my_maze, &x, &y, &direction);
    printf("\nCurrent Location: %d,%d", x, y);
    print_map(my_maze);
    check_start_reached(&x, &y, &found_goal);
    if (x < 0 || y < 0) {
      printf("NEGATIVE COORD: ERROR\n");
      return 0;
    }
    if (found_goal)
      printf("press enter to end simulation...\n");
    else
      printf("press enter to continue...\n");
    while(getchar() == 13);
    
  }
*/

  // Deallocate the Maze
  delete_Maze(&my_maze);

	return 1;
}



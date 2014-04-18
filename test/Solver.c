#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "Maze.h"

void dummyfunc() {

}

int getVal(char c)
   {
       int rtVal = 0;

       if(c >= '0' && c <= '9')
       {
           rtVal = c - '0';
       }

       //else if (c == ' ' || c == '\n')
       //{
       	//	rtval = -1;
      // }

       else
       {
           rtVal = c - 'a' + 10;
       }

       return rtVal;
   }

int main (int argc, char ** argv) {

	//int direction;

	//int x;
	//int y;

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
/*
	while((ch = fgetc(fp))  != EOF)
    {
   	  if (ch == ' ' || ch =='\n')
   	  	continue;
      int val = getVal(ch) * 16 + getVal(fgetc(fp));
      printf("current number - %d\n", val);
    }
*/
    for (j = 0; j < SIZE; j++) {
    	for (i = SIZE-1; i >= 0; i--) {
    		if((ch = fgetc(fp)) != EOF) {
    			if (ch == ' ' || ch == '\n') {
    				i++;
    				continue;
    			}
    			int val = getVal(ch) * 16 + getVal(fgetc(fp));
//    			printf("current number at %d, %d - %d\n", i, j, val);
    			Walls[i][j] = val;
//   			printf("%d\n", Walls[i][j]);
    		}
    		
    	}
    }


/*
	printf("The contents of %s file are :\n", file_name);

	for (i = 0; i < SIZE; i++) {
		for (j = SIZE-1; j >=0; j--) {
			fscanf (fp, "%x", &(Walls[i][j]));
		}
	}
)
 
    while( ( ch = fgetc(fp) ) != EOF )
      printf("%c",ch);
 */
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

    for (i = 0; i < SIZE; i++) {
   		for (j = 0; j < SIZE; j++) {
   			printf("  %2d  ", Walls[i][j]);
        }
   	printf("\n");
    }

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



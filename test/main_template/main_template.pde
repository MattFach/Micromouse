/*
 * Main Template
 *
 */
#include <stdlib.h>

// Constants

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define SIZE 16     // Size of one dimention of Map


// Directions
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// Shortcut Constants
//#define MAPIJ this_maze->map[i][j]
//#define MAP this_maze->map
//define FLOODVAL this_node->floodval
//#define ROW this_node->row
//#define COL this_node->column
//#define VISITED this_node->visited
#define LEFT this_node->left
#define RIGHT this_node->right
#define UP this_node->up
#define DOWN this_node->down

// Stack Constants
#define SPI 1     // Stack Pointer Index
#define SSI 0       // Stack Size Index
#define STACK_OFFSET 2  // Size of Stack's property Array
#define STACKSIZE 80

// Solver Constants - will be used on mouse
#define START_X 15
#define START_Y 0
#define LARGEVAL 301



/*** Struct Definition and Functions ***/

/* Node Struct */
typedef struct Node { 

  /* data fields */
  short floodval;
  short row;
  short column;
  short visited;

  /* pointers to neighbors */
  struct Node * left;
  struct Node * right;
  struct Node * up;
  struct Node * down;
  
} Node;

/* Maze Struct */
typedef struct Maze {

  Node * map [SIZE][SIZE];  

} Maze;


/* Stack Struct */
typedef struct Stack {

  short properties [STACK_OFFSET];
  Node * the_stack [STACKSIZE];

} Stack;


struct Node * new_Node (const short i, const short j);
void delete_Node (Node ** npp);
void flood_fill (Node * this_node, Stack * this_stack, const short reflood_flag);
void set_wall (Node * this_node, const short dir);
void set_value (Node * this_node, const short value);
void set_visited (Node * this_node);
short get_smallest_neighbor_dir (Node * this_node, const short preferred_dir);

struct Maze * new_Maze ();
void delete_Maze (Maze ** mpp);

Stack * new_Stack();
void delete_Stack (Stack ** spp);
int is_empty_Stack (Stack * this_stack);
void pop (Stack * this_stack, Node ** npp);
void push (Stack * this_stack, Node * this_node);



/*** Maple Pins Constants ***/


const int L90sensor = 3;   //  James's pin declarations
const int R90sensor = 8;
const int L45sensor = 4;
const int R45sensor = 9;
const int LeftMotor = 11;
const int RightMotor = 10;

const int sense_1 = 3, sense_2 = 4, sense_3 = 5, sense_4 = 9, sense_5 = 8;  // IR sensor pins

const int L_encoder1 = 1, L_encoder2 = 14;   // left encoder pins

const int R_encoder1 = 0, R_encoder2 = 31;  // right encoder pins

const int right_enable = 10, left_enable = 11;        // motor enable pins

const int led1 = 15, led2 = 16, led3 = 17, led4 = 18, led5 = 19;  // test led pins

const int switch1 = 20, switch2 = 21, switch3 = 22, switch4 = 23, switch5 = 24;   // switch pins

const int R_fwd = 13, R_bkw = 12, L_fwd = 7, L_bkw = 6;  // (verify)  motor direction pins

const int standby1 = 29, standby2 = 28;

//const int Kp = .85, Kd = 0;

int R_enable_val = 14000;  // initialize enable values high
int L_enable_val = 13000;

volatile int R_encoder_val = 0;  // declare encoder interrupt values
volatile int L_encoder_val = 0;



/* Solver variables */
Maze * my_maze;    /* maze for keeping track of flood values and walls */
Stack * my_stack;  /* stack used for flood fill */
Node * temp;  /* used for in-between start->goal, goal->start transition */
short found_dest;   /* flag if goal is reached */
short direction;    /* keeps track of direction that mouse is moving in */
short x, y; /* keeps track of current row, col value mouse is in within maze */
short goal_x, goal_y; /* keeps track of goal's x, y, once found */



/*** Setup ***/


void setup()
{
  
  pinMode(sense_1, INPUT_ANALOG);
  pinMode(sense_2, INPUT_ANALOG);
  pinMode(sense_3, INPUT_ANALOG);
  pinMode(sense_4, INPUT_ANALOG);
  pinMode(sense_5, INPUT_ANALOG);
  
  attachInterrupt(L_encoder1, left_interrupt, RISING);  // may need to adjust encoder operation
  attachInterrupt(L_encoder2, left_interrupt, RISING);
  attachInterrupt(R_encoder1, right_interrupt, RISING);
  attachInterrupt(R_encoder2, right_interrupt, RISING);  // comment out interrupts not used

  pinMode(right_enable, PWM);
  pinMode(left_enable, PWM);
  
  pinMode(led1, PWM);         // configure first two test LEDs as PWM outs
  pinMode(led2, PWM);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  pinMode(switch4, INPUT);
  pinMode(switch5, INPUT);
  
  pinMode(R_fwd, OUTPUT);
  pinMode(R_bkw, OUTPUT);
  pinMode(L_fwd, OUTPUT);
  pinMode(L_bkw, OUTPUT);
  pinMode(standby1, OUTPUT);
  pinMode(standby2, OUTPUT);
  
  digitalWrite(standby1, HIGH);
  digitalWrite(standby2, HIGH);
 
  pwmWrite(right_enable, R_enable_val);
  pwmWrite(left_enable, L_enable_val);
  

  /* allocating maze solving resources */
  my_maze = (Maze *) new_Maze();    /* Initialize new maze */
  my_stack = (Stack *) new_Stack();  /* Initialize new stack */
  
  /* Initialize variables */
  x = START_X;
  y = START_Y;
  direction = NORTH;
  found_dest = FALSE;
  exit_solver_loop = FALSE;
  
}


void loop()
{
  


  motor_test();
  drive_straight();
  //delay(100);
  //	turn_left();

  //	delay(2000);
	
	
	//int left, right, straight;  // make sure the left90 sensor is pin 4, left45 is pin 5, right45 is 9
				    // and right90 is pin 3
				    // if this isn't true, change the pin declarations up top
				    // (BOTH mine and James's)
				    // my senors from 1 through 5 correspond to from left to right (90,45,0,45,90)
	
	//left = analogRead(sense_1);
	//right = analogRead(sense_5);
	//straight = analogRead(sense_3);
	
	if(analogRead(sense_3) > 3000)     // if the mouse gets too close to the wall before turning, decrease the value
	{			// if the mouse starts to turn before getting close enough, increase delay
				// delay can be found in the next three if statements, all delay functions
				// must have the same delqy value;
		about_face();
		
		
	}
	/*
	else if(right < 3000)  // if the mouse doesnt see the opening, increase the value (including below)
	{			// if the mouse turns where it shouldnt, decrease the value (including below)
		
		delay(0);  // increase by 100's, if the mouse goes too far, increase by 10's or 20's
		
		turn_right;
	}
	
	else if(left < 3000)  //  if the mouse doesnt see the opening, increase the value
	{			// if the mouse turns where it shouldnt, decrease the value
		
		delay(0);  // increase by 100's, if the mouse goes too far, increase by 10's or 20's
		
		turn_left();
	}
	
	else
	{
		delay(0);  // increase by 100's, if the mouse goes too far, increase by 10's or 20's
		
		turn_left();
		turn_left();
	}
*/
  
	 /*
	 // figure out how fast mouse can slow down 
	 // need decision(algorithm) function 
	 // need mapping function 
	 // need function to determine current grid location
	 // need turning functions 
	 // need exploration(algorithm) function 
	 // need straight line function
	 // need race function (premapped maze) <- shortest path
	 // ^ race function may need to be called at dead end (to find closest door)
   
  
  
  */
  
  
}
/*** End of void loop() ***/


void solver() {

  while (!exit_solver_loop) {

    found_dest = FALSE;
    direction = NORTH;

    /* Forward trip: start -> goal */
    while (!found_dest) {

      // visit_node()
      move_dir(my_maze, &x, &y, &direction);
      check_goal_reached(&x, &y, &found_dest);


    }

    /* Once goal is reached, save the location */
    goal_x = x;
    goal_y = y;

  }

  /*** Reading the walls of the CENTER GOAL CELLS ***/  
    for (short i = 0; i < 4; i++) {
      //visit_Node(my_maze, my_stack, x, y, Walls[x][y], FALSE);  
      /*
      if ( x == SIZE / 2 - 1 && y == SIZE / 2 - 1 )
        x++;
      else if ( x == SIZE / 2 && y == SIZE / 2 - 1 ) 
        y++;
      else if ( x == SIZE / 2 && y == SIZE / 2 ) 
        x--;
      else 
        y--;
      */
    }


}




void left_interrupt()
{
  ++ L_encoder_val;
}

void right_interrupt()
{
  ++ R_encoder_val;
}

void motor_test()  // motor testing function
{
  //pwmWrite(right_enable, R_enable_val);
  //pwmWrite(left_enable, L_enable_val);
  
  digitalWrite(R_bkw, LOW);
  digitalWrite(L_bkw, LOW);
  
  digitalWrite(R_fwd, HIGH);
  digitalWrite(L_fwd, HIGH);
  /*
  delay(1000);
  
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
  
  delay(100);
  
  digitalWrite(R_bkw, HIGH);
  digitalWrite(L_bkw, HIGH);
  
  delay(1000);
  
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_bkw, LOW);
  
  delay(100);
  
  digitalWrite(R_bkw, HIGH);
  digitalWrite(L_fwd, HIGH);
  
  delay(1000);
  
  digitalWrite(R_bkw, LOW);
  digitalWrite(L_fwd, LOW);
  
  delay(100);
  
  digitalWrite(R_bkw, HIGH);
  digitalWrite(L_bkw, LOW);
  
  delay(1000);
  
  digitalWrite(R_bkw, LOW);
  digitalWrite(L_bkw, LOW);
  */
}

void turn_left() // point turn
{
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
  digitalWrite(R_bkw, LOW);
  digitalWrite(L_bkw, LOW);
  
  pwmWrite(right_enable, 17000);  // decrese the value for a slower turn, increase it to go faster
  pwmWrite(left_enable, 15000);	  // decrese the value for a slower turn, increase it to go faster
  
  delay(200);  // decrease delay if mouse pauses too much, increase it if the mouse tries to turn
  	       // before slowing down enough (same thing in turn_right)
  
  digitalWrite(R_fwd, HIGH);
  
  digitalWrite(L_bkw, HIGH);
  
  delay(400);  // tune this value for complete turn ************* ///////////////////

  digitalWrite(R_fwd, LOW);
  digitalWrite(L_bkw, LOW);
}

void turn_right()  // point turn
{
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
  digitalWrite(R_bkw, LOW);
  digitalWrite(L_bkw, LOW);
  
  pwmWrite(right_enable, 17000);  // decrese the value for a slower turn, increase it to go faster
  pwmWrite(left_enable, 15000);   // decrese the value for a slower turn, increase it to go faster
  
  delay(100);
  
  digitalWrite(L_fwd, HIGH);
  
  digitalWrite(R_bkw, HIGH);
  
  delay(400);  // tune this value for complete turn ******* ///////////////////

  digitalWrite(L_fwd, LOW);
  digitalWrite(R_bkw, LOW);
}


void about_face()  // because, why not?
{
  	int value = R_encoder_val;
  	
  	digitalWrite(L_fwd, LOW);
  	digitalWrite(L_bkw, HIGH);
  	
  	pwmWrite(R_enable_val, 15000);
  	pwmWrite(L_enable_val, 15000);
  	
  	while(R_encoder_val - value < 17);  // *********increase value to turn more***********
  	
  	digitalWrite(L_bkw, LOW);
  	digitalWrite(L_fwd, HIGH);
}

void GoStraight()
{
//int currentVoltage;
int voltageChange = 5;
int D1 = analogRead(L45sensor) - analogRead(R45sensor);
delay(20);						//  delay MIGHT need to be longer
int D2 = analogRead(L45sensor) - analogRead(R45sensor);

if(D1 == D2)
;
else if(D1 < D2)
{
if(voltageChange < 0)
{
  ChangeLeft(&voltageChange);
}
else
{
  ChangeRight(&voltageChange);
}
}
else if(D1 > D2)
{
if(voltageChange < 0)
ChangeRight(&voltageChange);
else
{
  ChangeLeft(&voltageChange);
}
}
}

void ChangeRight(int* change)
{
int currentVoltage = analogRead(RightMotor);
if(currentVoltage == 0 || currentVoltage > 3125)  //change 1020 value to max 
*change = -(*change);                                             //voltage wanted
pwmWrite(RightMotor, currentVoltage*16 + *change);
}

void ChangeLeft(int* change)
{
int currentVoltage = analogRead(LeftMotor);
if(currentVoltage == 0 || currentVoltage > 3125)  //change 1020 value to max 
*change = -(*change);                                             //voltage wanted
pwmWrite(LeftMotor, currentVoltage*16 + *change);
}

void drive_straight() // use 4 sensors?
{
  // must convert voltages to distances and adjust code
  
  static int previous_error = 0; 
  int error;  // error values
  static int last_big = 0;
  int biggest;
  double total;
  int time_now;
  static int previous_time = 0;
  bool good;
  int left90, left45, right45, right90;
  double Kp = .85, Kd = .1;
  
  if(!previous_time)
  {
    previous_time = millis();
   
    return;
   }
  
  left90 = analogRead(L90sensor);  // verify sensor orientation
  right90 = analogRead(R90sensor);
  //left45 = analogRead(sense_2);
 // right45 = analogRead(sense_3);
  /*
  SerialUSB.print(left90);
SerialUSB.print("   ");
SerialUSB.print(right90);
SerialUSB.print("   ");

    */
  
  if(1)
  {
    error = right90 - left90;
    biggest = 0;
    good = true;
  }
  
  else if(abs(right45 - left45) > 500)
  {
    error = right45 - left45;
    biggest = 0;
    good = true;
  }
  
  else
 { 
    
   biggest = -left90; 
   
   if(right90 > abs(biggest))
    {
      biggest = right90;
    }
    
    if(left45 > abs(biggest))
    {
      biggest = -left45;
    }
    
    if(right45 > abs(biggest))
    {
      biggest = right45;
    }
    
    if(last_big == 0)
    {
      last_big = biggest;
      return;
    }
    
    good = false;
    
  }
  
  if(good)
  {
    total = error * Kp; // (error - previous_error) / (time_now - previous_time) * Kd;
  }
  
  else
  {
    last_big = biggest;
    total = (last_big - biggest) * Kp;
  }

  {
    previous_time = time_now;
    
    L_enable_val -= (total);

    if(L_enable_val < 13000)
    {
      L_enable_val = 13000;
    }
    else if(L_enable_val > 16000)
    {
      L_enable_val = 16000;
    }
   //   constrain(L_enable_val, 5000, 14000);  // may need to adjust
    
    R_enable_val += (total); 
    
    if(R_enable_val < 14000)
    {
      R_enable_val = 14000;
    }
    else if(R_enable_val > 16000)
    {
      R_enable_val = 16000;
    }
   //   constrain(R_enable_val, 5000, 15000);
      
    if(previous_time - millis() > 100)
    {
    SerialUSB.print(L_enable_val);
    SerialUSB.print("   ");
    SerialUSB.print(R_enable_val);
    SerialUSB.print("   ");
    SerialUSB.println(analogRead(sense_3));
    previous_time = millis();
    }
    analogWrite(left_enable, L_enable_val);     // enable pins and values 
                                                // must be global
    analogWrite(right_enable, R_enable_val);    // different functions on maple
  }
}





/*** Maze and Node "Constructors" ***/

/* Node Constructor */
Node * new_Node (const short i, const short j) {

  Node * this_node;
  short halfsize;

  if (debug_on)
    printf("allocating %hd, %hd\n", i, j);

  this_node = (Node *) malloc(sizeof(Node));
  halfsize = SIZE / 2;

  this_node->row = i;
  this_node->column = j;
  this_node->visited = FALSE;

  /* Initializing the flood value at this coord
     NOTE : Right now this only works when SIZE is even -- which is ok */
  if (i < halfsize && j < halfsize)
    this_node->floodval = (halfsize - 1 - i) + (halfsize - 1 - j) ;
      
  else if (i < halfsize && j >= halfsize)
    this_node->floodval = (halfsize - 1 - i) + (j - halfsize) ;
      
  else if (i >= halfsize && j < halfsize)
    this_node->floodval = (i - halfsize) + (halfsize - 1 - j) ;

  else
    this_node->floodval = (i - halfsize) + (j - halfsize) ;

  return this_node;
}

/* Maze Constructor */
Maze * new_Maze () {

  Maze * this_maze;
  short i, j;
  
  this_maze = (Maze *) malloc(sizeof(Maze));

  /* Allocate a new Node for each coord of maze */
  for (i = 0; i < SIZE; ++i) 
    for (j = 0; j < SIZE; ++j) 
      this_maze->map[i][j] = (Node *) new_Node (i, j);

  /* setting the neighbors ptrs... must be done after all cells allocated */
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++) {
      this_maze->map[i][j]->left = (j == 0) ? NULL : (this_maze->map[i][j-1]);
      this_maze->map[i][j]->right = (j == SIZE-1) ? NULL : (this_maze->map[i][j+1]);
      this_maze->map[i][j]->up = (i == 0) ? NULL : (this_maze->map[i-1][j]);
      this_maze->map[i][j]->down = (i == SIZE-1) ? NULL : (this_maze->map[i+1][j]);
    }

  return this_maze;
}

/* Node Destructor */
void delete_Node (Node ** npp) {
  
  /* debug statements */
  //if (debug_on) 
  //  printf("deallocating %d, %d\n", (*npp)->row, (*npp)->column);

  free (*npp);
  *npp = 0;
}

/* Maze Destructor */
void delete_Maze (Maze ** mpp) {

  short i, j;

  for (i = 0; i < SIZE; i++) 
    for (j = 0; j < SIZE; j++) 
      delete_Node (&((*mpp)->map[i][j])); 
    
  free(*mpp);
  *mpp = 0;
}

// Stack Constructor
Stack * new_Stack() {

  Stack * this_stack = malloc(sizeof(Stack));

  this_stack->properties[SPI] = 0;
  this_stack->properties[SSI] = STACKSIZE;

  return this_stack;
}

// Stack Destructor
void delete_Stack (Stack ** spp) {

  if (spp == 0 || *spp == 0) {
    //fprintf(stderr, "NULL POINTER\n");
    return;
  }

  free(*spp);

  *spp = 0;
}




/*** Node Functions start here ***/

/* function for obtaining this_node's smallest neighbor's floodval */
short get_smallest_neighbor (Node * this_node) {

  /* debug statements */
  //if (debug_on)
  //  printf("In get_smallest_neighbor\n");

  // The Node's floodval will be 1 higher than the neigboring cell
  short smallestneighbor = LARGEVAL;

  // NOTE: LEFT, RIGHT, etc, are substituting:
  // this_node->left, this_node->right, etc.

  if (LEFT != NULL && (LEFT->right != NULL) && (LEFT->floodval) < smallestneighbor)
    smallestneighbor = LEFT->floodval;

  if (RIGHT != NULL && (RIGHT->left != NULL) && (RIGHT->floodval) < smallestneighbor)
    smallestneighbor = RIGHT->floodval; 

  if (UP != NULL && (UP->down != NULL) && (UP->floodval) < smallestneighbor)
    smallestneighbor = UP->floodval;

  if (DOWN != NULL && (DOWN->up != NULL) && (DOWN->floodval) < smallestneighbor)
    smallestneighbor = DOWN->floodval;

  return smallestneighbor;
}



/* function for obtaining this nodes's smallest neighbor's direction */
short get_smallest_neighbor_dir (Node * this_node, const short preferred_dir) {

  short smallestval;    /* smallest neighbor value */
  short pathcount;      /* number of available paths */

  /* debug statement */
  //if (debug_on)
  //  printf("In get_smallest_neighbor_dir\n");

  /* get the smallest neighboring flood_val */
  smallestval = get_smallest_neighbor(this_node);
  
  /* clear pathcount */
  pathcount = 0;

  /* A BUNCH OF DEBUG STATEMENTS! */
  /*
  if (debug_on) {
      printf("preferred_dir: %hd\n", preferred_dir);
      printf("smallestval: %hd\n", smallestval);
      printf("neighboring floodvals:\n");
      if (UP != NULL) {
        printf("UP: %hd\n", UP->floodval);
        if (UP->floodval == smallestval)
          printf("NORTH cell reachable\n");
      }
      if (RIGHT != NULL)
      {
        printf("RIGHT: %hd\n", RIGHT->floodval);
        if (RIGHT->floodval == smallestval)
          printf("EAST cell reachable\n");
      }
      if (DOWN != NULL)
      {
        printf("DOWN: %hd\n", DOWN->floodval);
        if (DOWN->floodval == smallestval)
          printf("SOUTH cell reachable\n");
      }
      if (LEFT != NULL)
      {
        printf("LEFT: %hd\n", LEFT->floodval);
        if (LEFT->floodval == smallestval)
          printf("WEST cell reachable\n");
    }
  }
  */

    /* count the number of available paths */
  if ((UP != NULL) && (UP->floodval == smallestval)) 
      pathcount++;
    
    if ((RIGHT != NULL) && (RIGHT->floodval == smallestval)) 
      pathcount++;
    
    if ((DOWN != NULL) && (DOWN->floodval == smallestval)) 
      pathcount++;
    
    if ((LEFT != NULL) && (LEFT->floodval == smallestval)) 
      pathcount++;

  /* more debug statments */
  //  if (debug_on)
  //    printf("pathcount: %d\n", pathcount);

    switch (preferred_dir){

      case NORTH: 
        if ((UP != NULL) && (UP->floodval == smallestval))
          return NORTH;
        break;
      case EAST: 
        if ((RIGHT != NULL) && (RIGHT->floodval == smallestval))
          return EAST;
        break;
      case SOUTH: 
      if ((DOWN != NULL) && (DOWN->floodval == smallestval))
        return SOUTH;
        break;
      case WEST:  
        if ((LEFT != NULL) && (LEFT->floodval == smallestval))
          return WEST;
        break;

    }

    /* if there is only one path, return that direction */
    //if (pathcount > 1)
    //  return preferred_dir;

    /* if there are multiple available paths, choose the favorable path */


      if ((UP != NULL) && (UP->floodval == smallestval) && (UP->visited == FALSE))
       return NORTH;
      else if ((RIGHT != NULL) && (RIGHT->floodval == smallestval) && (RIGHT->visited == FALSE))
        return EAST;
      else if ((DOWN != NULL) && (DOWN->floodval == smallestval) && (DOWN->visited == FALSE))
        return SOUTH;
      else if ((LEFT != NULL) && (LEFT->floodval == smallestval) && (LEFT->visited == FALSE))
        return WEST;

    if ((UP != NULL) && (UP->floodval == smallestval))
       return NORTH;
      else if ((RIGHT != NULL) && (RIGHT->floodval == smallestval))
        return EAST;
      else if ((DOWN != NULL) && (DOWN->floodval == smallestval))
        return SOUTH;
      else //if ((LEFT != NULL) && (LEFT->floodval) == smallestval)
        return WEST;

}


/* helper function for flood_fill 
   checks if this node already fulfills flood value requirements*/
short floodval_check(Node * this_node) {

  /* debug statments */
  //if (debug_on)
  //  printf("In floodval_check\n");

  /* return a flag determining wheter this node should be updated 
     aka, is this Node 1 + min open adj cell? */
  if (get_smallest_neighbor (this_node) + 1 == this_node->floodval)
    return TRUE;

  return FALSE;
}


/* helper fuction for flood_fill 
   updates this node's flood value to 1 greater than the smallest neighbor*/
void update_floodval (Node * this_node) {

  /* debug statements */
  //if (debug_on)
  //  printf("In update_floodval\n");

  /* set this node's value to 1 + min open adjascent cell */
  this_node->floodval = get_smallest_neighbor (this_node) + 1;

}

/* pushes the open neighboring cells of this node to the stack */
void push_open_neighbors (Node * this_node, Stack * this_stack) {

  /* debug statements */
  //if (debug_on)
  //  printf("In push_open_neighbors\n");

  /* A NULL neighbor represents a wall.
     if neighbor is accessible, push it onto stack! */
  if (LEFT != NULL && LEFT->right != NULL) 
    push (this_stack, LEFT);

  if (RIGHT != NULL && RIGHT->left != NULL) 
    push (this_stack, RIGHT);

  if (UP != NULL && UP->down != NULL) 
    push (this_stack, UP);

  if (DOWN != NULL && DOWN->up != NULL) 
    push (this_stack, DOWN);

}

/* main function for updating the flood values of this node */
void flood_fill (Node * this_node, Stack * this_stack, const short reflood_flag) {

  short status;  /* Flag for updating the flood value or not */

  /* debug statements */
  //if (debug_on)
  //  printf("In flood_fill (%d, %d) \n", this_node->row, this_node->column);
  
  /* we want to avoid flooding the goal values - this is for non-reverse */
  if (!reflood_flag) 
    if (this_node->row == SIZE / 2 || this_node->row == SIZE / 2 - 1) 
        if (this_node->column == SIZE / 2 || this_node->column == SIZE / 2 - 1) 
          return;

    /* we want to avoid flooding the goal values - this is reverse */
  if (reflood_flag) 
    if (this_node->row == START_X && this_node->column == START_Y)
        return;
  
  /* is the cell (1 + minumum OPEN adjascent cell) ? */
  status = floodval_check (this_node);

  /* if no, update curent cell's flood values, 
     then push open adjascent neighbors to stack. */
  if (!status) {
    update_floodval(this_node); /* Update floodval to 1 + min open neighbor */
    push_open_neighbors(this_node, this_stack); /* pushed, to be called later */
  }
  
  /* debug statements */
  //if (debug_on)
  //  printf ("Exiting flood_fill (%d, %d)\n", this_node->row, this_node->column);
  
}

/* Function for setting this node's floodval to a specific value */
void set_value (Node * this_node, const short value) {

  /* debug statements */
  //if (debug_on) {
  //  printf("In set_value\n");
  //  printf("Floodval set to : %d\n", this_node->floodval);
  //}
  
  /* set the flood value to specified value */
  this_node->floodval = value;
}

/* Function for setting this node's floodval to a specific value */
void set_visited (Node * this_node) {

  /* debug statements */
  //if (debug_on) 
  //  printf("In set_visited\n");

  /* set the flood value to specified value */
  this_node->visited = TRUE;
}

/* Function for setting the walls of this node */
void set_wall (Node * this_node, const short dir) {

  /* set a wall, of this node, of the specified direction  */
  switch (dir) {

    case NORTH :
      if (this_node->row != 0) {
        UP = NULL;
        //if (debug_on)
        //  printf("NORTH Wall Set\n");
      } break;

    case SOUTH :
      if (this_node->row != SIZE -1) {
        DOWN = NULL;
        //if (debug_on)
        //  printf("SOUTH Wall Set\n");
        
      } break; 

    case EAST : 
      if (this_node->column != SIZE - 1) {
        RIGHT = NULL;
        //if (debug_on)   
        //  printf("EAST Wall Set\n");
      } break;

    case WEST :
      if (this_node->column != 0) { 
        LEFT = NULL;
        //if (debug_on)
        //  printf("WEST Wall Set\n");
      } break;
  }
}



/*** Solver Functions start here ***/



/* update flag for whether goal cell was reached */
void check_start_reached (short * x, short * y, short * found_start) {

  if (*x == START_X && *y == START_Y) {
    *(found_start) = TRUE;
    //printf("Start Coorinates Reached: %d, %d\n", *x, *y);
  }
}

/* update flag for whether goal cell was reached */
void check_goal_reached (short * x, short * y, short * found_goal) {

  if (*x == SIZE / 2 || *x == SIZE / 2 - 1) {
    if (*y == SIZE / 2 || *y == SIZE / 2 - 1) {
      *(found_goal) = TRUE;
      //printf("Goal Coordinates Reached: %d, %d\n", *x, *y); 
    }
  }
}

/* function for updating the location and direction of mouse 
   the actual "move" function */
void move_dir (Maze * this_maze, short * x, short * y, short * dir) {

  /* x, y are current positions, dir is current directions
     these output params may be updated at the exit of this function */ 

  Node * this_node;   /* the node at this position x, y */ 
  short next_dir;       /* will hold the next direction to go */

  /* debug statements */
  //if (get_debug_mode()) {
  //  printf("In move_dir\n");
  //  printf("preffered_dir: %d\n", *dir );
  //  printf("current coords: %d,%d\n", *x, *y);
  //}

  this_node = this_maze->map[(*x)][(*y)];
  next_dir = get_smallest_neighbor_dir(this_node, *dir);
  
  //if (get_debug_mode())
  //  printf("%d\n", next_dir);

  /* update the appropriate location value x or y */
  if (next_dir == NORTH) 
    (*x) = (*x) - 1;
  else if (next_dir == EAST) 
    (*y) = (*y) + 1;
  else if (next_dir == SOUTH) 
    (*x) = (*x) + 1;
  else if (next_dir == WEST) 
    (*y) = (*y) - 1;

  /* update the direction */
  (*dir) = next_dir;
}


void visit_Node (Maze * this_maze, Stack * this_stack, short x, short y, short flag) {
  /* NOTE: the flag parameter determines whether to update goal cells or not */
  Node * this_node;   /* holds current node at x, y; also for reading from stack */
  short northwall, eastwall, southwall, westwall;  /* for reading in wall data */

  this_node = this_maze->map[x][y];
  northwall = eastwall = southwall = westwall = FALSE;


  /* this should physically check whether there is a wall using sensor, 
     and update the passed values to TRUE or FALSE according to the walls. */
  //read_walls(&northwall, &eastwall, &southwall, &westwall);


  /* push to stack the cell on other side of wall if valid 
     sets the walls as specified by the values checked above */
  if (northwall) {
    if (this_node->row != 0)
      push (this_stack, this_maze->map[this_node->row-1][this_node->column]);
    set_wall(this_node, NORTH);
  }
  if (eastwall) {
    if (this_node->column != SIZE-1)
      push (this_stack, this_maze->map[this_node->row][this_node->column+1]);
    set_wall(this_node, EAST);
  }
  if (southwall) {
    if (this_node->row != SIZE-1)
      push (this_stack, this_maze->map[this_node->row+1][this_node->column]);
    set_wall(this_node, SOUTH);
  }
  if (westwall) {
    if (this_node->column != 0)
      push (this_stack, this_maze->map[this_node->row][this_node->column-1]);
    set_wall(this_node, WEST);
  }

  /* push this node itself, as it was updated */
  push(this_stack, this_node);
    
  
  /* pop until the stack is empty, and call flood_fill on that node */  
  while (!is_empty_Stack(this_stack)) {
    pop(this_stack, &this_node);
    /* NOTE: the flag parameter determines whether to update goal cells or not */
    flood_fill(this_node, this_stack, flag);
  }
  
  set_visited (this_node);

}



/*** Stack functions ***/

// Checks if this_stack is empty
int is_empty_Stack (Stack * this_stack) {

  //printf("%d\n", this_stack->properties[SPI]);

  if (this_stack->properties[SPI] == 0)
    return 1;
  else return 0;
}

// Pops the top element of this_stack
void pop (Stack * this_stack, Node ** npp) {


  short index;

  index = this_stack->properties[SPI] - 1;

  *npp = this_stack->the_stack[index];

  this_stack->properties[SPI] -= 1;

}

// Pushes an element to the top of this_stack
void push (Stack * this_stack, Node * this_node) {

  short index;

  index = this_stack->properties[SPI];

  this_stack->the_stack[index] = this_node;

  this_stack->properties[SPI] += 1;
}







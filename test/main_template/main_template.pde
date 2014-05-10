/*
 * Main Template
 *
 */

#include "Maze.h"
#include "Maze.c"
#include "Stack.c"

const int sleft = 0;
const int sright = 1;


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
struct Maze * my_maze;    /* maze for keeping track of flood values and walls */
struct Stack * my_stack;  /* stack used for flood fill */
struct Node * temp;  /* used for in-between start->goal, goal->start transition */
short found_dest;   /* flag if goal is reached */
short direction;    /* keeps track of direction that mouse is moving in */
short x, y; /* keeps track of current row, col value mouse is in within maze */
short goal_x, goal_y; /* keeps track of goal's x, y, once found */
short exit_solver_loop;


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
  my_maze = new_Maze();    /* Initialize new maze */
  my_stack = new_Stack();  /* Initialize new stack */
  
  /* Initialize variables */
  x = START_X;
  y = START_Y;
  direction = NORTH;
  found_dest = FALSE;
  exit_solver_loop = FALSE;
  
}


void loop()
{
  /*
    SerialUSB.println(analogRead(sense_1));
    SerialUSB.println(analogRead(sense_3));
    SerialUSB.println(analogRead(sense_5));
    SerialUSB.println();
    SerialUSB.println();
    SerialUSB.println();
    delay(3000);
    */
 
   found_dest = FALSE;
    direction = NORTH;
  
  //Trip from goal to start 
  while (!found_dest) {
    
    if (direction == NORTH)
      led(true);
    else led(false);

    
    visit_node(my_maze, my_stack, x, y, FALSE);
    change_dir(my_maze, &x, &y, &direction);
    delay(1000);
    move_single_cell();
    Stop_Moving();
    delay(2000);
   }
  
  
  //motor_test();
  //drive_straight();
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
	/*
	if(analogRead(sense_3) > 3800)     // if the mouse gets too close to the wall before turning, decrease the value
	{			// if the mouse starts to turn before getting close enough, increase delay
				// delay can be found in the next three if statements, all delay functions
				// must have the same delqy value;

            while(analogRead(sense_3) > 2400)
            {
              drive_straight();
            }
		about_face();

               // delay(1000);
                
		
		
	}
        */
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
  int encoder_number = L_encoder_val;
  
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
  digitalWrite(R_bkw, LOW);
  digitalWrite(L_bkw, LOW);
  
  pwmWrite(right_enable, 15000);  // decrese the value for a slower turn, increase it to go faster
  pwmWrite(left_enable, 15000);	  // decrese the value for a slower turn, increase it to go faster
  
  //delay(200);  // decrease delay if mouse pauses too much, increase it if the mouse tries to turn
  	       // before slowing down enough (same thing in turn_right)
  
  digitalWrite(R_fwd, HIGH);
  
  digitalWrite(L_bkw, HIGH);
  
  //delay(400);
  while(L_encoder_val - encoder_number < 17);  // tune this value for complete turn ************* ///////////////////

  digitalWrite(R_fwd, LOW);
  digitalWrite(L_bkw, LOW);
  R_encoder_val = 0;
  L_encoder_val = 0;
}

void turn_right()  // point turn
{
  int encoder_number = L_encoder_val;
  
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
  digitalWrite(R_bkw, LOW);
  digitalWrite(L_bkw, LOW);
  
  pwmWrite(right_enable, 15000);  // decrese the value for a slower turn, increase it to go faster
  pwmWrite(left_enable, 15000);   // decrese the value for a slower turn, increase it to go faster
  
  //delay(100);
  
  digitalWrite(L_fwd, HIGH);
  
  digitalWrite(R_bkw, HIGH);
  
  while(L_encoder_val - encoder_number < 19);
  //delay(400);  // tune this value for complete turn ******* ///////////////////

  digitalWrite(L_fwd, LOW);
  digitalWrite(R_bkw, LOW);
  R_encoder_val = 0;
  L_encoder_val = 0;
}


void about_face()  // because, why not?
{
  	int value = R_encoder_val;
  	
  	digitalWrite(L_fwd, LOW);
  	digitalWrite(L_bkw, HIGH);
  	
  	pwmWrite(right_enable, 15000);
  	pwmWrite(left_enable, 15000);
  	
  	while(R_encoder_val - value < 41);  // *********increase value to turn more***********
  	
  	digitalWrite(L_bkw, LOW);
  	digitalWrite(R_fwd, LOW);
  R_encoder_val = 0;
  L_encoder_val = 0;
  
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
  int side = 1;
  static int offset = 0;
  static int flag = 1;
  /*
  static int encoder_number = 0;
  
  if(R_encoder_val - encoder_number > 60)
  {
    encoder_number = R_encoder_val;
    
    digitalWrite(R_fwd, LOW);
    digitalWrite(L_fwd, LOW);
    
    delay(1000);
  }
  */
  
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
  
  if(right90 > 1200 && left90 > 1200)
  {
    error = right90 - left90;
    offset = 0;
    good = true;
    led(false);
    if(right90 > left90)
    {
      side = 1;
    }
    
    else
    {
      side = -1;
    }
  }
 /* 
  else if(abs(right45 - left45) > 500)
  {
    error = right45 - left45;
    biggest = 0;
    good = true;
  }
  */
  else
 { 
   /*
   biggest = -left90;
   base = -2200;
   
   if(right90 > left90)
   {
     biggest = right90;
     base = 2200;
   }
    
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
    */
    if(!offset)
    offset = R_encoder_val - L_encoder_val;
    
    good = false;
    if(flag)
    {
      led(true);
      Break(1000);
      flag--;
    }
    
  }
  
  if(good)
  {
    total = error * Kp; // (error - previous_error) / (time_now - previous_time) * Kd;
  }
  
  else
  {
    //total = (R_encoder_val - L_encoder_val - offset) * 150 + 60*side;
    moveOne(sright);
    moveOne(sleft);
    return;
  }
  /*
  else
  {
    total = (biggest - last_big) * Kp;
        last_big = biggest;
  }
*/
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
    SerialUSB.print(left90);
    SerialUSB.print("   ");
    SerialUSB.println(right90);
    //SerialUSB.print("   ");
    //SerialUSB.println(analogRead(sense_3));
    previous_time = millis();
    }
    
    analogWrite(left_enable, L_enable_val);     // enable pins and values 
                                                // must be global
    analogWrite(right_enable, R_enable_val);    // different functions on maple
  }
}

void Break(int time)
{
    digitalWrite(R_fwd, LOW);
    digitalWrite(L_fwd, LOW);
    delay(time);
    digitalWrite(R_fwd, HIGH);
    digitalWrite(L_fwd, HIGH);
}

void Stop_Moving()
{
    digitalWrite(R_fwd, LOW);
    digitalWrite(L_fwd, LOW);
}

void Start_Moving()
{
   digitalWrite(R_fwd, HIGH);
   digitalWrite(L_fwd, HIGH);
}

void led(bool choice)
{
  if(choice)
  {
    digitalWrite(18, HIGH);
  }
  
  else
  {
    digitalWrite(18, LOW);
  }
}
    
void moveOne(int choice)
{
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
  
  int R = R_encoder_val;
  int L = L_encoder_val;
  
  if(choice)
  {
    while(R_encoder_val - R < 1)
    {
      digitalWrite(R_fwd, HIGH);
    }
    
    digitalWrite(L_fwd, HIGH);
    
  }
  
  else
  {
    while(L_encoder_val - L < 1)
    {
      digitalWrite(L_fwd, HIGH);
    }
    
    digitalWrite(R_fwd, HIGH);
  }
  
}

// 1200 == there is a wall
// Visiting the cell
void visit_node(Maze * this_maze, Stack * this_stack, short x, short y, short flag) {
  
  Node * this_node;
  short wall_on_left, wall_on_front, wall_on_right;
  short northwall, eastwall, southwall, westwall;
  
  this_node = this_maze->map[x][y];
  wall_on_left = wall_on_front = wall_on_right = FALSE;
  northwall = eastwall = southwall = westwall = FALSE;
  
  // read walls and set
  // read left
  if (analogRead(sense_1) > 2000) 
    wall_on_left = TRUE;
 
  if (analogRead(sense_3) > 2000)
    wall_on_front = TRUE;
   
  if (analogRead(sense_5) > 2000)
    wall_on_right = TRUE;  

  if (direction == NORTH) {
  
      if (wall_on_left) {
        set_wall(this_node, WEST);
        westwall = TRUE; 
      }
      if (wall_on_front) {
        set_wall(this_node, NORTH);
        northwall = TRUE;
      }
      if (wall_on_right) {
        set_wall(this_node, EAST); 
        eastwall = TRUE;
      }  
  }
  
  else if (direction == EAST){
  
      if (wall_on_left) {
        set_wall(this_node, NORTH);
        northwall = TRUE; 
      }
      if (wall_on_front) {
        set_wall(this_node, EAST);
        eastwall = TRUE;
      }
      if (wall_on_right) {
        set_wall(this_node, SOUTH);
        southwall = TRUE;
      }
  }
  
  else if (direction == SOUTH) {
  
      if (wall_on_left) {
        set_wall(this_node, EAST);
        eastwall = TRUE; 
      }
      if (wall_on_front) {
        set_wall(this_node, SOUTH);
        southwall = TRUE;
      }
      if (wall_on_right) {
        set_wall(this_node, WEST); 
        westwall = TRUE;
      }
  }
  
  else {
  
      if (wall_on_left) {
        set_wall(this_node, SOUTH);
        southwall = TRUE; 
      }
      if (wall_on_front) {
        set_wall(this_node, WEST);
        westwall = TRUE;
      }
      if (wall_on_right) {
        set_wall(this_node, NORTH); 
        northwall = TRUE;
      }
  }
  
  
    if (northwall) {
      if (this_node->row != 0)
        push (this_stack, MAP[ROW-1][COL]);
      set_wall(this_node, NORTH);
    }
    if (eastwall) {
      if (this_node->column != SIZE-1)
        push (this_stack, MAP[ROW][COL+1]);
      set_wall(this_node, EAST);
    }
    if (southwall) {
      if (this_node->row != SIZE-1)
        push (this_stack, MAP[ROW+1][COL]);
      set_wall(this_node, SOUTH);
    }
    if (westwall) {
      if (this_node->column != 0)
        push (this_stack, MAP[ROW][COL-1]);
      set_wall(this_node, WEST);
    }
  
  
   /* push this node itself, as it was updated */
  push(this_stack, this_node);
    
  
  /* pop until the stack is empty, and call flood_fill on that node */  
  while (!is_empty_Stack(this_stack)) {
    pop(this_stack, &this_node);
    /* NOTE: the flag parameter determines wheter to update goal cells or not */
    flood_fill(this_node, this_stack, flag);
  }
  
  set_visited (this_node);
  
}


void change_dir (Maze * this_maze, short * x, short * y, short * dir) {
  
  Node * this_node;
  short next_dir;
  
  this_node = this_maze->map[(*x)][(*y)];
  next_dir = get_smallest_neighbor_dir(this_node, *dir);
  
  /* update the appropriate location value x or y */
  if (next_dir == NORTH) 
    (*x) = (*x) - 1;
  else if (next_dir == EAST) 
    (*y) = (*y) + 1;
  else if (next_dir == SOUTH) 
    (*x) = (*x) + 1;
  else if (next_dir == WEST) 
    (*y) = (*y) - 1;

  // Turn the actual mouse 
  if (*dir == NORTH) {
    if (next_dir == WEST)
      turn_left();
    else if (next_dir == EAST)
      turn_right();
    else if (next_dir == SOUTH)
      about_face();
  }
  
  else if (*dir == EAST) {
    if (next_dir == NORTH)
      turn_left();
    else if (next_dir == SOUTH)
      turn_right();
    else if (next_dir == WEST)
      about_face();
  }
  
  else if (*dir == SOUTH) {
    if (next_dir == EAST)
      turn_left();
    else if (next_dir == WEST)
      turn_right();
    else if (next_dir == NORTH)
      about_face();
  }
  
   else if (*dir == WEST) {
    if (next_dir == SOUTH)
      turn_left();
    else if (next_dir == NORTH)
      turn_right();
    else if (next_dir == EAST)
      about_face();
  }
  
  /* update the direction */
  (*dir) = next_dir;
  
  
}


void move_single_cell() {
  
  for (int i = 0; i < 30; i++) {
     moveOne(sright);
     moveOne(sleft); 
  }
  
}


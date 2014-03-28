// COMMENT

//CHECKING IF THE BRANCHING IS WORKING>


const int sense_1 = 4, sense_2 = 5, sense_3 = 8, sense_4 = 9, sense_5 = 3;  // IR sensor pins

const int L_encoder1 = 1, L_encoder2 = 14;   // left encoder pins

const int R_encoder1 = 0, R_encoder2 = 31;  // right encoder pins

const int right_enable = 10, left_enable = 7;        // motor enable pins

const int led1 = 15, led2 = 16, led3 = 17, led4 = 18, led5 = 19;  // test led pins

const int switch1 = 20, switch2 = 21, switch3 = 22, switch4 = 23, switch5 = 24;   // switch pins

const int R_fwd = 12, R_bkw = 13, L_fwd = 11, L_bkw = 6;  // (verify)  motor direction pins

int R_enable_val = 65535;  // initialize enable values high
int L_enable_val = 65535;

volatile int R_encoder_val = 0;  // declare encoder interrupt values
volatile int L_encoder_val = 0;

typedef struct node
  {
  short int distance;
  short int section;
  
  short int row;
  short int column;

  bool traveled_to;
  bool traced;
  
  struct node* up;
  struct node* down;
  struct node* left;
  struct node* right;
  };

  struct node maze[16][16];


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
  
 
  
  //SerialUSB.println("hello world");
  
}


void loop()
{
  



  SerialUSB.print(sizeof(struct node));
  
  SerialUSB.print("  ");
  
  SerialUSB.println(sizeof(maze));
  
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
  pwmWrite(right_enable, R_enable_val);
  pwmWrite(left_enable, L_enable_val);
  
  digitalWrite(R_fwd, HIGH);
  digitalWrite(L_fwd, HIGH);
  
  delay(1000);
  
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
  
  delay(100);
  
  digitalWrite(R_fwd, HIGH);
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
}

void turn_left() // point turn
{
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
  digitalWrite(R_bkw, LOW);
  digitalWrite(L_bkw, LOW);
  
  pwmWrite(right_enable, HIGH);
  pwmWrite(left_enable, HIGH);
  
  digitalWrite(R_fwd, HIGH);
  
  digitalWrite(L_bkw, HIGH);
  
  delay(1500);  // tune this value for complete turn

  digitalWrite(R_fwd, LOW);
  digitalWrite(L_bkw, LOW);
}

void turn_right()  // point turn
{
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
  digitalWrite(R_bkw, LOW);
  digitalWrite(L_bkw, LOW);
  
  pwmWrite(right_enable, HIGH);
  pwmWrite(left_enable, HIGH);
  
  digitalWrite(L_fwd, HIGH);
  
  digitalWrite(R_bkw, HIGH);
  
  delay(1500);  // tune this value for complete turn

  digitalWrite(L_fwd, LOW);
  digitalWrite(R_bkw, LOW);
}

void left()  // arced turn
{
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
  digitalWrite(R_bkw, LOW);
  digitalWrite(L_bkw, LOW);
  
  pwmWrite(right_enable, HIGH);
  pwmWrite(left_enable, 20000);  // may want to hault or move? (test)
  
  digitalWrite(R_fwd, HIGH);
  digitalWrite(L_fwd, HIGH);

  delay(1500);  // tune this value for complete turn

  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
}

void right() // arced turn
{
  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
  digitalWrite(R_bkw, LOW);
  digitalWrite(L_bkw, LOW);
  
  pwmWrite(right_enable, 20000);  // may want to hault or move? (test)
  pwmWrite(left_enable, HIGH);
  
  digitalWrite(R_fwd, HIGH);
  digitalWrite(L_fwd, HIGH);

  delay(1500);  // tune this value for complete turn

  digitalWrite(R_fwd, LOW);
  digitalWrite(L_fwd, LOW);
}

void spin()  // because, why not?
{
  	while(1)
  	{
  		turn_left();
  	}
}

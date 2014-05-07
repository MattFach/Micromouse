// Constants

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define SIZE 16			// Size of one dimention of Map


// Directions
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// Shortcut Constants
#define MAPIJ this_maze->map[i][j]
#define MAP this_maze->map
#define FLOODVAL this_node->floodval
#define ROW this_node->row
#define COL this_node->column
#define VISITED this_node->visited
#define LEFT this_node->left
#define RIGHT this_node->right
#define UP this_node->up
#define DOWN this_node->down

// Stack Constants
#define SPI 2			// Stack Pointer Index
#define SSI 1 			// Stack Size Index
#define SCI 0			// Stack Counter Index.. Not used.
#define STACK_OFFSET 3
#define STACKSIZE 80

// Solver Constants - will be used on mouse
#define START_X 15
#define START_Y 0
#define LARGEVAL 301

// Solver Constants - for command line simulation only
#define NEWLINE 13
#define YES 'y'
#define NO 'n'



typedef struct Node { 

	/* data fields */
	int floodval;
	int row;
	int column;
	int visited;

	/* pointers to neighbors */
	struct Node * left;
	struct Node * right;
	struct Node * up;
	struct Node * down;
	
} Node;

typedef struct Maze {

	Node * map [SIZE][SIZE];	

} Maze;

typedef struct Stack {

	int properties [STACK_OFFSET];
	Node * the_stack [STACKSIZE];

} Stack;


// Node Functions
struct Node * new_Node (const int i, const int j);
void delete_Node (Node ** npp);
void flood_fill (Node * this_node, Stack * this_stack, const int reflood_flag);
void set_wall (Node * this_node, const int dir);
void set_value (Node * this_node, const int value);
void set_visited (Node * this_node);
int get_smallest_neighbor_dir (Node * this_node, const int preferred_dir);

// Floodfill Helper Functions
int get_smallest_neighbor (Node * this_node);
int floodval_check(Node * this_node) ;
void update_floodval (Node * this_node);
void push_open_neighbors (Node * this_node, Stack * this_stack);


// Maze Functions
struct Maze * new_Maze ();
void delete_Maze (Maze ** mpp);
void print_map (const Maze * this_maze);


// Stack Functions
Stack * new_Stack();
void delete_Stack (Stack ** spp);
int is_empty_Stack (Stack * this_stack);
void pop (Stack * this_stack, Node ** npp);
void push (Stack * this_stack, Node * this_node);

// Debug On, Off
void set_debug_on ();
void set_debug_off ();
int get_debug_mode ();



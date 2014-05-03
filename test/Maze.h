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


typedef struct Node { 

	/* data */
	int floodval;

	//int distance;
	//char section;

	int row;
	int column;

	int traveled_to;
	int traced;

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

typedef struct Stack {

	int properties [STACK_OFFSET];
	Node * the_stack [STACKSIZE];

} Stack;


// Node Functions
struct Node * new_Node ();
void delete_Node (Node ** npp);
void flood_fill (Node * this_node, Stack * this_stack);
void set_wall (Maze * this_maze, Node * this_node, int dir, int set_on);
void set_value (Node * this_node, int value);

// Floodfill Helper Functions
int get_smallest_neighbor (Node * this_node);
int floodval_check(Node * this_node) ;
void update_floodval (Node * this_node);
void push_open_neighbors (Node * this_node, Stack * this_stack);
// Used by Solver
int get_smallest_neighbor_dir (Node * this_node, int preferred_dir);
int get_largest_neighbor (Node * this_node);
int reverse_floodval_check(Node * this_node) ;
void update_reverse_floodval (Node * this_node);
void reverse_flood_fill (Node * this_node, Stack * this_stack);



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



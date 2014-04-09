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

// Debug On, Off
void set_debug_on ();
void set_debug_off ();



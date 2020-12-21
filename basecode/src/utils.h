#ifndef __UTILS__
#define __UTILS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>


#define SIZE 9
#define _XOPEN_SOURCE 500 //prolly size of board

/**
 * Data structure containing the information about the game state
 */

typedef struct { //cursor pos
	int8_t x,y;
} position_s;

typedef struct {
	int8_t field[SIZE][SIZE]; //board
	position_s cursor; //cursor
	bool selected; //whether the cursor has been selected
} state_t;


/**
* Move type
*/
typedef enum moves_e{ //possible moves
	left=0,
	right=1,
	up=2,
	down=3
} move_t;


/**
 * Search Node information
 */
struct node_s{ 
    int depth;
    move_t move;
    state_t state;
    struct node_s* parent;
	/* The pointer below was added by Hasne Hossain */ 
	struct node_s* next;
	
};

typedef struct node_s node_t;

/* This struct was added by Hasne Hossain  */
typedef struct {
	node_t *head;
	node_t *foot;
} list_t;  

//meeeeeeeeeee


/**
 * GLOBAL VARIABLES
*/

state_t solution[SIZE*SIZE]; //stores sequence of boards in making d soln;seq of state...items of datatype state_t
move_t  solution_moves[SIZE*SIZE]; //seq of action, i.e. left,right,up,down
int solution_size;

//meeeeeeeeeeeeeeeeeee
list_t* list;

int generated_nodes; //no. of generated nodes...some stats
int expanded_nodes; //prolly explored nodes

//command line args
bool ai_run; //Run AI
bool show_solution; //Play solution found by AI algorithm
int budget; // budget for expanded nodes



/**
 *  Useful functions for AI algorithm
 * funcs we most likely gonna use in our algo
 */

// Updates the field and cursor given the selected peg and the jump action chosen
void execute_move_t(state_t* state, position_s* selected_peg, move_t jump);

// returns true if move is legal
bool can_apply(state_t *board, position_s* selected_peg, move_t jump);

// Check if game is over
bool won(state_t *board);

// returns number of pegs in board
int num_pegs( state_t *board );



/**
 * Used for human games
 * funcs used for the human-played game
*/
void rotateBoard(state_t *board);
bool select_peg(state_t *board);
bool moveUp(state_t *board);
bool moveLeft(state_t *board); 
bool moveDown(state_t *board); 
bool moveRight(state_t *board);
int8_t validMovesUp(state_t *board);
bool gameEndedForHuman(state_t *board);

void initialize(state_t *board, int8_t layout);

/**
 * Output functions
*/
void drawBoard(state_t *board);
char* action_cstr(move_t move);
void print_solution();
void play_solution();


/*list functions added by Hasne Hossain taken and modified from
 * functions provided by Alistair Moffat */
list_t* make_empty_list(void);
list_t* insert_at_foot(list_t *list, node_t* n);
void free_list(list_t *list);

#endif

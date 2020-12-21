#ifndef __STACK_PEG__
#define __STACK_PEG__

#include "utils.h"

// The upperbound solution length = size of the matrix * 4 moves = maximum possible number of pegs * 4 moves
#define STACK_SIZE SIZE*SIZE* 4 //9*9*4=324

// Stack as an arrray
node_t* stack[STACK_SIZE]; //stack is a pointer that points to an array of node pointers

// Variable marking the top of the stack
int stack_top_idx;  //prolly global

// Needs to be called before using it for the first time
void initialize_stack();

void stack_push(node_t* n); 

void stack_pop();

node_t* stack_top();

int is_stack_empty();

void print_stack();

void free_stack();

#endif
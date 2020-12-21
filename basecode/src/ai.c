#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "ai.h"
#include "utils.h"
#include "hashtable.h"
#include "stack.h"

#include <assert.h>

void copy_state(state_t* dst, state_t* src){
	
	//Copy field
	memcpy( dst->field, src->field, SIZE*SIZE*sizeof(int8_t) );

	dst->cursor = src->cursor;
	dst->selected = src->selected;
}

/**
 * Saves the path up to the node as the best solution found so far...this func called in the graph code
*/
void save_solution( node_t* solution_node ){
	node_t* n = solution_node;
	while( n->parent != NULL ){
		copy_state( &(solution[n->depth]), &(n->state) ); 
		solution_moves[n->depth-1] = n->move; 

		n = n->parent;
	}
	solution_size = solution_node->depth;
}


node_t* create_init_node( state_t* init_state ){
	node_t * new_n = (node_t *) malloc(sizeof(node_t));
	new_n->parent = NULL;	
	//meeeeeeeeeee
	new_n->next = NULL;

	new_n->depth = 0;
	copy_state(&(new_n->state), init_state);  //ai.c..line12
	return new_n;
}

/**
 * Apply an action to node n and return a new node resulting from executing the action
*/
node_t* applyAction(node_t* n, position_s* selected_peg, move_t action ){ //n is parent/popped node

    node_t* new_node = NULL;

	//FILL IN MISSING CODE 
	new_node = (node_t *) malloc(sizeof(node_t));
	assert(new_node);

	new_node->next=NULL; 

	new_node->parent=n; 
	new_node->depth= (n->depth) + 1; 
	copy_state(&(new_node->state), &(n->state));
	new_node->state.cursor=(*selected_peg);

	new_node->move = action;
	
    execute_move_t( &(new_node->state), &(new_node->state.cursor), action ); 
	
	return new_node;

}

/**
 * Find a solution path as per algorithm description in the handout
 */

void find_solution( state_t* init_state  ){

	HashTable table; 

	// Choose initial capacity of PRIME NUMBER 
	// Specify the size of the keys and values you want to store once 
	ht_setup( &table, sizeof(int8_t) * SIZE * SIZE, sizeof(int8_t) * SIZE * SIZE, 16769023);

	// Initialize Stack
	initialize_stack(); 

	//Add the initial node
	node_t* n = create_init_node( init_state ); 

    /*We insert all unique fields made into the hashtable so that we can easily
     *check if a certain field is unique or already exists */
	ht_insert(&table, (n->state.field), (n->state.field)); 

	stack_push(n);
	int remainingPegs;
	remainingPegs= num_pegs(&(n->state)); 
	
	//FILL IN THE GRAPH ALGORITHM
	position_s ps; 
	move_t jump;

	/*Making list where I will put every single node that is made so that they can be
     *easily kept track of and hence easily freed  */
	list = make_empty_list();
	list = insert_at_foot(list, n);

	while (!is_stack_empty()){ 
		n = stack[stack_top_idx]; 
		stack_pop(); 
		expanded_nodes += 1;
		if(num_pegs(&(n->state)) < remainingPegs){ 
			save_solution(n);
			remainingPegs = num_pegs(&(n->state));
		}

		for(int8_t x=0; x<SIZE; x++){
			for(int8_t y=0; y<SIZE; y++){
				ps.x=x;
				ps.y=y;
				
                /* checking if selected move can move left,right,up or down and 
                 * proceeding accordingly */
				for(move_t jump= left; jump <= down; jump++){
				    if(can_apply(&(n->state), &ps, jump)){ 
				
					    node_t* n1=applyAction(n,&ps,jump); 
					    list = insert_at_foot(list, n1);

					    generated_nodes += 1;
					    if(won(&(n1->state))){
						    save_solution(n1);
						    remainingPegs= num_pegs(&(n1->state));

                            free_list(list);
							ht_destroy(&table);
						    return;
					    }
                        if(!ht_contains(&table, (n1->state.field))){ 
						    ht_insert(&table, (n1->state.field), (n1->state.field));
						    stack_push(n1);
					    }
				    }	
                }
			}
		}
		if(expanded_nodes >= budget){
			return;
		}
	}
	free_list(list);
	ht_destroy(&table);
}
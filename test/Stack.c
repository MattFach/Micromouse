#include <stdlib.h>
#include <stdio.h>
#include "Maze.h"



Stack * new_Stack() {

	Stack * this_stack = malloc(sizeof(Stack));

	this_stack->properties[SPI] = 0;
	this_stack->properties[SSI] = STACKSIZE;
	this_stack->properties[SCI] = 1;

	return this_stack;
}

void delete_Stack (Stack ** spp) {

	if (spp == 0 || *spp == 0) {
		fprintf(stderr, "NULL POINTER\n");
		return;
	}

	free(*spp);

	*spp = 0;

}

int is_empty_Stack (Stack * this_stack) {

	printf("%d\n", this_stack->properties[SPI]);

	if (this_stack->properties[SPI] == 0)
		return 1;
	else return 0;
}

void pop (Stack * this_stack, Node ** npp) {


	int index;

	index = this_stack->properties[SPI] - 1;

	*npp = this_stack->the_stack[index];

	this_stack->properties[SPI] -= 1;

}

void push (Stack * this_stack, Node * this_node) {

	int index;

	index = this_stack->properties[SPI];

	this_stack->the_stack[index] = this_node;

	this_stack->properties[SPI] += 1;
}


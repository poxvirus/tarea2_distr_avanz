//
// Created by gio on 18-06-17.
//

#include "../include/pointer_stack.h"
#include <stdio.h>
#include <stdlib.h>

PointerStack* stack_init(PointerStack* stack) {
    stack->size = 0;
    stack->top = NULL;
}

void stack_push(PointerStack* stack, int** array_pointer, int pointer_size,
                int pointer_cost) {
    PointerStackNode *node = (PointerStackNode *) malloc(sizeof(PointerStackNode));
    node->data = *array_pointer;
    node->size = pointer_size;
    node->cost = pointer_cost;
    node->lower = stack->top;
    stack->top = node;
    stack->size++;
}

void stack_pop(PointerStack* stack, int** array_pointer, int* pointer_size,
               int *pointer_cost) {
    PointerStackNode *top = stack->top;
    stack->top = top->lower;
    top->lower = NULL;
    stack->size--;

    *array_pointer = top->data;
    *pointer_size = top->size;
    *pointer_cost = top->cost;
    top->data = NULL;
    free(top);
}

void stack_peek(PointerStack* stack, int** array_pointer, int* pointer_size,
                int *pointer_cost) {
    *array_pointer = stack->top->data;
    *pointer_size = stack->top->size;
    *pointer_cost = stack->top->cost;
}

void stack_clear(PointerStack* stack) {
    PointerStackNode* node_aux;
    while(stack->top != NULL) {
        node_aux = stack->top;
        stack->top = node_aux->lower;
        stack->size--;
        node_aux->lower = NULL;

        free(node_aux->data);
        free(node_aux);
    }

}
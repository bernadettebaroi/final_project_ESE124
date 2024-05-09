#include "stack.h"
#include <stdio.h>
#define MAX_SIZE 100

int top = -1;

// 10. PUSH – pushes the planar coordinates x and y of Michael’s current position into Michael’s stack 
// for the memory. This way Michael memorizes the current position.
void push(Stack *stack, int x, int y) {
    if (is_full(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->top++;
    stack->coordinate[stack->top][0] = x;
    stack->coordinate[stack->top][1] = y;
}


// 11. POP - pops the planar coordinates x and y from the top of the Michael’s stack for the memory. 
// This way Michael remembers the position, but then it immediately forgets the position too.
void _pop(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack underflow\n");
        return;
    }
    stack->top--;
}


// 12. PEEK - peeks the planar coordinates x and y from the top of the Michael’s stack for the memory. 
// This way Michael remembers the position but does not forget the position.
void peek(Stack *stack, int *x, int *y) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    *x = stack->coordinate[stack->top][0];
    *y = stack->coordinate[stack->top][1];
}


//13. CLEAR – Michael clears its stack. 
//This way it has a total amnesia and forgets all its previous memories.
void clear(Stack *stack) {
    stack->top = -1;
}

int is_empty(Stack *stack) {
    return stack->top == -1;
}

int is_full(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}
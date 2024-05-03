#ifndef ANT_MEMORY_H
#define ANT_MEMORY_H

#define MAX_SIZE 100


typedef struct {
    int coordinate[MAX_SIZE][2];
    int top;
} Stack;

void _push(Stack *stack, int x, int y);
void _pop(Stack *stack);
void _peek(Stack *stack);
int is_empty(Stack *stack);
int is_full(Stack *stack);
void _clear(Stack *stack);

#endif /* ANT_MEMORY_H */


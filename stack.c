#define MAX_SIZE 100

int row[MAX_SIZE];
int col[MAX_SIZE];

int front = -1;


// 12. PEEK - peeks the planar coordinates x and y from the top of the Michael’s stack for the memory. 
// This way Michael remembers the position but does not forget the position.
void _peek(int *r, int *c){
    *r = row[front];
    *c = col[front];
}


//13. CLEAR – Michael clears its stack. 
//This way it has a total amnesia and forgets all its previous memories.
void _clear() {
    front = -1;
}


// 10. PUSH – pushes the planar coordinates x and y of Michael’s current position into Michael’s stack 
// for the memory. This way Michael memorizes the current position.
void _push(int a, int b) {
    if (isFull()) {
        printf("Stack overflow!\n");
        return;
    }
    row[++front] = a;
    col[front] = b;
}


// 11. POP - pops the planar coordinates x and y from the top of the Michael’s stack for the memory. 
// This way Michael remembers the position, but then it immediately forgets the position too.
void _pop(int *r, int *c) {
    if (isEmpty()) {
        printf("Stack underflow!\n");
        return;
    }
    *r = row[front];
    *c = col[front];
    front--;
    return;
}

int is_empty() {
    return front == -1;
}

int is_full() {
    return front == MAX_SIZE - 1;
}
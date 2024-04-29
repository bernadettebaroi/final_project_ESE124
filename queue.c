
int row[1000];
int col[1000];
int front = 0;
int end = -1;


// 12. PEEK - peeks the planar coordinates x and y from the top of the Michael’s stack for the memory. 
// This way Michael remembers the position but does not forget the position.
void _peek(int *r, int *c){
    *r = row[front];
    *c = col[front];
}


//13. CLEAR – Michael clears its stack. 
//This way it has a total amnesia and forgets all its previous memories.
void _clear() {
    front = 0;
    end = -1;
}


// 10. PUSH – pushes the planar coordinates x and y of Michael’s current position into Michael’s stack 
// for the memory. This way Michael memorizes the current position.
void _push(int a, int b) {
    end++;
    row[end] = a;
    col[end] = b;

}


// 11. POP - pops the planar coordinates x and y from the top of the Michael’s stack for the memory. 
// This way Michael remembers the position, but then it immediately forgets the position too.
int _pop() {
    int b = front;
    front++;
    return b;
}

int is_empty() {
    if (front > end) {
        return 1;
    }
    return 0;
}

int is_full() {
    if (end == 99) {
        return 1;
    }
    return 0;
}
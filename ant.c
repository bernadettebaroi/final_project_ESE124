#include <stdio.h>
#include "stack.h"
#include "ant.h"
#include <stdlib.h> 


//1. MARK – the ant marks its current position using a chemical called pheromone.
void mark(int *x, int *y, char **maze) {
    maze[*x][*y] = '@';
}

// 2. MOVE_F – moves the VA from the current position one position forward. If Michael 
// locates at coordinates (x, y), it will move to (x + 1, y).
void move_f(int *x, int *y, char **maze) {
    *x = (*x)+1;
}
// 3. MOVE_B – moves the virtual ant from the current position one position backward. 
// If Michael locates at coordinates (x, y), it will move to (x - 1, y).
void move_b(int *x, int *y, char **maze) {
    *x = (*x) - 1;
}
// 4. MOVE_L – moves the virtual ant from the current position one position left.
// If Michael locates at coordinates (x, y), it will move to (x, y - 1).
void move_l(int *x, int *y, char **maze) {
    *y = (*y) - 1;
}
// 5. MOVE_R – moves the virtual ant from the current position one position right.
// If Michael locates at coordinates (x, y), it will move to (x, y + 1).
void move_r(int *x, int *y, char **maze) {
    *y = (*y) + 1;
}

//6.CWL – Michael checks if the next locations to the left (until meeting a wall) are pheromone
// free. If the locations are free then Michael feels an itch. Otherwise, if no location is free
// (e.g., because there is a pheromone mark or a wall on the left of Michael), then Michael
// does not feel the itch.
int* cwl(int *x, int *y, char **maze) {
    int *position;
    *position = 0;
    if (*y == 0) {
        return 0;
    }
    for (int i = *y; i >= 0; i--) {
        if (maze[*x][i] == '@' || maze[*x][i] == '*') {
            return position;
        }
        position++;
    }
    return position;
}

// 14. BJPI (Bold jump for itching) – jump x position along the direction for which Michael felt
// an itch (left, right, forward, backward). For example, after performing CWR, Michael felt
// an itch because the direction to the right of the current position was free. Then it decided
// to act using BJPI, meaning that it jumped x positions to the right, as the itching was felt
// after Michael checked the locations to the right of its current position. The number of
// positions over which it jumped is found by after using the corresponding CWL, CWR, CWF,
// CWB action. For example, if the next 4 locations to the left of the current position are
// free, then x is 4 after executing CWL. If x is zero after executing action CWL, but the ant
// still executes action BJPI, then Michael stays in its current position. Every BJPI stops the
// corresponding itching of the ant, e.g., the itching type that triggered the jump.

void bjpi(int *x, int *y, char **maze, char*direction, int *itch) {
    if (strcmp(*direction,"left")==0) {
        if (*itch > 0) {
            *y = (*y) - (*itch);
        }
    }
    if (strcmp(*direction,"right")==0) {
        if (*itch > 0) {
            *y = (*y) + (*itch);
        }
    }
    if (strcmp(*direction,"forward")==0) {
        if (*itch > 0) {
            *x = (*x) + (*itch);
        }
    }
    if (strcmp(*direction,"backward")==0) {
        if (*itch > 0) {
            *x = (*x) - (*itch);
        }
    }
}

// 15. CJPI (cautious jump for itching) – jump one position along the direction for which Michael
// felt an itch (left, right, forward, backward). For example, after performing CWR, Michael
// felt an itch because the direction to the right of the current position was free. Then it
// decided to act using CJPI, meaning that it jumped one positions to the right, as the itching
// was felt after Michael checked the locations to the right of its current position. Every CJPI
// stops the corresponding itching of the ant.


// 16. BACKTRACK – Michael backtracks to the position that is retrieved from the memory, such
// as using POP or PEEK. Example: Michaele executes a pop and finds the position <4,4>.
// Backtrack will move Michael back to this position.
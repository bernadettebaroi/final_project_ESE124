#include <stdio.h>
#include "queue.h"
#include <stdlib.h> 

int maze_row;
int maze_col;
int row = 0;
int col = 0;
char maze[32][32];


void assign(int x, int y) {
    maze_row = x;
    maze_col = y;
}

//1. MARK – the ant marks its current position using a chemical called pheromone.
void mark(int x, int y, char c) {
    maze[x][y] = c;
}

// 2. MOVE_F – moves the VA from the current position one position forward. If Michael 
// locates at coordinates (x, y), it will move to (x + 1, y).
void move_f(int x, int y) {
    if (maze[row+1][col] != '*' || row+1 < maze_row) {
        mark(x+1, y, '@');
        _push(x+1,y);
    }
}

//6.CWL – Michael checks if the next locations to the left (until meeting a wall) are pheromone
// free. If the locations are free then Michael feels an itch. Otherwise, if no location is free
// (e.g., because there is a pheromone mark or a wall on the left of Michael), then Michael
// does not feel the itch.
int cwl(int x, int y) {
    int position = 0;
    if (y == 0) {
        return 0;
    }
    for (int i = y; i >= 0; i--) {
        if (maze[x][i] == '@' || maze[x][i] == '*') {
            return 0;
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

void bjpi(int x, int y) {
    int k = 0;
    if ((k = cwl(x, y)) > 0) {
        mark(x, y-k, '@');
    }
}


#include <stdio.h>
#include "stack.h"
#include "ant.h"
#include <stdlib.h> 
#include <string.h>


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


// 7. CWR – Michael checks if the next locations to the right (until meeting a wall) are
// pheromone free. If the locations are free then Michael feels another kind of itch.
// Otherwise, if no location is free (e.g., because there is a wall or a pheromone mark on the
// right of Michael), then Michael does not feel the itch.
int* cwr(int *x, int *y, char **maze) {
    int value = 0;
    int *position = &value;
    if (*y == 0) {
        return 0;
    }
    for (int i = *y + 1; i < sizeof(maze[0]); i++) {
        if (maze[*x][i] == '@' || maze[*x][i] == '*') {
            return position;
        }
        (*position)++; //doesn't this have to to be a pointer? 
    }
    return position;
}

// 8. CWF – Michael checks if the next locations in front (until meeting a wall) are pheromone
// free. If the locations are free then Michael feels a third kind of itch. Otherwise, if no
// location is free (e.g., because there is a wall or a pheromone mark in front of Michael),
// then Michael does not feel the itch

int* cwf(int *x, int *y, char **maze) {
    int value = 0;
    int *position = &value;
    if (*x == 0) {
        return 0;
    }
    for (int i = *x + 1; i < sizeof(maze); i++) { //doesn't the inequality go the oppostie way?
        if (maze[*y][i] == '@' || maze[*y][i] == '*') {
            return position;
        }
        position++;
    }
    return position;
}

// 9. CWB – Michael checks if the next locations backwards (until meeting a wall) are
// pheromone free. If the locations are free then Michael feels a fourth kind of itch.
// Otherwise, if no location is free (e.g., because there is a wall or a pheromone mark behind
// of Michael), then Michael does not feel the itch
int* cwb(int *x, int *y, char **maze) {
    int value = 0;
    int *position = &value;
    if (*x == 0) { 
        return 0;
    }
    for (int i = *x - 1; i >= 0; i--) {
        if (maze[*y][i] == '@' || maze[*y][i] == '*') {
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

void bjpi(int *x, int *y, char **maze, char*direction, int itch) {
    if (strcmp(direction,"left")==0) {
        if (itch > 0) {
            *y = (*y) - (itch);
        }
    }
    if (strcmp(direction,"right")==0) {
        if (itch > 0) {
            *y = (*y) + (itch);
        }
    }
    if (strcmp(direction,"forward")==0) {
        if (itch > 0) {
            *x = (*x) + (itch);
        }
    }
    if (strcmp(direction,"backward")==0) {
        if (itch > 0) {
            *x = (*x) - (itch);
        }
    }
}

// 15. CJPI (cautious jump for itching) – jump one position along the direction for which Michael
// felt an itch (left, right, forward, backward). For example, after performing CWR, Michael
// felt an itch because the direction to the right of the current position was free. Then it
// decided to act using CJPI, meaning that it jumped one positions to the right, as the itching
// was felt after Michael checked the locations to the right of its current position. Every CJPI
// stops the corresponding itching of the ant.

void cjpi(int *x, int *y, char **maze, char*direction, int itch) {
    if (strcmp(direction,"left")==0) {
        if (itch > 0) {
            (*y) -= 1;
        }
    }
    if (strcmp(direction,"right")==0) {
        if (itch > 0) {
           (*y) += 1;
        }
    }
    if (strcmp(direction,"forward")==0) {
        if (itch > 0) {
            (*x) += 1;
        }
    }
    if (strcmp(direction,"backward")==0) {
        if (itch > 0) {
            (*x) -= 1;
        }
    }
    itch = 0;
}

// 16. BACKTRACK – Michael backtracks to the position that is retrieved from the memory, such
// as using POP or PEEK. Example: Michaele executes a pop and finds the position <4,4>.
// Backtrack will move Michael back to this position.

void backtrack(int *x, int *y, Stack *memory) {
    if (is_empty(memory)) {
        printf("Memory stack is empty, cannot backtrack\n");
        return;
    }
    peek(memory, x ,y);
    _pop(memory);
}

//17. RP n t – repeats the n actions following the RP action for t times.
void rp(char* rp, char*n, int *t, int *x, int *y, char **maze, char*direction, int itch, Stack *memory) {
    for (int i = 0; i < *t;i++) {
        char *action = n;
        while (*action != '\0') {
            if (strcmp(action, "MARK") == 0) {
                mark(x, y, maze);
            } else if (strcmp(action, "MOVEF") == 0) {
                move_f(x, y, maze);
            } else if (strcmp(action, "MOVEB") == 0) {
                move_b(x, y, maze);
            } else if (strcmp(action, "MOVEL") == 0) {
                move_l(x, y, maze);
            } else if (strcmp(action, "MOVER") == 0) {
                move_r(x, y, maze);
            } else if (strcmp(action, "CWL") == 0) {
                cwl(x, y, maze);
            } else if (strcmp(action, "CWR") == 0) {
                cwr(x, y, maze);
            } else if (strcmp(action, "CWF") == 0) {
                cwf(x, y, maze);
            } else if (strcmp(action, "CWB") == 0) {
                cwb(x, y, maze);
            } else if (strcmp(action, "BJPI") == 0) {
                bjpi(x, y, maze, direction, itch);
            } else if (strcmp(action, "CJPI") == 0) {
                cjpi(x, y, maze, direction, itch);
            } else if (strcmp(action, "BACKTRACK") == 0) {
                backtrack(x, y, memory);
            } else {
                printf("Invalid action: %s\n", action);
            }
            action += strlen(action) + 1; // Move to the next action in the string
        }

        action = rp;
        while (*action != '\0') {
            if (strcmp(action, "MARK") == 0) {
                mark(x, y, maze);
            } else if (strcmp(action, "MOVEF") == 0) {
                move_f(x, y, maze);
            } else if (strcmp(action, "MOVEB") == 0) {
                move_b(x, y, maze);
            } else if (strcmp(action, "MOVEL") == 0) {
                move_l(x, y, maze);
            } else if (strcmp(action, "MOVER") == 0) {
                move_r(x, y, maze);
            } else if (strcmp(action, "CWL") == 0) {
                cwl(x, y, maze);
            } else if (strcmp(action, "CWR") == 0) {
                cwr(x, y, maze);
            } else if (strcmp(action, "CWF") == 0) {
                cwf(x, y, maze);
            } else if (strcmp(action, "CWB") == 0) {
                cwb(x, y, maze);
            } else if (strcmp(action, "BJPI") == 0) {
                bjpi(x, y, maze, direction, itch);
            } else if (strcmp(action, "CJPI") == 0) {
                cjpi(x, y, maze, direction, itch);
            } else if (strcmp(action, "BACKTRACK") == 0) {
                backtrack(x, y, memory);
            } else {
                printf("Invalid action: %s\n", action);
            }
            action += strlen(action) + 1; // Move to the next action in the string
        }
    }
}
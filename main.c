#include <stdlib.h> 
#include <stdio.h>
#include "stack.h"
#include "ant.h"

#define MAX_NUMBER_OF_STEPS 1000
#define MAX_ACTIONS 1000

char maze[32][32];
int MAX_ROW;
int MAX_COL;

int main() {

    // Write sequence of actions performed by Michael into output file
    FILE *fp3;
    fp3 = fopen("output.txt", "w");
    if (fp3 == NULL) {
        printf("Not able to open the file.");
        exit(1);
    }

    // Read labyrinth from file
    FILE *fp;
    fp = fopen("maze1.txt", "r");
    if (fp == NULL) {
        printf("Not able to open the file.");
        exit(1);
    }
    int row = 0;
    int col = 0;
    char d = fgetc(fp);
    while (d != EOF) {
        if (d == '\n') {
            row++;
            col = 0;
        } else {
            maze[row][col] = d;
            col++;
        }
        d = fgetc(fp);
    }
    MAX_ROW = row;
    MAX_COL = col;

    // Read sequence of actions from input file
    FILE *fp2;
    fp2 = fopen("instruction.txt", "r");
    if (fp2 == NULL) {
        printf("Not able to open the file.");
        exit(1);
    }

    //entry point
    fscanf(fp2, "%d\n", &row);
    fscanf(fp2, "%d\n", &col);

    // Initialize ant's memory
    Stack *memory;
    //memory.top = -1;

    // Perform actions
    int steps = 0;
    int i = 0;
    char n[32];
    int *itch;
    char direction[32];
    int points = 0;


    while (fscanf(fp2, "%s\n", &n) != EOF && steps < MAX_NUMBER_OF_STEPS) {
        if (maze[row][col] >= '0' && maze[row][col] <= '9') {
            points += atoi(maze[row][col]);
        }

        if(strcmp(n,"MARK")==0){
            mark(&row, &col, maze);
		}

        if(strcmp(n,"MOVEF")==0){
            if (maze[row+1][col] != '@' || maze[row+1][col] != '*' || row+1 >= MAX_ROW) {
                move_f(&row, &col, maze);
            }
            steps++;
		}
        if(strcmp(n,"MOVEB")==0){
            if (maze[row-1][col] != '@' || maze[row-1][col] != '*' || row-1 < 0) {
                move_b(&row, &col, maze);
            }
            steps++;
		}
        if(strcmp(n,"MOVEL")==0){
            if (maze[row][col-1] != '@' || maze[row][col-1] != '*' || col-1 < 0) {
                move_l(&row, &col, maze);
            }
            steps++;
		}
        if(strcmp(n,"MOVER")==0){
            if (maze[row][col+1] != '@' || maze[row][col+1] != '*' || col+1 >= MAX_COL) {
                move_r(&row, &col, maze);
            }
            steps++;
		}
        if(strcmp(n,"CWL")==0){
			itch = cwl(&row, &col, maze);
            strcpy(direction, "left");
		}
        if(strcmp(n,"CWR")==0){
			itch = cwr(&row, &col, maze);
            strcpy(direction, "right");
		}
        if(strcmp(n,"CWF")==0){
			itch = cwf(&row, &col, maze);
            strcpy(direction, "forward");
		}
        if(strcmp(n,"CWB")==0){
			itch = cwb(&row, &col, maze);
            strcpy(direction, "backward");
		}

        if(strcmp(n,"BJPI")==0){
            bjpi(row, col, maze, &direction, itch);
		}
        if(strcmp(n,"CJPI")==0){
            cjpi(row, col, maze, &direction, itch);
		}
        if(strcmp(n,"BACKTRACK")==0){
            backtrack(row, col, memory);
		}

    }
    return 0;
}
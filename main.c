#include <stdio.h>
#include "stack.h"
#include "ant.h"
#include <stdlib.h> 

char maze[32][32];
int max_row;
int max_col;


void read_maze(char filename) {
    FILE *fp;
    fp = fopen(filename, "r");
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
    max_row = row;
    max_col = col;
}


int main(int argc, char const *argv[])
{
    read_maze("maze1.txt");

    FILE *fp2;
    fp2 = fopen("output.txt", "w");
    if (fp2 == NULL) {
        printf("Not able to open the file.");
        exit(1);
    }

    FILE *fp;
    fp = fopen("instruction.txt", "r");
    if (fp == NULL) {
        printf("Not able to open the file.");
        exit(1);
    }

    char n[32];
    int t = 0;

    int row;
    int col;
    int itch = 0;
    char direction[32];
    //entry point
    (fscanf(fp, "%d %d\n", row, col));

    while (fscanf(fp, "%s %d\n", &n, &t) != EOF) {
        if(strcmp(n,"MOVE_F")==0){
            if (maze[row+1][col] != '*' || row+1 < max_row) {
                move_f(&row, &col, maze);
            }
		}
        if(strcmp(n,"MOVE_B")==0){
			
		}
		if(strcmp(n,"MOVE_L")==0){
			
		}
		if(strcmp(n,"MOVE_R")==0){
			
		}
		if(strcmp(n,"CWF")==0){
			
		}
		if(strcmp(n,"CWB")==0){
			
		}
		if(strcmp(n,"CWL")==0){
			itch = cwl(row, col, maze);
            strcpy(direction, "left");
		}
		if(strcmp(n,"CWR")==0){
			
		}
		if(strcmp(n,"BJPI")==0){
			if (strcmp(direction,"left")==0) {
                bjpi(row, col, maze);
            }
		}
		if(strcmp(n,"CJPI")==0){
			
		}
		if(strcmp(n,"BACKTRACK")==0){
			
		}
		if(strcmp(n,"CLEAR")==0){
			
		}
		if(strcmp(n,"PEEK")==0){
			
		}
		if(strcmp(n,"MARK")==0){ 
			
		}
		if(strcmp(n,"END")==0){
			
		}

    }
    
    return 0;
}

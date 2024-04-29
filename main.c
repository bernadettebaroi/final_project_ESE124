#include <stdio.h>
#include "queue.h"
#include "ant.h"
#include <stdlib.h> 




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
            mark(row, col, d);
            col++;
        }
        d = fgetc(fp);
    }
    // maze_row = row;
    // maze_col = col;
    assign(row,col);
}

int main(int argc, char const *argv[])
{
    read_maze("maze1.txt");
    
    return 0;
}

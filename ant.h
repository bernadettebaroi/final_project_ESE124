#ifndef ANT
#define ANT

#define MAX_SIZE 100

void mark(int *x, int *y, char **maze);
void move_f(int *x, int *y, char **maze);
void move_b(int *x, int *y, char **maze);
void move_l(int *x, int *y, char **maze);
void move_r(int *x, int *y, char **maze);
int* cwl(int *x, int *y, char **maze);
int* cwr(int *x, int *y, char **maze);
int* cwf(int *x, int *y, char **maze);
int* cwb(int *x, int *y, char **maze);
void bjpi(int *x, int *y, char **maze, char*direction, int itch);
void cjpi(int *x, int *y, char **maze, char*direction, int itch);
void backtrack(int *x, int *y, Stack *memory);
void rp(char* rp, char*n, int *t, int *x, int *y, char **maze, char*direction, int itch, Stack *memory);

#endif

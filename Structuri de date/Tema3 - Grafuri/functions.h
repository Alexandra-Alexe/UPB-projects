#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graf
{
    int n,m,d;
    int deposits[100];
    float **matrix;
}Graf;

void dijkstra(Graf,int,int,int,float *);
int mindistancenode(Graf,float*,int*);
void printPath(int*,int,int);
void plusminus(Graf g);
void recursive_dfs(Graf,int,int*,int);
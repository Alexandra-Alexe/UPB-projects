#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<inttypes.h>

typedef struct QuadtreeNode {
    unsigned char blue , green , red ;
    uint32_t area ;
    int32_t top_left , top_right ;
    int32_t bottom_left , bottom_right ;
} __attribute__ ( ( packed ) ) QuadtreeNode ;

typedef struct matrice {
    unsigned char r, g, b;
} matrice;


void cerinta1 ( matrice **grid, int factor, int stg, int dr, QuadtreeNode *v, uint32_t *numar_culori, uint32_t *numar_noduri) {
    long long s1 = 0, s2 = 0, mar = 0, mag = 0, mab = 0, mean; //media aritmetica pt fiecare culoare
    int i, j;
    for ( i = stg; i < dr; i++) //1 stanga sus
        for ( j = stg; j < dr; j++) {
            mar = mar + grid[i][j].r;
            mag = mag + grid[i][j].g;
            mab = mab + grid[i][j].b;
            mar = mar / (dr - stg)*(dr - stg);
            mag = mag / (dr - stg)*(dr - stg);
            mab = mab / (dr - stg)*(dr - stg);
        }
    
    for ( i = stg; i < dr; i ++) { //formula pt mean
        s2 = 0;
        for ( j = stg; j < dr; j++) {
            s2 = s2 + (mar - grid[i][j].r)*(mar - grid[i][j].r) + (mag - grid[i][j].g)*(mag - grid[i][j].g) + (mab - grid[i][j].b)*(mab - grid[i][j].b);
        }
        s1 = s1 + s2;
    }
    mean = s1 / ( 3 * (dr - stg) * (dr - stg));
    
    QuadtreeNode *node = (QuadtreeNode *)malloc(sizeof(QuadtreeNode));
    v = realloc( v, (((*numar_noduri) + 1)*sizeof(QuadtreeNode*)));
    v[(*numar_noduri)++] = *node;
    node->red = mar;
    node->green = mag;
    node->blue = mab;
    node->area = dr*dr;
    
    if( mean > factor ) { // e nevoie de split
        node->top_left = (*numar_noduri)++; //1 stanga sus
        cerinta1( grid, factor, stg, dr/2, v, numar_culori, numar_noduri);
        node->top_right = (*numar_noduri)++; //2 dreapta sus
        cerinta1( grid, factor, stg*2, dr, v, numar_culori, numar_noduri);
        node->bottom_right = (*numar_noduri)++; //3 dreapta jos
        cerinta1( grid, factor, stg*2, dr, v, numar_culori, numar_noduri);
        node->bottom_left = (*numar_noduri)++; //4 stanga jos
        cerinta1( grid, factor, stg, dr/2, v, numar_culori, numar_noduri);
    }
    else {
        node->top_left = -1;
        node->top_right = -1;
        node->bottom_right = -1;
        node->bottom_left = -1;
        (*numar_culori)++; //cresc numarul de noduri frunza
    }
}

void cerinta2( uint32_t poz, QuadtreeNode *v, matrice **grid) {
    int l, i, j;
    if( (v[poz].top_left != -1) && (v[poz].top_right != -1) && (v[poz].bottom_left != -1) && (v[poz].bottom_right != -1) ) {
        l = sqrt(v[poz].area);
        for(i = poz; i < l; i++)
            for( j = poz; j < l; j++) {
                grid[i][j].r = v[poz].red;
                grid[i][j].g = v[poz].green;
                grid[i][j].b = v[poz].blue;
            }
    }
    else {
        
        cerinta2(v[poz].top_left, v, grid);
        cerinta2(v[poz].top_right, v, grid);
        cerinta2(v[poz].bottom_right, v, grid);
        cerinta2(v[poz].bottom_left, v, grid);
    }
}

int main (int argc, const char * argv[]) {
    
    matrice **grid;
    char type[3];
    int width, height, i , j, k = 0, stg, dr, ok, factor;
    long long max;
    QuadtreeNode *v;
    v = malloc(1);
    uint32_t numar_culori = 0, numar_noduri = 0;
    
    for( i = 1; i < argc; i++)
        if( strcmp(argv[1],"-c") == 0) { //compresie
            
            factor = atoi(argv[2]);
            FILE *fi = fopen(argv[3], "rb");
            FILE *fo = fopen(argv[4], "wb");
            
            if ( fi == NULL || fo == NULL)
                printf("Nu se pot deschide fisierele\n");
            else {
                fscanf(fi,"%s%d%d%lld",type, &width, &height, &max);
                grid = (matrice **)malloc(height * sizeof(matrice*)); //aloc memorie pt matrice
                for( i = 0; i < height; i++)
                    grid[i] = (matrice *)malloc(width * sizeof(matrice));
        
                for( i = 0; i < height; i++) //citesc matricea
                    for( j = 0; j < width; j++) {
                        fread( &(grid[i][j].r), sizeof(unsigned char), 1, fi);
                        fread( &(grid[i][j].g), sizeof(unsigned char), 1, fi);
                        fread( &(grid[i][j].b), sizeof(unsigned char), 1, fi);
                    }
        
                cerinta1( grid, factor, 0, height - 1, v, &numar_culori, &numar_noduri);
                
                QuadtreeNode var;
                fwrite(&numar_culori, sizeof( uint32_t), 1, fo);
                fwrite(&numar_noduri , sizeof( uint32_t), 1, fo);
                for( i = 0; i < numar_noduri; i++) {
                    var = v[i];
                    fwrite(&var.red, sizeof( unsigned char), 1, fo);
                    fwrite(&var.green, sizeof( unsigned char), 1, fo);
                    fwrite(&var.blue, sizeof( unsigned char), 1, fo);
                    fwrite(&var.area, sizeof( uint32_t), 1, fo);
                    fwrite(&var.top_left, sizeof( uint32_t), 1, fo);
                    fwrite(&var.top_right, sizeof( uint32_t), 1, fo);
                    fwrite(&var.bottom_right, sizeof( uint32_t), 1, fo);
                    fwrite(&var.bottom_left, sizeof( uint32_t), 1, fo);
                }
                
                for( i = 0; i < height; i++) //eliberez memoria pt matrice
                    free(grid[i]);
                free(grid);
                for( i = 0; i < numar_noduri; i++) { //eliberez memorie pt vector
                    var = v[i];
                    free(&var.red);
                    free(&var.green);
                    free(&var.blue);
                    free(&var.area);
                    free(&var.top_left);
                    free(&var.top_right);
                    free(&var.bottom_right);
                    free(&var.bottom_left);
                }
                free(v);
            }
            fclose(fi);
            fclose(fo);
        }
        else if( strcmp(argv[1],"-d") == 0 ){  //decompresie
            
            FILE *fi = fopen(argv[2], "rb");
            FILE *fo = fopen(argv[3], "wb");
            
            if ( fi == NULL || fo == NULL)
                printf("Nu se pot deschide fisierele\n");
            else {
                uint32_t numar_noduri, numar_culori;
                QuadtreeNode *v, var;
                matrice **grid;
                int i, j, l;
                
                fread( &numar_culori, sizeof(uint32_t), 1 ,fi);
                fread( &numar_noduri, sizeof(uint32_t), 1, fi);
                
                v = malloc( numar_noduri*sizeof(QuadtreeNode));
                
                for( i = 0; i < numar_noduri; i++) {
                    QuadtreeNode *node = (QuadtreeNode *)malloc(sizeof(QuadtreeNode));
                    v[i] = *node;
                    fread(&node->red, sizeof( unsigned char), 1, fi);
                    fread(&node->green, sizeof( unsigned char), 1, fi);
                    fread(&node->blue, sizeof( unsigned char), 1, fi);
                    fread(&node->area, sizeof( uint32_t), 1, fi);
                    fread(&node->top_left, sizeof( uint32_t), 1, fi);
                    fread(&node->top_right, sizeof( uint32_t), 1, fi);
                    fread(&node->bottom_right, sizeof( uint32_t), 1, fi);
                    fread(&node->bottom_left, sizeof( uint32_t), 1, fi);
                }
                i = 0;
                grid = (matrice **)malloc( v[0].area* sizeof(matrice*)); //aloc memorie pt matrice
                for( i = 0; i < height; i++)
                    grid[i] = (matrice *)malloc(width * sizeof(matrice));
                
                cerinta2(v[i].top_left, v, grid);
                cerinta2(v[i].top_right, v, grid);
                cerinta2(v[i].bottom_right, v, grid);
                cerinta2(v[i].bottom_left, v, grid);
                
                l = sqrt(v[0].area);
                for( i = 0; i < l; i++) {
                    for( j = 0; j < l; j++) {
                        fwrite(&grid[i][j].r, sizeof( unsigned char), 1, fo);
                        fwrite(&grid[i][j].g, sizeof( unsigned char), 1, fo);
                        fwrite(&grid[i][j].b, sizeof( unsigned char), 1, fo);
                    }
                }
                
                for( i = 0; i < l; i++) //eliberez memoria pt matrice
                    free(grid[i]);
                free(grid);
                for( i = 0; i < numar_noduri; i++) { //eliberez memorie pt vector
                    var = v[i];
                    free(&var.red);
                    free(&var.green);
                    free(&var.blue);
                    free(&var.area);
                    free(&var.top_left);
                    free(&var.top_right);
                    free(&var.bottom_right);
                    free(&var.bottom_left);
                }
                free(v);
                
                fclose(fi);
                fclose(fo);
            }
        }
    return 0;
}


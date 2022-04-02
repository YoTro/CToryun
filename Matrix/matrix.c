#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "matrix.h"
#include "utils.h"

/*开辟矩阵空间*/
matrix make_matrix(int rows, int cols)
{
    int i;
    matrix m;
    m.rows = rows;
    m.cols = cols;
    m.vals = calloc(m.rows, sizeof(float *));
    for(i = 0; i < m.rows; ++i){
        m.vals[i] = calloc(m.cols, sizeof(float));
    }
    return m;
}
/*释放矩阵空间*/
void free_matrix(matrix m)
{
    int i;
    for(i = 0; i < m.rows; ++i) free(m.vals[i]);
    free(m.vals);
}
/*打印矩阵*/
void print_matrix(matrix m)
{
    int i, j;
    printf("%d X %d Matrix:\n",m.rows, m.cols);
    printf(" __");
    for(j = 0; j < 16*m.cols-1; ++j) printf(" ");
    printf("__ \n");

    printf("|  ");
    for(j = 0; j < 16*m.cols-1; ++j) printf(" ");
    printf("  |\n");

    for(i = 0; i < m.rows; ++i){
        printf("|  ");
        for(j = 0; j < m.cols; ++j){
            printf("%15.7f ", m.vals[i][j]);
        }
        printf(" |\n");
    }
    printf("|__");
    for(j = 0; j < 16*m.cols-1; ++j) printf(" ");
    printf("__|\n");
}

/*
int count_fields(char *line)
{
    int count = 0;
    int done = 0;
    char *c;
    for(c = line; !done; ++c){
        done = (*c == '\0');
        if(*c == ',' || done) ++count;
    }
    return count;
}
void malloc_error()
{
    fprintf(stderr, "Malloc error\n");
    exit(-1);
}
float *parse_fields(char *line, int n)
{
    float *field = calloc(n, sizeof(float));
    char *c, *p, *end;
    int count = 0;
    int done = 0;
    for(c = line, p = line; !done; ++c){
        done = (*c == '\0');
        if(*c == ',' || done){
            *c = '\0';
            field[count] = strtod(p, &end);
            if(p == c) field[count] = nan("");
            if(end != c && (end != c-1 || *end != '\r')) field[count] = nan(""); //DOS file formats!
            p = c+1;
            ++count;
        }
    }
    return field;
}
char *fgetl(FILE *fp)
{
    if(feof(fp)) return 0;
    size_t size = 512;
    char *line = malloc(size*sizeof(char));
    if(!fgets(line, size, fp)){
        free(line);
        return 0;
    }

    size_t curr = strlen(line);

    while((line[curr-1] != '\n') && !feof(fp)){
        if(curr == size-1){
            size *= 2;
            line = realloc(line, size*sizeof(char));
            if(!line) {
                printf("%ld\n", size);
                malloc_error();
            }
        }
        size_t readsize = size-curr;
        if(readsize > INT_MAX) readsize = INT_MAX-1;
        fgets(&line[curr], readsize, fp);
        curr = strlen(line);
    }
    if(line[curr-1] == '\n') line[curr-1] = '\0';

    return line;
}*/
matrix csv_to_matrix(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(!fp){
        fprintf(stderr, "Couldn't open file: %s\n", filename);
        exit(0);
    }

    matrix m;
    m.cols = -1;

    char *line;

    int n = 0;
    int size = 1024;
    m.vals = calloc(size, sizeof(float*));
    while((line = fgetl(fp))){
        if(m.cols == -1) m.cols = count_fields(line);
        if(n == size){
            size *= 2;
            m.vals = realloc(m.vals, size*sizeof(float*));
        }
        m.vals[n] = parse_fields(line, m.cols);
        free(line);
        ++n;
    }
    m.vals = realloc(m.vals, n*sizeof(float*));
    m.rows = n;
    return m;
}
/*把矩阵展开成一维*/
matrix flatten_matrix(matrix m){
    matrix t = make_matrix(1, m.cols*m.rows);
    int l=0;
    for(int i=0;i<m.rows;i++){
        for(int j=0;j<m.cols;j++){
            t.vals[0][l++]=m.vals[i][j];
        }
    }
    free_matrix(m);
    return t;
}
/*改变矩阵形状*/
matrix reshape_matrix(matrix m, int new_rows, int new_cols)
{
    assert(m.cols * m.rows == new_cols * new_rows);
    if (m.rows == new_cols && m.cols == new_rows) return m;
    matrix new_m = make_matrix(new_rows, new_cols);
    matrix fl_m = flatten_matrix(m);
    int l=0;
    for (int k = 0; k < new_rows; ++k)
    {
        for (int t = 0; t < new_cols; ++t)
        {
            new_m.vals[k][t] = fl_m.vals[0][l++];
        }
    }
    free_matrix(fl_m);
    return new_m;
}
/*转置矩阵*/
matrix transpose_matrix(matrix m){

    matrix t = make_matrix(m.cols, m.rows);
    for(int i=0;i<m.cols;i++){
        for(int j=0;j<m.rows;j++){
            t.vals[i][j]=m.vals[j][i];
        }
    }
    free_matrix(m);
    m=t;
    return m;
}


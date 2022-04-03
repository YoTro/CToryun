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
/*矩阵的迹*/
int trace_matrix(matrix m){
    assert(m.cols>0 && m.rows>0 && m.rows == m.cols);
    int i=0,j=0;
    int ans=0;
    while(i!=m.rows){
        ans += m.vals[i++][j++];
    }
    return ans;
}
/* 标量x矩阵 scale*m */
void scale_matrix(matrix m, float scale)
{
    int i,j;
    for(i = 0; i < m.rows; ++i){
        for(j = 0; j < m.cols; ++j){
            m.vals[i][j] *= scale;
        }
    }
}
/*矩阵相加*/
void matrix_add_matrix(matrix from, matrix to)
{
    assert(from.rows == to.rows && from.cols == to.cols);
    int i,j;
    for(i = 0; i < from.rows; ++i){
        for(j = 0; j < from.cols; ++j){
            to.vals[i][j] += from.vals[i][j];
        }
    }
}
/*矩阵的代数余因子式*/
matrix submatrix(matrix m, int index_i, int index_j){
    assert(m.cols >1 && m.rows>1 && index_j <m.cols && index_i < m.rows && index_i >=0 && index_j >=0);
    matrix fl_m = make_matrix(1, (m.rows-1)*(m.cols-1));
    int l=0;
    for(int i=0;i<m.rows;i++){
        for (int j = 0; j < m.cols; j++)
        {
            if(i!=index_i && j!=index_j){
                fl_m.vals[0][l++]=m.vals[i][j];
            }
        }
        
    }
    l=0;
    matrix sub_m = make_matrix(m.rows-1, m.cols-1);
    for(int i=0;i<m.rows-1;i++){
        for (int j = 0; j < m.cols-1; j++)
        {
            sub_m.vals[i][j]=fl_m.vals[0][l++];
        }
        
    }
    free_matrix(fl_m);
    return sub_m;
}

/*矩阵的行列式*/

float det_matrix(matrix m){
    int det=0;
    assert(m.cols==m.rows);
    if(m.rows==1) return m.vals[0][0];
    if(m.rows == 2) return (m.vals[0][0]*m.vals[1][1] - m.vals[0][1]*m.vals[1][0]);
    for(int j=0;j<m.cols;j++){
        det+=m.vals[0][j]*det_matrix(submatrix(m, 0, j))*pow(-1,j);
    }

    return det;
}
/*伴随矩阵*/
matrix adjugate_matrix(matrix m){
    matrix adj_m = make_matrix(m.rows, m.cols);
    for(int i=0;i<m.rows;i++){
        for(int j=0;j<m.cols;j++){
            adj_m.vals[j][i]=pow(-1, i+j)*det_matrix(submatrix(m, i,j));
        }
    }
    return adj_m;
}
/*单位向量*/
matrix identity_matrix(int n){
    assert(n>0);
    matrix I_n = make_matrix(n,n);
    int i=0,j=0;
    while(i!=n){
        I_n.vals[i++][j++]=1;
    }
    return I_n;
}
/*矩阵的点乘*/
matrix dot_matrix(matrix m, matrix n){
    assert(m.cols == n.rows);
    matrix dot_mn = make_matrix(m.rows, n.cols);
    for(int i=0;i<m.rows;i++){
        for(int j=0;j<n.cols;j++){
            for (int k = 0; k < m.cols; ++k)
            {
                dot_mn.vals[i][j]+=m.vals[i][k]*n.vals[k][j];
            }
        }
    }
    return dot_mn;
}
/*逆矩阵*/
matrix inverse_matrix(matrix m){
    matrix inv_m = adjugate_matrix(m);
    
    float scale = 1/det_matrix(m);
    for(int i = 0; i < m.rows; ++i){
        for(int j = 0; j < m.cols; ++j){
            inv_m.vals[i][j] *= scale;
        }
    }
    return inv_m;
}
/*导入csv到矩阵*/
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
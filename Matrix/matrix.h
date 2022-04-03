#ifndef MATRIX_H
#define MATRIX_H

/*定义矩阵类型*/
typedef struct matrix
{
	int cols,rows;//矩阵维度
	float **vals;//存放二维矩阵
}matrix;
void free_matrix(matrix m);
void print_matrix(matrix m);
matrix make_matrix(int rows, int cols);
matrix csv_to_matrix(char *filename);
matrix flatten_matrix(matrix m);
matrix reshape_matrix(matrix m, int new_rows, int new_cols);
matrix transpose_matrix(matrix m);
void matrix_add_matrix(matrix from, matrix to);
matrix submatrix(matrix m, int index_i, int index_j);
float det_matrix(matrix m);
int trace_matrix(matrix m);
void scale_matrix(matrix m, float scale);
matrix adjugate_matrix(matrix m);
matrix identity_matrix(int n);
matrix inverse_matrix(matrix m);
matrix dot_matrix(matrix m, matrix n);
#endif
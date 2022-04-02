#ifndef MATRIX_H
#define MATRIX_H

/*矩阵类型*/
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
#endif
#include "matrix.h"
#include "utils.h"
#include <stdlib.h>

int main()
{
    char *f="/Users/jin/Documents/GitHub/CToryun/Matrix/t.csv";
    //char *f1 = "/Users/jin/Desktop/t.csv";
	matrix m = csv_to_matrix(f);
	//matrix b = csv_to_matrix(f1);
	print_matrix(m);
	print_matrix(dot_matrix( m, transpose_matrix(m)));
	printf("%d\n",rank_matrix(m));
	matrix *svd = svd_matrix(m);
	print_matrix(svd[0]);
	print_matrix(svd[1]);
	print_matrix(svd[2]);
	free_matrix(svd[0]);
	free_matrix(svd[1]);
	free_matrix(svd[2]);
	free(svd);
	//free_matrix(s);
	free_matrix(m);
	return 0;
}
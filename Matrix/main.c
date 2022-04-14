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
	//print_matrix(b);
	matrix *qr = QR_decomposition_matrix(m);
	print_matrix(qr[0]);
	print_matrix(qr[1]);
    free_matrix(qr[0]);
    free_matrix(qr[1]);	
	free(qr);
	return 0;
}
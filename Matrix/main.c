#include "matrix.h"
#include "utils.h"


int main()
{
    char *f="/Users/jin/Documents/GitHub/CToryun/Matrix/t.csv";
	matrix m = csv_to_matrix(f);
	print_matrix(m);
	matrix dot =  inverse_matrix(m);
	print_matrix(dot);
	free_matrix(dot);
    free_matrix(m);
	return 0;
}
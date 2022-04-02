#include "matrix.h"
#include "utils.h"


int main()
{
    char *f="/Users/jin/Desktop/Matrix/t.csv";
	matrix m = csv_to_matrix(f);
	print_matrix(m);

    free_matrix(m);
	return 0;
}
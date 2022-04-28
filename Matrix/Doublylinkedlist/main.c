#include "OrthogonalLinkedlist.h"

int main(int argc, char const *argv[])
{
	Cross_list M;
	char *filepath = "./Documents/GitHub/CToryun/Matrix/Doublylinkedlist/t.csv";
	M = csv_to_olist(filepath);
	print_olist(M);
	Cross_list new_M = copy_olist(M);
	printf("Copy matrix:\n");
	print_olist(new_M);
	free_olist(M);
	free_olist(new_M);
	return 0;
}
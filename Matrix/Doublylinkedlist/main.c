#include "OrthogonalLinkedlist.h"

int main(int argc, char const *argv[])
{
	Cross_list M;
	char *filepath = "/Users/jin/Desktop/Doublylinkedlist/t.csv";
	M = csv_to_olist(filepath);
	print_olist(M);
	OLNode *p = (OLNode *)malloc(sizeof(OLNode));
	p->r = 3;
	p->c = 1;
	p->value = 2;
	delete_olnode(M, p);
	print_olist(M);
	insert_olist(M, p);
	print_olist(M);
	free_olist(M);
	return 0;
}
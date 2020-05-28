#include "bheap.h"
 
#define LENGTH(a) (sizeof(a) / sizeof(a[0]))
 
struct point
{
	int x;
	int y;
	long weight;
};
 
struct point nodes[] = {
	{10,10,10}, {3,3,3}, {2,2,2},
	{5,5,5}, {4,4,4}, {6,6,6},
	{7,7,7}, {8,8,8}, {9,9,9},
	{10,10,10},{11,11,11}, {12,12,12}
};
 
static int _comp(struct Bheap_node* n1, struct Bheap_node* n2)
{
	if ((NULL != n1) && (NULL != n2))
	{
		if (((struct point*)(n1->value))->weight > ((struct point*)(n2->value))->weight)
			return (1);
		else if(((struct point*)(n1->value))->weight == ((struct point*)(n2->value))->weight)
			return (0);
		else
			return (-1);
	}
	else
		return (0);
}
 
static int _eq(struct Bheap_node* n1, struct Bheap_node* n2)
{
	if ((NULL != n1) && (NULL != n2))
		return ((((struct point*)(n1->value))->x == ((struct point*)(n2->value))->x)
		 && (((struct point*)(n1->value))->y ==((struct point*)(n2->value))->y));
	else
		return (0);
}
 
static void _free_node(struct Bheap_node* bn)
{
	free(bn->value);
	free(bn);
}
 
static void print_point(struct point* p, char c)
{
	if (NULL != p)
		printf("{%d,%d,%ld}%c", p->x, p->y, p->weight, c);
}
 
/* 打印heap内容 */
static void print_heap(struct Bheap* heap)
{
	int i = 1;
 
	for (; i <= heap->size; i++)
		print_point((struct point*)((heap->head[i])->value), ' ');
	
	printf("\n");
}
 
int main(int argc, char* argv[])
{
	int i;
	struct Bheap* heap = NULL;
	struct Bheap_node* inode = NULL, *onode = NULL;
	struct point* p = NULL;
	heap = Bheap_create(2, BHEAP_TYPE_SMALL);
	Bheap_init(heap);
	
	for (i = 0; i < LENGTH(nodes); i++)
	{
		inode = (struct Bheap_node*)malloc(sizeof(struct Bheap_node));
		inode->value = nodes + i;
		Bheap_push(heap, inode, _comp);
#if 0
		print_heap(heap);
#endif
	}
 
	for ( ; ; )
	{
		if (NULL == (onode = Bheap_pop(heap, _comp)))
			break;
#if 1
		print_point((struct point*)onode->value, '\n');
#endif
		free(onode);
	}
 
	Bheap_destory(&heap, 0, NULL);
	return (0);
}

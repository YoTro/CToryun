#ifndef ORTHOGONALLINKEDLIST_H
#define ORTHOGONALLINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include "utils.h"
typedef float ElemType;

typedef struct OLNode {    
     int  r, c;                     //行号与列号     
     ElemType value;                //值     
     struct OLNode *right, *down;   //同行、同列下一个元素的指针     
}OLNode, *OList;

typedef struct {
	int rows, cols, len;  // 稀疏矩阵的行,列,非零元素个数
	OList *rhead, *chead; // 稀疏矩阵的行列表头
}Cross_list;
Cross_list csv_to_olist(char *filepath);
Cross_list create_olist(Cross_list M);
Cross_list copy_olist(Cross_list M);
int find_olnode(Cross_list M, OLNode *p);
void delete_olnode(Cross_list M, OLNode *p);
int update_olnode(Cross_list M, OLNode *p, ElemType value);
void insert_olist(Cross_list M, OLNode *p);
void print_olist(Cross_list M);
void free_olist(Cross_list M);
#endif

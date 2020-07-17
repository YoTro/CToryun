#ifndef _STACK_H
#define _STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
 
typedef int ElemType;
typedef struct
{
	int len;//当前栈大小
    ElemType *base;//栈底指针
    ElemType *top;//栈顶指针
    int stackSize;//栈初始化大小
}stack;
 
static void InitStack(stack *s)
{
	//申请空间
    s->base = (ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
    if(!s->base)
    {
    	printf("The memory can't allocate space \n");
        exit(1);
    }
    s->top = s->base;//赋值初始化指针
    s->len = 0;
    s->stackSize = STACK_INIT_SIZE;
}
 
static void push(stack *s,ElemType e)
{
    if(s->top-s->base >= s->stackSize )
    {
        s->base = (ElemType *)realloc(s->base,(s->stackSize + STACKINCREMENT)*sizeof(ElemType));
        if(!s->base)
        {
            exit(0);
        }
	    s->top = s->base + s->stackSize;
	    s->stackSize = s->stackSize + STACKINCREMENT;
    }
    *(s->top) = e;
    s->top++;
    s->len++;
 
}
static int pop(stack *s)
{
    if(s->top == s->base)
    {
    	printf("The stack is None\n");
        return -1;
    }else{
    	ElemType e = *--(s->top);
    	s->len--;
        return e;
    }
}
static void printStack(stack *s){
	if(s->top == s->base){
		printf("The stack is None\n");
	}
	for (ElemType *i = s->base; i < s->top;i++){
		printf("%d, ", *i);
	}
	printf("\n");
}
#endif
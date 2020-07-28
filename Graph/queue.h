#ifndef _QUEUE_H
#define _QUEUE_H 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct TreeNode nodetype;
typedef int Elemtype;


struct TreeNode{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};
/*define a node of queue*/
typedef struct node
{
	nodetype *data;//数据域
	struct node *Next;//指向下一个节点
}queuenode;

typedef struct  queue
{
	queuenode *front;//队首指针
	queuenode *end; //队尾指针
	Elemtype *len; //队的长度
}cqueue;

/*创建一个节点*/
static queuenode* createnode(nodetype *data){
	queuenode *res = (queuenode*)malloc(sizeof(queuenode));
	if(!res){
		printf("The memory can't allocate any space to queuenode\n");
		exit(1);
	}
	res->data = data;
	res->Next = NULL;
	return res;
}

/*初始化队列*/
static cqueue *init_queue(void){
	cqueue *queue = (cqueue*)malloc(sizeof(cqueue));
	if(!queue){
		printf("The memory can't allocate any space to queue\n");
		exit(1);
	}
	queue->front = NULL;
	queue->end = NULL;
	queue->len = 0;
	return queue;
}

/*入队*/
static void push(cqueue *queue, nodetype *data){
	queuenode *tmp = createnode(data);//创建一个节点
	if(!queue->len){
		queue->front = tmp;
		queue->end = tmp;
	}else{
		queue->end->Next = tmp;
		queue->end = tmp;
	}
	queue->len++;
}

/*出队*/
static queuenode *pop(cqueue *queue){
	if(!queue->len){
		printf("The queue is None\n");
		return NULL;
	}
	queuenode *tmp = (queuenode*)malloc(sizeof(queuenode));
	tmp = queue->front;
	queue->front = tmp->Next;
	tmp->Next = NULL;
	if(queue->end == tmp){
		queue->end = NULL;
	}
	queue->len--;
	return tmp;
}

/*判断队列是否为空*/
static bool isEmpty(cqueue *queue){
	if(!queue->len){
		return 0;
	}else{
		return 1;
	}
}

/*销毁队列*/
static void destory_queue(cqueue *queue){
	while(queue->len){
		queuenode *tmp = pop(queue);
		free(tmp);
	}
	free(queue);
	printf("Destory the queue successfully\n");
}

/*打印队列*/
static void print_queue(cqueue *queue){
	if(!isEmpty(queue)){
		printf("The queue is None\n");
	}else{
		queuenode *tmp = queue->front;
		while(tmp){
			printf("%d ", tmp->data->val);
			tmp = tmp->Next;
		}
		printf("\n");
	}
	
}

#endif
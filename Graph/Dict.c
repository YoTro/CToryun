#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAXWORD 25
#define MAXMEAN 50
 
struct record { //记录结构_读者
    char word[MAXWORD+1];   //key
    char mean[MAXMEAN+1];
};
 
struct lnode {  //链表结点结构
    struct record data;
    struct lnode *next;
};
 
/* 按主键查找 */
struct lnode *SearchPrimarykey(struct lnode *list, char *key)
{
    struct lnode *p = list->next;
 
    while (p != NULL) {
        if(strcmp((p->data).word, key) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
/* 将记录按姓名字母升序插入链表 */
void InsertList(struct lnode *list, struct lnode *n)
{
    struct lnode *p = list;
 
    while (p->next != NULL && strcmp((p->next->data).word, (n->data).word) < 0)
    {
        p = p->next;
    }
    n->next = p->next;
    p->next = n;
}

/* 显示表头 */
void DisplayTableHead(void) {
    printf("%-10s %s\n","WORD","MEANING");
}
/* 显示一条记录 */
void DisplayRecord(struct lnode *r)
{
    printf("%-10s %s\n", (r->data).word, (r->data).mean);
}
 
/* 添加 */
void Add(struct lnode *list)
{
    int i;
    struct record t;
    struct lnode *n, *r;
 
    /* 录入记录 */
    printf("Please input the word: ");
    getchar();
    gets(t.word);
    fflush(stdin);
    printf("Please input the meaning:");
    gets( t.mean);
 
    /* 判断记录是否已存在，若存在则显示记录，若不存在则添加记录 */
    if((r = SearchPrimarykey(list, t.word)) == NULL) {
        /* 申请lnode空间并初始化 */
        n = (struct lnode *)malloc(sizeof(struct lnode));
        if(n != NULL) {
            /* 复制记录 */
            strcpy((n->data).word,t.word);
            strcpy((n->data).mean, t.mean);
            /* 插入链表 */
            InsertList(list, n);
        }
    } else {
        printf("Record Existed!\n");
        DisplayTableHead();
        DisplayRecord(r);
    }
}
 
/* 修改 */
void Edit(struct lnode *list)
{
	
    struct record t;
    struct lnode *r, *p;
    char e[MAXWORD];
    p = list;
 
    printf("Please input the word you want to edit: ");
    getchar();
    gets(e);
    
    if((r = SearchPrimarykey(list, e)) != NULL) {
        fflush(stdin);
        printf("Please edit the word: ");
        gets(t.word);
        printf("Please edit the meaning:");
        gets(t.mean);
 
        /* 复制记录 */
        strcpy((r->data).word,t.word);
        strcpy((r->data).mean,t.mean);
       
        
    } else {
        printf("Record cann't find!\n");
    }
}
/* 查找 */
void Search(struct lnode *list)
{
    char e[MAXWORD];
    struct lnode *r;
 
    printf("Please input the word you want to search: ");
    getchar();
    gets(e);
 
    if((r = SearchPrimarykey(list, e)) != NULL) {
        DisplayTableHead();
        DisplayRecord(r);
    } else {
            printf("Cann't find the word.");
    }
}
 
/* 删除 */
void Delete(struct lnode *list)
{
    char e[MAXWORD];
    struct lnode *q, *p;
    q = list;
    p = list->next;
 
    printf("Please input the word you want to delete: ");
    getchar();
    gets(e);
 
    while(p != NULL) {
        if(strcmp((p->data).word, e) == 0) {
            q->next = p->next;
            free(p);    /* 释放空间 */
            return ;    /* 函数返回 */
        }
        q = p;
        p = p->next;
    }
}
 
/* 显示所有记录 */
void Display(struct lnode *list)
{
    int c = 0;
    struct lnode *p = list->next;
 
    printf("\n--------- ReaderMessage Display ---------\n");
    DisplayTableHead();
    while(p != NULL) {
        DisplayRecord(p);
        c++;    /* 记录条数 */
        p = p->next;
    }
    printf("\n--------- Total:  %d  Record(s) ---------\n",c);
}
 

 

 
/* 释放整个链表空间 */
void FreeList(struct lnode *list)
{
    struct lnode *p = list;
    while(p->next != NULL) {
        p = p->next;
        free(list);
        list = p;
    }
    free(p);
}
 

 

/* 显示菜单 */
void DisplayMenu(void)
{
    printf("\n--------- ReaderMessage Menu ---------\n");
    printf("\n\t1.Add\n\t2.Search\n\t3.Edit\n\t4.Del\n\t5.Display\n\t0.Exit\n");
    printf("\nPlease select the function number(0-5):");
}
/* 主程序 */
int main(int argc, char *argv[])
{
    struct lnode *dictionary;
    /* 功能选择，依次为：退出、添加、查找、删除、显示所有记录 */
    enum {EXIT, ADD, SEARCH, EDIT, DEL, DISP} function = DISP;
 
    /* 头结点 */
    dictionary = (struct lnode *)malloc(sizeof(struct lnode));
    if(dictionary != NULL) {
        dictionary->next = NULL; //初始化
    }
 
    while(function != EXIT) {
        DisplayMenu();
        scanf("%d",&function);
        while(function < EXIT || function > DISP) {
            scanf("%d",&function);
        }
 
        switch(function) {
    case ADD:
        Add(dictionary);
        break;
    case SEARCH:
        Search(dictionary);
        break;
    case EDIT:
        Edit(dictionary);
        break;
    case DEL:
        Delete(dictionary);
        break;
    case DISP:
        Display(dictionary);
        break;
    case EXIT:
        exit(0);
        break;
    default:
        printf("Input Error! Please input the right word.");
        break;
        }
    }
    FreeList(dictionary);
}
 


/*编写完整的程序实现顺序的建立、查找、插入、删除等基本操作*/
#include<stdio.h>
#include<stdlib.h>
 
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
 
typedef int EleType;
 
/*定义顺序表类型定义*/
typedef struct SqList{
    EleType *elem;
    int length ;    //当前链表的长度
    int listsize;   //当前链表分配的存储容量
}SqList;    //顺序表类型
 
/*构造一个空的线性表L*/
int InitList_Sq(SqList *L)
{
  L->elem=(EleType *)malloc(sizeof(EleType));
  if(! L->elem) exit(OVERFLOW);  //存储空间分配失败
  L->length=0;           //空表的长度为0
  L->listsize=LIST_INIT_SIZE; //分配给空表的存储容量
 
  return OK;
}
 
/*返回线性表L第i个位置的数据*/
 EleType GetElem_Sq(SqList L,int i)
 {
     //检查i的合法性
     if(i<1 || i>L.length)  return ERROR;    //i非法
 
     return L.elem[i-1];
 }
 
 /*查找线性表中第一个与所给数据匹配的数据元素的位置*/
 int LocateElem( SqList L, EleType e)
 {
    int i=1;
    EleType *p=L.elem;
    while(*p != e && i<=L.length)  {i++;p++;}  //p指向下一个元素
 
    if(i>L.length)  return 0;   //没有找到数据,返回0
    else return i;          //找到返回位置i
 }
 
 
/*向顺序表L第i个位置插入e*/
int InsList_Sq(SqList *L, int i, EleType e)
{
    EleType *p;
    EleType *q;
    EleType *newbase;
    //合法性检查1<=i<=*L.length+1
    if(i<1 || i> (L->length+1)) return ERROR;   //i值不合法
    if( L->length>=L->listsize)         //存储空间已满，需要增加分配的空间
    {
       newbase=(EleType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(EleType));     //再分配LISTINCREMENT个存储空间
       if(!newbase) exit(OVERFLOW);       //存储空间分配失败
       L->elem=newbase;             //新基址
       L->listsize+=LISTINCREMENT;  //分配的存储容量增加
    }
 
    q=&(L->elem[i-1]);  //确定需要插入的位置
    p=L->elem+L->length-1;//p指向最后一个元素的位置
 
    for(; p>=q;p--) *(p+1)=*(p);  //将插入位置后的数据均向后移一个位置
    *q=e;   //插入e
 
    L->length++;    //表长加1
 
    return OK;
}
 
/*删除顺序表L中第i个位置的数据*/
int DeList_Sq( SqList *L, int i)
{
    EleType *p,*q;
    p=&(L->elem[i-1]); //指向链表的第i个位置
    q=L->elem+L->length-1;  //指向表尾元素
 
    while(p<q) {*p=*(p+1);p++;}    //i位置后的数据均向前移动一个数据
    --L->length;
 
    return OK;
}
 
/*打印顺序表的元素*/
int Print_Sq( SqList L)
{
    int j;
 
    printf("顺序表L：");
    for(j=1;j<=L.length;j++) printf("%d\t",L.elem[j-1]);
    printf("\n");
 
 
    return OK;
}
 
int main()
{
    SqList *pL=(SqList *)malloc(sizeof(SqList));//第一次试验时，没有给pL分配存储空间，结果编译没问题，运行就出现了错误，这是因为没有初始化指针就已经使用指针的原因
    InitList_Sq(pL);
 
    int a,i;
    EleType data;
    while(1)
    {
        printf("\n\n/*********欢迎使用本系统**********/\n\n");
        printf("\n1.创建一个链表\n");
        printf("\n2.输出链表中的所有数据\n");
        printf("\n3.查询链表中某个位置的数据\n");
        printf("\n4.查询与数据匹配的元素的位置\n");
        printf("\n5.向链表中插入数据\n");
        printf("\n6.删除链表中的数据\n");
        printf("\n0.退出\n");
        printf("\n输入1-6，选择您需要的功能:");
        scanf("%d",&a);
        printf("\n您选择的功能号为：%d\n",a);
 
        switch(a)
        {
            case 1:InitList_Sq(pL);printf("\n创建成功\n");break;
            case 2:Print_Sq( *pL);break;
            case 3:printf("\n请输入您需要查询的元素的编号1-%d:",pL->length);
                   scanf("%d",&i);
                   data=GetElem_Sq(*pL,i);
                   printf("\n您查询的数据为%d\n",data);
                   break;
            case 4:printf("\n请输入您需要查询的数据元素:\n");
                   scanf("%d",&data);
                   if(LocateElem(*pL,data)) printf("\n您查询的元素的位置是:%d\n",LocateElem(*pL,data));
                   else printf("\n没有查询到您输入的数据\n");
                   break;
            case 5:printf("\n请输入您需要插入的数据以及它的位置:");
                   scanf("%d%d",&data,&i);
                   printf("\n您需要插入的数据是%d\n您要插入的位置是:%d\n",data,i);
                   if(InsList_Sq(pL,i,data)) printf("\n插入成功\n");
                   printf("插入后的链表排序为:\n");
                   Print_Sq(*pL);
                   break;
            case 6:printf("\n请输入您需要删除元素的位置:");
                   scanf("%d",&i);
                   printf("您要删除的位置是:%d\n",i);
                   if(DeList_Sq(pL,i)) printf("删除成功\n");
                   printf("删除后的链表为：\n");
                   Print_Sq(*pL);
                   break;
            case 0: return OK;
            default:break;
 
        }
    }
    return 0;
}


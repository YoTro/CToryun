#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef int ElementType;//堆元素类型
typedef int LengthType; //堆的长度类型
/*定义堆*/
typedef struct
{
    ElementType* heap;//堆(数组)
    LengthType len; //堆的实时长度
    LengthType Maxsize;//用于保存初始化时所给的动态数组空间的大小,当堆满时可以扩大堆
}defheap;

//1. 初始化堆
void Init_Heap(defheap* heapq, ElementType m){
    if (m <= 0){
        printf("The size is less than 0, reinput the size of heap\n");
        exit(1);
    }
    /*给heap在堆区动态分配内存*/
    heapq->heap = (ElementType*)malloc(sizeof(ElementType)*m);
    if(!heapq->heap){
        printf("The memory is exhausted, please exit\n");
        exit(1);
    }
    heapq->len = 0;
    heapq->Maxsize = m;
    return;
}

//2. 清除堆
void Clear_Heap(defheap* heapq){
    if (heapq->heap != NULL){
        free(heapq->heap);
        heapq->len = 0;
        heapq->Maxsize = 0;
    }
}

//3. 检测堆是否为空
int isEmpty_Heap(defheap* heapq){
    if(!heapq->len){
        return 0;
    }else{
        return 1;
    }
}
//4. 插入堆,先添加到堆尾后移动x到对应的位置
void Insert_Heap(defheap* heapq, ElementType x){
    LengthType i;
    /*如果堆满了,就扩充堆尺寸*/
    if(heapq->len == heapq->Maxsize){
        ElementType* p = realloc(heapq->heap, 2*heapq->Maxsize*sizeof(ElementType));
        if(!p){
            printf("空间用完!\n");
            exit(1);
        }
        heapq->heap = p;
        heapq->Maxsize = 2*heapq->Maxsize;
    }
    /*向堆尾添加新元素x*/
    heapq->heap[heapq->len] = x;
    heapq->len++;
    i = heapq->len - 1;
    while(i != 0){
        //调整堆
        int j = (i - 1)/2;//i位置元素的父节点
        /*如果x大于i的父节点则退出*/
        if (x > heapq->heap[j]){
            break;
        }
        /*将父节点移动到i位置*/
        heapq->heap[i] = heapq->heap[j];
        i = j;

    }
    heapq->heap[i] = x;
}

//5. 删除堆顶元素

ElementType Delete_Heap(defheap* heapq){
    if(!heapq->len){
        printf("The heap is None\n");
        exit(1);
    }
    ElementType tmp, x;
    LengthType i, j;
    /*临时存储堆顶元素*/
    tmp = heapq->heap[0];
    heapq->len--;
    /*如果删除后堆空,则返回*/
    if (heapq->len == 0){
        return tmp;
    }
    x = heapq->heap[heapq->len];
    i = 0;
    j = 2*i + 1;//i节点的左孩子
    while(j <= heapq->len-1){
        /*如果存在右孩子且小于左孩子, j指向右孩子*/
        if (j < heapq->len-1 && heapq->heap[j] > heapq->heap[j+1]){
            j++;
        }
        /*如果x比j小,则退出*/
        if (x <= heapq->heap[j]){
            break;
        }
        /*否则把j孩子移到父节点*/
        heapq->heap[i] = heapq->heap[j];
        i = j;
        j = 2*i + 1;
    }
    heapq->heap[i] = x;
    return tmp;
}
//6. 返回堆顶元素
ElementType get_heap(defheap* heapq){
    if(!heapq->len){
        printf("The heap is empty\n");
        exit(1);
    }
    return heapq->heap[0];
}
//交换函数
void swap(int *a, int *b){
    int tmp = *b;
    *b = *a;
    *a = *b;
    return;
}
//7. heapify
void heapify(defheap* heapq, int i){
    /*如果大于堆的长度,返回*/
    if(i >= heapq->len){
        return;
    }
    int l, r, maxnode;
    l = 2*i + 1;//左节点下标(初始值为1)
    r = 2*i + 2;//右节点下标(初始值为2)
    maxnode = i;//父节点下标(最大值,初始值为0)
    /*如果左节点在堆范围内,且左节点大于最大值,交换下标*/
    if (l < heapq->len && heapq->heap[l] > heapq->heap[maxnode]){
        maxnode = l;
    }
    if (r < heapq->len && heapq->heap[r] > heapq->heap[maxnode]){
        maxnode = r;
    }
    /*如果发生了下标交换,则交换它们的值, 并递归地进行下一次heapify*/
    if (maxnode != i){
        swap(&heapq->heap[maxnode], &heapq->heap[i]);
        heapify(heapq, maxnode);
    }
}
int main(void)
{
    clock_t c0 = clock();
    int i, j, off = 0;
    int m = 10000000;
    int *a = (int*)malloc(sizeof(int)*m);
    ElementType x;
    srand((unsigned)time(NULL));
    defheap hp;
    Init_Heap(&hp, 5);
    for(i = 0; i < m; i++){
        a[i] = rand() % m + 1;
        Insert_Heap(&hp, a[i]);
    }
    while(isEmpty_Heap(&hp)){
        x = Delete_Heap(&hp);

        if(off){
            printf("%d", x);
            if(isEmpty_Heap(&hp)){
                printf(",");
            }
        }
    }
    Clear_Heap(&hp);
    clock_t c1 = clock();
    clock_t t = (c1 - c0)/CLOCKS_PER_SEC;
    printf("\nThe total time is %fs\n", (float)t);
    return 0;
}
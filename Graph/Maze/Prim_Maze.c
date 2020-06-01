#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int L=21;
static const int WALL=0;
static const int ROUTE=1;
//Prime迷宫生成算法的原理：

//（1）初始地图所有位置均设为墙

//（2）任意插入一个墙体进墙队列

//（3）判断此时墙体是否可以设置为路（判断依据在于上下左右四个位置是否只有一个位置是路）

//（4）若设置为路，则将该位置周围（上下左右）的所有墙插入队列，接着执行（5）；若无法设置为路，直接执行（5）

//（5）从墙队列中删去当前位置所在节点

//（6）若墙队列不为空，则从队列中随机选取一面墙重新执行（3），直到墙队列为空

//定义一个链表LinkList
typedef struct queueWall{
	int x;
	struct queueWall *next;
} LinkedList;

//初始化一个链表，n为链表节点个数。返回一个链表指针,指向链表的头节点地址
LinkedList *creat(int n){
	LinkedList *head, *node, *end;//定义头节点，普通节点，尾部节点；
	head = (LinkedList*)malloc(sizeof(LinkedList));//在堆区动态分配地址
	end = head;         //若是空链表则头尾节点一样
	for (int i = 0; i < n; i++) {
		node = (LinkedList*)malloc(sizeof(LinkedList));
		scanf("%d", &node->x);
		end->next = node;
		end = node;
	}
	end->next = NULL;//结束创建
	return head;
}
//尾部添加节点
void append(LinkedList * head, int val) {
    LinkedList * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (LinkedList *) malloc(sizeof(LinkedList));
    current->next->x = val;
    current->next->next = NULL;
}
//头部添加节点
void push(LinkedList ** head, int val) {
    LinkedList * new_node;
    new_node = (LinkedList *) malloc(sizeof(LinkedList));

    new_node->x = val;
    new_node->next = *head;
    *head = new_node;
}	
//获取链表长度
int len(LinkedList *list)
{
    LinkedList *pListNodeTmp = list;
    int i = 0;
 
    // 判断是否有链表输入
    if(list == NULL)
    {
        fprintf(stderr, "There is no list.\n");
        return -1;
    }
 
    // 获得长度
    while(pListNodeTmp != NULL)
    {
        i++;
        pListNodeTmp = pListNodeTmp->next;
    }
    return i;
}
//查找节点并返回值
int search(LinkedList *list, int n)
{
	int i=0;
	if(n<1) return -1;
	LinkedList *p=list;
	while(p->next!=NULL&&i<n){
		++i;
		p=p->next;
	}
	return p->x;
}

//定义修改链表函数
void change(LinkedList *list,int n) {//n为第n个节点
	LinkedList *t = list;
	int i = 0;
	while (i < n && t != NULL) {
		t = t->next;
		i++;
	}
	if (t != NULL) {
		puts("输入要修改的值");
		scanf("%d", &t->x);
	}
	else {
		puts("节点不存在");
	}
}

//删除一个第n个节点
void delet(LinkedList *list, int n) {
	LinkedList *t = list, *in;
	int i = 0;
	while (i < n && t != NULL) {
		in = t;
		t = t->next;
		i++;
	}
	if (t != NULL) {
		in->next = t->next;
		free(t);
	}
	else {
		puts("节点不存在");
	}
}

//插入节点
void insert(LinkedList *list, int n) {
	LinkedList *t = list, *in;
	int i = 0;
	while (i < n && t != NULL) {
		t = t->next;
		i++;
	}
	if (t != NULL) {
		in = (LinkedList*)malloc(sizeof(LinkedList));
		puts("输入要插入的值");
		scanf("%d", &in->x);
		in->next = t->next;//填充in节点的指针域，也就是说把in的指针域指向t的下一个节点
		t->next = in;//填充t节点的指针域，把t的指针域重新指向in
	}
	else {
		puts("节点不存在");
	}
}
//打印链表
void show(LinkedList *list){
	LinkedList *h = list;
    while (h->next != NULL) {
		h = h->next;
		printf("%d  ", h->x);
	}
}

void showMaze(int **maze){
    for(int i=0; i<L; i++){
        for (int j=0; j<L; j++){
            if (maze[i][j]==WALL){
                printf("XX");
            }
            else{
                printf("  ");
            }
        }
        printf("\n");
    }
} 
void CreateMaze() {
	int Maze[L][L] = { 0 };
 
	//最外围设置为路，可以有效的保护里面一层墙体，并防止挖出界
	for (int i = 0; i < L; i++) {
		Maze[i][0] = 1;
		Maze[0][i] = 1;
		Maze[L - 1][i] = 1;
		Maze[i][L - 1] = 1;
	}
 
	//墙队列，包括X , Y
	LinkedList *X;
	LinkedList *Y;

	//任取初始值
	append(X, 2);
	append(Y, 2); 
	//当墙队列为空时结束循环
	while (len(X)>0) {
		//在墙队列中随机取一点
		int r = rand() % len(X);
		int x = search(X,r);
		int y = search(Y,r);
 
		//判读上下左右四个方向是否为路
		int count = 0;
		for (int i = x - 1; i < x + 2; i++) {	
			for (int j = y - 1; j < y + 2; j++) {
				if (abs(x - i) + abs(y - j) == 1 && Maze[i][j] > 0) {
					++count;
				}
			}
		}
 
		if (count <= 1) {
			Maze[x][y] = 1;
			//在墙队列中插入新的墙
			for (int i = x - 1; i < x + 2; i++) {
				for (int j = y - 1; j < y + 2; j++) {
					if (abs(x - i) + abs(y - j) == 1 && Maze[i][j] == 0) {
						append(X, i);
						append(Y, j);
					}
				}
			}
		}
 
		//删除当前墙
		delet(X, r);
		delet(Y, r);
	}
 
	//设置迷宫进出口
	Maze[2][1] = 1;
	for (int i = L - 3; i >= 0; i--) {
		if (Maze[i][L - 3] == 1) {
			Maze[i][L - 2] = 1;
			break;
		}
	}
 
}
int main(void) {
    //随机种子生成
    srand((unsigned)time(NULL));
    //在堆区动态分配一块指定大小(L*sizeof(int*))的迷宫内存空间
    int **Maze=(int**)malloc(L*sizeof(int*));
    for(int i=0;i<L;i++){
        //动态分配连续空间,初始值为0
        Maze[i]=(int*)calloc(L,sizeof(int));
    }
    
    //外侧一圈为墙
    for(int i=0;i<L;i++){
        Maze[0][i]=WALL;
        Maze[i][0]=WALL;
        Maze[L-1][i]=WALL;
        Maze[i][L-1]=WALL;
    }
    LinkedList *head;
    head = (LinkedList *)malloc(sizeof(LinkedList));
    head->x = 2;
    head->next =NULL;
    printf("%d", head->x);
    //生成迷宫
    CreateMaze();
    
    //设置出口
    Maze[1][0]=ROUTE;
    Maze[L-2][L-1]=ROUTE;
    
    //打印迷宫
    showMaze(Maze);
    //释放迷宫内存
    for(int i=0;i<L;i++) free(Maze[i]);
    free(Maze);
    
    return 0;
}
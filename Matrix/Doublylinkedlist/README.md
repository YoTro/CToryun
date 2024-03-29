# 稀疏矩阵下的十字链表

`文件结构`
```
Doublylinkedlist
	├── OrthogonalLinkedlist.c
	├── OrthogonalLinkedlist.h
	├── utils.h
	├── utils.c
	├── main.c
	├── main
	└── README
```
## 使用方法

```bash
git clone https://github.com/YoTro/CToryun.git
cd ./Doublylinkedlist
gcc /Users/jin/Desktop/Doublylinkedlist/utils.c /Users/jin/Desktop/Doublylinkedlist/OrthogonalLinkedlist.c /Users/jin/Desktop/Doublylinkedlist/main.c -o /Users/jin/Desktop/Doublylinkedlist/main
```
点击main文件运行

## 十字链表结构

![](https://web.njit.edu/~avp38/projects/mae/img/sm.jpg "十字链表结构")

## 稀疏矩阵元素

```c
typedef struct OLNode {    
     int  r, c;                     //行号与列号     
     ElemType value;                //值     
     struct OLNode *right, *down;   //同行、同列下一个元素的指针     
}OLNode, *OList;
```
## 稀疏矩阵的行列表头

```c
typedef struct {
	int rows, cols, len;  // 稀疏矩阵的行,列,非零元素个数
	OList *rhead, *chead; // 稀疏矩阵的行列表头
}Cross_list;
```
## 十字链表方法

```c
Cross_list csv_to_olist(char *filepath);                   //导入csv到十字链表
Cross_list create_olist(Cross_list M);                     //手动输入
int find_olnode(Cross_list M, OLNode *p);                  //查找节点
void delete_olnode(Cross_list M, OLNode *p);               //删除节点
int update_olnode(Cross_list M, OLNode *p, ElemType value);//更新节点值 
void insert_olist(Cross_list M, OLNode *p);                //插入节点
void print_olist(Cross_list M);                            //打印十字链表
void free_olist(Cross_list M);                             //释放十字链表内存
```

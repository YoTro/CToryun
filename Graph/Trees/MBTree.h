
 
#ifndef MBTree_h
#define MBTree_h
 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
#define M (4)
#define LIMIT_M_2 (M % 2 ? (M + 1)/2 : M/2)
 
typedef struct MBNode *MBTree,*Position;
typedef int KeyType;
struct MBNode{
    int KeyNum;/* 关键字个数 */
    KeyType Key[M + 1];/* 内部节点从1开始(实际上0的位置存储了第一棵子树的最小值)，树叶节点从0开始 */
    MBTree Children[M + 1];/* 存储M个孩子节点 */
};
 
/* 初始化 */
extern MBTree Initialize();
/* 插入 */
extern MBTree Insert(MBTree T,KeyType Key);
/* 删除 */
extern MBTree Remove(MBTree T,KeyType Key);
/* 销毁 */
extern MBTree Destroy(MBTree T);
/* 遍历节点 */
extern void Travel(MBTree T);
/* 搜索 */
extern void Retrieval(MBTree T, KeyType y);
#endif /* MBTree_h */

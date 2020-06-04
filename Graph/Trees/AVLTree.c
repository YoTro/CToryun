#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Maxsize 1024
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };

void inorder(int *q, int *i, struct TreeNode* root){
    if(root){
	    inorder(q, i, root->left);
	    q[(*i)++]=root->val;
	    printf("%d\n",root->val);
	    inorder(q, i, root->right);
    }
    return;
}
//层序遍历返回数组类型,root为指向根节点的指针, arraySize为指向二维数组中每一层[]的指针,levelsize是指向二维数组[][]的指针
int** bfs(struct TreeNode* root){
	int **levelsize=(int **)malloc(sizeof(int*) * Maxsize);
	if (!root){
		//如果根节点为空,二维数组大小为0,返回NULL
		return NULL;
	}
	struct TreeNode *queue[Maxsize], *p ;//环形队列取余法
	int front=0,rear=0,k=0;//队列的头下标和尾下标,二维数组第k行
	int **res = (int **)malloc(sizeof(int *) * Maxsize);//为二维数组res分配堆区动态内存空间
	*levelsize = (int *)malloc(sizeof(int) * Maxsize);//队列的一级指针分配空间
	rear = (rear + 1)%Maxsize;
	queue[rear] = root;//存储根节点指针
	printf("层序遍历\n");
	while(front != rear){
		int sum = (rear - front + Maxsize) % Maxsize;
		(*levelsize)[k] = sum;
		res[k] = (int*)malloc(sizeof(int)*sum);
		printf("第%d行\n", k);
		for(int i=0;i < sum;i++){
			front = (front + 1) % Maxsize;
			p = queue[front];//从下标为1的位置开始遍历队列
			res[k][i] = p->val;
			printf("%d ", p->val);
			if(p->left){
				rear = (rear + 1) % Maxsize;
				queue[rear] = p->left;//入队左节点
			}
			if(p->right){
				rear = (rear + 1) % Maxsize;
				queue[rear] = p->right;//入队右节点
			}

		}
		printf("\n");
		k++;//遍历二叉树下一层
	}
	return res;
}

struct TreeNode *creatBiTree()
{
    int k;
    printf("请输入二叉树值\n");
    scanf("%d",&k);
    if(k == -1)
        return NULL;
    struct TreeNode *T=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    T->val=k;
    T->left=creatBiTree();
    T->right=creatBiTree();
    return T;
}

struct TreeNode *AVLTree( int *q, int L, int R)
{
	struct TreeNode* avlroot = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	if(L>R){
		return NULL;
	}
	int mid=(R+L)>>1;
	avlroot->val = q[mid];
    avlroot->left = AVLTree( q, L, mid-1);
    avlroot->right = AVLTree( q, mid+1, R);
    return avlroot;
}



int getheigh(struct TreeNode* root){
	if(!root){
		return -1;
	}
	if (getheigh(root->left)>getheigh(root->right)){
		return getheigh(root->left)+1;
	}else{
		return getheigh(root->right)+1;

	}
}
int isBalanced(struct TreeNode* root){
	if(!root){
		printf("它是平衡的\n");
		return 1;
	}
	int leftheight = getheigh(root->left);
	int rightheight = getheigh(root->right);
	if (abs(leftheight-rightheight ) < 2 && isBalanced(root->left)&& isBalanced(root->right)){
		printf("它是平衡的\n");
		return 1;
	}
	printf("它是不平衡的\n");
	return 0;
}
struct TreeNode* balanceBST(struct TreeNode* root){
    int *q = (int*)malloc(sizeof(int));
    struct TreeNode *p;
    int end,i=0;
    inorder(q, &i, root);
    int j,t;
    end = i-1;
	t = isBalanced(root);
	if (t == 0){
		printf("平衡后\n");
		p = AVLTree(q, 0, end);
		return p;
	}
	return root;
    
}
int main(void){

	struct TreeNode *root=creatBiTree();
	//showTree(root);
	//struct TreeNode* b  = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	//b = balanceBST(root);
	//showTree(b);
	
	int i=0;
	int t;
	struct TreeNode *p;
	p = balanceBST(root);
	int **levelarray = bfs(p);
	return 0;

}
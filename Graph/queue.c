#include "queue.h"



struct TreeNode *creatBTree()
{
    int k;
    printf("请输入二叉树值\n");
    scanf("%d",&k);
    if(k == -1)
        return NULL;
    struct TreeNode *T=(struct TreeNode *)malloc(sizeof(struct TreeNode));
    T->val=k;
    T->left=creatBTree();
    T->right=creatBTree();
    return T;
}
/*中序遍历入队*/
void inoderpush(struct TreeNode* root , cqueue *queue ){
	if(root){
		inoderpush(root->left, queue);
		push(queue, root);
		inoderpush(root->right, queue);
	}
	return;
}

int main(void)
{
	cqueue *queue = init_queue();
	struct TreeNode* root = creatBTree();
	inoderpush(root, queue);
	print_queue(queue);
	destory_queue(queue);
	return 0;
}
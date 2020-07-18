
//Date: 2020-05-31 17)30
//Author: Toryun
//Function: finding the strongly connected components of a graph
//pseudocode
/*algorithm tarjan is
    input: graph G = (V, E)
    output: set of strongly connected components (sets of vertices)
   
    index := 0
    S := empty stack
    for each v in V do
        if v.index is undefined then
            strongconnect(v)
        end if
    end for
   
    function strongconnect(v)
        // Set the depth index for v to the smallest unused index
        v.index := index
        v.lowlink := index
        index := index + 1
        S.push(v)
        v.onStack := true
      
        // Consider successors of v
        for each (v, w) in E do
            if w.index is undefined then
                // Successor w has not yet been visited; recurse on it
                strongconnect(w)
                v.lowlink := min(v.lowlink, w.lowlink)
            else if w.onStack then
                // Successor w is in stack S and hence in the current SCC
                // If w is not on stack, then (v, w) is an edge pointing to an SCC already found and must be ignored
                // Note: The next line may look odd - but is correct.
                // It says w.index not w.lowlink; that is deliberate and from the original paper
                v.lowlink := min(v.lowlink, w.index)
            end if
        end for
      
        // If v is a root node, pop the stack and generate an SCC
        if v.lowlink = v.index then
            start a new strongly connected component
            repeat
                w := S.pop()
                w.onStack := false
                add w to current strongly connected component
            while w ≠ v
            output the current strongly connected component
        end if
    end function
 */

#include "stack.h"
#define min(x,y) ((x)<(y)?(x):(y))
#define maxsize 101
int j = 0;
int result[6][6];//定一个储存强连通分量的数组

void number_to_alpha(int number){
	if (number == 0){printf("A->");}
	if (number == 1){printf("B->");}
	if (number == 2){printf("C->");}
	if (number == 3){printf("D->");}
	if (number == 4){printf("E->");}
	if (number == 5){printf("F->");}
	if (number == 6){printf("G->");}
	if (number == 7){printf("H->");}
	if (number == 8){printf("I->");}
	if (number == 9){printf("J->");}
	if (number == 10){printf("K->");}
	if (number == 11){printf("L->");}
	if (number == 12){printf("M->");}
	if (number == 13){printf("N->");}	
}
void print(int *p, int size){
	for (int i = 0; i < size; i++){
		number_to_alpha(p[i]);
	}
	printf("\n");
}

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
element | trype  | intro
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
dfn     | array  | depth-first-number:Add the time stamp of the first access to the node. Once the node is time stamped, the timestamp will not be modified
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
low     | array. | Record the timestamp of the node when it visited and update it every time it traverses the child node to look back its parent node, so as to find the root node of the entire search subtree
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
stack.  | array  | Used to store the strong connected nodes that have been traversed, if the low[node] == dfn[node], pop them
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
c       | int    | Timestamp
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
graph   | array  | Adjacency matrix 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
onStack | array  | record the node if it is in stack
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
size    | int    | the size of graph
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
rowsize | int    | the size of graph[0]
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
//innerLoop of scc
void strongconnect(int node, int graph[6][6], stack *s, int size, int rowsize, int c, int *onStack, int *low, int *dfn){
	dfn[node] = c;
	low[node] = c;
	c++;
	push(s, node);
	onStack[node] = 1;//记录是否入栈
	for (int i = 0; i < rowsize; i++){

		if(graph[node][i] == 1){

			if (dfn[i] == -1){
			//后继节点i未访问，递归调用strongconnect函数把i加入low并编号入栈
				strongconnect(i, graph, s, size, rowsize, c, onStack, low, dfn);
				low[node] = min(low[node], low[i]);

			}
			else if (onStack[i]){
				//number_to_alpha(node);number_to_alpha(i);printf("\n");
				low[node] = min(low[node], dfn[i]);
			}
		}

	}
	//printStack(s);number_to_alpha(node);printf("%d\n", low[node]);
	if (low[node] == dfn[node]){
		//把栈内的子节点全部加入array
		
		int k = 0;
		printf("The %d th strongconnected components:\n", j);
		int* t = (int*)malloc(sizeof(int)*size);
	    if(!t)
	    {
	    	printf("The memory can't allocate space \n");
	        exit(1);
	    }
		while (1){
			
			int v = pop(s);
			onStack[v] = -1;
			t[k] = v;
			result[j][k++] = v + 1;
			if (v == node){
				break;
			}
		}
		print(t, k);
		free(t);
		j++;
	}

}
void strongly_connected_components(int graph[6][6], stack *s, int size, int rowsize){
	int c = 0;
	int onStack[maxsize];
	int low[maxsize];
	int dfn[maxsize];
	for (int i = 0; i < size; i++)
    {
       dfn[i] = -1;
       low[i] = -1;
       onStack[i] = -1;
    }
	//依次push入栈,遍历图所有节点,防止存在因一次tarjan而没有遍历到的节点
	for (int i = 0;i < size;i++){
		if (dfn[i] == -1){
			strongconnect(i, graph, s, size, rowsize, c, onStack, low, dfn);
		}
	}
}

int main(void){
	int v = 6;
	//Adjacency matrix 图的邻接矩阵
	int graph[6][6] = {{0,1,0,0,0,0},{0,0,1,0,0,0},{1,0,0,0,0,0},{0,1,1,0,1,0},{0,0,0,1,0,1},{0,0,1,0,0,0}};
	//初始化dfn,low,onStack
    stack s;
    int n = 6;
    InitStack(&s);
	strongly_connected_components(graph, &s, v, v);
	free(s.base);
	return 0;
}
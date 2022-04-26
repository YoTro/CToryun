#include "OrthogonalLinkedlist.h"
/*
___________                               
\__    ___/__________ ___.__.__ __  ____  
  |    | /  _ \_  __ <   |  |  |  \/    \ 
  |    |(  <_> )  | \/\___  |  |  /   |  \
  |____| \____/|__|   / ____|____/|___|  /
                      \/               \/ 
[Doubly linked list](https://en.wikipedia.org/wiki/Doubly_linked_list)

https://arxiv.org/pdf/cs/0011047.pdf 
*/
Cross_list csv_to_olist(char *filepath){
	FILE *fp = fopen(filepath, "r");
	if (!fp)
	{
		printf("The file is not exist, please check the path!\n");
		exit(0);
	}
	Cross_list M;
	OLNode *p;
	int n = 0; //矩阵行大小
	int size = 1024;
	M.cols = -1;
	M.len = 0;
	ElemType **mat = (ElemType **)malloc(size*sizeof(ElemType*));
	char *line;
	while((line = fgetl(fp))){
		if (M.cols == -1)
		{
			M.cols = count_fields(line);
		}
		mat[n] = (ElemType *)malloc(M.cols * sizeof(ElemType));
		if (n == size)
		{
			size*=2;
			mat = realloc(mat, size * sizeof(ElemType*));
		}
		mat[n] = parse_fields(line, M.cols);
		free(line);
		n++;
	}
	mat = realloc(mat, n * sizeof(ElemType*));
	M.rows = n;
	for (int i = 0; i < M.rows; ++i){
		for (int j = 0; j < M.cols; ++j)
		{
			printf("%f ", mat[i][j]);
		}
		printf("\n");
	}
	if (!(M.rhead = (OList *)malloc((M.rows+1)*sizeof(OList))) || !(M.chead = (OList *)malloc((M.cols+1)*sizeof(OList))))
	{
		printf("Malloc error: size %d is too large\n", M.rows);
		exit(-1);
	}

	for (int i = 1; i <= M.rows; ++i)
	{
		M.rhead[i] = NULL;
	}
	for (int i = 1; i <= M.cols; ++i)
	{
		M.chead[i] = NULL;
	}	
	for (int i = 0; i < M.rows; ++i){
		
		for (int j = 0; j < M.cols; ++j)
		{
			if (mat[i][j] != 0 && mat[i][j] != nan(""))
			{	
				
				if (!(p = (OLNode *)malloc(sizeof(OLNode))))
				{
					printf("Initialize cell failed\n");
					exit(0);
				}
				p->r = i+1;
				p->c = j+1;
				p->value = mat[i][j];
				insert_olist(M, p);
				M.len++;
			}
		}
		free(mat[i]);
		mat[i] = NULL;
	}
	free(mat);
	mat = NULL;
	fclose(fp);
	return M;
}

Cross_list create_olist(Cross_list M){
	int i,j,k;
	OLNode *p;
	int m, n, t;
	int flg = 1;

	while(flg == 1){
		printf("Please inpute the row, col and nozero's number of sparse matrix: \n");
		scanf("%d %d %d", &m, &n, &t);
		if (m <= 0 || n <= 0 || t < 0)
		{
			char c;
			printf("Please input geater than zero!\n");
			while((c = getchar()) != EOF && c != '\n' );//清除缓冲区中的数据, 否则会出现无限循环如果输入的不是数字
			continue;
		}else{
			flg = 0;
		}		
	}
	if (t > m*n/2)
	{
		printf("The matrix is sparse matrix, nozero's number is less than %dx%d/2 = %d\n", m, n, m*n/2);
	}
	M.rows = m;
	M.cols = n;
	M.len = t;
	if ( !(M.rhead = (OList *)malloc((m+1)*sizeof(OList))) || !(M.chead = (OList *)malloc((n+1)*sizeof(OList))) )
	{
		printf("Initialize failed\n");
		exit(0);
	}
	//初始化行表头
	for (i = 1; i <= m; ++i)
	{
		M.rhead[i] = NULL;
	}
	//初始化列表头
	for (i = 1; i <= n; ++i)
	{
		M.chead[i] = NULL;
	}
	printf("Please input the (i, j, value) in the sparse matrix \n(e.g. 2 1 3 separate with spaces then Enter to next line):\n1. Change: If you want to change the value, please inpute 'T'\n2. Deleted: Deleted the node, please inpute 'D'\n");
	int num = 0;//计算添加节点数量
	while ( num != M.len )
	{
		scanf("%d %d %d", &i, &j, &k);
		if(isnumber(i) != 0 && isnumber(j) != 0 && isnumber(k) != 0){
			printf("Please inpute number\n");
			char c;
			while((c = getchar()) != EOF && c != '\n' );//清除缓冲区中的数据, 否则会出现无限循环如果输入的不是数字
			continue;
		}
		if (i > M.rows || j > M.cols)
		{
			printf("The i, j is greater than the matrix\n");
			continue;
		}
		if (!(p = (OLNode *)malloc(sizeof(OLNode))))
		{
			printf("Initialize cell failed\n");
			exit(0);
		}
		p->r = i;
		p->c = j;
		p->value = k;
		// link the p to head 连接元素到表头

		if (M.rhead[p->r] == NULL || M.rhead[p->r]->c > j){
			p->right = M.rhead[p->r];
			M.rhead[p->r] = p;

		}else{
			OLNode *q = M.rhead[p->r];
			while(q->right && q->right->c < j){
				q = q->right;
			}
			if (q->right && q->right->c == p->c)
			{
				printf("%d %d %f This node is not None, please insertq new element\n", q->right->r, q->right->c, q->right->value);
				continue;
			}		
			
			if (q->c == p->c)
			{
				printf("%d %d %f This node is not None, please insert new element\n", q->r, q->c, q->value);
				continue;
			}
			p->right = q->right;
			q->right = p;
		}

		if(M.chead[p->c] == NULL || M.chead[p->c]->r > i){
			p->down = M.chead[p->c];
			M.chead[p->c] = p;
		}else{
			OLNode *q = M.chead[p->c];
			while(q->down && q->down->r < i){
				q = q->down;
			}
			if (q->right && q->right->r == p->r)
			{
				printf("%d %d %f This node is not None, please insertq new element\n", q->right->r, q->right->c, q->right->value);
				continue;
			}		
			
			if (q->r == p->r)
			{
				printf("%d %d %f This node is not None, please insert new element\n", q->r, q->c, q->value);
				continue;
			}
			p->down = q->down;
			q->down = p;
		}
		num++;
	}
	return M;

}
int find_olnode(Cross_list M, OLNode *p){
	if (p->r > M.rows || p->c > M.cols || !M.rhead[p->r])
	{
		printf("The node (%d, %d) %f is not in the matrix\n", p->r, p->c, p->value);
		return 0;
	}
	OLNode *q = M.rhead[p->r];

	while(q->c < p->c && q->right){
		q = q->right;
	}
	if (q->c != p->c || p->value != q->value)
	{
		printf("The node (%d, %d) %f is not in the matrix\n", p->r, p->c, p->value);
		return 0;
	}
	return 1;
}
void delete_olnode(Cross_list M, OLNode *p){
	if (p->r > M.rows || p->c > M.cols || !M.rhead[p->r])
	{
		printf("The node (%d, %d) %f is not in the matrix\n", p->r, p->c, p->value);
		return;
	}
	OLNode *q = M.rhead[p->r];
	OLNode *pre_q = q;

	while(q->c < p->c && q->right){
		pre_q = q;
		q = q->right;
	}
	if (q->c != p->c || p->value != q->value)
	{
		printf("The node (%d, %d) %f is not in the matrix\n", p->r, p->c, p->value);
		return;
	}

	OLNode *g = M.chead[p->c];
	OLNode *pre_g = g;
	while(g->r < p->r && g->down){
		pre_g = g;
		g = g->down;
	}
	pre_q->right = q->right;
	pre_g->down = g->down;
	printf("Delete sucessfully\n");
	
	if (q == M.rhead[p->r])
	{
		M.rhead[p->r] = q->right;
	}
	if (g == M.chead[p->c])
	{
		M.chead[p->c] = g->down;
	}
	free(q);
	q = NULL;
	g = NULL;	
	
	M.len--;
	return;
}
int update_olnode(Cross_list M, OLNode *p, ElemType value){
	if (p->r > M.rows || p->c > M.cols || !M.rhead[p->r])
	{
		printf("The node (%d, %d) %f is not in the matrix\n", p->r, p->c, p->value);
		return 0;
	}
	OLNode *q = M.rhead[p->r];

	while(q->c < p->c && q->right){
		q = q->right;
	}
	if (q->c != p->c || p->value != q->value)
	{
		printf("The node (%d, %d) %f is not in the matrix\n", p->r, p->c, p->value);
		return 0;
	}
	q->value = value;
	return 1;
}
void insert_olist(Cross_list M, OLNode *p){

	if (p->r > M.rows || p->c > M.cols)
	{
		printf("The node (%d, %d) %f is not in the matrix\n", p->r, p->c, p->value);
		return;
	}
	if (M.rhead[p->r] == NULL || M.rhead[p->r]->c > p->c){
		p->right = M.rhead[p->r];
		M.rhead[p->r] = p;
	}else{
		OLNode *q = M.rhead[p->r];
		while(q->right && q->right->c < p->c){
			q = q->right;
		}
		if (q->right && q->right->c == p->c)
		{
			printf("%d %d %f This node is not None, please insertq new element\n", q->right->r, q->right->c, q->right->value);
			return;
		}		
		
		if (q->c == p->c)
		{
			printf("%d %d %f This node is not None, please insert new element\n", q->r, q->c, q->value);
			return;
		}
		p->right = q->right;
		q->right = p;
	}
	if (M.chead[p->c] == NULL || M.chead[p->c]->r > p->r)
	{
		p->down = M.chead[p->c];
		M.chead[p->c] = p;
	}else{
		OLNode *g = M.chead[p->c];

		while (g->down && g->down->r < p->r){
			g = g->down;
		}
		if (g->down && g->down->r == p->r)
		{
			printf("%d %d %f This node is not None, please insertg new element\n", g->down->r, g->down->c, g->down->value);
			return;
		}		
		if (g->r == p->r)
		{
			printf("%d %d %f This node is not None, please insert_ new element\n", g->r, g->c, g->value);
			return;
		}
		p->down = g->down;
		g->down = p;
	}
}
void free_olist(Cross_list M){
	int i = 1, j = 1;
	while (i <= M.rows && j <= M.cols)
	{

		OLNode *q = M.rhead[i];
		
		while (q)
		{
			
			OLNode *tmp = q;
			q = q->right;
			free(tmp);

		}
		M.rhead[i++] = NULL;
		M.chead[j++] = NULL;

	}
	free(M.rhead);
	free(M.chead);
}
void print_olist(Cross_list M){
	printf("%d x %d Matrix:\n", M.rows, M.cols);
	for (int i = 1; i <= M.rows; ++i)
	{
		if (M.rhead[i])
		{
			OList p = M.rhead[i];
			while(p){
				printf("%d\t%d\t%f\n", p->r, p->c, p->value);
				p = p->right;
			}
		}
	}
}


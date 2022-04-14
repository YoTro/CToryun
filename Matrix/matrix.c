#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <complex.h>
#include "matrix.h"
#include "utils.h"

/*开辟矩阵空间*/
matrix make_matrix(int rows, int cols)
{
    int i;
    matrix m;
    m.rows = rows;
    m.cols = cols;
    m.vals = calloc(m.rows, sizeof(float *));
    for(i = 0; i < m.rows; ++i){
        m.vals[i] = calloc(m.cols, sizeof(float));
    }
    return m;
}
/*释放矩阵空间*/
void free_matrix(matrix m)
{
    int i;
    for(i = 0; i < m.rows; ++i) free(m.vals[i]);
    free(m.vals);
}
/*打印矩阵*/
void print_matrix(matrix m)
{
    int i, j;
    printf("%d X %d Matrix:\n",m.rows, m.cols);
    printf(" __");
    for(j = 0; j < 16*m.cols-1; ++j) printf(" ");
    printf("__ \n");

    printf("|  ");
    for(j = 0; j < 16*m.cols-1; ++j) printf(" ");
    printf("  |\n");

    for(i = 0; i < m.rows; ++i){
        printf("|  ");
        for(j = 0; j < m.cols; ++j){
            printf("%15.7f ", m.vals[i][j]);
        }
        printf(" |\n");
    }
    printf("|__");
    for(j = 0; j < 16*m.cols-1; ++j) printf(" ");
    printf("__|\n");
}

/*把矩阵展开成一维*/
matrix flatten_matrix(matrix m){
    matrix t = make_matrix(1, m.cols*m.rows);
    int l=0;
    for(int i=0;i<m.rows;i++){
        for(int j=0;j<m.cols;j++){
            t.vals[0][l++]=m.vals[i][j];
        }
    }
    return t;
}
/*改变矩阵形状*/
matrix reshape_matrix(matrix m, int new_rows, int new_cols)
{
    assert(m.cols * m.rows == new_cols * new_rows);
    if (m.rows == new_cols && m.cols == new_rows) return m;
    matrix new_m = make_matrix(new_rows, new_cols);
    matrix fl_m = flatten_matrix(m);
    int l=0;
    for (int k = 0; k < new_rows; ++k)
    {
        for (int t = 0; t < new_cols; ++t)
        {
            new_m.vals[k][t] = fl_m.vals[0][l++];
        }
    }
    free_matrix(fl_m);
    return new_m;
}
/*转置矩阵*/
matrix transpose_matrix(matrix m){

    matrix t = make_matrix(m.cols, m.rows);
    for(int i=0;i<m.cols;i++){
        for(int j=0;j<m.rows;j++){
            t.vals[i][j]=m.vals[j][i];
        }
    }
    return t;
}
/*矩阵的迹*/
int trace_matrix(matrix m){
    assert(m.cols>0 && m.rows>0 && m.rows == m.cols);
    int i=0,j=0;
    int ans=0;
    while(i!=m.rows){
        ans += m.vals[i++][j++];
    }
    return ans;
}
/* 标量x矩阵 scale*m */
matrix scale_matrix(matrix m, float scale)
{
    matrix m_scale = make_matrix(m.rows, m.cols);
    int i,j;
    for(i = 0; i < m.rows; ++i){
        for(j = 0; j < m.cols; ++j){
             m_scale.vals[i][j] = m.vals[i][j]*scale;
        }
    }
    return m_scale;
}
/*矩阵相加*/
matrix matrix_add_matrix(matrix from, matrix to)
{
    assert(from.rows == to.rows && from.cols == to.cols);
    matrix m = make_matrix(from.rows, from.cols);
    int i,j;
    for(i = 0; i < from.rows; ++i){
        for(j = 0; j < from.cols; ++j){
            m.vals[i][j] = to.vals[i][j] + from.vals[i][j];
        }
    }
    return m;
}
/*矩阵的代数余因子式*/
matrix submatrix(matrix m, int index_i, int index_j){
    assert(m.cols >1 && m.rows>1 && index_j <m.cols && index_i < m.rows && index_i >=0 && index_j >=0);
    matrix fl_m = make_matrix(1, (m.rows-1)*(m.cols-1));
    int l=0;
    for(int i=0;i<m.rows;i++){
        for (int j = 0; j < m.cols; j++)
        {
            if(i!=index_i && j!=index_j){
                fl_m.vals[0][l++]=m.vals[i][j];
            }
        }
        
    }
    l=0;
    matrix sub_m = make_matrix(m.rows-1, m.cols-1);
    for(int i=0;i<m.rows-1;i++){
        for (int j = 0; j < m.cols-1; j++)
        {
            sub_m.vals[i][j]=fl_m.vals[0][l++];
        }
        
    }
    free_matrix(fl_m);
    return sub_m;
}

/*矩阵的行列式*/

float det_matrix(matrix m){
    int det=0;
    assert(m.cols==m.rows);
    if(m.rows==1) return m.vals[0][0];
    if(m.rows == 2) return (m.vals[0][0]*m.vals[1][1] - m.vals[0][1]*m.vals[1][0]);
    for(int j=0;j<m.cols;j++){
        det+=m.vals[0][j]*det_matrix(submatrix(m, 0, j))*pow(-1,j);
    }

    return det;
}
/*伴随矩阵*/
matrix adjugate_matrix(matrix m){
    matrix adj_m = make_matrix(m.rows, m.cols);
    for(int i=0;i<m.rows;i++){
        for(int j=0;j<m.cols;j++){
            adj_m.vals[j][i]=pow(-1, i+j)*det_matrix(submatrix(m, i,j));
        }
    }
    return adj_m;
}
/*单位矩阵*/
matrix identity_matrix(int n){
    assert(n>0);
    matrix I_n = make_matrix(n,n);
    int i=0,j=0;
    while(i!=n){
        I_n.vals[i++][j++]=1;
    }
    return I_n;
}
/*矩阵的点乘*/
matrix dot_matrix(matrix m, matrix n){
    assert(m.cols == n.rows);
    matrix dot_mn = make_matrix(m.rows, n.cols);
    for(int i=0;i<m.rows;i++){
        for(int j=0;j<n.cols;j++){
            for (int k = 0; k < m.cols; ++k)
            {
                dot_mn.vals[i][j]+=m.vals[i][k]*n.vals[k][j];
            }
        }
    }
    return dot_mn;
}
/*矩阵外积*/
matrix outer_matrix(matrix a, matrix b){
    matrix a_fl, b_fl;
    if(a.rows > 1){
        a_fl = flatten_matrix(a);
    }else{
        a_fl = copy_matrix(a);
    }
    if(b.rows > 1){
        b_fl = flatten_matrix(b);
    }else{
        b_fl = copy_matrix(b);
    }    
    return dot_matrix(transpose_matrix(a_fl), b_fl);
}
/*逆矩阵*/
matrix inverse_matrix(matrix m){
    assert(det_matrix(m)!=0);
    matrix inv_m = adjugate_matrix(m);
    
    float scale = 1/det_matrix(m);
    for(int i = 0; i < m.rows; ++i){
        for(int j = 0; j < m.cols; ++j){
            inv_m.vals[i][j] *= scale;
        }
    }
    return inv_m;
}
matrix random_matrix(int rows, int cols){
    assert(rows>0 && cols>0);
    srand((unsigned)time(NULL));
    matrix m = make_matrix(rows, cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            m.vals[i][j]=rand()/100000000;
        }
    }
    return m;
}
/*矩阵范数*/
float norm_matrix(matrix m, int ord){
    assert(m.rows>0 && m.cols>0);
    float Norm_l = 0;
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.cols; ++j)
        {
            Norm_l += powf(fabsf(m.vals[i][j]), ord);
        }
    }
    return powf(Norm_l, (float)1/ord);
}
/*计算Ax=b => x = A^-1·b*/
matrix solve_matrix(matrix m, matrix b){
    assert(m.rows == m.cols && m.rows > 0 && m.cols > 0 && b.rows == m.rows);
    return dot_matrix(inverse_matrix(m),b);
}
matrix copy_matrix(matrix m){
    assert(m.rows > 0 && m.cols > 0);
    matrix m_copy = make_matrix(m.rows, m.cols);
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.cols; ++j)
        {
            m_copy.vals[i][j] = m.vals[i][j];
        }
    }
    return m_copy;
}

/*矩阵的特征值和特征向量*/
matrix *Eigen_matrix(matrix m){
    //检测是否为对称矩阵
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.cols; ++j)
        {
            if (i!=j)
            {
                if (m.vals[i][j] != m.vals[j][i])
                {
                    printf("This matrix is not symmetric matrix\n");
                    assert(m.vals[i][j] == m.vals[j][i]);
                }
            }
        }
    }
    matrix *Eigenvalues_vector = (matrix *)malloc(sizeof(matrix)*2);
    //Jacobi eigenvalue algorithm
    //Step1. 初始化特征值矩阵D 和 单位矩阵 S
    matrix S = identity_matrix(m.rows);
    matrix D = copy_matrix(m);
    float error = 0.00001;
    int flag = 0;
    int iter = 0;
    while(flag == 0){
        float d_ij = 0;
        float d_ii = 0;
        float d_jj = 0;
        float theta = 0;
        int p = 0;//记录最大值位置[p,q]
        int q = 0;
        //Step2. 查找非对角线矩阵元素中的绝对值最大值并记录位置
        for (int i = 0; i < D.rows; ++i)
        {
            for (int j = 0; j < D.cols; ++j)
            {
                if ( i!=j && fabsf(D.vals[i][j]) > d_ij ){
                    d_ij = D.vals[i][j];
                    d_ii = D.vals[i][i];
                    d_jj = D.vals[j][j];
                    p = i;
                    q = j;
                }
            }
        }
        // Step3. Find the rotational angle
        if (d_ii == d_jj)
        {
            if (d_ij > 0)
            {
                theta = pi/4;
            }else{
                theta = -pi/4;
            }
        }else{
            theta = 0.5*atan( 2*d_ij/( d_ii - d_jj ) );
        }
        // Step4. Compute the matrix S1 = [s_pq]
        matrix S1 = identity_matrix(D.rows);
        S1.vals[p][p] = cos(theta);
        S1.vals[q][q] = cos(theta);
        S1.vals[p][q] = -sin(theta);
        S1.vals[q][p] = sin(theta);
        //Step5. Find D = S1^T·D·S1 and S = S·S1
        D = dot_matrix(dot_matrix(transpose_matrix(S1), D), S1);
        S = dot_matrix( S, S1 );
        //Step6. 检测D是否收敛成对角矩阵[lambda]
        float sum = 0;
        for (int i = 0; i < D.rows; ++i)
        {
            for (int j = 0; j < D.cols; ++j)
            {
                if(i != j){
                    sum += D.vals[i][j]*D.vals[i][j];
                }
            }
        }
        if(sqrt(sum) <= error){
            flag = 1;
        }
        iter++;
        printf("sum = %f, iter = %d\n", sqrt(sum), iter);
        //超过迭代数退出循环
        if (iter > 10000)
        {
            break;
        }
    }
    Eigenvalues_vector[0] = D;
    Eigenvalues_vector[1] = S;
    return Eigenvalues_vector;
}
/*sign返回矩阵元素正负号*/
matrix sign(matrix m){
    matrix sign_m = make_matrix(m.rows, m.cols);
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.cols; ++j)
        {
            if (m.vals[i][j] > 0)
             {
                 sign_m.vals[i][j] = 1;
             }else{
                sign_m.vals[i][j] = 0;
                if (m.vals[i][j] < 0)
                {
                    sign_m.vals[i][j] = -1;
                }
             }
        }
    }
    return sign_m;
}
/*QR分解: Q为正交矩阵, R为上三角矩阵*/
matrix *QR_decomposition_matrix(matrix A){
    /*
    return (Q, R) Q为正交矩阵, R为上三角矩阵

    householder反射法
      H = I − 2*v*v^T
        = I - 2(uu^T)/(u^Tu)
        = I - beta*W*W^T
    其中 
      x = A[i:,i] 矩阵的下三角列
      u = x − s||x||e1
      v = u/||u||
      W = u/u1
      beta = −sign*u1/||x||
      sign = 1  when x1>=0;
      sign = -1 when x1<0;

    */
    assert(A.rows > 2 && A.cols > 2);
    matrix *qr = (matrix*)malloc(sizeof(matrix)*2);
    matrix Q = identity_matrix(A.rows);
    matrix R = copy_matrix(A);
    for(int j = 0; j < A.cols-1; j++){
        matrix x = make_matrix( A.rows - j, 1 );
        for (int i = 0; i < A.rows - j; ++i)
        {
            x.vals[i][0] = R.vals[i+j][j];
        }
        float norm_x = norm_matrix(x, 2);
        float alpha = 0;
        if (x.vals[0][0] >= 0)
        {
             alpha = -1;
        }
        if (x.vals[0][0] < 0)
        {
            alpha = 1;
        }

        float u1 = x.vals[0][0] - alpha * norm_x;
        
        if (u1 == 0)
        {
            continue;
        }
        matrix u = scale_matrix(x, 1/u1);
        u.vals[0][0] = 1;
        float beta = -alpha*u1/norm_x;
        matrix outer = outer_matrix(u,u);
        matrix old_R = copy_matrix(R);
        for(int i=0;i<outer.rows;i++){
            for(int c=0;c<R.cols;c++){
                for (int k = 0; k < outer.cols; k++)
                {
                    R.vals[i+j][c] -=  beta*outer.vals[i][k]*old_R.vals[k+j][c];
                }
                
            }
        }
        matrix old_Q = copy_matrix(Q);
        for (int i = 0; i < Q.rows; ++i)
        {
            for (int c = 0; c < outer.cols; ++c)
            {
                for (int k = 0; k < outer.cols; ++k)
                {
                    Q.vals[i][c+j] -= beta*old_Q.vals[i][k+j]*outer.vals[k][c];
                }
            }
        }
        free_matrix(old_R);
        free_matrix(old_Q);
        free_matrix(outer);
        free_matrix(x);
        free_matrix(u);
    }
    qr[0] = Q;
    qr[1] = R;
    return qr;
}
/*导入csv到矩阵*/
matrix csv_to_matrix(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(!fp){
        fprintf(stderr, "Couldn't open file: %s\n", filename);
        exit(0);
    }

    matrix m;
    m.cols = -1;

    char *line;

    int n = 0;
    int size = 1024;
    m.vals = calloc(size, sizeof(float*));
    while((line = fgetl(fp))){
        if(m.cols == -1) m.cols = count_fields(line);
        if(n == size){
            size *= 2;
            m.vals = realloc(m.vals, size*sizeof(float*));
        }
        m.vals[n] = parse_fields(line, m.cols);
        free(line);
        ++n;
    }
    m.vals = realloc(m.vals, n*sizeof(float*));
    m.rows = n;
    return m;
}
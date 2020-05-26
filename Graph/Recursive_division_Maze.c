#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//原理
//1. 首先假设迷宫全是路，在里面画四面墙，把迷宫分割成四个新区域，
//2. 递归地分割下去
//3. 随机选择三面墙打通，这时原本隔开的四个区域又被打通了。然后递归地，在四个新区域内继续设墙分割区域，然后把墙打通，直到不能继续分割才结束。

static const int L=21;
static const int ROUTE=0;
static const int WALL=1;

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
void CreateMaze(int **maze,int x1,int y1,int x2,int y2){
    //判断是否还能继续分割
    if(x2-x1<2||y2-y1<2){
        return ;
    }
    
    //随机取点
    int x=x1+1+rand()%(x2-x1-1);
    int y=y1+1+rand()%(y2-y1-1);
    
    //开始分割
    for(int i=x1;i<=x2;i++) maze[i][y]=WALL;
    for(int i=y1;i<=y2;i++) maze[x][i]=WALL;
 
    //递归分割，继续划分区域
    CreateMaze(maze,x1,y1,x-1,y-1);
    CreateMaze(maze, x+1, y+1, x2, y2);
    CreateMaze(maze,x+1,y1,x2,y-1);
    CreateMaze(maze, x1, y+1, x-1, y2);
    
    //随机取其中的三面墙
    int r[4]={0};
    r[rand()%4]=1;
    
    //在墙上随机取点开孔
    for(int i=0;i<4;i++){
        if(r[i]==0){
            int rx=x;
            int ry=y;
            switch (i) {
                case 0:
                    //判断该位置是否能确保打通相邻两块区域，判断依据，上下左右位置最多只有两面墙，下面一样
                    do{
                        rx=x1+rand()%(x-x1);
                    }while(maze[rx-1][ry]+maze[rx+1][ry]+maze[rx][ry-1]+maze[rx][ry+1]>2*WALL);
                    break;
                case 1:
                    do{
                        ry=y+1+rand()%(y2-y);
                    }while(maze[rx-1][ry]+maze[rx+1][ry]+maze[rx][ry-1]+maze[rx][ry+1]>2*WALL);
                    break;
                case 2:
                    do{
                        rx=x+1+rand()%(x2-x);
                    }while(maze[rx-1][ry]+maze[rx+1][ry]+maze[rx][ry-1]+maze[rx][ry+1]>2*WALL);
                    break;
                case 3:
                    do{
                        ry=y1+rand()%(y-y1);
                    }while(maze[rx-1][ry]+maze[rx+1][ry]+maze[rx][ry-1]+maze[rx][ry+1]>2*WALL);
                    break;
                default:
                    break;
            }
            maze[rx][ry]=ROUTE;
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
    
    //生成迷宫
    CreateMaze(Maze, 1,1, L-2, L-2);
    
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
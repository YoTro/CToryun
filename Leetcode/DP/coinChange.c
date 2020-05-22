#include <stdio.h>
#include <stdlib.h>
#define min(a,b) ( (a)>(b) ? (b):(a) )/*返回最小值*/
#define random(x) (rand()%x)/*随机函数*/
#define INT_MAX 2147483647 /*最大值(随便定义的)*/
int retMin = INT_MAX;/*初始化retMin : 最少硬币数*/

/*逆序数组并从大到小排列*/
int cmpCoin(const void *a, const void *b) {
  int *ap = (int *)a;
  int *bp = (int *)b;

  return *bp - *ap;
}
/*DFS深度遍历+剪枝*/
void coinChange_dfs(int* coins, int coinsSize, int amount, int index, int c) {
  
  /*如果刚好凑够amount*/
  if (amount == 0) {
    retMin = min(c, retMin);
    return;
  }
  /*如果越界则返回*/
  if (index == coinsSize) return;
  
  for (int i = amount / coins[index]; i >= 0 && i+c < retMin; i --) {
    coinChange_dfs(coins, coinsSize, amount - i * coins[index], index+1, c+i);
  }

}
/*主函数
换零钱:用最少的硬币数换刚好的零钱
coins:面额不等的数组
coinsSize: coins数组的大小
amount: 所要交换的目标值总金额
*/
int coinChange(int* coins, int coinsSize, int amount){
  /*
  retMin : 最少硬币数
  */
  retMin = INT_MAX;
  /*如果数组为空,则立马返回-1*/
  if ((coins == NULL) || (coinsSize == 0)) {
    return -1;
  }
  /*如果amount为空,则立马返回0,表示不需要交换*/
  if (amount == 0) {
    return 0;
  }
  /*sorts an array对数组排序*/
  qsort(coins, coinsSize, sizeof(int), cmpCoin);
  /*打印数组*/
  for(int x = 0; x < coinsSize; x++){
    printf("coins = %d\n", coins[x]);
  }
  
  coinChange_dfs(coins, coinsSize, amount, 0, 0);
  /*如果最小硬币数依然等于最大值表示匹配不到零钱,返回-1,否则返回最小值*/
  return (retMin == INT_MAX) ? -1 : retMin;
}

int main()
{
  int coins[]={1,2,5,10,50,100};
  int amount = 17;
  printf("amount = %d\n", amount);
  int coinsSize = sizeof(coins) / sizeof(coins[0]);
  int res;
  res=coinChange(coins, coinsSize, amount);
  printf("res = %d",res);
  return 0;
}
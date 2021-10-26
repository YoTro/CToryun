#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
算法:  归并排序
方法:  先拆分成n个子序列,排序后合并子序列,最后合并成了一个有序数组
原理讲解可参考视频: https://www.bilibili.com/video/BV1Ax411U7Xx
参数:
-num:  数组大小
-m:    随机生成m值范围内的数字
-temp: 临时储存空间
-arr:  原数组
-l:    原数组左边的索引值
-r:    原数组右边索引值
-mid:  原数组中间索引值
-k:    临时数组索引值
*/
#define num 10
#define m 100
int temp[num];
void Mergesort(int *arr, int l, int r){
	if (l == r){
		return;
	}
	int mid = (r+l)>>1;
	Mergesort(arr, l, mid);
	Mergesort(arr, mid+1, r);
	int i = l, k = l, j = mid+1;
	while(i <= mid && j <= r){
		if (arr[i] <= arr[j]){
			temp[k] = arr[i++];
		}else{
			temp[k] = arr[j++];
		}
		k++;
	}
	while(i <= mid){
		temp[k++] = arr[i++];
	}
	while(j <= r){
		temp[k++] = arr[j++];
	}
	for (int i = l; i <= r; i++){
		arr[i] = temp[i];
	}
}
int main()
{
	srand((unsigned) time(NULL));/*随机种子*/
	int n[num];
	for (int i=0;i<num;i++){
		n[i] = rand()%m+i;
		printf("%d\n", n[i]);
	}
	printf("\n");
	Mergesort(n, 0, num-1);
	for (int i=0;i<num;i++){
		printf("%d\n", n[i]);
	}
	return 0;
}
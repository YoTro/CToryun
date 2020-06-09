#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    return (*(int*)a) - (*(int*)b);
}
int max(int a, int b){
    return a>b?a:b;
}
void swap(int *a, int *b)
{
    if (a == b)
        return;
    printf("交换前:%d %d\n", *a, *b);
	int tmp = *a;
	*a = *b;
	*b = tmp;
    printf("交换后:%d %d\n", *a, *b);
    return;
}
//去重
void deduplicate(int *nums, int numsSize)
{
    int i, j, len = numsSize;
    for (i = 0, j = 1; j < len; j++)
    {
        if (nums[j] == nums[i])
            numsSize = numsSize - 1;
        else
        {
            swap(nums+i+1, nums+j);
            i++;
        }        
    }
    return;
}

int longestConsecutive(int* nums, int numsSize){
    if (!numsSize){
        return 0;
    }
    qsort(nums, numsSize, sizeof(int), cmp);
    int *res = (int*)malloc(sizeof(int)*numsSize);
    deduplicate(nums, numsSize);
    int c = 0, count = 0;
    for(int i = 0; i < numsSize; i++){
        if (nums[i]+1 == nums[i+1]){
            c++;
            }
            else{
                c = 0;
            }
            count = max(count, c);
    }
    return count+1;
}

int main(void)
{
    int nums[9] = {1,2,4,3,10,11,12,13,14};
    int numsSize = sizeof(nums)/sizeof(nums[0]);
    int c = longestConsecutive(nums, numsSize);
    printf("%d\n", c);
    return 0;
}
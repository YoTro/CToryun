#include <stdlib.h>
#include <stdio.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize){
    int *q = (int*)malloc(sizeof(int)*numsSize);
    int l = 1;
    int r = 1;
    for(int i = 0; i < numsSize; i++){
        q[i] = 1;
    }
    for(int i=0; i < numsSize; i++){
        
        q[i] *= l;
        l *= nums[i];
    }
    for(int j = numsSize-1; j >= 0; j--){
        q[j] *= r;
        r *= nums[j];
    }
    *returnSize = numsSize;
    return q;
}

int main(void){
    int nums[4] = {2,3,4,5};
    int numsSize = 4;
    int *returnSize = (int*)malloc(sizeof(int));
    int *q = productExceptSelf(nums, numsSize, returnSize);
    printf("除 nums[i] 之外其余各元素的乘积:\n");
    for(int i = 0; i < numsSize; i++){
        printf("%d ", q[i]);
    }
    return 0;
}
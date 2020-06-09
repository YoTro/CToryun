#include <stdlib.h>
#include <stdio.h>
#define Maxsize 1000
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize){
    if (!matrix || matrixSize == 0){
        *returnSize = 0;
        return NULL;
    }
    int left = 0, right = matrixColSize[0] - 1, top = 0, bottom = matrixSize-1;
    int k = 0;
    int *res = (int *)malloc(sizeof(int) * (matrixSize * matrixColSize[0]));
    while (left <= right && top <= bottom){
        for(int i = left; i <= right; i++){
            res[k] = matrix[left][i];
            k++;
        }
        for(int j =  top+1; j <= bottom; j++){
            res[k] = matrix[j][right];
            k++;
        }
        if (left < right && top < bottom){
            for(int i = right-1; i >= left; i--){
                res[k] = matrix[bottom][i];
                k++;
            }
            for(int j = bottom-1; j > top; j--){
                res[k] = matrix[j][left];
                k++;
            }
        }
        left++;
        right--;
        top++;
        bottom--;
    }
    return res;

}

int main(void){
    int a[3][4]={{1,2,3,5},{4,5,6,12},{7,8,9,34}};
    int matrixColSize = sizeof(a[0])/sizeof(int);
    int matrixSize = sizeof(a)/sizeof(a[0]);
    int returnSize = matrixSize*matrixColSize;
    int **matrix = (int **)malloc(sizeof(int*)*Maxsize);
    for(int i = 0; i < Maxsize; i++){
        matrix[i] = (int*)malloc(sizeof(int)*(matrixColSize));
    }
    for(int i = 0; i < matrixSize; i++){
        for(int j = 0; j < matrixColSize; j++){
            matrix[i][j] = a[i][j];
        }
    }
    int *res = spiralOrder(matrix, matrixSize, &matrixColSize, &returnSize);
    for(int i = 0; i < returnSize; i ++){
        printf("%d\n", res[i]);
    }
    free(matrix);
    for(int i = 0; i < Maxsize; i++){
        free(matrix[i]);
    }
    return 0;
}
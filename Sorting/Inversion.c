//
//  Inversion.c
//  Function: get the inversion on array used by mergesort
//
//  Created by Jin on 2020/7/14.
//

#include <stdio.h>
#include <stdlib.h>
#define maxsize 100
int c = 0;
int merge(int a[], int start, int mid, int end, int *ai){
    if(start >= end){
        return 0;
    }
    int coun = 0;
    int i = start, j = mid + 1, k = start;
    while (i <= mid && j <= end){
        if (a[i] <= a[j]){
            ai[k++] = a[i++];
        }else{
            c += mid - i + 1;
            coun += mid - i + 1;
            ai[k++] = a[j++];
        }
    }
    while (i <= mid){
        ai[k++] = a[i++];
    }
    while (j <= end){
        ai[k++] = a[j++];
    }
    for(int i = start; i <= end; i++){
        a[i] = ai[i];//copy sorted array to a
    }
    return coun;
}

int Mergesort(int a[], int start, int end, int *ai){
    if (start < end)
    {
        int mid = (start + end)/2;
        int i = Mergesort(a, start, mid, ai);
        int j = Mergesort(a, mid+1, end, ai);
        int c = merge(a, start, mid, end, ai); //merge all array
        return i+j+c;
    }
    return 0;
}
int main(void){
    int a[] = {2,5,9,4,1,3,8,7,6};
    int *ai = (int*)malloc(maxsize*sizeof(int));
    if(!ai){
        printf("动态申请内存失败！\n"); exit(1); //异常退出
    }
    int l = sizeof(a)/sizeof(int);
    printf("The length of array: %d\n", l);
    int cont;
    cont = Mergesort(a, 0, l-1, ai);
    printf("Inversion is %d, %d\n",c,cont);
    for (int i = 0; i <9;i++){
        printf("%d\n", ai[i]);
    }
    free(ai);
    return 1;
}

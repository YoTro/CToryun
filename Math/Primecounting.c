//Sieve of Eratosthenes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

typedef struct{
	int first;
	int last;
}primeargs;

float *result;
unsigned long long int Prime(unsigned long long int n){
	if (n < 2){
		return 0;
	}
	unsigned long long int notprimenumber = 0;
	//初始化为0
	bool *isPrime = (bool*)calloc(n+1, sizeof(bool));
	if(!isPrime){
		printf("The memory can't allocate any space\n");
		exit(1);
	}
	for(int i = 2; i < sqrt(n)+1;i++){
		if (!isPrime[i]){
			for (int j = i*i;j < n+1; j += i){
				if(!isPrime[j]){
					isPrime[j] = 1;
					notprimenumber++;
				}
			}
		}
	}
	free(isPrime);
	isPrime = NULL;
	return n - notprimenumber - 1;
}

void Primerate(){
	clock_t start2 = clock();
	for (int i = 1; i < 10; i++){
		unsigned long long int primenumber = Prime((unsigned long long int  )pow(10, i));
		printf("%5f\n", primenumber/pow(10, i));
	}
	clock_t end2 = clock();
	double t2 = (double)(end2 - start2)/CLOCKS_PER_SEC;
	printf("The singlethread prime counting used time is %5fs\n", t2);
}

void* multithreadPrime(void* args){
	primeargs* pargs = (primeargs*) args;
	int first = pargs->first;
	int last = pargs->last;
	for (int i = first; i < last; i++){
		unsigned long long int primenumber = Prime((unsigned long long int)pow(10, i));
		float s = primenumber/pow(10, i);
		result[i-1] = s;
	}
	return NULL;
}
void printList(float *result0, int size){
	for (int i = 0; i < size; i++){
		printf("%5f\n", result0[i]);
	}
}
int main(void){
	//unsigned long long int的最大值为 18,446,744,073,709,551,615
	unsigned long long int n = pow(10, 8);
	clock_t start0 = clock();
	unsigned long long int m = Prime(n);
	clock_t end0 = clock();
	double t0 = (double)(end0 - start0)/CLOCKS_PER_SEC;
	printf("Total numbers of prime: %llu\nThe counting used time is %5fs\n", m, t0);
	pthread_t th1, th2;
	result = (float*)malloc(9*sizeof(float));
	Primerate();
	primeargs args1, args2;
	args1.first = 0;
	args1.last = 5;
	args2.first = 5;
	args2.last = 10;
	clock_t start1 = clock();
	pthread_create(&th1, NULL, multithreadPrime, &args1);
	pthread_create(&th2, NULL, multithreadPrime, &args2);
	//wait
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	clock_t end1 = clock();
	double t1 = (double)(end1 - start1)/CLOCKS_PER_SEC;
	printList(result, 9);
	printf("The multithread prime counting used time is %5fs\n", t1);
	free(result);
	result = NULL;
	return 0;
}
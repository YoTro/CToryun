//Sieve of Eratosthenes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

unsigned long long int Prime(unsigned long long int n){
	unsigned long long int notprimenumber = 0;
	bool *isPrime = (bool*)calloc(n+1, sizeof(bool));
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
	for (int i = 1; i < 28; i++){
		unsigned long long int primenumber = Prime((unsigned long long int )pow(10, i));
		printf("%5f\n", primenumber/pow(10, i));
	}
}
int main(void){
	unsigned long long int n = 13;
	clock_t start = clock();
	unsigned long long int m = Prime(n);
	clock_t end = clock();
	double t0 = (double)(end - start)/CLOCKS_PER_SEC;
	printf("Total numbers of prime: %llu\nThe counting used time is %5fs\n", m, t0);
	Primerate();
	return 0;
}
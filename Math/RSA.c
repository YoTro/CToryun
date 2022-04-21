#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>

/*Sieve of Eratosthenes*/
unsigned long long int *Prime(void){
	unsigned long long int *result = (unsigned long long int *)malloc(sizeof(unsigned long long int)*3);
	srand((unsigned) time(NULL));
	unsigned long long int n = 1024;//rand()%INT_MAX;
	if (n < 2){
		return 0;
	}
	unsigned long long int p = 4,q = 4;
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
				}
			}
		}
	}

	while(isPrime[p] != 0 || isPrime[q] != 0 ){
		p = rand()%n+1;
		q = rand()%n+1;
	}
	free(isPrime);
	isPrime = NULL;
	result[0] = p;
	result[1] = q;
	return result;
}
/*是否互素*/
int coprime(unsigned long long int a, unsigned long long int b){
	unsigned long long int temp = 0;
	if (a < b)
	{
		temp = a;
		a = b;
		b = temp;
	}
	unsigned long long int r;
	//辗转相除法
	while(b != 0){
		r = b;
		b = a%b;
		a = r;
		if (b == 1)
		{
			return 1;//互质
		}
	}
	return b;
}
/*最大公因数Greatest common divisor*/
unsigned long long int gcd(unsigned long long int a, unsigned long long int b) {
	if(b) while((a %= b) && (b %= a));
	return a + b;
}
/*最大公倍数Least common multiple*/
unsigned long long int lcm(unsigned long long int a, unsigned long long int b) {
	return a * b / gcd(a, b);
}

unsigned long long int inverse_modular(unsigned long long int a, unsigned long long int n){
	//扩展欧几里得算法
	for (int i = 1; i < n; ++i){
		if (((a%n) * (i%n)) % n == 1){
			return i;
		}
	}
	return 0;
}
unsigned long long int *prive_public_keys(){
	
	unsigned long long int *keys = (unsigned long long int *)malloc(sizeof(unsigned long long int)*3);
	unsigned long long int *result = Prime();
	unsigned long long int N = result[0]*result[1];
	unsigned long long int r = lcm(result[0] - 1, result[1] - 1);
	unsigned long long int d = 2;
	unsigned long long int e;
	for (e = 1;e<r;e++){
		if (coprime(e, r) == 1)
		{
			d = inverse_modular(e, r);
			break;
		}
	}
	keys[0] = N;
	keys[1] = e;
	keys[2] = d;
	free(result);
	return keys;
}
/*模意义下取幂, 大数幂存储和计算*/
unsigned long long int bigpow(unsigned long long int a, unsigned long long int p, unsigned long long int c){
	/*
	math:
		\begin{eqnarray}
		a^p \ mod \ x & = & a^{bin(p)} mod \ x \\
		& = & a^{n_{t}2^{t} + n_{t-1}2^{t-1} \cdots n_{0}2^{0}} mod \ x\\
		 3^{17} \ mod \ 5 & = & 3^{(1101)_{2}} mod \ 5 \\
		& = & 3^{1\cdot2^{3} + 1\cdot2^{2} + 0\cdot2^{1} + 1\cdot2^{0}} mod \ 5 \\
		& = & 3^{8} \cdot 3^{4} \cdot 3^{1} mod \ 5 \\
		\end{eqnarray}
	*/
	assert(c > 0 );
	unsigned long long int ans = 1;
	if (p == 0 && c == 1)
	{
		return 0;
	}
	a %= c;
	while(p>0){
		if (p & 1)//p为奇数 => 二进制位数字是1
		{
			ans = ans * a % c;
		}
		a = a * a % c;
		p >>= 1;
	}
	return ans;
}
unsigned long long int *RSA(char *s, unsigned long long int *public_keys){
	unsigned long long int N = public_keys[0];
	unsigned long long int e = public_keys[1];
	unsigned long long int *c = (unsigned long long int *)malloc(N*sizeof(unsigned long long int));
	unsigned long long int i = 0;
	printf("Resource ascii RSACODE\n");
	printf("======================\n");
	while(s[i] != '\0')
	{
		c[i] = bigpow(s[i], e, N);
		printf(" %c       %d       %llu  \n", s[i], s[i], c[i]);
		i++;
	}
	return c;
}

unsigned long long int *decode_RSA(unsigned long long int *c, unsigned long long int *prive_keys){
	unsigned long long int N = prive_keys[0];
	unsigned long long int d = prive_keys[1];
	unsigned long long int *n =  (unsigned long long int *)calloc(N, sizeof(unsigned long long int));
	for (int i = 0; i < N; ++i)
	{
		n[i] = bigpow(c[i], d, N);
		printf("%c ", (char)n[i]);
		if (n[i] == 00)
		{
			break;
		}
	}
	return n;
}
int main(int argc, char const *argv[])
{
	char *s = "Hello, the world\n";
	unsigned long long int *result = prive_public_keys();
	printf("公钥和密钥: N = %llu, e = %llu, d = %llu\n", result[0], result[1], result[2]);
	unsigned long long int public_keys[] = {result[0], result[1]};
	unsigned long long int prive_keys[] = {result[0], result[2]};
	unsigned long long int *c = RSA(s, public_keys);
	printf("\n");
	unsigned long long int *n = decode_RSA(c, prive_keys);
	free(result);
	free(c);
	free(n);
	return 0;
}
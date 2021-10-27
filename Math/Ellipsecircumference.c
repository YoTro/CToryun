#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.141592653589793

/*
计算椭圆周长的4种公式
1. p ≈ 2π√[(a^2 + b^2)/2]                                           (a<=3b, error: 5%)
2. p ≈ π{3(a+b) - √[(3a+b)(a+3b)]}                                  (拉马努金, error:1/10^5)
3. p = 2aπ(1 - ∑(∞,i=1){{[(2i)!^2]/[(2^i)(i!)]^4}[(e^2i)/(2i - 1)]} (e: 偏心率)
4. p = π(a+b)∑(∞, n=0)[(0.5, n)^2](h^n)                             ((0.5, n)^2半整数阶乘的二项式系数)
参数：
-c:  椭圆周长
-a:  椭圆长轴长度
-b:  椭圆短轴长度
-pi: π
-e:  椭圆离心率
-h: 
*/ 

double *p(double *c, double a, double b){
	c[0] = 2*pi*sqrt((a*a+b*b)/2);
	c[1] = pi*(3*(a+b) - sqrt((3*a+b)*(a+3*b)));
	double e  = sqrt(a*a - b*b)/a;
	c[2] = 2*a*pi*(1 - (1/4)*pow(e, 2) - (9/64)*pow(e, 4)/3 - ((15*15)/(48*48)*pow(e, 6)/5));
	double h  = ((a - b)*(a - b))/((a + b)*(a + b));
	c[3] = pi*(a+b)*(1 + (h/4) + (pow(h, 2)/64 + pow(h, 3)/256 + 25*pow(h, 4)/16384));
	return c;
}

int main(void)
{
	double a = 10.0, b = 0.0;
	double c[4];
	double *t = p(c, a, b);
	for (int i = 0;i<4;i++){
		printf("%f, ", t[i]);
	} 
	return 0;
}
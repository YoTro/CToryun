#include <stdio.h>

/*https://web.archive.org/web/20150511044204/http://www.daxia.com/bibis/upload/406Fast_Inverse_Square_Root.pdf*/
float Q_rsqrt( float number )
{
	
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking（对浮点数的邪恶位元hack）
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?（这他妈的是怎么回事？）
	y  = * ( float * ) &i;
	float error = 1;
	while(error > 0.000001){
		float y_old = y;
		y  = y * ( threehalfs - ( x2 * y * y ) );   // Newton iteration （牛顿迭代）
		error = y - y_old;
	}
	return y;
}
int main(int argc, char const *argv[])
{
	float i = 4;
	
	printf("%f\n", Q_rsqrt(i));
	return 0;
}
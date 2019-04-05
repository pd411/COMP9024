#include <stdio.h>

#define MIN 10000
#define MAX 25000

int main(int argc, char const *argv[])
{
	int a,b,c,d,e;
	int four_times;
	int f_a,f_b,f_c,f_d,f_e;
	for (int i = MIN; i < MAX; ++i)
	{
		a = (i/10000);
		b = (i/1000)%10;
		c = (i/100)%10;
		d = (i/10)%10;
		e = (i%10);
		if (i * 4 == 10000*e + 1000*d + 100*c + 10*b + a)
		{
			printf("%d\n", i);
			break;
		}
	}
}
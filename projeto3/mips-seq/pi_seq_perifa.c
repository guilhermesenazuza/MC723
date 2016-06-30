#include<stdio.h>
#include<stdlib.h>

#define RAND_ADDRESS 0x6440000;
volatile int *randNum = (volatile int *) RAND_ADDRESS;

long long unsigned int monte_carlo_pi(unsigned int n) {
	long long unsigned int in = 0, i;
	double x, y, d;

	for (i = 0; i < n; i++) {
		x = ((*randNum % 1000000)/500000.0)-1;
		//printf("%d\n", *randNum);
		y = ((*randNum % 1000000)/500000.0)-1;
		d = ((x*x) + (y*y));
		if (d <= 1) in+=1;
	}

	return in;
}

int main(void) {
	int size;
	unsigned int n, i;
	long long unsigned int in;
	double d, pi, x, y;
	
	n = 100000;

	//srand (time(NULL));
	*randNum = 598;

	in = monte_carlo_pi(n);

	pi = 4*in/((double)n);
	printf("%lf\n",pi);

	return 0;
}

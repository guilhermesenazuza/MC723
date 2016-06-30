#include<stdio.h>
#include<stdlib.h>

#define ITERATION_ADDRESS 0x6450000;
volatile int *result = (volatile int *) ITERATION_ADDRESS;


long long unsigned int monte_carlo_pi(unsigned int n) {
	long long unsigned int in = 0, i;
	double d;

	for (i = 0; i < n; i++) {
		d = *result;
//		printf("%f", d);
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

	srand (time(NULL));

	in = monte_carlo_pi(n);

	pi = 4*in/((double)n);
	printf("%lf\n",pi);

	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#define ADDRESS 0x6410000;
#define RAND_ADDRESS 0x6440000;


volatile int procCounter = 0;
#define CORES 2

volatile int done=0;
volatile int *lock = (volatile int *) ADDRESS;
volatile int *randNum = (volatile int *) RAND_ADDRESS;
void AcquireLock() {
	while (*lock);
}

void ReleaseLock() {
	*lock = 0;
}

long long unsigned int monte_carlo_pi(unsigned int n, int procNumber) {
	AcquireLock();
	printf("CORE %d\n", procNumber);
	ReleaseLock();
	int in = 0, i;
	float x, y, d;
        int limit;
	
        limit = n*(procNumber + 1)/CORES;
	if (procNumber == CORES - 1) {
		//ultimo core, faz o resto
		limit = n;
	}
	
	
	for (i = n*procNumber/CORES; i < limit; i++) {
		x = ((*randNum % 1000000)/500000.0)-1;
		y = ((*randNum % 1000000)/500000.0)-1;
		//x = 1;
		//y = 2;
		d = ((x*x) + (y*y));
		//AcquireLock();
		if (d <= 1.0) {
		  in+=1;
		}
		//ReleaseLock();
	}
	

	return in;
}

long long unsigned int results[CORES];

int main(void) {

	int procNumber;
	AcquireLock();
	procNumber = procCounter++;
	//printf("got lock\n");
	ReleaseLock();
	int size;
	unsigned int n, i;
	long long unsigned int in = 0;
	double d, pi, x, y;


	n = 100;

	//srand (time(NULL));
	*randNum = 100;
	//in = monte_carlo_pi(n);
	
	for(i = 0; i < CORES; i++) {
	  if(i == procNumber) {
	    results[i] = monte_carlo_pi(n, i);
	    AcquireLock();
	    done++;
	    ReleaseLock();
	  }
	}
	/*

	if (procNumber == 0) {
	  printf("PRJOCCJCJ\n");
	  while(done < CORES);
	  for (i=0; i < CORES; i++) {
	    in += results[i];
	  }
	  pi = 4*in/((double)n);
	  printf("%lf\n",pi);
	}
	AcquireLock();
	printf("OI\n");
	ReleaseLock();


	*/
	return 0;
}

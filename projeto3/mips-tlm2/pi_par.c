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

void setSeed(int seed) {
	*randNum = seed;
}

int getRandomNumber() {
	return *randNum;
}

int monte_carlo_pi(unsigned int n, int procNumber) {
	AcquireLock();
	printf("CORE %d\n", procNumber);
	ReleaseLock();
	int in = 0, i;
	int x, y, d;
        int limit;
	
        limit = n*(procNumber + 1)/CORES;
	if (procNumber == CORES - 1) {
		//ultimo core, faz o resto
		limit = n;
	}
	
	
	for (i = n*procNumber/CORES; i < limit; i++) {
		//x = ((*randNum % 1000000)/500000.0)-1;
		x = (((getRandomNumber() % 1000000)/500000)-1)*10;
		y = (((getRandomNumber() % 1000000)/500000)-1)*10;
		//y = ((*randNum % 1000000)/500000.0)-1;
		//x = 1;
		//y = 2;
		d = ((x*x) + (y*y));
		//AcquireLock();
		
		if (d <= 10) {
		  in+=1;
		}
		//ReleaseLock();
	}
	AcquireLock();
	printf("IN: %d\n", in);
	ReleaseLock();
	return in;
}

int results[CORES];

void g() {

	int procNumber;
	AcquireLock();
	procNumber = procCounter++;
	//printf("got lock\n");
	ReleaseLock();
	int size;
	unsigned int n, i;
	int in = 0;
	int d, pi, x, y;


	n = 1000000;

	//srand (time(NULL));
//	*randNum = 100;
	setSeed((int)time(NULL));
	//in = monte_carlo_pi(n);
	
	for(i = 0; i < CORES; i++) {
	  if(i == procNumber) {
	    results[i] = monte_carlo_pi(n, i);
	    AcquireLock();
	    done++;
	    ReleaseLock();
	  }
	}
	AcquireLock();
	if (procNumber == 0) {
	  while(done < CORES);
	  for (i=0; i < CORES; i++) {
	    in += results[i];
	  }
	  in *= 1000;
	  pi = 4*in/n;
	  //AcquireLock();
	  printf("Resposta in: %d\n",pi);
	  //ReleaseLock();
	} else {
	  printf("SOU O CORE %d\n", procNumber);
	}
	ReleaseLock();

}

int main(void) {

	g();	


	
	return 0;
}

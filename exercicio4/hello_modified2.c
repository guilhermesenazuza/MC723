#include <stdio.h>
#include <stdlib.h>

#define PERIPHERAL_BASE_ADDRESS 0x6400000

int main() {

	volatile int *base = (volatile int *)PERIPHERAL_BASE_ADDRESS;
	*base = 1; 

  while(*base < 5)
	 printf("Base content: %d\n", *base++);
	 
	return 0;
}

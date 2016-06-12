#include <stdio.h>
#include <stdlib.h>

#define PERIPHERAL_BASE_ADDRESS 0x6400000

int main() {

	int *base = (int *)PERIPHERAL_BASE_ADDRESS;
	*base = 1; 

	printf("Base content: %d\n", *base);
	return 0;
}



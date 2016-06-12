#include <stdio.h>
#include <stdlib.h>

#define PERIPHERAL_BASE_ADDRESS 0x6400000

int main() {

	int *lock = (int *)PERIPHERAL_BASE_ADDRESS;
	*lock = 1; 

	printf("! %d !\n", *lock);
	return 0;
}



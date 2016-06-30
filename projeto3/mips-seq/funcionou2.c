#include <stdio.h>
#include <string.h>
#define ADDRESS 0x6410000;

volatile int procCounter = 0;

#define THREAD_NUM 2

volatile int *lock = (volatile int *) ADDRESS;

int hist[26];
volatile int done=0;
void AcquireLock() {
//	printf("LOCK %d\n", *lock);
	while (*lock);
//	printf("PASSEI\n");
}

void ReleaseLock() {
//	printf("RELEASING LOCK\n");
	*lock = 0;
//	printf("TESTE\n");

}

int main() {
	int procNumber;
	AcquireLock();
	procNumber = procCounter;
	procCounter++;	
	ReleaseLock();
		
	int vet[20];
	//char *str = "abcdefgdfddfsdffdsfssfdsfasdaaqeqwa\0";
	char *str = "noqncjueyuirytcnbcnbvbbvaasoaospasskaposkderyuwetuygbcbchjbvhvgegwgccyvwytynbcvpqwiufyqamxbchkz\0";
	int n = strlen(str);
	//int n = sizeof(str)/sizeof(char);
	//printf("%s e %d\n", str, n);
	int i,j,k;
	//for (i = 0; i < 20; i++) vet[i] = i;
	if (procNumber == 0) {
		for (i=0; i < n/2; i++) {
			int num = str[i] - 'a';
			AcquireLock();
			hist[num]++;
			ReleaseLock();
		}
	AcquireLock();
	done++;
	ReleaseLock();
	}
	
	
	else if (procNumber == 1) {
		for (i=n/2; i < n; i++) {
			int num = str[i] - 'a';
			AcquireLock();
			hist[num]++;
			ReleaseLock();
		}
		AcquireLock();
		done++;
		ReleaseLock();
	}
	if (procNumber == 0) {
		while(done < 2);	
		for (i = 0; i < 26; i++) {
			printf("%d ", hist[i]);
		}
		printf("\n done\n");
	}
	return 0;
}

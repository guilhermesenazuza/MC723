#include <stdio.h>
#include <string.h>

#define SIZE 26


int main() {

	   //input
    //input size
    int n = strlen(str);
    int i;

    int hist[SIZE];
    for (i=0; i < SIZE;i++)
        hist[i] = 0;
    for (i =0; i < n; i++){
        int num = str[i] - 'a';
        hist[num]++;
    }

    for (i = 0; i < SIZE; i++) {
        printf("%d ", hist[i]);
    }
    printf("\ndone!\n");

return 0;
}
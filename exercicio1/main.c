//
//  main.c
//  Exercício1
//
//  Created by Pedro Rodrigues Grijó on 3/4/16.
//  Copyright © 2016 Pedro Rodrigues Grijó. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int primo(int n)
{
    int i;
    
    for(i = 2; i < n; i ++)
        if (n % i == 0)
            return 0;
    
    return 1;
}
int main(int argc, char *argv[])
{
    int n = atoi(argv[1]); 
    int i, prime_counter = 0;
    
    
    #pragma omp parallel for
    for (i = 2; i <= n; i++) {
        
        if (i%2 || i==2)
            if (primo(i))
				#pragma omp atomic
                prime_counter++;
    }
    
    printf("Quantidade de primos: %d\n", prime_counter);

    return 0;
}



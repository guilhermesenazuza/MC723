# Relatório Exercício 2                                                                   

#### Pedro Rodrigues Grijó
#### 139715

## Introdução
O objetivo deste exercício foi definir, através de simulação com o uso do software DineroIV, qual a melhor configuração de cache para um trace de execução. O trace de execução utilizado foi 178.galgel.m2b, e seu tamanho foi reduzido de 101 para 20.

## Análise

#### Observações iniciais

Ambos os caches (L1 e L2) foram analisados seguindo o procedimento a seguir:
primeiramente foram fixados os parâmetros tamanho do bloco, associatividade, fetch policy e replacement policy. Com estes parâmetros fixados, foram testados diversos tamanhos para as caches, sendo escolhido aquele mais satisfatório. Após escolhido o tamanho, este foi fixado e o mesmo procedimento foi realizado para o tamanho do bloco, ou seja, um parâmetro é fixado por cada fase de iteração dos testes, para que possa ser descoberto o valor ótimo/satisfatório do parâmetro para a próxima iteração.

#### Cache L1
Fixado o tamanho do bloco em 8 B, associatividade 1, fetch policy demand e replacement policy LRU, foram testados tamanhos para a cache L1.

![](/exercicio2/graphs/miss-rate-cache-size.png "")

Cache L1 escolhido: 64 KB (32 KB p/ instrução e 32 KB p/dados), pois é um valor que representa processadores relativamente atuais, como os das máquinas do Instituto de Computação da UNICAMP. O processador do computador utilizado é um Intel(R) i5-4590 3.30GHz, com cache L1 de 64 KB, blocos de 64 B e cache L2 de 256 KB 
O tamanho dos caches foi descoberto com o comando $lscpu, e o tamanho dos blocos de L1 com o comando $less /proc/cpuinfo

Fixado o tamanho da cache em 64 KB, associatividade 1, fetch policy demand e replacement policy LRU, foram testados tamanhos para o bloco da cache L1.

![](/exercicio2/graphs/miss-rate-block-size.png "")

O tamanho do bloco escolhido para L1 foi 64B, pois é o block size da máquina testada. Após este tamanho a quantidade de misses não diminuiu consideravelmente.

Fixado o tamanho da cache 64 KB, tamanho do bloco 64 B, fetch policy demand e replacement policy LRU, foram testadas associatividades da cache L1.

![](/exercicio2/graphs/miss-rate-associativity.png "")

O melhor valor para associatividade foi 4 que é um valor razoável considerando os processadores e seus caches L1 da atualidade. Este foi o valor escolhido

![](/exercicio2/graphs/miss-rate-fetch-policy.png "")

![](/exercicio2/graphs/miss-rate-replacement-policy.png "")

![](/exercicio2/graphs/miss-rate-cache-l2-size.png "")

![](/exercicio2/graphs/miss-rate-cache-l2-block-size.png "")

![](/exercicio2/graphs/miss-rate-cache-l2-associativity.png "")

![](/exercicio2/graphs/miss-rate-cache-l2-fetch-policy.png "")

![](/exercicio2/graphs/miss-rate-cache-l2-replacement-policy.png "")





### Cache L2

O melhor valor para o tamanhao foi cache de 2MB, mas como não é um tamanhao de cache L2 encontrando nos processadores atuais mais comuns, o valor escolhido foi de 256KB


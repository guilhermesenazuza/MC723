# Projeto 3: Multicore e Aceleração em Hardware

#### Equipe
- 139455 - Gabriel Bueno de Oliveira
- 136242 - João Guilherme Daros Fidelis
- 137036 - Matheus Figueiredo
- 139715 - Pedro Rodrigues Grijó

## Introdução
Neste projeto, foi modelado um sistema com múltiplos cores e executado programa o [pi_par.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/pi_par.c). Este programa é uma modificação de [pi_seq.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/pi_seq.c). As modificações foram feitas com o intuito de paralelizar a execução do programa original. Além disto, o módulo de hardware extra [pi_seq_perifa.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/pi_seq_perifa.c) foi criado para acelerar o desempenho deste programa.

## Metodologia

Inicialmente um [roteiro](https://github.com/pedrogrijo/MC723/blob/master/projeto3/ROTEIRO.md) foi criado para definir os passos para realização do projeto e o cronograma do mesmo. Porém, após dificuldades com o programa [poisson_openmp.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/poisson_openmp.c) [1], decidimos descartar o roteiro original e usar o calculador de pi [pi_seq.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/pi_seq.c), desenvolvido pelo aluno João Guilherme Daros Fidélis na disciplina MC970 - Introdução à Programação Paralela. Partindo desse programa foi criada a versão paralelizada [pi_seq.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/pi_par.c). 

## Análise e Resultados

## Conclusão

## Referências
1. https://people.sc.fsu.edu/~jburkardt/c_src/poisson_openmp/poisson_openmp.c

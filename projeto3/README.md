# Projeto 3: Multicore e Aceleração em Hardware

#### Equipe
- 139455 - Gabriel Bueno de Oliveira
- 136242 - João Guilherme Daros Fidelis
- 137036 - Matheus Figueiredo
- 139715 - Pedro Rodrigues Grijó

## Introdução
Neste projeto, foi modelado um sistema com múltiplos cores e executado programa o [poisson.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/poisson.c). Este programa é uma modificação de [poisson_openmp.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/poisson_openmp.c) [1]. As modificações foram feitas com o intuito de paralelizar a execução do programa original. Além disto, o módulo de hardware extra [act_tlm_peripheral2.cpp](https://github.com/pedrogrijo/MC723/blob/master/projeto3/act_tlm_peripheral2.cpp) foi criado para acelerar o desempenho deste programa.

## Metodologia

[Roteiro](https://github.com/pedrogrijo/MC723/blob/master/projeto3/ROTEIRO.md)

## Análise e Resultados

## Conclusão

## Referências
1. https://people.sc.fsu.edu/~jburkardt/c_src/poisson_openmp/poisson_openmp.c


------------------------
## Otimização
Para otimização escolhemos melhorar o desempenho da função de floating point, já que é muito utilizada no software que escolhemos.

## Ganho de desempenho
Para medirmos ganho de desempenho serão mensuradas:
- tempo
- ciclos
- número de instruções

## Experimentos
Serão variados os parâmetros NX e NY da aplicação escolhida e executada em 1,2,4 *cores*.
- Experimento 1: 1 Core, NX,NY = 30
- Experimento 2: 2 Cores, NX,NY = 30
- Experimento 3: 4 Cores, NX,NY = 30
- Experimento 4: 1 Core, NX,NY = 161
- Experimento 5: 2 Cores, NX,NY = 161
- Experimento 6: 4 Cores, NX,NY = 161
- Experimento 7: 1 Core, NX,NY = 260
- Experimento 8: 2 Cores, NX,NY = 260
- Experimento 9: 4 Cores, NX,NY = 260

## Cronograma
- Semana 1: Escolhas iniciais serão definidas.
- Semana 2: Modificações no código para otimizar a função e mudança no código para paralelizarmos a aplicação no mips.
- Semana 3: Fim das implementações, execução dos testes e análise dos resultados.

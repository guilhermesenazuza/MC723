# Roteiro Experimento 3
* Gabriel Bueno de Oliveira       ra.139455 
* Matheus Figueiredo              ra:137036
* Pedro Grijó                     ra:139715
* João Guilherme Daros Fidelis    ra:136242 

------------------------
## Software
Utilizaremos o software poisson que pode ser obtido no seguinte site:
https://people.sc.fsu.edu/~jburkardt/c_src/poisson_openmp/poisson_openmp.c

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

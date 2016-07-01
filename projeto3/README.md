# Projeto 3: Multicore e Aceleração em Hardware

#### Equipe
- 139455 - Gabriel Bueno de Oliveira
- 136242 - João Guilherme Daros Fidelis
- 137036 - Matheus Figueiredo
- 139715 - Pedro Rodrigues Grijó

## Introdução
Neste projeto, foi modelado um sistema com múltiplos cores e foram executados os programas [pi seq](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-tlm2/pi_seq.c), [pi paralelo](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-4core/pi_par.c), [pi seq. periférico](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-seq-newperif/pi_seq_perifa.c) e [pi seq. novo perif.](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-seq-newperif/pi_seq_newperifa.c). O programa original é [pi_seq](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-tlm2/pi_seq.c), todos os outros são modificações dele. As modificações foram feitas com o intuito de paralelizar a execução do programa original e acelerar o seu desempenho. Para isso, foi criado o módulo de hardware extra [periférico acelerado](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-seq-newperif/ac_tlm_peripheral.cpp).

## Metodologia

Inicialmente um [roteiro](https://github.com/pedrogrijo/MC723/blob/master/projeto3/ROTEIRO.md) foi criado para definir os passos para realização do projeto e o cronograma do mesmo. Porém, após dificuldades com o programa [poisson_openmp](https://github.com/pedrogrijo/MC723/blob/master/projeto3/poisson_openmp.c) [1], decidimos descartar o roteiro original e usar o calculador de pi [pi_seq](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-tlm2/pi_seq.c), desenvolvido pelo aluno João Guilherme Daros Fidélis na disciplina MC970 - Introdução à Programação Paralela.  As particularidades desse programa e dos outros 3 criados a partir dele são:

* [pi_seq.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-tlm2/pi_seq.c): Código original sequencial, sem uso do [periférico original](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-tlm2/ac_tlm_peripheral.cpp) para aceleração.
* [pi_seq_perifa.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-seq-newperif/pi_seq_perifa.c): Modificação do programa anterior para usar o [periférico original](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-tlm2/ac_tlm_peripheral.cpp) para aceleração.
* [pi_par.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-4core/pi_par.c)(2 e 4 cores): Versão paralelizada de [pi_seq.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-tlm2/pi_seq.c). Esta versão foi executada com 2 e 4 cores. Para isso, o programa [main.cpp](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-4core/main.cpp) foi modificado para instanciar 2 e 4 cores em cada caso. Foi rodado usando o [periférico original](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-tlm2/ac_tlm_peripheral.cpp)
* [pi_seq_newperifa.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-seq-newperif/pi_seq_newperifa.c): Modificação de [pi_seq.c](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-tlm2/pi_seq.c) para usar o [periférico acelerado](https://github.com/pedrogrijo/MC723/blob/master/projeto3/mips-seq-newperif/ac_tlm_peripheral.cpp)

Para cada um dos 4 programas foram feitos 5 testes. Os parâmetros medidos em cada teste foram: 
* **#instructions**: número de instruções executadas pelo simulador mips
* **pi aproximation**: aproximação calculada para o valor de pi
* **temp user**:  tempo de execução do programa. Foi usado user time, que é o tempo de CPU gasto em modo usuário.

### Otimização
Para a primeira otimização foi introduzido apenas um periférico que realizava a operação mais utilizada no corpo do código, no nosso caso a multiplicação de números longos.
 Para a segunda e terceira execução foi inserida a plataforma multicores, com 2 e 4 cores respectivamente e também alteramos os tipos das variáveis de *unsigned long long int*  para *int*  a fim de melhorar o desempenho do mips nas multiplicações de tipos longos.
 Por fim, a última otimização proposta foi a criação de um novo periférico que além de realizar as operações e as alterações de tipo também realiza-se grande parte do algoritmo de calculo de pi.

Após os 5 testes, a média de cada resultado foi calculada para comparação entre os programas e periféricos utilizados.
  

## Análise e Resultados
Executamos os testes e obtivemos os seguintes resultados.
<br/>

|                 | pi seq.         | pi seq.  periférico | pi paralelo (2cores) | pi paralelo (4cores) | pi seq. novo perif. | 
|-----------------|---------------------|----------------------|----------------------|---------------------|----------| 
| #instructions   | 415580929           | 406041536            | 39774757             | 39825072            | 17808886 | 
| pi aproximation | 3.1382              | 3.1328               | -                    | -                   | 3.5896   | 
| temp user       | 27.37               | 26.52                | 2.15                 | 2.52                | 1.73     | 
| #instructions   | 415568650           | 406041536            | 39774757             | 39825072            | 17808886 | 
| pi aproximation | 3.13164             | 3.1328               | -                    | -                   | 3.5896   | 
| temp user       | 27.12               | 26.45                | 2.12                 | 3.65                | 2.01     | 
| #instructions   | 415571997           | 406041536            | 39774757             | 39825072            | 17808886 | 
| pi aproximation | 3.1472              | 3.1328               | -                    | -                   | 3.5896   | 
| temp user       | 27.58               | 26.49                | 2.26                 | 3.64                | 1.2      | 
| #instructions   | 415526974           | 406041536            | 39774757             | 39825072            | 17808886 | 
| pi aproximation | 3.13224             | 3.1328               | -                    | -                   | 3.5896   | 
| temp user       | 27.24               | 26.85                | 3.06                 | 3.65                | 1.2      | 
| #instructions   | 415542553           | 406041536            | 39774757             | 39825072            | 17808886 | 
| pi aproximation | 3.13716             | 3.1328               | -                    | -                   | 3.5896   | 
| temp user       | 27.11               | 27.98                | 3.06                 | 3.42                | 1.26     | 


| averages        | pi seq.     | pi seq.  periférico | pi paralelo (2cores) | pi paralelo (4cores) | pi seq. novo perif. | 
|-----------------|-------------|---------------------|----------------------|----------------------|---------------------| 
| #instructions   | 415558220.6 | 406041536           | 39774757             | 39825072             | 17808886            | 
| pi aproximation | 3.137288    | 3.1328              | -                    | -                    | 3.5896              | 
| temp user       | 27.284      | 26.858              | 2.53                 | 3.376                | 1.48                | 

Não conseguimos obter o valor da aproximação de pi para a execução multicore devido a presença de um bug no simulador onde a presença do print que exibia a aproximação de pi atrapalhava a simulação, devido a isso os valores para a aproximação nestes casos não foram obtidas. 
Ao análisar o número de instruções obtivemos uma grande discrepância das duas primeira simulações (pi seq. e pi seq. periférico) das demais,como pode ser observado na primeira imagem abaixo, isso se dá principalmente devido ao fato de termos alterarmos os tipos dos dados de *long long unsigned* para *unsigned int* nas simulações de pi paralelo(2 e 4 cores) e pi seq. novo perf. para otimizarmos esse tipo de operação. Como em um processador como  o mips fazer operações matemáticas com números longos em mips demanda muitas movimentações de registradores e o uso de vários registradores em alguns casos. Analisando os tempos de execução (segunda imagem abaixo) observamos um grande grande ganho de performace com as otimizações implementadas e apesar de perdermos precisão o valor obtido apresenta um valor satisfatório para uma aproximação de pi. Por fim, notamos que ao movermos a parte principal da aplicação para um periférico foi onde obtivemos a maior ganho de desempenho, o que faz sentido já que quando você utiliza um periférico especialmente desenvolvido e otimizado para aquela tarefa acarrete em ganho de desempenho considerável.

<br/>
![](/projeto3/images/avg.png "")
<br/>
![](/projeto3/images/time.png "")
</br>
![](/projeto3/images/aprox.png "")
<br/>
## Conclusão

## Referências
1. https://people.sc.fsu.edu/~jburkardt/c_src/poisson_openmp/poisson_openmp.c

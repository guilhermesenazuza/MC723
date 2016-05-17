# Relatório Projeto 2 

#### Integrantes
- Gabriel Bueno de Oliveira 139455
- Pedro Rodrigues Grijó 139715
- Titouan Thibaud 180879
- Yugo Kuno 033324 

## Introdução
<br/>
Este projeto tem como objetivo a avaliação do impacto e desempenho de um processador de várias características arquiteturais estudadas na disciplina teórica MC722 - Projeto de Sistemas Computacionais.

## Metodologia
<br/>
A avaliação de impacto e desempenho foi realizada no simulador MIPS baseado em [ArchC](http://www.archc.org/). 
As configurações utilizadas e os critérios avaliados podem ser encontrados no [roteiro](https://github.com/pedrogrijo/MC723/blob/master/projeto2/ROTEIRO.md)
 deste projeto.
 
#### Observações Sobre Pipelines

##### 5 Estágios
Baseado na arquitetura MIPS. Os 5 estágios são: IF (instruction fetch), ID (instruction decode and register file read), EX (execute or address calculation), MEM (memory access) e WB (write-back). 
##### 7 Estágios
##### 13 Estágios
#### Arquitetura Superescalar 
Essa técnica permite o processamento de mais de uma instrução por estágio do pipeline, o que por sua vez torna possível a obtenção de CPI (ciclos por instrução) menor que 1. As instruções são selecionadas durante a execução. 

Trabalharemos com um pacote de duas instruções baseado no pipeline de 5 estágios da arquitetura MIPS. Os pacotes representam o conjunto de instruções que serão enviadas em conjunto em um ciclo de clock. Apesar de atualmente existirem processadores que enviam pacotes de 4 a 6 instruções, o valor de duas instruções foi escolhido devido a existência de poucas aplicações que podem sustentar um número maior de instruções por ciclo de clock. Isso ocorre devido a dependências que não podem ser resolvidas em paralelo e a perdas na hierarquia de memória que limitam a capacidade do pipeline de se manter cheio.[1] 

## Resultados e Análise
<br/>

## Conclusão
<br/>

## Referências
<br/>

1. Patterson, D. A., & Hennessy, J. L. 2014. Computer Organization And Design. 5th ed. 

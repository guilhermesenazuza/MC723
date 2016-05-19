# Projeto 2: Desempenho do Processador

#### Equipe
- 139455 - Gabriel Bueno de Oliveira
- 139715 - Pedro Rodrigues Grijó
- 180879 - Titouan Thibaud
- 033324 - Yugo Kuno


## Introdução
O desempenho de um processador não se resume à sua frequência de clock ou ao seu número de núcleos. Muito além da "potência" em números da CPU, uma parte fundamental do seu desempenho depende de uma arquitetura bem planejada e que seja apropriada para as sequências de instruções mais comuns nos programas que demandam alta performance.  
Com isso em mente, foram realizados experimentos em simulação do processamento de quatro benchmarks com diferentes configurações de arquitetura de CPU. Para avaliação foi considerado o impacto no número de ciclos dos programas a partir da mudança de parâmetros da CPU como o tamanho de _pipeline_, o paralelismo de instruções, o tipo de _branch predictor_ e as configurações de _cache_.


## Metodologia
Neste experimento foi usado um simulador do processador MIPS, criado com a linguagem ArchC, criado pelo time do IC/Unicamp de mesmo nome e baseado na linguagem de descrição de hardware SystemC. O ArchC permite, entre outras funcionalidades, a avalição do número de execuções de cada tipo de instrução pelo programa e o que ocorre com o _dataflow_ a cada instrução.

Serão avaliados os seguintes benchmarks:
- dijkstra
- bitcount
- qsort
- susan  
Os arquivos foram obtidos dos servidores do IC sob o diretório
`/home/staff/lucas/mc723/ex3/MipsMibench/`

Seguem abaixo as opções escolhidas para cada configuração do experimento:

#### _Pipeline_:
Será considerado um tempo de execução completa do _pipeline_ de 2.5ns, tal que para:
- 1 estágio
Tempo por estágio de 2.5ns, correspondente a um _clock_ de 400MHz.
- 5 estágios
Tempo por estágio de 0.5ns, correspondente a um _clock_ de 2.0GHz.
- 7 estágios
Tempo por estágio de 0.36ns, correspondente a um _clock_ de ~2.8GHz.
- 13 estágios
Tempo por estágio de 0.19ns, correspondente a um _clock_ de ~5.2GHz.

#### Paralelismo de instruções
- escalar
- superescalar

#### `Branch prediction`
- nenhum
- _always taken_
- _never taken_
- _repeat taken/not-taken_

#### Cache

|configurações|cache 1|cache 2|cache 3|cache 4|
|---|:---:|:---:|:---:|:---:|
|L1 instruction size|128KB|128KB|32KB|32KB|
|L1 instruction blocksize|128B|128B|16B|16B|
|L1 instruction associativity|4|4|4|4|
|L1 instruction fetch policy|always|always|always|always|
|L1 instruction replacement policy|LRU|LRU|LRU|LRU|
|L1 data size|128KB|128KB|32KB|32KB|
|L1 data blocksize|128B|128B|16B|16B|
|L1 data associativity|4|4|4|4|
|L1 data fetch policy|always|always|always|always|
|L1 data replacement policy|LRU|LRU|LRU|LRU|
|L2 unified size|1024KB|x|512KB|x|
|L2 unified blocksize|512B|x|512B|x|
|L2 unified associativity|4|x|4|x|
|L2 unified fetch policy|always|x|always|x|
|L2 unified replacement policy|LRU|x|LRU|x|



#### Observações Sobre _Pipeline_s

##### 5 Estágios
Baseado na arquitetura MIPS. Os 5 estágios são: IF (instruction fetch), ID (instruction decode and register file read), EX (execute or address calculation), MEM (memory access) e WB (write-back).[1, p. 300] 
##### 7 Estágios
##### 13 Estágios
#### Arquitetura Superescalar 
Essa técnica permite o processamento de mais de uma instrução por estágio do _pipeline_, o que por sua vez torna possível a obtenção de CPI (ciclos por instrução) menor que 1. As instruções são selecionadas durante a execução. 

Trabalharemos com um pacote(*issue packet*) de duas instruções baseado no _pipeline_ de 5 estágios da arquitetura MIPS. Os pacotes representam o conjunto de instruções que serão enviadas em conjunto em um ciclo de clock. Apesar de atualmente existirem processadores que podem enviar pacotes de 4 a 6 instruções, o valor de duas instruções foi escolhido devido a existência de poucas aplicações que podem sustentar um número maior de instruções por ciclo de clock. Isso ocorre devido a dependências que não podem ser resolvidas em paralelo e a perdas na hierarquia de memória que limitam a capacidade do _pipeline_ de se manter cheio.[1, p. 343] 

Para representar o processador superescalar, foi utilizado um vetor para guardar o pacote de instruções. Conforme uma instrução é recebida, ela é adicionada ao pacote apenas se a instrução que já estiver nele não conflitar(Write After Write) com a instrução que chegou. No caso de conflitos, o pacote é enviado com apenas uma instrução(neste caso há aumento de CPI) e a instrução que acabou de chegar só irá no próximo pacote. Caso não haja conflitos, a instrução é adicionada ao pacote, que é enviado normalmente. Essa abordagem faz com que as instruções recebidas sejam enviadas em ordem, ou seja, não há reordenação de instruções. Porém, apesar da escolha limitada, o envio é dinâmico

## Resultados e Análise
<br/>

## Conclusão
<br/>

## Referências
<br/>

1. Patterson, D. A., & Hennessy, J. L. 2014. Computer Organization And Design. 5th ed. 

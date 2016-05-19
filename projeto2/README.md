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
O tempo estimado de execução de um programa é `(#instr + #stalls + (#estágios - 1)) · tempo_por_estágio + (l1_hits * l1_custo + l2_hits * l2_custo + l2_misses * ram_custo)`.  
Será considerado um tempo de execução completa do _pipeline_ de 2.5ns, tal que para:  
- 1 estágio  
Tempo por estágio de 2.5ns, correspondente a um _clock_ de 400MHz.  
- 5 estágios  
Tempo por estágio de 0.5ns, correspondente a um _clock_ de 2.0GHz.  
Este pipeline será o caso base para estudo neste experimento; baseado na arquitetura MIPS, os 5 estágios são: IF (instruction fetch), ID (instruction decode and register file read), EX (execute or address calculation), MEM (memory access) e WB (write-back). [1, p. 300]  
- 7 estágios  
Tempo por estágio de ~0.36ns, correspondente a um _clock_ de ~2.8GHz.  
- 13 estágios  
Tempo por estágio de ~0.19ns, correspondente a um _clock_ de ~5.2GHz.  

#### Paralelismo de instruções
- escalar  
A cada ciclo uma instrução está sendo processada em cada elemento do _pipeline_ caso não ocorram _hazards_; como _forwarding_ resolve todos os _data hazards_, serão perdidos ciclos apenas nos casos de _control hazard_, que serão avaliados na seção de _Branch prediction_ abaixo.  
- superescalar  
Será utilizado um pacote (_issue packet_) de duas instruções baseado no _pipeline_ de 5 estágios da arquitetura MIPS. Os pacotes representam o conjunto de instruções que serão enviadas em conjunto em um ciclo de clock. Apesar de atualmente existirem processadores que podem enviar pacotes de 4 a 6 instruções, o valor de duas instruções foi escolhido devido a existência de poucas aplicações que podem sustentar um número maior de instruções por ciclo de clock. Isso ocorre devido a dependências que não podem ser resolvidas em paralelo e a perdas na hierarquia de memória que limitam a capacidade do _pipeline_ de se manter cheio. [1, p. 343] 
Como as instruções estão ocorrendo em paralelo, o _forwarding_ não consegue resolver os _data hazards_, tal que perde-se a segunda instrução do par sempre que isto ocorrer. Da mesma forma que no caso escalar, _control hazards_ serão avaliados na seção de _Branch prediction_ abaixo.  

#### _Branch prediction_
Pode-se calcular o número de ciclos perdidos por todas instruções de _branch_ avaliando cada instrução do tipo executada conforme o padrão abaixo:  
- nenhum  
Toda instrução de _branch_ faz com que a instrução seguinte do _pipeline_ seja atrasada em dois ciclos para que se possa calcular se o resultado será _branch taken_ ou _branck not taken_.  
- _always taken_  
Caso a predição de _branch taken_ esteja correta, atrasa-se a próxima instrução em um ciclo para que se possa calcular o endereço de _branch_.  
Caso a predição esteja errada, a instrução executada após um ciclo é abortada e a instrução correta é atrasada em dois ciclos por ter sido necessário calcular o resultado _branck not taken_.  
- _never taken_  
Caso a predição de _branch not taken_ esteja correta, a instrução de _branch_ é simplesmente ignorada e não há atraso para executar a próxima instrução.  
Caso a predição esteja errada, as instrução executadas em seguida são abortadas e a instrução correta é atrasada em dois ciclos por ter sido necessário calcular o resultado _branck taken_.  
- _repeat taken/not-taken_  
Caso a predição de _branch taken_ esteja correta, atrasa-se a próxima instrução em um ciclo para que se possa calcular o endereço de _branch_.  
Caso a predição de _branch not taken_ esteja correta, a instrução de _branch_ é simplesmente ignorada e não há atraso para executar a próxima instrução.  
Caso ambas predições estejam erradas, aborta-se o número de instruções executadas erroneamente e a instrução correta é atrasada em dois ciclos por ter sido necessário calcular o resultado _branck taken_.  

#### Cache

O número de ciclos estimado para acesso às memórias são[2]:
- L1 Data Cache Latency = 5 cycles
- L2 Cache Latency = 12 cycles
- RAM Latency = 42 cycles + 51 ns

Portanto, considerando cada pipeline separadamente, o tempo total para cada categoria de acesso é (baseado nos tempos de estágio listados na sessão pipeline):
##### Pipeline 1
- L1 Data Cache Latency = 12.5 ns
- L2 Cache Latency = 30 cycles
- RAM Latency = 156 ns

##### Pipeline 5
- L1 Data Cache Latency = 2.5 ns
- L2 Cache Latency = 6 ns
- RAM Latency = 72 ns

##### Pipeline 7
- L1 Data Cache Latency = 1.8 ns
- L2 Cache Latency =  4.3 ns
- RAM Latency = 66 ns

##### Pipeline 13
- L1 Data Cache Latency =  0.95 ns
- L2 Cache Latency = 2.3 ns 
- RAM Latency = 59 ns


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

## Análise e Resultados
<br/>

Os dados a serem avaliados no experimento são:
- Número de _write-after-read (WAR) data hazards_  
- Número de _read-after-write (RAW) data hazards_  
- Número de _write-after-write (WAW) data hazards_  
- Número de ciclos perdidos devido a _data hazards_  
- Número de _correct branch taken predictions_  
- Número de _correct branch not taken predictions_  
- Número de _branch mispredictions_  
- Número de ciclos perdidos devido a _control hazards_  
- Número de ciclos perdidos devido a _hazards_ de qualquer tipo  
- Número de instruções executadas  
- Número total de ciclos de execução considerando o número de estágios do _pipeline_  
- Tempo estimado de execução  





|configurações|conf. 1|←|←|←|conf. 2|←|←|←|conf. 3|←|←|←|conf. 4|←|←|←|conf. 5||||conf. 6|←|←|←|conf. 7||||conf. 8|←|←|←|conf. 9|←|←|←|conf. 10|←|←|←|conf. 11|←|←|←|  
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|  
|tamanho de pipeline|5|←|←|←|1|←|←|←|7|←|←|←|13|←|←|←|5|←|←|←|5|←|←|←|5|←|←|←|5|←|←|←|5|←|←|←|5|←|←|←|5|←|←|←|  
|instr. paral.|escalar|←|←|←|escalar|←|←|←|escalar|←|←|←|escalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|  
|branch predictor|no prediction|←|←|←|no prediction|←|←|←|no prediction|←|←|←|no prediction|←|←|←|no prediction|←|←|←|always|←|←|←|never|←|←|←|repeat|←|←|←|repeat|←|←|←|repeat|←|←|←|repeat|←|←|←|  
|cache|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 2|←|←|←|cache 3|←|←|←|cache 4|←|←|←|  
|benchmark|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|  
|hazards WAR|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|  
|hazards RAW|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|  
|hazards WAW|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|151663|647230|591208|192760|151663|647230|591208|192760|151663|647230|591208|192760|151663|647230|591208|192760|151663|647230|591208|192760|151663|647230|591208|192760|151663|647230|591208|192760|  
|ciclos perdidos por data hazards|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|  
|correct branch-taken predictions|||||||||||||||||||||||||||||||||||||||||||||  
|correct branch-not-taken predictions|||||||||||||||||||||||||||||||||||||||||||||  
|branch mispredictions|||||||||||||||||||||||||||||||||||||||||||||  
|ciclos perdidos por control hazards|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|  
|ciclos perdidos por hazards|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|  
|instruções executadas|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|  
|total de ciclos|35787807|49165904|39464255|89682194|35787803|49165900|39464251|89682190|35787809|49165906|39464257|89682196|35787815|49165912|39464263|89682202|38810997|59347054|45866010|106055234|38810997|59347054|45866010|106055234|38810997|59347054|45866010|106055234|38810997|59347054|45866010|106055234|38810997|59347054|45866010|106055234|38810997|59347054|45866010|106055234|38810997|59347054|45866010|106055234|  
|tempo estimado de execução (s)|0.018|0.025|0.020|0.045|0.089|0.123|0.099|0.224|0.013|0.018|0.014|0.032|0.007|0.009|0.008|0.017|0.019|0.030|0.023|0.053|0.019|0.030|0.023|0.053|0.019|0.030|0.023|0.053|0.019|0.030|0.023|0.053|0.019|0.030|0.023|0.053|0.019|0.030|0.023|0.053|0.019|0.030|0.023|0.053|  

## Conclusão
<br/>

## Referências
<br/>

1. Patterson, D. A., & Hennessy, J. L. 2014. Computer Organization And Design. 5th ed. 
2. http://www.7-cpu.com/cpu/Skylake.html

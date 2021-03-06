# Projeto 2: Desempenho do Processador

#### Equipe
- 139455 - Gabriel Bueno de Oliveira
- 139715 - Pedro Rodrigues Grijó
- 180879 - Titouan Thibaud
- 033324 - Yugo Kuno


## Introdução
O desempenho de um processador não se resume à sua frequência de _clock_ ou ao seu número de núcleos. Muito além da "potência" em números da CPU, uma parte fundamental do seu desempenho depende de uma arquitetura bem planejada e que seja apropriada para as sequências de instruções mais comuns nos programas que demandam alta performance.  
Com isso em mente, foram realizados experimentos em simulação do processamento de quatro benchmarks com diferentes configurações de arquitetura de CPU. Para avaliação de resultados foi considerado o impacto no número de ciclos, tempo de execução, número de _hazards_ e latência de memória dos programas a partir da mudança de parâmetros da CPU como o tamanho de _pipeline_, o paralelismo de instruções, o tipo de _branch predictor_ e as configurações de _cache_.


## Metodologia
Neste experimento foi usado um simulador do processador _MIPS_, criado com a linguagem _ArchC_, desenvolvidos pelo time do IC/Unicamp de mesmo nome e baseado na linguagem de descrição de hardware _SystemC_. Este simulador permite, entre outras funcionalidades, a avalição do número de execuções de cada tipo de instrução pelo programa e o que ocorre com o _dataflow_ a cada instrução.

Foram avaliados os seguintes benchmarks:
- dijkstra
- bitcount
- qsort
- susan  

Os arquivos foram obtidos dos servidores do IC sob o diretório
`/home/staff/lucas/mc723/ex3/MipsMibench/`

Seguem abaixo as opções escolhidas para cada configuração do experimento:

#### _Pipeline_:
O tempo estimado de execução de um programa é  
`(NI + CP + (NE - 1)) · TE + (L1_fetches · TA_L1) + (L2_fetches · TA_L2) + (L2_misses · TA_RAM)`   
sendo
- NI: número de instruções para o caso escalar e sua metade arredondada para cima no caso superescalar  
- CP: número de ciclos perdidos por _hazards_  
- NE: número de estágios do _pipeline_  
- TE: período de execução por estágio do _pipeline_ (inverso do _clock_)  
- TA: período de acesso à unidade de memória
  
Como o tempo de acesso à L1 e à L2 é perdido mesmo que os dados procurados não sejam encontrados, devem ser contabilizados o número de _fetches_ e não _hits_ para estas _caches_.

Foi considerado um tempo de execução completa do _pipeline_ de 2.5ns, tal que para:  
- 1 estágio  
Tempo por estágio de 2.5ns, correspondente a um _clock_ de 400MHz.  
- 5 estágios  
Tempo por estágio de 0.5ns, correspondente a um _clock_ de 2.0GHz.  
Este _pipeline_ foi o caso base para estudo neste experimento; baseado na arquitetura _MIPS_, os 5 estágios são: IF (instruction fetch), ID (instruction decode and register file read), EX (execute or address calculation), MEM (memory access) e WB (write-back). [1, p. 300]  
- 7 estágios  
Tempo por estágio de ~0.36ns, correspondente a um _clock_ de ~2.8GHz.  
- 13 estágios  
Tempo por estágio de ~0.19ns, correspondente a um _clock_ de ~5.2GHz.  

#### Paralelismo de instruções
- escalar  
A cada ciclo uma instrução está sendo processada em cada elemento do _pipeline_ caso não ocorram _hazards_; como _forwarding_ resolve todos os _data hazards_, serão perdidos ciclos apenas nos casos de _control hazard_, que serão avaliados na seção _Branch prediction_ abaixo.  
- superescalar  
Foi utilizado um pacote (_issue packet_) de duas instruções baseado no _pipeline_ de 5 estágios da arquitetura _MIPS_. Os pacotes representam o conjunto de instruções que serão enviadas em conjunto em um ciclo de _clock_. Apesar de atualmente existirem processadores que podem enviar pacotes de 4 a 6 instruções, o valor de duas instruções foi escolhido devido a existência de poucas aplicações que podem sustentar um número maior de instruções por ciclo de _clock_. Isso ocorre devido a dependências que não podem ser resolvidas em paralelo e a perdas na hierarquia de memória que limitam a capacidade do _pipeline_ de se manter cheio. [1, p. 343]  
Como as instruções estão ocorrendo em paralelo, o _forwarding_ não consegue resolver os _data hazards_, tal que perde-se a segunda instrução do par sempre que isto ocorrer. Da mesma forma que no caso escalar, _control hazards_ serão avaliados na seção _Branch prediction_ abaixo.  

#### _Branch prediction_
Pode-se calcular o número de ciclos perdidos por todas instruções de _branch_ avaliando cada instrução do tipo executada conforme o padrão abaixo:  
- nenhum  
Toda instrução de _branch_ faz com que a instrução seguinte do _pipeline_ seja atrasada em dois ciclos para que se possa calcular se o resultado será _branch taken_ ou _branch not taken_.  
- _always taken_  
Caso a predição de _branch taken_ esteja correta, atrasa-se a próxima instrução em um ciclo para que se possa calcular o endereço de _branch_.  
Caso a predição esteja errada, a instrução executada após um ciclo é abortada e a instrução correta é atrasada em dois ciclos por ter sido necessário calcular o resultado _branch not taken_.  
- _never taken_  
Caso a predição de _branch not taken_ esteja correta, a instrução de _branch_ é simplesmente ignorada e não há atraso para executar a próxima instrução.  
Caso a predição esteja errada, as instrução executadas em seguida são abortadas e a instrução correta é atrasada em dois ciclos por ter sido necessário calcular o resultado _branch taken_.  
- _repeat taken/not-taken_  
Caso a predição de _branch taken_ esteja correta, atrasa-se a próxima instrução em um ciclo para que se possa calcular o endereço de _branch_.  
Caso a predição de _branch not taken_ esteja correta, a instrução de _branch_ é simplesmente ignorada e não há atraso para executar a próxima instrução.  
Caso ambas predições estejam erradas, aborta-se o número de instruções executadas erroneamente e a instrução correta é atrasada em dois ciclos por ter sido necessário calcular o resultado _branch taken_.  

#### _Memory access latency_

Não faz sentido que o acesso à memória em um _pipeline_ de 1 estágio seja 5 vezes mais lento que em um _pipeline_ de 5 estágios; assim foram consideradas latências em tempo estimado de acesso à memória ao invés de ciclos perdidos, conforme valores calculados a partir de exemplos de arquiteturas atuais [2] a seguir:  
- fetches em L1i e L1d: 1ns  
- fetches em L2u: 3ns  
- fetches em RAM: 62ns  
Para simplificar as estimativas, assume-se que os dados procurados estarão pelo menos na RAM e o número de fetches nesta é igual ao número de misses na L2 (quando disponível) ou na L1 (quando não).

#### _Cache_

|configurações|_cache_ 1|_cache_ 2|_cache_ 3|_cache_ 4|
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

Os dados avaliados no experimento foram:
- Número de _write-after-read (WAR) data hazards_  
- Número de _read-after-write (RAW) data hazards_  
- Número de _write-after-write (WAW) data hazards_  
- Número de ciclos perdidos devido a _data hazards_  
- Número de _correct branch-taken predictions_  
- Número de _correct branch-not-taken predictions_  
- Número de _branch mispredictions_  
- Número de ciclos perdidos devido a _control hazards_  
- Número de ciclos perdidos devido a _hazards_ de qualquer tipo  
- Número de instruções executadas  
- Número total de ciclos de execução considerando o número de estágios do _pipeline_  
- Tempo de execução desconsiderando latência de memória (s)  
- Número de _fetches_ em L1  
- Número de _fetches_ em L2  
- Número de _misses_ em L2  
- Tempo total usado em _memory access_  
- Tempo total estimado de execução  
- Fração do tempo perdido em latência de acesso à memória  

Os resultados para cada configuração seguem abaixo:

|configurações|conf. 1|←|←|←|conf. 2|←|←|←|conf. 3|←|←|←|conf. 4|←|←|←|conf. 5||||conf. 6|←|←|←|conf. 7||||conf. 8|←|←|←|conf. 9|←|←|←|conf. 10|←|←|←|conf. 11|←|←|←|  
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|  
|tamanho de pipeline|5|←|←|←|1|←|←|←|7|←|←|←|13|←|←|←|5|←|←|←|5|←|←|←|5|←|←|←|5|←|←|←|5|←|←|←|5|←|←|←|5|←|←|←|  
|instr. paral.|escalar|←|←|←|escalar|←|←|←|escalar|←|←|←|escalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|superescalar|←|←|←|  
|branch predictor|no prediction|←|←|←|no prediction|←|←|←|no prediction|←|←|←|no prediction|←|←|←|no prediction|←|←|←|always|←|←|←|never|←|←|←|repeat|←|←|←|repeat|←|←|←|repeat|←|←|←|repeat|←|←|←|  
|cache|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 1|←|←|←|cache 2|←|←|←|cache 3|←|←|←|cache 4|←|←|←|  
|benchmark|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|bitcount|dijkstra|qsort|susan|  
|hazards WAR|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|77891|1995573|2054542|5314374|  
|hazards RAW|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|2793636|7538347|3756005|10865906|  
|hazards WAW|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|151663|647230|591208|192760|151663|647230|591208|192760|151663|647230|591208|192760|151663|647230|591208|192760|151663|647230|591208|192760|151663|647230|591208|192760|151663|647230|591208|192760|  
|ciclos perdidos por data hazards|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|3023190|10181150|6401755|16373040|  
|branch wait|6687307|8737329|2705413|2649353|6687307|8737329|2705413|2649353|6687307|8737329|2705413|2649353|6687307|8737329|2705413|2649353|6687307|8737329|2705413|2649353|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
|correct branch-taken predictions|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|4134899|3828804|2021382|2087072|0|0|0|0|1658571|2103152|1642235|1830072|1658571|2103152|1642235|1830072|1658571|2103152|1642235|1830072|1658571|2103152|1642235|1830072|  
|correct branch-not-taken predictions|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|2552408|4908525|684031|562281|76079|3182872|304883|305281|76079|3182872|304883|305281|76079|3182872|304883|305281|76079|3182872|304883|305281|  
|branch mispredictions|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|2552408|4908525|684031|562281|4134899|3828804|2021382|2087072|4952657|3451305|758295|514000|4952657|3451305|758295|514000|4952657|3451305|758295|514000|4952657|3451305|758295|514000|  
|ciclos perdidos por control hazards|13374614|17474658|5410826|5298706|13374614|17474658|5410826|5298706|13374614|17474658|5410826|5298706|13374614|17474658|5410826|5298706|13374614|17474658|5410826|5298706|9239715|13645854|3389444|3211634|8269798|7657608|4042764|4174144|11563885|9005762|3158825|2858072|11563885|9005762|3158825|2858072|11563885|9005762|3158825|2858072|11563885|9005762|3158825|2858072|  
|ciclos perdidos por hazards de qualquer tipo|13374614|17474658|5410826|5298706|13374614|17474658|5410826|5298706|13374614|17474658|5410826|5298706|13374614|17474658|5410826|5298706|16397804|27655808|11812581|21671746|12262905|23827004|9791199|19584674|11292988|17838758|10444519|20547184|14587075|19186912|9560580|19231112|14587075|19186912|9560580|19231112|14587075|19186912|9560580|19231112|14587075|19186912|9560580|19231112|  
|instruções executadas|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|35787803|49165900|39464251|89682190|  
|total de ciclos|49162421|66640562|44875081|94980900|49162417|66640558|44875077|94980896|49162423|66640564|44875083|94980902|49162429|66640570|44875089|94980908|34291710|52238762|31544711|66512845|30156811|48409958|29523329|64425773|29186894|42421712|30176649|65388283|32480981|43769866|29292710|64072211|32480981|43769866|29292710|64072211|32480981|43769866|29292710|64072211|32480981|43769866|29292710|64072211|  
|tempo de execução desconsiderando latência de memória (s)|0.025|0.033|0.022|0.047|0.123|0.167|0.112|0.237|0.018|0.024|0.016|0.034|0.009|0.013|0.009|0.018|0.017|0.026|0.016|0.033|0.015|0.024|0.015|0.032|0.015|0.021|0.015|0.033|0.016|0.022|0.015|0.032|0.016|0.022|0.015|0.032|0.016|0.022|0.015|0.032|0.016|0.022|0.015|0.032|
|fetches em L1|75283074|121531013|104373554|244107209|75283074|121531013|104373554|244107209|75283074|121531013|104373554|244107209|75283074|121531013|104373554|244107209|75283074|121531013|104373554|244107209|75283074|121531013|104373554|244107209|75283074|121531013|104373554|244107209|75283074|121531013|104373554|244107209|75283074|121531013|104373554|244107209|75283074|121531013|104373554|244107209|75283074|121531013|104373554|244107209|
|fetches em L2|869|3697|155817|8086|869|3697|155817|8086|869|3697|155817|8086|869|3697|155817|8086|869|3697|155817|8086|869|3697|155817|8086|869|3697|155817|8086|869|3697|155817|8086|0|0|0|0|3176|374367|971213|15493|0|0|0|0|
|misses em L2|224|622|7421|2999|224|622|7421|2999|224|622|7421|2999|224|622|7421|2999|224|622|7421|2999|224|622|7421|2999|224|622|7421|2999|224|622|7421|2999|425|1635|56615|3952|217|703|10068|3154|1543|178932|334536|7051|
|tempo total em memory access (s)|0.075|0.122|0.105|0.244|0.075|0.122|0.105|0.244|0.075|0.122|0.105|0.244|0.075|0.122|0.105|0.244|0.075|0.122|0.105|0.244|0.075|0.122|0.105|0.244|0.075|0.122|0.105|0.244|0.075|0.122|0.105|0.244|0.075|0.122|0.108|0.244|0.075|0.123|0.108|0.244|0.075|0.133|0.125|0.245|
|tempo total estimado de execução (s)|0.100|0.155|0.128|0.292|0.198|0.288|0.217|0.482|0.093|0.145|0.121|0.278|0.085|0.134|0.114|0.263|0.092|0.148|0.121|0.278|0.090|0.146|0.120|0.277|0.090|0.143|0.120|0.277|0.092|0.143|0.120|0.276|0.092|0.144|0.123|0.276|0.092|0.145|0.123|0.276|0.092|0.155|0.140|0.277|  
|fração do tempo perdido em latência de memória|75%|78%|82%|84%|38%|42%|48%|51%|81%|84%|87%|88%|89%|90%|92%|93%|81%|82%|87%|88%|83%|83%|88%|88%|84%|85%|87%|88%|82%|85%|88%|88%|82%|85%|88%|88%|82%|85%|88%|88%|82%|86%|90%|88%|


## Conclusão

Apesar de a avaliação do tamanho de _pipeline_ ter sido uma aproximação simples sem levar em consideração os detalhes de arquiteturas de 1, 7 e 13 estágios, a primeira vista os ganhos com o aumento do número de estágios é expressivo. Como não foram levadas em conta mudanças no número de hazards e o número de instruções é elevado, o número de ciclos e o tempo de execução desconsiderando tempos de acesso a memória é quase inversamente proporcional ao número de estágios para todos os benchmarks.  
Por outro lado, levando em conta os tempos expressivos de acesso a memória e comparando ao _pipeline_ de 5 estágios, o de 1 estágio leva aproximadamente o dobro do tempo, o de 7 estágios é ligeiramente mais rápido e o de 13 estágios consome ~15% menos tempo (também para todos os benchmarks): ganhos bem menos significativos.  

A mudança para paralelismo superescalar de duas instruções por pacote também reduz significativamente o número de ciclos consumidos e o tempo de execução desconsiderando a latência de memória, com uma redução de ~22% para o _dijkstra_ e ~30% para os demais. Entretanto a latência novamente reduz este ganho para ~7.5% no caso do _bitcount_ e apenas ~5% para os demais.

A política de _branch prediction_ de _never taken_ tem resultado significativamente melhor que as outras políticas para o _bitcount_ e _dijkstra_: o número de _control hazards_ cai para aproximadamente metade quando comparado ao _no prediction_.  
Já para _qsort_ e _susan_ a política de _repeat_ é a melhor, reduzindo em ~40% comparado ao _no prediction_.  
Essas diferenças se devem às características de _loops_, condicionais, etc do programa, além das características de cada política já discutidas acima.  

Os tempos de acesso à memória são obviamente um gargalo para o desempenho de todos os benchmarks: para o processamento mais ineficiente com _pipeline_ de 1 estágio entre 40 e 50% do tempo total é consumido em latência, enquanto para o mais eficiente com 13 estágio a fração do tempo de latência chega a ~90% do tempo total. No caso padrão de 5 estágios essa fração fica entre 80 e 90%.  

Para o _bitcount_ as quatro configurações de _cache_ geram resultados praticamente indistinguíveis.
Para os demais _benchmarks_, há pouca diferença entre a configuração de _cache_ 1 e 2, sendo que a perda da L2 gerou aumentos em latência inferiores a 3%.  
O mesmo ocorre entre a _cache_ 1 e 3, sendo que a redução de tamanho de L1 e L2 gerou aumentos inferiores a 2.5%.  
Entretanto a perda da L2 da _cache_ 4 comparada à 3 é mais significativa para _dijkstra_ e _qsort_, gerando aumentos de latência de ~8% e ~16%, respectivamente.  

Encerrando a análise do experimento, percebe-se como as diferentes configurações de arquitetura tem impactos significativos na execução de instruções propriamente dita; apesar disso não há uma "configuração ótima" que atenda todos os _benchmarks_ aqui avaliados, quanto mais todas as aplicações utilizadas em computadores.  
Por outro lado percebe-se como é significativo o gargalo imposto pelo acesso a memória, sendo a redução desta latência um dos pontos mais relevantes para melhorar o desempenho de quaisquer programas que demandem acesso a um volume minimamente significativo de dados.


## Referências

1. Patterson, D. A., & Hennessy, J. L. 2014. Computer Organization And Design. 5th ed. 
2. http://www.7-cpu.com/cpu/Skylake.html

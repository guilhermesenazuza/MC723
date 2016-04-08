# Relatório Exercício 2                                                                   

##### Pedro Rodrigues Grijó
##### 139715
<br/> 

## Introdução
O objetivo deste exercício foi definir, através de simulação com o uso do software DineroIV, qual a melhor configuração de cache para um trace de execução. Existiam duas opções de exercício, a escolhida foi: *"Simular um programa com dois níveis de cache e achar a melhor configuração para os dois níveis (L1 de instruções, L1 de dados e L2 unificado). Você pode usar qualquer um dos 46 traces que estão disponíveis (cada programa tem dois traces, f2b e m2b, veja informações sobre isso na página dos traces)"*. O trace de execução utilizado foi **178.galgel.m2b**, e seu tamanho foi reduzido de 101 para 20.

## Análise

#### Observações iniciais

* Ambos os caches (L1 e L2) foram analisados seguindo o procedimento a seguir:
primeiramente foram fixados os parâmetros tamanho do bloco, associatividade, fetch policy e replacement policy. Com estes parâmetros fixados, foram testados diversos tamanhos para as caches, sendo escolhido aquele mais satisfatório. Após escolhido o tamanho, este foi fixado e o mesmo procedimento foi realizado para o tamanho do bloco, ou seja, um parâmetro é fixado por cada fase de iteração dos testes, para que possa ser descoberto o valor ótimo/satisfatório do parâmetro para a próxima iteração.

* Todos os **instruction miss rates da cache L1 foram insignificantes** percentualmente (menores que 0.00%), portanto não foram representados nos gráficos. Assim, os gráficos para a cache L1 só estão representando os miss rates de dados(data miss rates)

#### Cache L1
Fixado o tamanho do bloco em 8 B, associatividade 1, fetch policy demand e replacement policy LRU, foram testados tamanhos para a cache L1.

![](/exercicio2/graphs/miss-rate-cache-size.png "")

Nota-se que a % de misses decai conforme o tamanho da cache aumenta, como era de se esperar. Porém, não podemos ter uma cache L1 arbitrariamente grande, pois este tipo de memória tem preço alto e a latência aumenta conforme fica esta memória fica muita grande.

**Cache L1 escolhido: 64 KB** (32 KB p/ instrução e 32 KB p/dados), pois é um valor que representa processadores relativamente atuais, como os das máquinas do Instituto de Computação da UNICAMP. O processador do computador utilizado é um Intel(R) i5-4590 3.30GHz, com cache L1 de 64 KB, blocos de 64 B e cache L2 de 256 KB 
O tamanho dos caches foi descoberto com o comando $lscpu, e o tamanho dos blocos de L1 com o comando $less /proc/cpuinfo

**Fixado** o **tamanho da cache em 64 KB**, associatividade 1, fetch policy demand e replacement policy LRU, foram testados tamanhos para o bloco da cache L1.

![](/exercicio2/graphs/miss-rate-block-size.png "")

O **tamanho do bloco escolhido para L1 foi 64 B**, pois é o block size da máquina testada. Após este tamanho a quantidade de misses não diminuiu consideravelmente, chegando a aumentar quando pulamos de 128 para 256 bytes. 

**Fixado** o tamanho da cache 64 KB, **tamanho do bloco 64 B**, fetch policy demand e replacement policy LRU, foram testadas associatividades da cache L1.

![](/exercicio2/graphs/miss-rate-associativity.png "")

O melhor valor para associatividade foi 64, pois este foi o maior valor testado e é esperado que maiores valores resultem em menor miss rate. Porém, após associatividade 4, não foram obtidos ganhos significativos na taxa de miss. Portanto **associatividade 4 foi o valor escolhido**.

**Fixado** o tamanho da cache 64 KB, tamanho do bloco 64 B, **associatividade em 4** e replacement policy LRU, foram testadas fetch policies da cache L1.

![](/exercicio2/graphs/miss-rate-fetch-policy.png"")

Os melhores valores para fetch policies foram obtidos com always e **subblock**, com uma pequena vantagem de menores miss rates para subblocks.

**Fixado** o tamanho da cache 64 KB, tamanho do bloco 64 B, associatividade 4 e **subblock fetch policy**, foram testadas replacement policies da cache L1.

![](/exercicio2/graphs/miss-rate-replacement-policy.png"")

Os melhores miss rates foram obtidos com a replacement policy padrão usada pelo DineroIV, **Least Recently Used (LRU)**

Sendo assim, temos a seguinte cache L1 para os testes realizados:
<br/>
Tamanho da cache: **64(32 instruções + 32 dados) KB** 
<br/>
Tamanho do bloco: **64(32 instruções + 32 dados) KB**
<br/>
Associativity: **4**
<br/>
Fetch policy: **Subblock**
<br/>
Replacement policy: **Last Recently Used (LRU)**
<br/>
### Cache L2

Fixada a cache L1 definida na primeira parte do exercício, foi feita uma análisa semelhante para a cache L2. Porém, a cache L2 foi testada unificadamente, ao contrário da L1, em que dados e instruções foram separados na análise.

Seguem os resultados obtidos para a cache L2:
![](/exercicio2/graphs/miss-rate-cache-l2-size.png"")
Miss rate diminui conforme a cache aumenta, como esperado. Foi escolhido o valor de **256 KB** para a L2, pois está de acordo com certos processadores no mercado( o que não ocorre com o valor de 1024 KB)

![](/exercicio2/graphs/miss-rate-cache-l2-block-size.png"")
Miss rate diminui conforme o tamanho do bloco aumenta até 512 bytes, piorando consideravelmente ao chegar em 1024 bytes. Foi escolhido o valor de **256 bytes** para manter a consistência com o tamanho da cache.

![](/exercicio2/graphs/miss-rate-cache-l2-associativity.png"")
Como na cache L1, o valor ideal foi de **associatividade 4**.

![](/exercicio2/graphs/miss-rate-cache-l2-fetch-policy.png"")

![](/exercicio2/graphs/miss-rate-cache-l2-replacement-policy.png"")

Ambas as policies também obtiveram resultados semelhantes aos testes da cache L1, ou seja, **subblock** como melhor fetch policy e **LRU** como melhor replacement policy.

## Conclusão
Sendo assim, o resultado deste exercício são as duas caches como se segue

Tipo da cache | Tamanho (B) | Bloco (B) | Associatividade | Fetch Policy | Replacement Policy
------------ | ------------- | ------------- | ------------- | ------------- | -------------
L1 | 64K | 64 | 4 | Subblock | LRU
L2 | 256K | 256 | 4 | Subblock | LRU

Vale notar que para escolher a melhor configuração de cache, faltam informações relevantes como o tamanho da memória primária(RAM) e os valores para o próprio tamanho da cache, seu bloco e a associatividade que poderiam ser considerados dentro de padrões normais aceitáveis. Esses valores podem variar conforme a tecnlogia evolui, e portanto uma cache L1 de 256 KB talvez não seja tão incomum daqui alguns anos.


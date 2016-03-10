#Relatório Exercício 1


Exercício feito na seguinte máquina:

MacBook Pro  
Processor: 2.8 GHz Intel Core i5  
Memory: 8 GB 1600 MHz DDR3  
Disk: 500GB PCIe-based flash storage  

#### Desempenho do programa **primo.c** 
Valores obtidos pelo comando **time**, tempo **real** indicado

Flag | Tempo(ms) 1 | Tempo(ms) 2 | Tempo(ms) 3 | Tempo Médio(ms)
------------ | ------------- | ------------- | ------------- | -------------
-- | 386 | 378 | 380 | 383
O0 | 394 | 376 | 383 | 384
O1 | 305 | 311 | 313 | 310
O2 | 293 | 282 | 288 | 288
**O3** | **279** | **280** | **282** | **280**

#### Desempenho do programa com otimizações da categoria **-mtune**
Flag | Tempo(ms) 1 | Tempo(ms) 2 | Tempo(ms) 3 | Tempo Médio(ms)
------------ | ------------- | ------------- | ------------- | -------------
**intel** | **378** | **371** | **381** | **377**
corei5 | 388 | 385 | 369 | 381
native | 380 | 374 | 386 | 380

Nota-se que as 3 flags obtiveram desempenho semelhante. Não houve melhora significativa em relação à compilação simples sem flags de otimização da tabela anterior. Houve perda de desempenho em relação à compilação com as flags O1, O2 e O3. As otimizações da categoria **-mtune** servem para ajustar ao tipo da CPU usada tudo que for aplicável sobre o código gerado

------

#### Desempenho do programa quebrado em 2, com a flag -O3
Flag | Tempo(ms) 1 | Tempo(ms) 2 | Tempo(ms) 3 | Tempo Médio(ms)
------------ | ------------- | ------------- | ------------- | -------------
O3 | 300 | 305 | 312 | 306

Comparado ao programa não quebrado em 2, este gasta mais tempo.

------

#### Desempenho do programa que calcula o número de primos entre 1 e n , sem quebrar em 2
n: 104729(10000 primos) 

Flag | Tempo(ms) 1 | Tempo(ms) 2 | Tempo(ms) 3 | Tempo Médio(ms)
------------ | ------------- | ------------- | ------------- | -------------
-- | 1742 | 1741 | 1751 | 1745
O3 | 1418 | 1397 | 1405 | 1407

#### Desempenho do programa que calcula o número de primos entre 1 e n , quebrado em 2
n: 104729(10000 primos)

Flag | Tempo(ms) 1 | Tempo(ms) 2 | Tempo(ms) 3 | Tempo Médio(ms)
------------ | ------------- | ------------- | ------------- | -------------
-- | 1690 | 1699 | 1711 | 1700
O3 | 1416 | 1410 | 1434 | 1420

O resultado é semelhante nos dois casos, porém era esperado que o programa não dividido em 2 fosse mais rápido, como aconteceu no primeiro teste. 

------


#### Desempenho do programa que calcula o número de primos entre 1 e n,  
#### sem quebrar em 2, sem varrer números pares
n: 104729(10000 primos) 

Flag | Tempo(ms) 1 | Tempo(ms) 2 | Tempo(ms) 3 | Tempo Médio(ms)
------------ | ------------- | ------------- | ------------- | -------------
-- | 1690 | 1688 | 1747 | 1708
O3 | 1388 | 1393 | 1427 | 1403

#### Desempenho do programa que calcula o número de primos entre 1 e n,    
#### quebrado em 2, sem varrer números pares  
n: 104729(10000 primos)

Flag | Tempo(ms) 1 | Tempo(ms) 2 | Tempo(ms) 3 | Tempo Médio(ms)
------------ | ------------- | ------------- | ------------- | -------------
-- | 1706 | 1711 | 1706 | 1708
O3 | 1394 | 1393 | 1400 | 1396

O resultado é semelhante aos casos que varrem os números pares    

------

#### Usando o gprof para descobrir qual parte do programa gasta mais tempo

Desta parte em diante o exercício foi realizado em outra máquina(linux) para facilitar o uso do gprof e do OpenMP.    
A parte do programa que mais toma tempo é a funçao primo, que foi chamada 52365 vezes, com um gasto de 43.54µs por chamada(n = 104729). No total, foram necessários 2.28 segundos para rodar o programa nesta máquina e com essas configurações.

------

#### Paralalização

De acordo com os resultados do gprof, o melhor a se fazer é paralelizar a função primo. 

####Utilizando o OpenMP: programa não quebrado
n: 104729(10000 primos)

Flag | Tempo(ms) 1 | Tempo(ms) 2 | Tempo(ms) 3 | Tempo Médio(ms)
------------ | ------------- | ------------- | ------------- | -------------
-- | 833 | 967 | 913 | 904
O3 | 774 | 778 | 958 | 837

------

O programa pode ser melhorado, por exemplo, usando um algoritmo mais eficiente para encontrar os números primos.

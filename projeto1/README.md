# Programa 1 - GENETIC

## O que faz? Para que serve?

O programa recria a imagem através de polígonos semi transparentes que são gerados por um algoritmo genético. O programa não tem um propósito certo, apenas é algo interessante.

## Por que é bom para medir desempenho?

O programa pode ser rodado por um tempo arbitrário, então é um bom algoritmo para fazer um benchmark. No nosso benchmark, usaremos 50 mil iterações.

O programa também é bom, pois existe um potencial de paralelização.

No final, ele escreve a imagem gerada em disco e utilizamos esse momento para medir o desempenho do disco.

## O que baixar

O código original pode ser baixado em: http://www.ggsoft.org/archives/genetic.zip.

Nós fizemos modificações para o programa parar em 50 mil iterações (para termos um tempo fixo para medir) e para escrever uma imagem em disco no final, fatos que não ocorrem no código original.


## Como compilar/instalar
Na versão original, o programador esqueceu alguns includes no arquivo _streamer.h_, que foi corrigido para que o programa rodasse corretamente. É necessário incluir:

* _cstdio_
* _cstring_

O código tem uma dependencia, [a biblioteca SDL](https://wiki.libsdl.org/Installation).

Feito isso, basta digitar _make_ para compilar o programa.

## Como executar
Rodar ./genetic nome_arquivo.bmp. Por exemplo, ./genetic mona.bmp

## Como medir o desempenho

Para medir o desempenho, utilizamos o comando _time_ do linux, executando "time ./genetic mona.bmp" e pegando o valor _real_ escrito na tela no final.
Utilizamos o valor de real porque é o tempo real gasto entre o começo do programa e o seu final, ao contrário de user e sys que medem o tempo de CPU gasto pelo programa, que nesse caso, não nos interessa.
O tempo é dado em segundos pelo comando.

No final, medimos o tempo de escrever a imagem resultante no disco, utilizando funções da biblioteca **time**. Esse tempo é medido em micro segundos, pegamos o tamanho do arquivo escrito em disco e dividimos ele pelo tempo medido na escrita para ter a performace do disco em MB por segundo.

Para nossos dados, rodamos o programa dez vezes em diferentes computadores com diferentes hardwares e tiramos as médias, desvio padrão e variância desses dados.

## Como apresentar o desempenho
Nós mostraremos tabelas com os dados coletadas para todas as máquinas e junto estarão os dados como média, desvio padrão e a variância.

## Máquinas
Especificações máquina um:

* Processador: Intel Core i7-Intel(R) Core(TM) i7-4700HQ CPU @ 2.40GHz
* Memória: 16GB DDR3
* Cores: 4
* SO: Ubuntu 14.04LTS
* HD: Western Digital WD10S21X-24R1BTO / 7200RPM / Interface Sata III

Especificações da máquina dois:
* Processador: Intel(R) Core(TM) i7-4510U CPU @ 2.00GHz
* Memória: 8GB DDR3 1600MHz
* Cores: 2
* SO: Ubuntu 15.10
* HD: Disco rígido SATA de 500 GB / 5400 RPM

Especificações da máquina três:
* Processador: Intel(R) Core(TM) i7-2670QM CPU @ 2.20GHz
* Memória: 8GB DDR3 1600MHz
* Cores: 4
* SO: Ubuntu 14.04LTS 32-bit
* HD: SAMSUNG HN-M101MBB / 5400RPM / Interface Sata III

## Resultados
###Máquina um
Iteração   | Tempo de execução (ms) | Desempenho de disco (MB/s)
:------: | :------------: | :------------------------------:
1   |     56.04             |    104.861
2   |     54.421             |    114.809
3   |     54.571              |    111.257
4   |     56.601             |    118.088
5   |     51.251             |    81.212
6   |     55.149             |    87.514
7   |     52.604              |    112.416
8   |     55.169             |    109.537
9   |     53.558              |    115.236
10   |     54.406             |    112.365

###Máquina dois
Iteração   | Tempo de execução (ms) | Desempenho de disco (MB/s)
:------: | :------------: | :------------------------------:
1   |   54.547	      |69.109
2   |   67.648	       |63.453
3   |   65.195	      |97.871
4   |   61.878	      |78.192
5   |   63.274	      |91.483
6   |   55.156	      |106.254
7   |   64.714	      |53.025
8   |   61.712	      |81
9   |   63.139	      |99.162
10    |   58.732	     |76.504

###Máquina três
Iteração   | Tempo de execução (ms) | Desempenho de disco (MB/s)
:------: | :------------: | :------------------------------:
1   |     72.5283             |    62.763
2   |     70.513             |    61.396
3   |     71.817              |    56.272
4   |     69.321             |    57.685
5   |     67.215             |    57.846
6   |     68.823             |    57.035
7   |     73.189              |    62.369
8   |     65.943             |    50.987
9   |     66.876              |    50.571
10   |     62.993             |    49.344

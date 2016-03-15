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
* HD: ?

Especificações da máquina dois:
* Processador: Intel(R) Core(TM) i7-4510U CPU @ 2.00GHz
* Memória: ?
* Cores: 2
* SO: ?
* HD: ?

## Resultados

Iteração   | Tempo de execução (ms) | Desempenho de disco (MB/s)
:------: | :------------: | :------------------------------:
1   |     51.85             |    104.861
2   |     411             |    104.861
3   |     276              |    104.861
4   |     407             |    104.861
5   |     51.85             |    104.861
6   |     411             |    104.861
7   |     276              |    104.861
8   |     407             |    104.861
9   |     276              |    104.861
10   |     407             |    104.861


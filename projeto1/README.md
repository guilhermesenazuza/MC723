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

Logo, para utilizar o programa que nós editamos e fizemos medidas de desempenho, baixe a versão disponível na pasta /projeto1/genetic dentro desse repositório.


## Como compilar/instalar

O código tem uma dependencia, [a biblioteca SDL](https://wiki.libsdl.org/Installation).

Após baixar a versão modificada por nós, basta digitar _make_ para compilar o programa.

## Como executar
Rodar time ./genetic nome_arquivo.bmp. Por exemplo, time ./genetic mona.bmp

## Como medir o desempenho

Para medir o desempenho, utilize o comando _time_ do linux, executando "time ./genetic imagem.bmp" e pegando o valor _real_ escrito na tela no final.
Utilize o valor de real porque é o tempo real gasto entre o começo do programa e o seu final, ao contrário de user e sys que medem o tempo de CPU gasto pelo programa, que nesse caso, não o interessa.
O tempo é dado em segundos pelo comando.

No final, medimos o tempo de escrever a imagem resultante no disco, utilizando funções da biblioteca **time**. Esse tempo é medido em micro segundos, pegamos o tamanho do arquivo escrito em disco e dividimos ele pelo tempo medido na escrita para ter a performace do disco em MB por segundo. Esse dado é impresso na tela no final do programa.

Sugerimos rodar um alto número de iterações do programa e tirar medidas de estatística como média, desvio padrão e variância. Para a máquina base, usamos o número de dez iterações.

## Medições base
Especificações da máquina base:
* Processador: Intel Core i7-Intel(R) Core(TM) i7-4700HQ CPU @ 2.40GHz
* Memória: 16GB DDR3
* Cores: 4
* SO: Ubuntu 14.04LTS
* HD: Western Digital WD10S21X-24R1BTO / 7200RPM / Interface Sata III

Resultados de desempenho para a máquina base:

Iteração   | Tempo de execução (ms) | Desempenho de disco (MB/s)
:------: | :------------: | :------------------------------:
1   |     56.040             |    104.861
2   |     54.421             |    114.809
3   |     54.571              |    111.257
4   |     56.601             |    118.088
5   |     51.251             |    81.212
6   |     55.149             |    87.514
7   |     52.604              |    112.416
8   |     55.169             |    109.537
9   |     53.558              |    115.236
10   |     54.406             |    112.365

Análise estatística sobre esses dados:

Dado | Média   | Desvio Padrão | Variância
:----: | :------: | :------------: | :------------------------------:
Tempo de execução (s) | 54.377  |     1.583             |    2.507
Desempenho de Disco (MB/s) | 106.730  |     12.396            |    153.667
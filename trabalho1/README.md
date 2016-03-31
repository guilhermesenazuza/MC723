# Relatório Projeto 1: Benchmarking
##### Pedro Rodriques Grijó
##### 139715
### Introdução

Este relatório tem por objetivo comparar o desempenho dos computadores utilizados nas partes 1 e 2 do projeto 1 da disciplina MC723 - Laboratório de Projetos de Sistemas Computacionais. Na parte 1, os alunos se separaram em 8 grupos para definição de um benchmark utilizando um programa escolhido por cada grupo. Na parte 2, os grupos foram re-formados, e cada programa da parte 1 teve seu desempenho medido em pelo menos 3 novos computadores. Aqui serão feitas considerações sobre o desempenho das máquinas para cada um dos 8 benchmarks.

### Computadores Utilizados
Máquina | Nome | Especificações Técnicas 
------------ | ------------- | -------------
3 |Mateus Ruivo  | Intel(R) Core(TM) i3-3110M CPU @ 2.40GHz 3072 KB Cache, 4GB RAM DDR3, 5400rpm SATA
4|Pedro Meireles  |Intel® Core™ i5-4590 CPU @ 3.30GHz × 4;  Memory 8 GiB;  64-bit graph: Intel® Haswell Desktop , Gnome: Version 3.18.2; Disk 216.9 GB; Fedora 23 
5|Klaus Rollman  | Intel(R) Core(TM) i7-3610QM CPU 4 cores, 8 threads @ 2.30GHz @ L1 256 KB / L2 1024 KB / L3 6144 KB
6|yk0 - Yugo Kuno  | AMD PhenonII, 4 cores, 3.2MHz; 10GB, ddr3, 1.333 MHz; hdd sata3, 7200rpm, 32MB buffer
7|Cygnus X-1  | Intel® Core™ i7 × 4;  Memory 8 GiB;  
8|Luiz Sekijima  | Intel® Core™2 Duo CPU T6500 @ 2.10GHz × 2, 4GB RAM
9|IC-legiao  | Intel® Core™2 Quad CPU Q8400 @ 2.66GHz × 4 Intel® Q45/Q43 
10|Renan Gomes  | Intel® Core™ i7-4702MQ CPU @ 2.20GHz × 8 (64 bits) Memory 8 GiB; Graphics Intel® Haswell Mobile ; Ubuntu 14.04
11|Bruno Hori - Mamonas  | Intel(R) Core(TM)2 Quad CPU    Q8400  @ 2.66GHz
12|debios  |  Intel(R) Core(TM) i7-3612QM CPU @ 2.10GHz x 4, 8 threads, 8GB, 64-bit, SSD 32GB, HDD1TB (5400rpm), Debian
13|Gabriel Bueno  | Intel(R) Core(TM) i7-4510U CPU @ 2.00GHz x 2, 4 threads, 64-bit; Memory 8 GB DDR3; HD SATA 5400rpm;Ubuntu  15.10
14|Renan Castro  | Intel(R) Core(TM) i7-3740QM CPU @ 2.70GHz @ 2 CORES @ Virtual Machine
15|Gabriel Magalhães  | Intel® Core™ i7-3612QM CPU @ 2.10GHz × 8; Memory 8GB, SSD Kingston 240GB V300 Sata III;  Ubuntu 15.04 
16|Victor Souza  | Intel(R) Core(TM)2 Quad CPU Q8400  @ 2.66GHz; Memory 4GB, Fedora release 21
17|IC301-Titan  | Intel® Core™2 Quad CPU Q8400 @ 2.66GHz × 4 Intel® Q45/Q43, 3.8GB RAM
18|João Fidélis  | Intel Core i7-Intel(R) Core(TM) i7-4700HQ CPU @ 2.40GHz x 4, 16GB DDR3, Ubuntu 14.04LTS, HD: WD10S21X-24R1BTO / 7200RPM / Sata III
19|floyd  | Intel(R) Core(TM)2 Quad CPU    Q8400  @ 2.66GHz, Memory 4GB
20|Rodrigo Silva  | Intel(R) Core(TM) i5-2450M @ 2.5GHZ; Memory 6GB
21|IC-sepultura  | Intel® Core™2 Quad CPU Q8400 @ 2.66GHz × 4 Intel® Q45/Q43 × 3.8GB RAM
22|Pedro Grijó  | Intel(R) Core(TM) i7-2670QM CPU @ 2.20GHz x4, 8GB DDR 1333Mhz ,Ubuntu 14.04LTS 32bits,HDD: SAMSUNG HN-M101MBB / 5400 RPM/ Sata III
23|Pedro Vasconcellos  | Raspberry Pi, 900MHz quad-core ARM Cortex-A7 CPU, 1GB RAM, 32GB SD Card
24|Wendrey  | Intel Core i5-5200U CPU 2.20GHz x 4 L1 32KiB L2 256KiB L3 3MiB Memory 8GiB DDR3 Disk 1TB WDC WD10JPVX-22J Ubuntu 14.04 LTS
25|Matheus Figueiredo  | Intel Core i7-4700HQ CPU @ 2.4GHz, 16GB DDR3, Ubuntu 14.04LTS, HDD 5400RPM
26|Titouan Thibaud  |Intel® Core™ i5-4590 CPU @ 3.30GHz × 4;  Memory 8 GiB;  64-bit graph: Intel® Haswell Desktop , Gnome: Version 3.18.2; Disk 216.9 GB; Fedora 23 
27|Titouan Thibaud  | Intel Core i7-2630QM CPU @2.00GHz Memory 4GiB Linux Mint
28|Rafael Faria  | Intel(R) Core(TM) i7-4750HQ CPU @ 2.00GHz; Memory 8 GB 1600 MHz DDR3; Mac OS X El Capitan (version 10.11.4)
29|João Paulo  | Intel(R) Core(TM) i7-4510U CPU @ 2.00GHz; Memory 16 GB; Ubuntu 14.04.4
30|Matheus Pinheiro  | Intel® Core™ i5-4200U CPU @ 1.60GHz × 4 ; Memory 3,8 GiB; Ubuntu 15.04 64-bit; 
31|Gustavo Basso  |Intel Core i7 @ 2.3GHz; 8 GB 1600 MHz DDR3
32|Netbook - Felipe Emos  | Intel Atom Processor D4xx/D5xx/N4xx/N5xx DMI Bridge

## Programas avaliados pelo meu grupo
### Benchmark 1: Genetic
Programa que recebe uma imagem em formato bmp e a recria com polígonos semi transparentes gerados por um algoritmo genético. Após 50 mil iterações, o programa fornece, para avaliar o desempenho: tempo de execução(s) e desempenho de disco (MB/s).

##### Análise - Tempo de execução
O computador que obteve o menor tempo de execução é o único desktop da lista. Por ser um desktop, seu processador(Intel Core i5-4590) não possui a limitação de potência que costuma ocorrer para os processadores de laptop, portanto possui a maior frequência de clock da lista: 3,30GHz.

Após este, temos uma sequência de 7 laptops com processadores Intel-i7 de diferentes gerações. Os tempos obtidos dentre estes são de pouca diferença, principalmente quando consideramos o desvio padrão. O melhor desempenho deste subgrupo foi de um processador Intel Core i7-4700HQ com 2,4GHz e 16GB de RAM. O pior foi de um Intel Core i7-2670QM com 2,2GHz e 8GB de RAM, sendo que o sistema operacional utilizado neste é de 32 bits, portanto a RAM fica limitada a < 4GB. Nota-se que os computadores Matheus Figueiredo e João Fidélis possuem especificações muito semelhantes, porém desempenhos diferentes. Isso pode ter ocorrido devido a quantidade de processos que era executada em ambas as máquinas durante o benchmark, o que pode ter afetado negativamente a máquina Matheus Figueiredo.

O próximo subgrupo é composto por 3 laptos com processadores de menor desempenho: Intel Core i5-4200U 1,6GHz; Intel Core i3-3110M 2.4GHz; Intel Core 2 Duo T6500 2.10GHz; Os 3 com 4GB de RAM. O desempenho mais fraco é o do Intel Core 2 Duo, que é um processador de geração já ultrapassada se comparado aos i3/i5/i7. 

Por último, temos um Raspberry Pi, com tempo de execução bem inferior aos outros computadores da lista. Isso era esperado, visto que possui um processador com apenas 900MHz de clock e 1GB de RAM

##### Análise - Desempenho de disco
Este parâmetro variou mais que o tempo de execução, porém sua análise correta é inviável, visto que muitas máquinas não possuem informação sobre seus HDDs/SSDs. Quando há informação, é sobre o número de RPM, a qual não é suficiente para se fazer uma análise concreta sobre os resultados obtidos

### Benchmark 4: Gnuplot
Programa de linha de comando para plotar gráficos de funcões matemáticas e outros conjuntos de dados em 2 ou 3 dimensões. Neste benchmark foi analisado o tempo de execução, o tempo de clock e os ciclos de barramento.

##### Análise Geral
O computador Pedro Grijó e o Pedro Vasconcellos possuem desempenhos muito fora do padrão se comparados aos outros resultados obtidos. No primeiro caso, provavelmente ocorreram problemas na execução do Gnuplot que não permitiram a obtenção de dados válidos. O segundo caso se trata de um Raspberry Pi, como já citado no Benchmark 1, e portanto o baixo desempenho era esperado.

Analisando os resultados, nota-se que os 4 primeiros melhores desempenhos de tempo(excluindo o Pedro Grijó) estão nas mesmas posições em relação ao número de clocks e aos ciclos de barramento. Os outros 6 computadores(excluindo o Raspberry Pi) se alternam em relação ao tempo de execução, número de clocks e ciclos de barramento.

É difícil indicar o motivo para os resultados dos 4 primeiros colocados, visto que o computador que ficou em primeiro(Gabriel Magalhães) possui um processador inferior ao que ficou em quarto(Matheus Figueiredo). Uma possibilidade pode ser um número alto de acesso/escrita ao disco feito pelo Gnuplot, o que daria a vantagem para o Gabriel Magalhães devido ao SSD que está máquina possui. Outro motivo pode ser um número alto de processos concorrentes sendo executados no computador Matheus Figueiredo durante o benchmark.

A simetria entre os gráficos dos 3 parâmetros analisados é esperada, visto que são todos altamente dependentes do processador.

### Benchmark 5: Ordenação
Programa que roda vários algoritmos de ordenação para a mesma entrada de tamanho **n** e retorna o tempo de execução de cada um deles.

##### Análise Geral
Primeiramente, nota-se a diferença gerada pelos níveis de complexidade dos algoritmos testados. Enquanto que para o Bubble Sort, Selection Sort e Insertion Sort temos O(n^2) para o caso médio, para o Quicksort temos O(nlgn). 

Nota-se que, como ocorreu para o Benchmark 1, o desktop Pedro Meireles obteve o melhor desempenho. Também pode ser observado que as posições de melhores e piores desempenhos pouco variaram entre os computadores, mesmo com os diferentes algoritmos usados nos testes. 

Como esperado, o Raspberry Pi ocupa a pior posição, seguido de um Netbook com processador Intel Atom, de desempenho fraco se comparado aos processadores Intel i3/i5/i7.

Comentando novamente sobre os algoritmos, como temos Insertion sort com complexidade O(n) para o melhor caso e Selection Sort com complexidade O(n^2) para o melhor caso, o desempenho obtido em relação a estes algoritmos foi o esperado.

## Outros programas

### Benchmark 2: ffmpeg
FFmpeg é um programa de linha de comando que grava, converte e cria stream de áudio e vídeo em diversos formatos. Foram medidos: tempo de execução, page-faults, stalled-cycles-frontend e L1-dcache-load-misses.
##### Análise Geral
O pior tempo de execução foi obtido pela máquina LuizSekijima, o que era de se esperar devido ao processador mais antigo (Intel Core 2 Duo CPU T6500 2.10GHz). Seguindo, temos outros 2 processadores relativamente antigos nas máquinas Victor Souza(Intel(R) Core(TM)2 Quad CPU Q8400 2.66GHz) e yk0 - Yugo Kuno(AMD PhenonII, 4 cores 3.2MHz). Seguindo temos uma sequência de processadores Intel i7 com clocks variados, sendo que os de gerações mais recentes obtiveram melhores desempenhos.

Sobre page-faults e cache misses, nota-se que computadores com processadores mais antigos obtiveram melhor desempenho nos dois casos. Isso deve estar relacionado com uma menor quantidade de cores desses processadores(comparados aos mais recentes) e de memória nos sistemas analisados.



### Benchmark 3: Convolução
Processamento de convoluções em imagens tridimensionais. Foram medidos: melhor tempo e tempo médio em segundos; melhor escrita, escrita média, melhor leitura e leitura média em MB/s.
##### Análise Geral
O pior tempo de execução foi o esperado, devido ao processador antigo(Intel(R) Core(TM)2 Quad Q8400  2.66GHz), porém mesmo assim parece ter sido muito alto. Os melhores tempos pertencem a processadores Intel-i7, mas também há i7 entre os piores tempos, talvez de gerações mais antigas. 

Em relação ao desempenho de disco, não é possível fazer comentários aprofundados pois faltam informações sobre os discos dos computadores utilizados. 

### Benchmark 6: imagemagick
Imagemagick é uma suite de aplicativos para edição não interativa de imagens, ou seja, com ele é possível editar, converter, combinar etc. imagens de dezenas de tipos(https://pt.wikipedia.org/wiki/ImageMagick). Foram medidos tempo de execução, instruções por ciclo, frequência por ciclos clock por tarefas.
##### Análise Geral
Mais uma vez o netbook possui o pior tempo de execução, como esperado. O número de instruções por ciclo é mais alto nos melhores processadores, com o netbook novamente como pior resultado.





### Benchmark 7: tcc
##### Análise Geral


### Benchmark 8: FFTW 
##### Análise Geral






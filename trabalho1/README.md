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


### Benchmark 1: Genetic
Programa que recebe uma imagem em formato bmp e a recria com polígonos semi transparentes gerados por um algoritmo genético. Para avaliar o desempenho, foram medidos: tempo de execução(ms) e desempenho de disco (MB/s).

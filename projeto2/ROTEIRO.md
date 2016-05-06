#Projeto 2 

## Integrantes
- Pedro Rodrigues Grijó 139715
- Titouan Thibaud 180879
- Gabriel Bueno de Oliveira 139455
- Yugo Kuno 033324 
 
## Escolha de Benchmarks
- basicmath
- bitcount
- qsort
- susan

## Estratégias para critérios básicos 


Serão avaliados números de hazards, número de ciclos, tempo de execução, missrates (L1, L2), branch prediction rate e números de ciclos perdidos 

### Configuração de pipeline  
   - 5 estágios
   - 7 estágios
   - 13 estágios

### Configuração de escalabilidade
   - escalar 
   - superescalar


### Configuração branch
- nenhuma branch predictor
- sempre tomar o branch 
- repetir a escolha anterior de branch/não branch

####Hazards
Vamos trabalhar com dois tipos de hazards: hazards de dados e hazards de controle. 

O hazard de dados surge quando uma instrução tem uma dependência com uma instrução anterior que ainda não foi finalizada, ou seja, dados necessários à instrução atual não estão disponíveis. Existem três tipos de hazards de dados: 
- Read After Write (RAW) : i2 tenta ler uma informação antes que i1 tenha escrito ela. Por exemplo : 
i1. R2 <- R1 + R3
i2. R4 <- R2 + R3

Esse hazard consegue ser resolvido por forwarding.

- Write After Read (WAR) : i2 tenta escrever numa destinação antes que i1 tenha lido ela. Por exemplo :
i1. R4 <- R1 + R5
i2. R5 <- R1 + R2

Nesse caso tem que adicionar uma bolha, o que significa perder um ciclo.

- Write After Write (WAW) : i2 tenta escrever uma operand antes que ela esteja escrita por i1. Por exemplo :
i1. R2 <- R4 + R7
i2. R2 <- R1 + R3



Os hazards de controle correspondem a seguinte situação: quando ocorre uma instrução de branch, até a execução da instrução que decide se o branch deve ser tomado não saberemos qual será a instrução seguinte. Para resolver esse problema temos as seguintes estratégias:
- sem branch prediction: esperamos até a execução da instrução que decide se temos que fazer o branch ou não. Essa estrategia faz perder tempo.
- estática: always taken ou never taken. No caso de erro, há penalidade de tempo.
- dinâmica: guardando um histórico, poderemos fazer uma previsão dinâmica que dependente do que aconteceu anteriormente. Nesse caso também, só há penalidade de tempo quando a predição não acertar. 

Iremos contabilizar os hazards de controle junto com a execução do branch prediction. 

No caso dos hazards de dados, não precisamos contabilizar os que podem ser resolvidos por forwarding.
Para contabilizar os hazards que não podem ser resolvidos por forwarding, podemos usar um pequeno histórico para ver se a instrução atual depende de alguma das instruções que ainda estão no pipline.


### Configuração cache

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

### Configurações finais
|configurações|conf. 1|conf. 2|conf. 3|conf. 4|conf. 5|conf. 6|conf. 7|conf. 8|
|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|tamanho de pipeline|5|7|13|5|5|5|5|5|5|
|escalar/superescalar|escalar|escalar|escalar|superescalar|superescalar|superescalar|superescalar|superescalar|superescalar|
|branch predictor|always|always|always|always|no prediction|repeat|repeat|repeat|repeat|
|cache|cache 1|cache 1|cache 1|cache 1|cache 1|cache 1|cache 2|cache 3|cache 4|

## Roteiro dos experimentos
### Semana 1
Avaliar o resultado de cada configuração de cache.
Começar o impacto dos hazards e do processador escalar e super escalar.
### Semana 2
Implementação dos hazards.
Implementar os pipelines (5, 7, 13estágios).
### Semana 3
Terminar a implementação dos processadores escalar/superescalar.
Rodar os testes e escrever o relatório final.





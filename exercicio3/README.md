# Relatório Exercício 3                                                                  

##### Pedro Rodrigues Grijó
##### 139715

##Contando instruções
Inicialmente o arquivo **mips_isa.cpp** foi modificado para que as instruções add fossem contabilizadas. Esta tarefa foi realizada com um contador global inteiro. Esse contador é incrementado de 1 unidade a cada passagem pela função add.
<br/>

Um programa "Hello, World!"([hello.c](https://github.com/pedrogrijo/MC723/blob/master/exercicio3/hello.c)) básico foi escrito e testado em busca do uso da instrução add pelo MIPS. Como o programa não realiza cálculos aritméticos, **nenhum add foi contabilizado**.

Para tentar forçar o uso da instrução add, foi escrito o programa [arithmetics.c](https://github.com/pedrogrijo/MC723/blob/master/exercicio3/arithmetics.c), que faz soma, subtração, multiplicação e divisão. Mais uma vez, **nenhum add foi contabilizado**.

Utilizando a ferramenta **objdump**([arithmetics_objdump](https://github.com/pedrogrijo/MC723/blob/master/exercicio3/arithmetics_objdump.txt)) e checando o output da função main, foram encontrados apenas **addu** e **addiu** 

Checando o arquivo **mips_isa.cpp** para entender a diferença entras essas funções, foi observado que a função **add** imprime um erro para casos de overflow de inteiros, enquanto que **addu** e **addiu** não o fazem. 

Para entender o funcionamento da função **addu** em relação a inteiros com sinal, foi escrito o programa [signed_arithmetics.c](https://github.com/pedrogrijo/MC723/blob/master/exercicio3/signed_arithmetics.c). O entendimento foi de que **addu** devolve o resultado esperado mesmo operando com inteiros com sinal, a diferença está no fato de que não há tratamento para casos de overflow, que neste caso devem ser tratados pelo programador.

Sobre a **política da linguagem C** com relação a overflows em operações com inteiros, se forem inteiros sem sinal(declarados como unsigned), não ocorrerá overflow, pois de acordo com a C Standard Library: *"A computation involving unsigned operands can never overflow, because a result that cannot be represented by the resulting unsigned integer type is reduced modulo the number that is one greater than the largest value that can be represented by the resulting type."*. Porém, no caso de signed integers: *"If an exceptional condition occurs during the evaluation of an expression (that is, if the result is not mathematically defined or not in the range of representable values for its type), the behavior is undefined."* (http://c0x.coding-guidelines.com/index.html)

## Avaliando o desempenho
Os programas avaliados e seus resultados seguem abaixo

###Lame(7)

| Categoria        | Instruções           | Ciclos  |
| ------------- |:-------------:| -----:|
| Acesso à memória      | 1643642840 | 16436428400 |
| Controle (branch/jump)      | 1053533660      |   3160600980 |
| Outras | 3806668037      |    3806668037 |
| Total |6503844537 |23403697417 |

[Lame Small Output](https://github.com/pedrogrijo/MC723/blob/master/exercicio3/lame_small.txt)

###Rijndael coder(small)(1)

| Categoria        | Instruções           | Ciclos  |
| ------------- |:-------------:| -----:|
| Acesso à memória      |13706334  | 137063340 |
| Controle (branch/jump)      |   1600121    |  4800363  |
| Outras |    31164158   |   31164158  |
| Total |46470613 | 173027861|

[Rijndael Coder Small Output](https://github.com/pedrogrijo/MC723/blob/master/exercicio3/rijndael_coder_small_output.txt)

###Rijndael coder(large)(5)

| Categoria        | Instruções           | Ciclos  |
| ------------- |:-------------:| -----:|
| Acesso à memória      | 142712100 |1427121000  |
| Controle (branch/jump)      |    16654333   |   49962999 |
| Outras |      324496155 |   324496155  |
| Total | 483862588| 1801580154|

[Rijndael Coder Large Output](https://github.com/pedrogrijo/MC723/blob/master/exercicio3/rijndael_coder_large_output.txt)

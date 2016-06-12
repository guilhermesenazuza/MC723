# Relatório Exercício 4                                                                  

##### Pedro Rodrigues Grijó
##### 139715

Inicialmente foi criada a aplicação ([hello_world.c](https://github.com/pedrogrijo/MC723/blob/master/exercicio4/hello_world.c)) para observar a execução do simulador. A aplicação faz escrita no endereço base(1024*1024*100 = 0x6400000) do periférico. Abaixo está a saída do simulador:

Após isso, foram modificadas as funções readm e writem do programa ac_tlm_peripheral.cpp para armazenar e manipular os valores lidos/escritos, e a aplicação ([hello_modified.c](https://github.com/pedrogrijo/MC723/blob/master/exercicio4/hello_modified.c)) foi criada. O ponteiro de acesso ao periférico dessa aplicação foi declarado como **volatile**

## Referências

1. https://en.wikipedia.org/wiki/Volatile_(computer_programming)

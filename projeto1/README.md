# Programa ? - GENETIC

## O que faz? Para que serve?

O programa recria a imagem através de polígonos semi transparentes que são gerados por um algoritmo genético. O programa não tem um propósito certo, apenas é algo interessante.

## Por que é bom para medir desempenho?

O programa pode ser rodado por um tempo arbitrário, então é um bom algoritmo para fazer um benchmark. No nosso benchmark, usaremos 50 mil iterações.

O programa também é bom, pois existe um potencial de paralelização.

Que tipo de atividade ele estÃ¡ medindo? Somente desempenho do processador? Desempenho do disco? Algo mais? Processador single-core, multi-core?

## O que baixar

O código pode ser baixado em: http://www.ggsoft.org/archives/genetic.zip.
Na versão original, o programador esqueceu alguns includes no arquivo _streamer.h_, que foi corrigido para que o programa rodasse corretamente. É necessário incluir:

* _cstdio_
* _cstring_

O código tem uma dependencia, [a biblioteca SDL](https://wiki.libsdl.org/Installation).

## Como compilar/instalar
O programa deverÃ¡ ser instalado no computador, compilado localmente. NÃ£o deixar o binÃ¡rio disponÃ­vel. NÃ£o deve ser necessÃ¡rio instalar como administrador do computador (root)

## Como executar
InstruÃ§Ãµes para execuÃ§Ã£o. Se seu programa precisa de entradas, vocÃª deve fornece-las para que todos executem corretamente.

## Como medir o desempenho
Como que o desempenho Ã© medido atravÃ©s deste programa? Se for atravÃ©s de tempo, vocÃª deve especificar claramente qual tempo deverÃ¡ ser utilizado e indicar o motivo aqui. Quantas vezes a medida deverÃ¡ ser feita? O que fazer com ela (mÃ©dia, etc) ? NÃ£o especificar o tempo serÃ¡ considerado falha grave.

## Como apresentar o desempenho
Como o desempenho deverÃ¡ ser mostrado. Margem de erro, etc. 

## MediÃ§Ãµes base (uma mÃ¡quina)
Inclua a especificaÃ§Ã£o dos componentes relevantes e os resultados de desempenho.

# Otimização_Multimodal_GA
Aplicação da função de otimização multimodal para encontrar o mínimo local, utilizando-se a abordagem de algoritmos genéticos

## Descrição 

<ul>
  <li> Os números do espaço de estados são gerados aleatoriamente no intervalo de -10 a 10, com 4 casas decimais </li>
  <li> O objetivo é encontrar o mínimo global </li>
  <li> Parâmetros: tamanho da população, número de gerações, probabilidade de mutação e probabilidade de cruzamento </li>
</ul>

<div style="display: block; margin-left: auto; margin-right: auto;">
  <img height="110" width="400" src="img/equation.jpg">
</div>

## Execução do programa pelo terminal

É necesário realizar a instalação do C++ e seus compiladores antes de executar o programa. Para instalar no windows, basta procurar algum instalador de IDE e intalar o ser executável. Para instalar no Linux, basta executar os comandos:

```
sudo apt update
```
```
sudo apt install build-essential
```

Para executar o programa pelo terminal basta abrir o terminal no diretporio do código fonte, compilá-lo e executá-lo utilizando os comandos abaixo.


Para compilar:
```
g++ geneticAlg.cpp -o exec
```

Para executar:
```
./exec
```
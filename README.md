# Representacao-Computacional-de-Grafos-de-Listas-de-Adjacencia
Tanto a matriz de adjacência como a matriz de incidência são representações que consomem muito espaço de memória, principalmente se o grafo representado é um grafo relativamente esparso. Uma estrutura mais conveniente e econômica é a lista de adjacência.

## A estrela é uma estrutura com dois componentes:
- i) na primeira componente temos uma entrada para cada vértice e um
ponteiro para uma posição na segunda componente que contém a lista de
adjacências;

- ii) a segunda componente compreende as listas de adjacências de todos os
vértices.
  - l A estrutura é mais difícil de atualizar que as listas de adjacência simples.

  - l Explora melhor a “esparsidade” do grafo e ocupa menos espaço que outras
estruturas de dados.

  - l Bastante útil em algoritmos que buscam arcos específicos a partir de um
nó.


  - Feito por: Lucas Garcia E Luis Augusto
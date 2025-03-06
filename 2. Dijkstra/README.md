# Algoritmo de Dijkstra - Grafo com Arestas e Vértices

Este programa implementa o **Algoritmo de Dijkstra** para encontrar os caminhos mínimos entre um vértice de origem e os outros vértices de um grafo ponderado, utilizando uma estrutura de dados de grafo com listas de adjacência.

## Funcionalidades

- **Inserção de Vértices**: Permite adicionar vértices ao grafo.
- **Inserção de Arestas**: Permite adicionar arestas entre vértices com um peso associado.
- **Algoritmo de Dijkstra**: Calcula a menor distância do vértice de origem para todos os outros vértices do grafo.
- **Impressão de Caminhos Mínimos**: Mostra a menor distância de um vértice para a origem, utilizando o algoritmo de Dijkstra.

## Estruturas de Dados

- **Grafo**: Representado por uma estrutura contendo vértices e arestas com listas de adjacência.
- **Vértice**: Cada vértice tem uma lista de adjacência para armazenar as arestas conectadas.
- **Aresta**: Cada aresta tem um vértice de destino e um peso associado.

## Como Usar

1. Compile o código:
   ```bash
   gcc -o dijkstra dijkstra.c
   ```

2. Execute o programa:
   ```bash
   ./dijkstra
   ```

3. O programa oferece as seguintes opções no menu interativo:
   - **0**: Sair
   - **1**: Inserir um vértice e adicionar aresta entre vértices.
   - **2**: Imprimir o caminho mínimo de um vértice até a origem usando Dijkstra.

### Exemplo de Execução

```bash
0 - Sair
1 - Inserir Vértice
2 - Imprimir Caminhos Mínimos

Escolha a opção: 1
Digite o valor a ser inserido: 1
Digite o antecessor do valor a ser inserido: 0
Digite o peso da aresta: 10

0 - Sair
1 - Inserir Vértice
2 - Imprimir Caminhos Mínimos

Escolha a opção: 2
Digite o vértice que deseja saber o caminho minimo: 1
A menor distância do nó 1 até a origem é 10
```

## Funções Importantes

- **`inicializaD()`**: Inicializa os vetores de distâncias e predecessores para o algoritmo de Dijkstra.
- **`relaxa()`**: Realiza a operação de relaxamento de aresta durante o algoritmo.
- **`dijkstra()`**: Implementa o algoritmo de Dijkstra para encontrar as distâncias mínimas.
- **`existeAberto()`**: Verifica se há algum vértice aberto (não visitado).
- **`menorDist()`**: Encontra o vértice com a menor distância ainda não processada.
- **`imprimirDistancia()`**: Imprime a menor distância de um vértice até a origem.

# Árvore AVL

A árvore AVL (Árvore Binária de Busca Balanceada) é uma estrutura de dados auto-balanceada onde a diferença de altura entre as subárvores de qualquer nó é no máximo 1. A árvore realiza rotações automaticamente para manter o balanceamento após inserções e remoções.

## Funcionalidades

- **Inserção:** Adiciona um novo nó à árvore mantendo o balanceamento.
- **Remoção:** Remove um nó da árvore e reequilibra a estrutura, se necessário.
- **Busca:** Procura por um valor específico na árvore.
- **Impressão:** Exibe a árvore de forma visual (em formato "lado a lado").
- **Balanceamento:** A árvore realiza rotações simples e duplas (à esquerda e à direita) quando necessário para garantir o balanceamento.

## Estrutura de Dados

A árvore AVL é representada por um nó que contém:
- `valor`: o valor do nó.
- `esquerdo`: ponteiro para o filho esquerdo.
- `direito`: ponteiro para o filho direito.
- `fb`: fator de balanceamento do nó (a diferença entre a altura da subárvore direita e esquerda).

## Funções

- **`cria_no(int num)`**: Cria um novo nó com o valor `num`.
- **`max(int a, int b)`**: Retorna o maior valor entre `a` e `b`.
- **`altura(Pont p)`**: Calcula a altura de uma sub-árvore.
- **`rotacao_L(Pont p)`**: Realiza rotação à esquerda para balancear a árvore.
- **`rotacao_R(Pont p)`**: Realiza rotação à direita para balancear a árvore.
- **`atualiza_balanceamento_raiz(Pont raiz)`**: Atualiza o fator de balanceamento de um nó.
- **`inserir(No *raiz, int num)`**: Insere um novo nó na árvore AVL.
- **`buscar_no(Pont raiz, int num)`**: Busca um nó na árvore com o valor `num`.
- **`remover(Pont raiz, int num)`**: Remove um nó da árvore com o valor `num`.
- **`imprimir(No *raiz, int nivel)`**: Imprime a árvore em formato visual.

## Como Usar

1. Compile o código:

```bash
gcc avl.c -o avl
```

2. Execute o programa:

```bash
./avl
```

3. O menu do programa permite escolher entre as seguintes opções:
   - **0 - Sair**: Encerra o programa.
   - **1 - Inserir**: Insere um valor na árvore AVL.
   - **2 - Remover**: Remove um valor da árvore AVL.
   - **3 - Buscar**: Busca um valor na árvore.
   - **4 - Imprimir**: Exibe a árvore AVL no formato visual.

## Exemplo de Execução

A imagem a seguir representa a inserção da sequência: 5, 6, 2 3, 1, 7 e 8. Observe que a árvore fica representada de lado.  

<p align="center">
  <img src="avl.png" alt="Árvore AVL">
</p>


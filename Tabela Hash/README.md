# Tabela Hash

## Descrição

Este programa implementa uma tabela hash utilizando o método da multiplicação para calcular o índice dos elementos na tabela. O código inclui as operações básicas de inserção, remoção, busca e impressão dos elementos da tabela, além de resolver colisões utilizando listas encadeadas.

## Funcionalidades

O programa oferece as seguintes funcionalidades:

- **Inserção**: Insere um valor na tabela hash.
- **Remoção**: Remove um valor da tabela hash.
- **Busca**: Busca um valor na tabela hash.
- **Impressão**: Exibe a tabela hash, mostrando as posições e valores armazenados.

## Estruturas de Dados

### `No`

Representa um nó da lista encadeada utilizada para resolver colisões na tabela hash. Cada nó contém:

- `posicao`: A posição na tabela onde o valor está armazenado.
- `valor`: O valor armazenado no nó.
- `proximo`: Ponteiro para o próximo nó na lista encadeada.

### `TabelaHash`

Representa a tabela hash. Contém:

- `quantidade`: A quantidade de elementos armazenados na tabela.
- `tamanho`: O tamanho da tabela.
- `itens`: Vetor de ponteiros para os nós da tabela hash.

## Funções

### `criar_tabela(int tamanho)`

Cria uma tabela hash com o tamanho especificado.

**Parâmetros**:
- `tamanho`: O tamanho desejado para a tabela hash.

**Retorna**:
- Ponteiro para a tabela hash criada, ou `NULL` em caso de falha na alocação.

### `libera_hash(TabelaHash *th)`

Libera a memória alocada para a tabela hash e seus nós.

**Parâmetros**:
- `th`: Ponteiro para a tabela hash a ser liberada.

### `decimal_para_binario(int decimal)`

Converte um número decimal para uma representação binária de 10 bits e retorna os 6 bits centrais.

**Parâmetros**:
- `decimal`: O número decimal a ser convertido.

**Retorna**:
- Os 6 bits centrais representados como um valor decimal.

### `chave_multiplicacao(int chave, int tamanho_tabela)`

Calcula o índice de inserção usando o método da multiplicação, baseando-se no quadrado da chave.

**Parâmetros**:
- `chave`: A chave para a qual o índice será calculado.
- `tamanho_tabela`: O tamanho da tabela hash.

**Retorna**:
- O índice calculado para a chave na tabela.

### `inserir(int chave, TabelaHash *th)`

Insere uma chave na tabela hash.

**Parâmetros**:
- `chave`: A chave a ser inserida.
- `th`: Ponteiro para a tabela hash.

**Retorna**:
- 0 em caso de sucesso, ou um valor indicando erro.

### `remover(int chave, TabelaHash *th)`

Remove uma chave da tabela hash.

**Parâmetros**:
- `chave`: A chave a ser removida.
- `th`: Ponteiro para a tabela hash.

**Retorna**:
- 1 se a chave for removida com sucesso, ou 0 se a chave não for encontrada.

### `buscar(int chave, TabelaHash *th)`

Busca uma chave na tabela hash.

**Parâmetros**:
- `chave`: A chave a ser buscada.
- `th`: Ponteiro para a tabela hash.

**Retorna**:
- Ponteiro para o nó encontrado, ou `NULL` se a chave não for encontrada.

### `imprimir_tabela(TabelaHash *th)`

Imprime os elementos da tabela hash, mostrando as posições e valores.

**Parâmetros**:
- `th`: Ponteiro para a tabela hash.

---

## Como Usar

1. Compile o programa:

   ```bash
   gcc -o tabela_hash tabela_hash.c
   ```

2. Execute o programa:

   ```bash
   ./tabela_hash
   ```

3. O programa exibirá um menu com as seguintes opções:

   - **0**: Sair.
   - **1**: Inserir um valor na tabela hash.
   - **2**: Remover um valor da tabela hash.
   - **3**: Buscar um valor na tabela hash.
   - **4**: Imprimir a tabela hash.

## Exemplo de Execução

```text
    0 - Sair
    1 - Inserir
    2 - Remover
    3 - Buscar
    4 - Imprimir

    Digite a opção: 1
    Digite a chave a ser inserida: 25

    Digite a opção: 4

    Tabela Hash:
    0 -> {25} -> NULL
    1 -> NULL
    2 -> NULL
    ...

    Digite a opção: 0
```

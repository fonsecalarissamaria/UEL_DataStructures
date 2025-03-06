#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//Estruturas 
struct no
{
    int posicao;
    int valor;
    struct no *proximo; 
};

typedef struct no No;

struct tabelaHash
{
    int quantidade, tamanho; 
    No **itens; 
};

typedef struct tabelaHash TabelaHash; 




/**
 * Cria uma nova tabela hash com o tamanho especificado.
 *
 * @param tamanho O tamanho desejado da tabela hash.
 * @return Um ponteiro para a tabela hash recém-criada ou NULL se a alocação de memória falhar.
 */
TabelaHash* criar_tabela(int tamanho)
{
    TabelaHash *th = (TabelaHash*) malloc(sizeof(TabelaHash)); //Alocando um espaço pra tabela 
    if(th)
    {
        th->tamanho = tamanho; 
        th->itens = (No**) malloc(tamanho * sizeof(No*)); //Alocando os nós da tabela 
        if(th->itens == NULL)
        {
            free(th);
            return NULL; //Caso não tenha dado certo alocar os nós da tabela 
        }
        
        th->quantidade = 0; //Quantidade inicial é zero 
        for(int i=0; i < th->tamanho; i++)
            th->itens[i] = NULL; //Fazendo cada nó da tabela apontar pra nulo, inicialmente 
    }
    return th; 
}




/**
 * Libera a memória alocada para uma tabela hash e seus nós.
 * @param th Um ponteiro para a tabela hash a ser liberada.
 */
void libera_hash(TabelaHash *th)
{
    if(th)
    {
        for(int i=0; i < th->tamanho; i++)
        {
            if(th->itens[i])
                free(th->itens[i]);
        }
        free(th->itens);
        free(th);
    }
}




/**
 * Converte um número decimal em uma representação binária de 10 bits
 * e obtém os 6 bits centrais como um valor decimal.
 *
 * @param decimal O número decimal a ser convertido.
 * @return Os 6 bits centrais do número binário resultante, representados como um valor decimal.
 */
int decimal_para_binario(int decimal) 
{
    int binario = 0;
    int peso = 1;

    //Colocando em 10 bits 
    for (int i = 0; i < 10; i++) 
    {
        int digito = decimal % 2;
        binario += digito * peso;
        peso *= 10;
        decimal /= 2;
    }

    //Obtendo os 6 bits centrais já em decimal 
    int bits_centrais = (binario >> 2) & 0x3F;
    return bits_centrais;
}




/**
 * Calcula o índice de inserção na tabela hash usando o método da multiplicação.
 * Converte o quadrado da chave em uma representação binária de 10 bits e ajusta o índice
 * para garantir que esteja dentro dos limites da tabela.
 *
 * @param chave A chave a ser usada no cálculo.
 * @param tamanho_tabela O tamanho da tabela hash.
 * @return O índice calculado para inserção na tabela hash.
 */
int chave_multiplicacao(int chave, int tamanho_tabela) 
{   
    double quadrado = chave * chave; // Calculando o quadrado da chave
    int endereco = decimal_para_binario(quadrado);

    //Garantindo que o índice esteja dentro dos limites da tabela
    endereco = endereco % tamanho_tabela;

    return endereco;
}




/**
 * Insere um elemento na tabela hash usando o método da multiplicação.
 * Calcula a posição na tabela usando a chave e insere o elemento na posição correspondente.
 * Se a posição já estiver ocupada, o novo elemento é adicionado no início da lista encadeada.
 *
 * @param chave A chave do elemento a ser inserido.
 * @param th Um ponteiro para a tabela hash onde o elemento será inserido.
 * @return 0 se a inserção for bem-sucedida, caso contrário, um valor indicando erro.
 */
int inserir(int chave, TabelaHash *th) 
{
    int posicao_hash = chave_multiplicacao(chave, th->tamanho);

    No *novo = (No*)malloc(sizeof(No));
    novo->valor = chave; 
    novo->posicao = posicao_hash;
    novo->proximo = NULL;

    //Verifica se a posição está vazia
    if (th->itens[posicao_hash] == NULL) 
    {
        th->itens[posicao_hash] = novo;
    } else 
    {
        // Se a posição não estiver vazia, insira o novo elemento no início da lista encadeada
        novo->proximo = th->itens[posicao_hash];
        th->itens[posicao_hash] = novo;
    }

    return 0; 
}




/**
 * Remove um elemento da tabela hash com base em sua chave.
 * Calcula a posição na tabela usando a chave e remove o elemento da posição correspondente.
 *
 * @param chave A chave do elemento a ser removido.
 * @param th Um ponteiro para a tabela hash onde o elemento será removido.
 * @return 1 se a remoção for bem-sucedida, 0 se a chave não for encontrada.
 */
int remover(int chave, TabelaHash *th) 
{
    int posicao = chave_multiplicacao(chave, th->tamanho);

    No *atual = th->itens[posicao];
    No *anterior = NULL;

    // Percorrendo os elementos nessa posição procurando a chave
    while (atual != NULL) 
    {
        if (atual->valor == chave) 
        {
            // Encontrou a chave
            if (anterior == NULL) 
            {
                // Se o elemento é o primeiro da lista, atualizando o ponteiro da posição
                th->itens[posicao] = atual->proximo;
            } else
            {
                // Se o elemento não é o primeiro, atualizando o ponteiro do elemento anterior
                anterior->proximo = atual->proximo;
            }

            free(atual); //removendo o elemento
            return 1; 
        }

        anterior = atual;
        atual = atual->proximo;
    }

    //Chave não encontrada
    return 0; 
}




/**
 * Busca um elemento na tabela hash com base em sua chave.
 * Calcula a posição na tabela usando a chave e procura o elemento na posição correspondente.
 *
 * @param chave A chave do elemento a ser buscado.
 * @param th Um ponteiro para a tabela hash onde o elemento será buscado.
 * @return Um ponteiro para o elemento encontrado ou NULL se a chave não for encontrada.
 */
No* buscar(int chave, TabelaHash *th) 
{
    int posicao = chave_multiplicacao(chave, th->tamanho);

    //indo para a posição na tabela hash
    No *atual = th->itens[posicao];

    //Percorrendo os elementos nessa posição
    while (atual != NULL) 
    {
        if (atual->valor == chave) //Encontrou a chave
            return atual;
        
        atual = atual->proximo;
    }

    //Se não encontrar 
    return NULL;
}




/**
 * Imprime os elementos da tabela hash, mostrando suas posições e os valores associados.
 * @param th Um ponteiro para a tabela hash a ser impressa.
 */
void imprimir_tabela(TabelaHash *th)
{
    int posicao; 
    printf("\n\n");
    for(posicao=0; posicao < th->tamanho; posicao++)
    {
        printf("\t%d ", posicao);
        No *aux = th->itens[posicao]; //Printa todas as posições da tabela 
        while(aux)
        {
            printf("{%d} -> ", aux->valor);
            aux = aux->proximo; //Avançando em cada nó inserido 
        }
        printf("NULL\n");
    }
    printf("\n\n");
}




int main()
{
    TabelaHash *th = criar_tabela(41); //escolher um número primo 
    int opcao, chave, valor; 


    do{
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2- Remover\n\t3- Buscar\n\t4- Imprimir\n\n");
        scanf("%d", &opcao);
        
        switch(opcao)
        {
        case 0:     
            break;
        case 1: 
            printf("\n\tDigite a chave a ser inserida: ");
            scanf("%d", &chave);
			inserir(chave, th);
        	break;
        case 2: 
            printf("\n\tDigite o valor a ser removido: ");
            scanf("%d", &chave);
            int remov = remover(chave, th); 
            if(remov == 1)
            {
                printf("\n\tValor %d removido com sucesso.\n", chave);
            }else
            {
                printf("\n\tValor não encontrado!\n");
            }
            break;
        case 3:
            printf("\n\tDigite o valor que deseja buscar:\n\t");
            scanf("%d", &valor);
            No* busca = buscar(chave, th);
            if(busca)
            {
                printf("\n\tValor %d encontrado na posição %d da tabela.\n", busca->valor, busca->posicao);
            }else
            {
                printf("\n\tValor não encontrado!\n");
            }
            break;
        case 4:
            imprimir_tabela(th); 
            break; 
        default:
            printf("\n\tOpção inválida!\n");
        }
	}while(opcao!=0);
}

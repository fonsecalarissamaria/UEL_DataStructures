#include <stdio.h>
#include <stdlib.h> 



typedef struct no
{
    int valor;
    struct no *esquerdo, *direito; 
    int fb; //fator de balanceamento 
}No, *Pont;


/**
 * Função que cria um novo nó 
 * @param num valor a ser inserido no nó 
 * @return o endereço do nó criado 
*/
Pont cria_no(int num)
{
    Pont novo_no = malloc(sizeof(No)); 

    if(novo_no)
    {
        novo_no->valor = num;
        novo_no->direito = NULL; 
        novo_no->direito = NULL;  
        novo_no->fb = 0; 
    }else
    {
        printf("\nERRO ao alocar nó em cria_no!\n");
        return NULL;
    }
    
    return novo_no; 
}


/**
 * Retorna o maior valor entre dois inteiros
 * @param a inteiro qualquer 
 * @param b inteiro qualquer 
 * @return o maior valor entre a e b 
*/
int max(int a, int b){
	if (a>b) return a;
	return b;
}



/**
 * Retorna a altura de uma sub-árvore
 * 
 * @param raiz Ponteiro para o nó raiz da árvore que será calculada a sua altura.
 * @return Um número inteiro que representa a altura da árvore ou -1 caso a árvore não tenha nenhum elemento
*/
int altura(Pont p)
{
	if (p == NULL) 
        return -1;
	else 
        return 1 + max(altura(p->esquerdo),altura(p->direito));
}




/**
 * Rotaciona à esquerda (LL ou LR)
 * @param p nó que possui o fator de balanceamento menor ou igual a -2
 * @return um ponteiro para a nova raiz que foi definida 
*/
Pont rotacao_L(Pont p)
{
	printf("\n\tRotação à esquerda, problema no nó: %i\n",p->valor);
    Pont u, v; 
    u = p->esquerdo;

    if(u->fb == -1) //Simples LL
    {
        p->esquerdo = u->direito; 
        u->direito = p; 

        p->fb = 0;
        u->fb = 0;

        return u; 
    }else if(u->fb == 1) //Dupla LR
    {
        v = u->direito;
        u->direito = v->esquerdo; 
        v->esquerdo = u; 
        p->esquerdo = v->direito; 
        v->direito = p;

        if(v->fb == -1)
            p->fb = 1;
        else 
            p->fb = 0;
        
        if(v->fb == 1)
            u->fb = -1;
        else 
            u->fb = 0;

        v->fb = 0; 

        return v; 
    }else // caso necessario para a exclusao (u->fb == 0)
    {   
		p->esquerdo = u->direito;
		u->direito = p;
		u->fb = 1;
		
        return u;
	}
}



/**
 * Rotaciona à direita (RR ou RL) 
 * @param p nó que possui o fator de balanceamento maior ou igual a +2
 * @return um ponteiro para a nova raiz que foi definida 
*/
Pont rotacao_R(Pont p)
{
	printf("\n\tRotação à direita, problema no nó: %i\n",p->valor);
    Pont u, v; 
    u = p->direito;

    if(u->fb == 1) //Simples RR
    {
        p->direito = u->esquerdo; 
        u->esquerdo = p; 

        p->fb = 0;
        u->fb = 0; 

        return u; 
    }else if(u->fb == -1) //Dupla RL
    {
        v = u->esquerdo; 
        u->esquerdo = v->direito; 
        v->direito = u; 
        p->direito = v->esquerdo; 
        v->esquerdo = p; 
 
        if(v->fb == 1) 
            p->fb = -1;
		else 
            p->fb = 0;
		if(v->fb == -1) 
            u->fb = 1;
		else 
            u->fb = 0;
		
        v->fb = 0;

        return v; 
    }else // para a exclusao (u->fb == 0)
    {   
		p->direito = u->esquerdo;
		u->esquerdo = p;
		u->fb = -1;

        return u;	
	}
}


/**
 * Retorna o fator de balanceamento da raiz.
 * @param raiz nó que está desbalanceado 
 * @return novo fator de balanceamento 
*/
int atualiza_balanceamento_raiz(Pont raiz)
{
	if (!raiz) 
        return 0;
	int dir = altura(raiz->direito);
	int esq = altura(raiz->esquerdo);
	
    raiz->fb = dir - esq;

    return raiz->fb; 
}




/**
 * Insere um novo nó na árvore AVL
 * @param raiz Passa uma "CÓPIA" DO ENDEREÇO que o ponteiro raiz guarda 
 * @return retorna um ponteiro para o novo nó inserido para que de fato a função no main seja modificada 
 * @note função com recursividade 
*/
No* inserir(No *raiz, int num) 
{
    if(raiz == NULL) //Se o conteúdo da cópia do endereço que o ponteiro guarda é nulo
    {
        return cria_no(num);
    }else //Analisar se é > ou < que a raiz e identificar se vou pra esquerda ou direita 
    {
        if(num < raiz->valor)
            raiz->esquerdo = inserir(raiz->esquerdo, num); 
        else if(num > raiz->valor)
            raiz->direito = inserir(raiz->direito, num); 
        else 
            printf("\n\tInserção não realizada pois o elemento %d já existe.\n", num);
    }

    //Recalcula o fator de balanceamento 
    raiz->fb = atualiza_balanceamento_raiz(raiz); 
    //printf("Fb: %d\n\n", raiz->fb);
    
    //verifica a necessidade de rebalancear a árvore 
    if(raiz->fb > 1)
        raiz = rotacao_R(raiz); 
    else if(raiz->fb < -1)
        raiz = rotacao_L(raiz); 

    return raiz; 
}



/**
 * Realiza uma busca pelo nó que possui o valor inteiro 'num' 
 * 
 * @param raiz Ponteiro para o nó raiz da árvore onde a busca é realizada
 * @param num Número a ser buscado na árvore
 * 
 * @return Um ponteiro para o nó que contém o valor buscado, ou NULL se não for encontrado
 */
Pont buscar_no(Pont raiz, int num)
{
    while(raiz)
    {
        if(num < raiz->valor)
        {
            raiz = raiz->esquerdo;
        }else if(num > raiz->valor)
        {
            raiz = raiz->direito;
        }else if(num == raiz->valor)
        {
            return raiz; 
        }
    }
    
    return NULL; //Se a raiz for NULA ou se não existir o nó
}


/**
 * Remove o nó que possui o valor inteiro 'num' 
 * 
 * @param raiz Ponteiro para o nó raiz da árvore 
 * @param num Número a ser removido da árvore
 * 
 * @return Um ponteiro para o nó que contém o valor buscado, ou NULL se não for encontrado
 */
Pont remover(Pont raiz, int num)
{
    if(raiz == NULL)
    {
        printf("Nó não encontrado!\n");
        return NULL;
    }else
    {
        if(raiz->valor == num)
        {
            if((raiz->esquerdo == NULL) && (raiz->direito == NULL))
            {
                //remove o nó FOLHA
                free(raiz);
                printf("\n\tElemento folha removido: %d!\n", num);
                return NULL; 
            }else if((raiz->esquerdo) && (raiz->direito))
            {
                //remove o nó que tem dois filhos
                No *aux = raiz->esquerdo; 
                
                while(aux->direito)
                {
                    aux = aux->direito; 
                }

                raiz->valor = aux->valor; 
                aux->valor = num;
                printf("\n\tElemento trocado: %d\n", num); 
                raiz->esquerdo = remover(raiz->esquerdo, num); 
                return raiz; 
                
            }else 
            {
                //remove o nó que tem um filho apenas
                No *aux;
                if(raiz->esquerdo)
                {
                    aux = raiz->esquerdo;  
                }else 
                {
                    aux = raiz->direito; 
                }
                free(raiz); 
                printf("\n\tElemento com 1 filho removido: %d!\n", num);
                return aux; 
            }
             
        }else
        {  
            if(num < raiz->valor)
                raiz->esquerdo = remover(raiz->esquerdo, num);
            else 
                raiz->direito = remover(raiz->direito, num);
        }

        //Recalcula o fator de balanceamento 
        raiz->fb = atualiza_balanceamento_raiz(raiz); 
        //printf("Fb: %d\n\n", raiz->fb);

        //verifica a necessidade de rebalancear a árvore 
        if(raiz->fb > 1)
            raiz = rotacao_R(raiz); 
        else if(raiz->fb < -1)
            raiz = rotacao_L(raiz); 

        return raiz;
    }
}


/**
 * Função para imprimir a árvore 
 * @param raiz nó raiz da árvore 
 * @param nivel sempre que chamar a função deve passar 1 como nivel
 * @note A árvore será impressa de lado, sendo a raiz o nó mais à esquerda 
*/
void imprimir(No *raiz, int nivel)
{
    int i;
    if(raiz)
    {
        imprimir(raiz->direito, nivel+1);
        printf("\n\n");

        for(i=0; i<nivel; i++)
        {
            printf("\t");
        }
        printf("%d", raiz->valor);
        imprimir(raiz->esquerdo, nivel+1);
    }
}


int main() 
{
    int opcao, valor;
    No *raiz = NULL; 

    do
    {
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2- Remover\n\t3- Buscar\n\t4- Imprimir\n\n");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 0:
                break;
            case 1:
                printf("\n\tDigite o valor a ser inserido: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor); 
                break;
            case 2: 
                printf("\n\tDigite o valor a ser removido: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor); 
                break;
            case 3:
                printf("\n\tDigite o valor que deseja buscar:\n\t");
                scanf("%d", &valor);
                Pont busca = buscar_no(raiz, valor);
                if(busca)
                {
                    printf("\n\tValor encontrado: %d\n", busca->valor);
                }else
                {
                    printf("\n\tValor não encontrado!\n");
                }
                break;
            case 4:
                imprimir(raiz, 1); 
                break; 
            default:
                printf("\n\tOpção inválida!\n");
        }

    }while(opcao != 0);     

    return 0;
}


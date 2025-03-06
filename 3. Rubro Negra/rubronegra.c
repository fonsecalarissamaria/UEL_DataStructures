#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <assert.h>


//Estruturas 
typedef struct no
{
    int valor;
    struct no *esquerdo, *direito, *pai; 
    char cor[10]; //cor: Rubro ou Negro 
}No, *Pont;

typedef struct tipoArvore
{
    No *raiz; //Topo da árvore 
}tipoArvore;


//PROTOTIPOS 
void verifica_balanceamento(tipoArvore *topo, Pont novoNo);
Pont remover(tipoArvore *arvore, Pont raiz, int num);
No* remocao_caso1(Pont raiz, int num, tipoArvore *arvore);
No* remocao_caso2(Pont raiz, int num, tipoArvore *arvore);
No* remocao_caso3_1(Pont raiz, int num, tipoArvore *arvore);
No* remocao_caso3_2(Pont raiz, int num, tipoArvore *arvore);
No* remocao_caso3_3(Pont raiz, int num, tipoArvore *arvore);
No* remocao_caso3_4(Pont raiz, int num, tipoArvore *arvore);


//Inicializando o topo da árvore 
tipoArvore arvore; 
void cria_arvore(tipoArvore *arvore)
{
    arvore->raiz = NULL;
}


/**
 * Realiza uma rotação à esquerda em um nó da árvore rubro-negra.
 *
 * @param node Um ponteiro para um ponteiro para o nó que será rotacionado.
 * @param topo Um ponteiro para a estrutura que contém a raiz da árvore.
 */
void rotacionaEsquerda(No** node, tipoArvore *topo)
{
    printf("\n\tRotacao à esquerda.\n");
    assert(node); 

    if(*node == NULL)
        return; 

    No* pai;
    if((*node) != topo->raiz) //Se o node não for raiz, guarda quem é o pai dele 
        pai = (*node)->pai; 

    No* aux = (*node)->direito;

    if(aux->esquerdo) //Se o nó a ser rotacionado pra "cima" tiver filho esquerdo, esse filho precisa ser reposicionado 
        (*node)->direito = aux->esquerdo;
    else
        (*node)->direito = NULL;

    aux->esquerdo = (*node); //O que foi pra "cima" recebe quem antes era seu pai 
    (*node)->pai = aux; //aux era filho e virou pai do seu antigo pai 

    if((*node) != topo->raiz) //Se o nó a ser rotacionado não é raiz 
    {
        if(aux->valor > pai->valor)
            pai->direito = aux; 
        else 
            pai->esquerdo = aux;
        aux->pai = pai;
    }else //Se o nó a ser rotacionado é raiz 
    {
        topo->raiz = aux;
    }     

    strcpy(aux->cor, "NEGRO"); //Quem sobe fica negro 
    if((*node) != topo->raiz)
        strcpy((*node)->cor, "RUBRO"); //Quem desce fica rubro   
}



/**
 * Realiza uma rotação à direita em um nó da árvore rubro-negra.
 *
 * @param node Um ponteiro para um ponteiro para o nó que será rotacionado.
 * @param topo Um ponteiro para a estrutura que contém a raiz da árvore.
 */
void rotacionaDireita(No** node, tipoArvore *topo)
{
    printf("\tRotação à direita.\n");
    assert(node && *node);

    if (*node == NULL)
        return;

    No* pai;
    if((*node) != topo->raiz) //Se o node não for raiz, guarda quem é o pai dele 
        pai = (*node)->pai;
    No* aux = (*node)->esquerdo;

    if(aux->direito) //Se o nó a ser rotacionado pra "cima" tiver filho direito, esse filho precisa ser reposicionado 
        (*node)->esquerdo = aux->direito;
    else
        (*node)->esquerdo = NULL;

    aux->direito = (*node); //O que foi pra "cima" recebe quem antes era seu pai 
    (*node)->pai = aux; //aux era filho e virou pai do seu antigo pai

    if((*node) != topo->raiz) //Se o nó a ser rotacionado não é raiz 
    {
        if(aux->valor > pai->valor)
            pai->direito = aux; 
        else 
            pai->esquerdo = aux;
        aux->pai = pai;
    }else //Se o nó a ser rotacionado é raiz 
    {
        topo->raiz = aux;
    }    

    strcpy(aux->cor, "NEGRO"); //Quem sobe fica negro 
    if((*node) != topo->raiz)
        strcpy((*node)->cor, "RUBRO"); //Quem desce fica rubro
}


/**
 * Insere um novo nó com o valor 'num' na árvore rubro-negra.
 *
 * @param arvore Ponteiro para a estrutura que representa a árvore.
 * @param raiz Ponteiro para um ponteiro para a raiz da árvore.
 * @param num Valor a ser inserido na árvore.
 */
void inserir(tipoArvore *arvore, No **raiz, int num) //Insere um novo nó na árvore
{
    No *aux = *raiz; //O ponteiro auxiliar recebe o CONTEÚDO que o endereço do ponteiro passado por parâmetro aponta 
    No *pai = NULL;
    No **raiz_original = raiz; //Guarda o endereço da raiz original
    bool inseriu = true; 

    while(aux)
    {
        pai = aux;
        if(num < (*raiz)->valor)
        {
            raiz = &aux->esquerdo; //O conteúdo do ponteiro "raiz" que está apenas no ESCOPO DESSA FUNÇÃO, recebe o endereço do ponteiro esquerdo da raiz 
            //o ponteiro 'raiz' recebeu o endereço do ponteiro que aponta pra esquerda, ou seja, o conteudo de raiz agora (*raiz) será a região de memória que o ponteiro da esquerda aponta, ou seja, o nó da esquerda 
        }else if(num > (*raiz)->valor)
        {
            raiz = &aux->direito; 
            //o ponteiro raiz guarda o endereço do ponteiro que aponta para o nó da direita, logo, o conteúdo desse ponteiro é o endereço da região que guarda esse nó
        }else
        {
            printf("\n\tInserção não realizada pois o elemento %d já existe.\n", num); 
            inseriu = false; 
            break;
        }
        aux = *raiz; //aux recebe o endereço da região de memória que o ponteiro da esquerda ou da direita aponta 
    }

    if(inseriu)
    {
        aux = malloc(sizeof(No)); //Endereço dessa região de memória vai pro aux
        aux->valor = num; 
        aux->esquerdo = NULL; 
        aux->direito = NULL; 
        
        if(pai)
        {
            strcpy(aux->cor, "RUBRO");
            //aux->raiz = pai->raiz; //mantém a raiz original
            
            if(num > pai->valor)
                pai->direito = aux; 
            else 
                pai->esquerdo = aux;
        }else 
        {
            strcpy(aux->cor, "NEGRO"); //Se for raiz
            //aux->raiz = aux; 
            *raiz = aux;
            arvore->raiz = aux;
        }
 
        aux->pai = pai; 
        
        //Conteúdo do endereço do ponteiro que foi passado por parâmetro recebe o endereço da região de memória que aux guardava 
        //OBS: Após percorrer a árore, o conteúdo de *raiz guarda o endereço do último nó percorrido 

        verifica_balanceamento(arvore, *raiz); 
    }
}



/**
 * Verifica e corrige o balanceamento de um nó na árvore rubro-negra após uma inserção.
 *
 * @param topo Ponteiro para a estrutura que representa a árvore.
 * @param novoNo Ponteiro para o nó recém-inserido que pode ter causado desbalanceamento.
 */
void verifica_balanceamento(tipoArvore *topo, Pont novoNo)
{
    
    //Se o novo nó é vermelho e tem pai vermelho
    while((strcmp(novoNo->cor, "RUBRO")==0) && (novoNo->pai != NULL) && (strcmp(novoNo->pai->cor, "RUBRO")==0))
    {
        printf("\n\tO novo nó %d é VERMELHO e tem pai vermelho\n", novoNo->valor);

        if(novoNo->pai == novoNo->pai->pai->esquerdo) //Pai do novo nó é filho esquerdo do pai dele (A)
        {
            if(novoNo->pai->pai->direito)
                printf("\n\tO pai do nó %d é filho esquerdo e o seu tio possui cor %s\n", novoNo->valor, novoNo->pai->pai->direito->cor);
            if((novoNo->pai->pai->direito != NULL) && (strcmp(novoNo->pai->pai->direito->cor, "RUBRO") == 0)) //Caso 1: Tio do novo nó também é vermelho 
            {
                strcpy(novoNo->pai->cor, "NEGRO"); //O pai passa a ser negro 
                strcpy(novoNo->pai->pai->direito->cor, "NEGRO"); //O tio também passa a ser negro 
                strcpy(novoNo->pai->pai->cor, "RUBRO"); //O avô passa a ser rubro 
                printf("\n\tA cor do novo nó é: %s\n", novoNo->cor);
                printf("\tA nova cor do pai do nó é: %s\n", novoNo->pai->cor);
                printf("\tA nova cor do tio do nó é: %s\n", novoNo->pai->pai->direito->cor);
                printf("\tA nova cor do avô do nó é: %s\n\n", novoNo->pai->pai->cor);
                if((novoNo->pai->pai) && (novoNo->pai))
                    novoNo = novoNo->pai->pai; //novo nó aponta agora para o avô, pra conferir os ancestrais 
                
                if (novoNo == topo->raiz) 
                {
                    strcpy(topo->raiz->cor, "NEGRO");
                    printf("\tComo o avô do novo nó é raiz, a nova cor dele é: %s\n", novoNo->cor);
                }
                
            }else  //Tio do novo nó é preto 
            {
                if((novoNo == novoNo->pai->direito) && ((novoNo->pai->pai->direito == NULL) || (strcmp(novoNo->pai->pai->direito->cor, "NEGRO")==0))) //Caso 2: Se o tio é preto (ou nulo) e o novo nó é filho da direita
                {
                    rotacionaEsquerda(&novoNo->pai, &arvore); 
                    novoNo = novoNo->esquerdo; //Cai no caso 3 logo abaixo
                }
                
                //Caso 3: Continuação do Caso 2 ou se novo nó for filho esquerdo e tem tio preto 
                rotacionaDireita(&novoNo->pai->pai, &arvore);  //rotação entre o pai e o avô
                novoNo = novoNo->pai; //continua a verificar os ancestrais
            }
        }else //Pai do novo nó é filho direito do pai dele  (B)
        {
            if(novoNo->pai->pai->esquerdo)
                printf("\n\tO pai do nó %d é filho direito e o seu tio possui cor %s\n", novoNo->valor, novoNo->pai->pai->direito->cor);
            if((novoNo->pai->pai->esquerdo != NULL) && (strcmp(novoNo->pai->pai->esquerdo->cor, "RUBRO") == 0)) //Caso 1: Tio do novo nó também é vermelho 
            {
                strcpy(novoNo->pai->cor, "NEGRO"); //O pai passa a ser negro 
                strcpy(novoNo->pai->pai->esquerdo->cor, "NEGRO"); //O tio também passa a ser negro 
                strcpy(novoNo->pai->pai->cor, "RUBRO"); //O avô passa a ser rubro 
                printf("\n\t**A cor do novo nó é: %s\n", novoNo->cor);
                printf("\tA nova cor do pai do nó é: %s\n", novoNo->pai->cor);
                printf("\tA nova cor do tio do nó é: %s\n", novoNo->pai->pai->direito->cor);
                printf("\tA nova cor do avô do nó é: %s\n\n", novoNo->pai->pai->cor);
                if((novoNo->pai->pai) && (novoNo->pai))
                    novoNo = novoNo->pai->pai; //novo nó aponta agora para o avô, pra conferir os ancestrais 
                
                if (novoNo == topo->raiz) 
                {
                    strcpy(topo->raiz->cor, "NEGRO");
                    printf("\tComo o avô do novo nó é raiz, a nova cor dele é: %s\n", novoNo->cor);
                }
            }else  //Tio do novo nó é preto 
            {
                if((novoNo == novoNo->pai->esquerdo) && ((novoNo->pai->pai->esquerdo == NULL) || (strcmp(novoNo->pai->pai->esquerdo->cor, "NEGRO")==0))) //Caso 2: Se o tio é preto (ou nulo) e o novo nó é filho da esquerda
                {
                    rotacionaDireita(&novoNo->pai, &arvore); 
                    novoNo = novoNo->direito; 
                }
                
                //Caso 3: Continuação do Caso 2 ou se novo nó for filho direito e tem tio preto 
                rotacionaEsquerda(&novoNo->pai->pai, &arvore);  //rotação entre o pai e o avô
                novoNo = novoNo->pai; //continua a verificar os ancestrais
            }
        }

        //Corrigindo a raiz, por precaução
        if(strcmp(topo->raiz->cor,"RUBRO")==0)
            strcpy(topo->raiz->cor, "NEGRO"); 
    }
}



/**
 * Função auxiliar para verificar a quantidade de negros da folha até a raiz 
 * e consertar, caso seja necessário 
 * @param raiz Ponteiro para um ponteiro para a raiz da árvore.
 * @param no Ponteiro para o primeiro nó da árvore, que é a raiz também
 * @return a quantidade de negros da raiz até a folha 
*/
int verifica_negros_aux(No* no, No* raiz) 
{
    if (no == NULL) {
        return 0; // Nó nulo é considerado preto
    }

    int esquerdo = verifica_negros_aux(no->esquerdo, raiz);
    int direito = verifica_negros_aux(no->direito, raiz);

    // Se o nó tem uma cor vermelha, não afeta a contagem de pretos
    if (strcmp(no->cor, "RUBRO") == 0) {
        return esquerdo;
    }

    // Se o nó é preto, incrementa a contagem e verifica se ambos os lados têm a mesma quantidade de pretos
    if (esquerdo != direito) {
        // Corrige o desequilíbrio ajustando a cor do nó
        strcpy(no->cor, "RUBRO");
        if (no == raiz) {
            // Se o nó raiz estava desequilibrado, corrige para negro
            strcpy(no->cor, "NEGRO");
        }
    }

    return esquerdo + 1; // Conta o próprio nó preto
}


/**
 * Função principal para verificar e corrigir a quantidade de nós pretos até a raiz 
 * @param arvore Ponteiro para o topo da árvore 
*/
void verifica_negros(tipoArvore* arvore) 
{
    No* raiz = arvore->raiz;
    int pretos = verifica_negros_aux(raiz, raiz);

    if (strcmp(raiz->cor, "NEGRO") != 0) {
        // Se o nó raiz não for negro, corrige
        strcpy(raiz->cor, "NEGRO");
    }
}




/**
 * Remove um nó rubro que não é folha 
 * @param raiz Ponteiro para um ponteiro para a raiz da árvore.
 * @param num valor do nó a ser removido
 * @param arvore ponteiro para o topo da árvore  
*/
No* remocao_caso1(Pont raiz, int num, tipoArvore *arvore)
{
    if((raiz->esquerdo) && (raiz->direito)) //Se ele tiver 2 filhos 
    {
        No *aux = raiz->direito; //Vai pra direita e procura o nó mais à esquerda 
    
        while(aux->esquerdo)
        {
            aux = aux->esquerdo; 
        }
        raiz->valor = aux->valor; 
        aux->valor = num;
        printf("\n\tTroca de id %d para %d\n", num, raiz->valor); 
        raiz->direito = remover(arvore, raiz->direito, num); 
        return raiz;
    }else //Se ele tiver apenas 1 filho
    {
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
}

/**
 * Remove um nó negro que possui pelo menos um filho rubro
 * @param raiz Ponteiro para um ponteiro para a raiz da árvore.
 * @param num valor do nó a ser removido
 * @param arvore ponteiro para o topo da árvore  
*/
No* remocao_caso2(Pont raiz, int num, tipoArvore *arvore)
{
    if((raiz->direito) && (strcmp(raiz->direito->cor, "RUBRO")==0)) //Se o filho direito for rubro 
    {
        No *aux = raiz->direito; //Vai pra direita e procura o filho mais à esquerda 
        while(aux->esquerdo)
        {
            aux = aux->esquerdo; 
        }
        raiz->valor = aux->valor; 
        aux->valor = num;
        printf("\n\tTroca de id %d para %d\n", num, raiz->valor); 
        raiz->direito = remover(arvore, raiz->direito, num); 
        return raiz;
    }else if((raiz->esquerdo) && (strcmp(raiz->esquerdo->cor, "RUBRO")==0)) //Se o filho esquerdo for rubro
    {
        No *aux = raiz->esquerdo; //Vai pra esquerda e procura o filho mais à direita 
        while(aux->direito)
        {
            aux = aux->direito; 
        }
        raiz->valor = aux->valor; 
        aux->valor = num;
        printf("\n\tTroca de id %d para %d\n", num, raiz->valor); 
        raiz->esquerdo = remover(arvore, raiz->esquerdo, num); 
        return raiz;
    }else 
        return NULL;
}


/**
 * Remove um nó negro que o irmão é rubro
 * @param raiz Ponteiro para um ponteiro para a raiz da árvore.
 * @param num valor do nó a ser removido
 * @param arvore ponteiro para o topo da árvore  
*/
No* remocao_caso3_1(Pont raiz, int num, tipoArvore *arvore)
{
    if((raiz->pai->direito) && (strcmp(raiz->pai->direito->cor, "RUBRO")==0)) //Se o irmão é rubro e filho direito do pai dele
    {
        strcpy(raiz->pai->cor, "RUBRO"); //Pai fica rubro
        strcpy(raiz->pai->direito->cor, "NEGRO"); //Irmão fica negro
        rotacionaEsquerda(&raiz->pai, arvore); 
        printf("O novo irmão é: %d\n", raiz->pai->direito->valor);
    }else if((raiz->pai->esquerdo) && (strcmp(raiz->pai->direito->cor, "RUBRO")==0)) //Seo o irmão é rubro e filho esquerdo do pai dele
    {
        strcpy(raiz->pai->cor, "RUBRO"); //Pai fica rubro
        strcpy(raiz->pai->esquerdo->cor, "NEGRO"); //Irmão fica negro
        rotacionaEsquerda(&raiz->pai, arvore);
        printf("O novo irmão é: %d\n", raiz->pai->esquerdo->valor);
    }

    //Caso 3.1 cai em algum dos próximos casos:
    No* aux = remocao_caso3_2(raiz, raiz->valor, arvore);
    No* aux2 = remocao_caso3_3(raiz, raiz->valor, arvore);
    No* aux3 = remocao_caso3_4(raiz, raiz->valor, arvore);

    if(aux)
        return aux;
    else if(aux2)
        return aux2; 
    else 
        return aux3;
}



/**
 * Remove um nó negro que o irmão é negro e os dois filhos do irmão também são negros 
 * @param raiz Ponteiro para um ponteiro para a raiz da árvore.
 * @param num valor do nó a ser removido
 * @param arvore ponteiro para o topo da árvore  
*/
No* remocao_caso3_2(Pont raiz, int num, tipoArvore *arvore)
{
    if((raiz->pai->direito) && (strcmp(raiz->pai->direito->cor, "NEGRO")==0)) //Se o irmão direito é negro               
    {
        if(((raiz->pai->direito->esquerdo == NULL) || (strcmp(raiz->pai->direito->esquerdo->cor, "NEGRO")==0)) && 
                                            ((raiz->pai->direito->direito == NULL) || (strcmp(raiz->pai->direito->direito->cor, "NEGRO")==0))) //e seus filhos tb
        {
            strcpy(raiz->pai->direito->cor, "RUBRO"); //irmão fica rubro 
            No *pai = raiz->pai; 
            if(strcmp(pai->cor, "RUBRO")==0) //Se o nó pai for rubro 
            {
                strcpy(pai->cor, "NEGRO"); //Pai fica negro
                return remover(arvore, raiz, num); //Remove o nó  
            }else //Se o pai for negro 
            {
                //Novo nó é duplo negro - começa a verificação da exclusão novamente
                verifica_negros(arvore);
                return remover(arvore, raiz, num);
            }   
        }
    }else if((raiz->pai->esquerdo) && (strcmp(raiz->pai->esquerdo->cor, "NEGRO")==0)) //se o irmão esquerdo é negro
    {
        if(((raiz->pai->esquerdo->esquerdo == NULL) || (strcmp(raiz->pai->esquerdo->esquerdo->cor, "NEGRO")==0)) && 
                        ((raiz->pai->esquerdo->direito == NULL) || (strcmp(raiz->pai->esquerdo->direito->cor, "NEGRO")==0))) //e seus filhos tb
        {
            strcpy(raiz->pai->esquerdo->cor, "RUBRO");
            No *pai = raiz->pai; 
            if(strcmp(pai->cor, "RUBRO")==0)
            {
                strcpy(pai->cor, "NEGRO");
                return remover(arvore, raiz, num); //Remove o nó
            }else
            {
                //Novo nó é duplo negro 
                verifica_negros(arvore);
                return remover(arvore, raiz, num);
            } 
        }
    }else 
        return NULL;
}


/**
 * Remove um nó negro que o irmão é negro e o filho da direta do irmão é negro
 * @param raiz Ponteiro para um ponteiro para a raiz da árvore.
 * @param num valor do nó a ser removido
 * @param arvore ponteiro para o topo da árvore  
*/
No* remocao_caso3_3(Pont raiz, int num, tipoArvore *arvore)
{
    if((((raiz->pai->direito) && (strcmp(raiz->pai->direito->cor, "NEGRO")==0)) && (((raiz->pai->direito->direito) && ((strcmp(raiz->pai->direito->direito->cor, "NEGRO")==0)) || (raiz->pai->direito->direito == NULL)))))
    {
        strcpy(raiz->pai->direito->esquerdo->cor, "NEGRO"); //Filho esquerdo do irmão fica negro 
        strcpy(raiz->pai->direito->cor, "RUBRO"); //Irmão fica rubro 
        rotacionaDireita(&raiz->pai->direito, arvore); //Rotaciona o irmão pra direita 
        raiz = remocao_caso3_4(raiz, raiz->valor, arvore); //chama o remover 3.4 
        return raiz;
    }else 
        return NULL; 
}



/**
 * Remove um nó negro que o irmão é negro e o filho da direta do irmão é rubro 
 * @param raiz Ponteiro para um ponteiro para a raiz da árvore.
 * @param num valor do nó a ser removido
 * @param arvore ponteiro para o topo da árvore  
*/
No* remocao_caso3_4(Pont raiz, int num, tipoArvore *arvore)
{
    if((((raiz->pai->direito) && (strcmp(raiz->pai->direito->cor, "NEGRO")==0)) && ((raiz->pai->direito->direito) && (strcmp(raiz->pai->direito->direito->cor, "RUBRO")==0))))
    {
        strcpy(raiz->pai->direito->cor, raiz->pai->cor); //Irmão copia a cor do pai;
        strcpy(raiz->pai->cor, "NEGRO"); //Pai e filho direito do irmão ficam negros;
        strcpy(raiz->pai->direito->direito->cor, "NEGRO");
        rotacionaEsquerda(&raiz->pai, arvore); //Rotacione o pai a esquerda;
        raiz = arvore->raiz;

        if(strcmp(arvore->raiz->cor, "RUBRO")==0)
                strcpy(arvore->raiz->cor, "NEGRO");
        return raiz;
    }else 
        return NULL;
}


/**
 * Remove o nó que possui o valor inteiro 'num' 
 * 
 * @param raiz Ponteiro para o nó raiz da árvore 
 * @param num Número a ser removido da árvore
 * @param arvore ponteiro para o topo da árvore
 * @return o ponteiro para a raiz da árvore modificada pela remoção 
 */
Pont remover(tipoArvore *arvore, Pont raiz, int num)
{
    if(raiz == NULL)
    {
        printf("Nó não encontrado!\n");
        return NULL;
    }else
    {
        if(raiz->valor == num)
        {
            printf("Cor do nó: %s\n", raiz->cor); 
            if((raiz->esquerdo == NULL) && (raiz->direito == NULL) && (strcmp(raiz->cor, "RUBRO")==0))
            {
                //remove o nó FOLHA RUBRO
                free(raiz);
                printf("\n\tElemento folha removido: %d!\n", num);
                return NULL; 
            }else if(strcmp(raiz->cor, "RUBRO")==0) //Se o nó for vermelho, mas não é folha - Caso 1
            {
                return remocao_caso1(raiz, num, arvore); 
            }else //Se o nó a ser removido é NEGRO
            {   
                //Caso 2 - Se o nó é negro com filho rubro
                if(((raiz->direito) && (strcmp(raiz->direito->cor, "RUBRO")==0)) || ((raiz->esquerdo) && (strcmp(raiz->esquerdo->cor, "RUBRO")==0)) || ((raiz == arvore->raiz)))
                    remocao_caso2(raiz, num, arvore);
                  
                //Caso 3.1 - Se o irmão do nó é rubro 
                if(((raiz->pai->direito) && (strcmp(raiz->pai->direito->cor, "RUBRO")==0)) || ((raiz->pai->esquerdo) && (strcmp(raiz->pai->direito->cor, "RUBRO")==0)))
                    remocao_caso3_1(raiz, num, arvore);

                //Caso 3.2 - O irmão é negro e os filhos do irmão também são negros
                if(((raiz->pai->direito) && (strcmp(raiz->pai->direito->cor, "NEGRO")==0)) || ((raiz->pai->esquerdo) && (strcmp(raiz->pai->esquerdo->cor, "NEGRO")==0))) //Se o irmão é negro
                    remocao_caso3_2(raiz, num, arvore);
    
                    
                //Caso 3.3 - O irmão é negro e o filho da direita do irmão é negro
                if((((raiz->pai->direito) && (strcmp(raiz->pai->direito->cor, "NEGRO")==0)) && (((raiz->pai->direito->direito) && ((strcmp(raiz->pai->direito->direito->cor, "NEGRO")==0)) || (raiz->pai->direito->direito == NULL)))))
                    remocao_caso3_3(raiz, num, arvore);

                //Caso 3.4 - O irmão é negro e o filho da direita do irmão é rubro
                if((((raiz->pai->direito) && (strcmp(raiz->pai->direito->cor, "NEGRO")==0)) && ((raiz->pai->direito->direito) && (strcmp(raiz->pai->direito->direito->cor, "RUBRO")==0))))
                    remocao_caso3_4(raiz, num, arvore);
            } 
        }else //Percorre a árvore 
        { 
            if(num < raiz->valor)
                raiz->esquerdo = remover(arvore, raiz->esquerdo, num);
            else 
                raiz->direito = remover(arvore, raiz->direito, num);
        }

        //Conserta a cor da raiz, por precaução
        if(strcmp(arvore->raiz->cor, "RUBRO")==0)
                strcpy(arvore->raiz->cor, "NEGRO");

        return raiz;
    }
}




/**
 * Função para imprimir a árvore 
 * @param raiz nó raiz da árvore 
 * @param nivel sempre que chamar a função passar 1 como nivel, para ficar mais visível
 * @note A árvore será impressa de lado, sendo a raiz o nó mais à esquerda 
*/
void imprimir(No *raiz, int nivel)
{
    //printf("Quem é a raiz: %d\n", raiz->valor);
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
                inserir(&arvore, &raiz, valor); 
                break;
            case 2: 
                printf("\n\tDigite o valor a ser removido: ");
                scanf("%d", &valor);
                raiz = remover(&arvore, arvore.raiz, valor); 
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
                imprimir(arvore.raiz, 1); 
                break; 
            default:
                printf("\n\tOpção inválida!\n");
        }

    }while(opcao != 0);     

    return 0;
}

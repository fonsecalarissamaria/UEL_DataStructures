#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define INF 999999



/*
    Caminhos Mínimos 
*/



typedef struct adjacencia
{
    int vertice;
    int peso;
    struct adjacencia *prox;
}ADJACENCIA;


typedef struct vertice
{
    ADJACENCIA *cab;
}VERTICE; 

typedef struct grafo
{
    int vertices;
    int arestas;
    VERTICE *adj;
}GRAFO;


//Prototipos 
bool existeAberto(GRAFO *g, int *aberto);
int menorDist(GRAFO *g, int *aberto, int *d);



/**
* Inicializa os vetores `d` e `p` para o algoritmo de Dijkstra.
*
* @param g Ponteiro para a estrutura de dados do grafo.
* @param d Vetor que armazenará as distâncias dos vértices à origem.
* @param p Vetor que armazenará os predecessores dos vértices.
* @param s Vértice inicial do algoritmo de Dijkstra.
*/
void inicializaD (GRAFO *g, int *d, int *p, int s)
{
    int v;
    for(v=0; v<g->vertices; v++)
    {
        d[v] = INT_MAX/2;
        p[v] = -1;
    }

    d[s] = 0;
}




/**
* Relaxa a aresta entre os vértices `u` e `v` no grafo `g`.
*
* @param g Ponteiro para a estrutura de dados do grafo.
* @param d Vetor que armazena as distâncias dos vértices à origem.
* @param p Vetor que armazena os predecessores dos vértices.
* @param u Vértice de origem da aresta.
* @param v Vértice de destino da aresta.
*/
void relaxa (GRAFO *g, int *d, int *p, int u, int v)
{
    ADJACENCIA *ad = g->adj[u].cab;

    while(ad && ad->vertice != v)
    {
        ad = ad->prox; 
    }

    if(ad)
    {
        if(d[v] > d[u] + ad->peso)
        {
            d[v] = d[u] + ad->peso;
            p[v] = u;
        }
    }
}



/**
* Descrição: Implementa o algoritmo de Dijkstra para encontrar as 
* distâncias mais curtas entre todos os vértices e a origem em um grafo 
* não direcionado com pesos não-negativos.
*
* @param g Ponteiro para a estrutura de dados do grafo.
* @param s Vértice inicial do algoritmo de Dijkstra.
* @return Vetor de distâncias contendo a distância de cada vértice à origem.
*/
int *dijkstra(GRAFO *g, int s)
{
    int *d = (int *)malloc(g->vertices*sizeof(int));

    int p[g->vertices];
    int aberto [g->vertices]; 
    inicializaD(g,d,p,s);

    int i;
    for(i=0; i<g->vertices; i++)
    {
        aberto[i] = true; 
    }

    while(existeAberto(g, aberto))
    {
        int u = menorDist(g, aberto, d);
        aberto[u] = false;
        ADJACENCIA *ad = g->adj[u].cab;
        while(ad)
        {
            relaxa(g,d,p,u,ad->vertice);
            ad = ad->prox;
        }
    }

    return (d);
}


/**
* Verifica se existe algum vértice aberto no grafo 'g'.
*
* @param g Ponteiro para a estrutura de dados do grafo.
* @param aberto Vetor que indica se um vértice está aberto ou fechado.
* @return Verdadeiro se existir algum vértice aberto, falso caso contrário.
*/
bool existeAberto(GRAFO *g, int *aberto)
{
    int i;
    for(i=0; i<g->vertices; i++)
    {
        if(aberto[i])
            return (true); 
    }
    return (false); 
}




/**
* Encontra o vértice aberto com a menor distância atual no grafo 'g'
*
* @param g Ponteiro para a estrutura de dados do grafo.
* @param aberto Vetor que indica se um vértice está aberto ou fechado.
* @param d Vetor de distâncias contendo a distância de cada vértice à origem.
* @return O índice do vértice aberto com a menor distância atual, ou -1 se não houver nenhum vértice aberto.
*/
int menorDist(GRAFO *g, int *aberto, int *d)
{
    int i;

    for(i=0; i<g->vertices; i++)
    {
        if(aberto[i])
            break;
    }

    if(i==g->vertices)
        return -1; 

    int menor = i;
    for(i-menor+1; i<g->vertices; i++)
    {
        if(aberto[i] && (d[menor]>d[i]))
            menor = i;
    }

    return menor; 
}




/**
* Insere um novo vértice no grafo 'g'
*
* @param g Ponteiro para a estrutura de dados do grafo.
* @param v Índice do vértice a ser inserido.
*/
void inserirNo(GRAFO *g, int v)
{
    if (g->adj[v].cab)
    {
        printf("\n\tErro ao inserir: o vértice %d já existe\n", v);
        return;
    }

    //criando uma nova aresta
    ADJACENCIA *ad = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    ad->vertice = v;
    ad->peso = 0;
    ad->prox = NULL;

    //adicionando a aresta ao grafo
    ad->prox = g->adj[v].cab;
    g->adj[v].cab = ad;
}




/**
* Imprime a menor distância do vértice 'v' até a origem no grafo 'g'
*
* @param g Ponteiro para a estrutura de dados do grafo.
* @param v Índice do vértice a ser impresso.
*/
void imprimirDistancia(GRAFO *g, int v)
{
    if (!g->adj[v].cab)
    {
        printf("\n\tO vértice %d não existe\n", v);
        return;
    }

    int *d = dijkstra(g, 0);
    printf("\n\tA menor distância do nó %d até a origem é %d\n", v, d[v]);

    free(d);
}




/**
* Insere uma aresta entre os vértices 'v1' e 'v2' no grafo 'g'
*
* @param g Ponteiro para a estrutura de dados do grafo.
* @param v1 Índice do vértice de origem da aresta.
* @param v2 Índice do vértice de destino da aresta.
* @param peso Peso da aresta.
*/
void inserirAresta(GRAFO *g, int v1, int v2, int peso)
{
    if (!g->adj[v1].cab)
    {
        printf("O vértice %d não existe\n", v1);
        return;
    }

    if (!g->adj[v2].cab)
    {
        printf("O vértice %d não existe\n", v2);
        return;
    }

    //criando uma nova aresta
    ADJACENCIA *ad = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    ad->vertice = v2;
    ad->peso = peso;
    ad->prox = NULL;

    //adicionando a aresta ao grafo
    ad->prox = g->adj[v1].cab;
    g->adj[v1].cab = ad;
}



int main()
{
    GRAFO g;
    int opcao, origem, destino, peso, vertice; 

    // Inicializando o grafo
    g.vertices = 5;
    g.arestas = 0;
    g.adj = (VERTICE *)malloc(g.vertices*sizeof(VERTICE));
    inserirNo(&g, 0); //OBS: Considerei o primeiro vértice como 0

    do
    {
        printf("\n\n\t0 - Sair\n\t1 - Inserir Vértice\n\t2- Imprimir Caminhos Mínimos\n\n");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 0:
                break;
            case 1:
                printf("\n\tDigite o valor a ser inserido: ");
                scanf("%d", &destino);
                inserirNo(&g, destino);
                printf("\n\tDigite o antecessor do valor a ser inserido: ");
                scanf("%d", &origem);
                printf("\n\tDigite o peso da aresta: ");
                scanf("%d", &peso);
                inserirAresta(&g, origem, destino, peso);
                break;
            case 2: 
                printf("\n\tDigite o vértice que deseja saber o caminho minimo: ");
                scanf("%d", &vertice);
                imprimirDistancia(&g,vertice);
                break;
            default:
                printf("\n\tOpção inválida!\n");
        }

    }while(opcao != 0);

    return 0;
}

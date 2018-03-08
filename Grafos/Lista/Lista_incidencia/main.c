#include <stdio.h>
#include <stdlib.h>

#define MAXVERTICES 10


typedef struct                                                                  // Celula
{
  int Vertice;
  int Aresta;
}TItem;

typedef struct SCelula *TApontador;

typedef struct SCelula
{
  TItem Item;
  TApontador Ant, Prox;
}TCelula;

typedef struct                                                                  // Lista
{
  TApontador Primeiro, Ultimo;                                                  // Apontador para primeiro e ultimo item
  int Tamanho;                                                                  // Tamanho da lista
}TLista;


typedef struct                                                                  // grafo
{
  TLista vertices[MAXVERTICES];                                                 // vetor de listas
  int NVertices;
  int NArestas;
}TGrafo;


void TLista_Inicia (TLista *pLista)               // Cria lista
{

  pLista->Tamanho = 0;                            // Inicializa com tamanho 0

  pLista->Primeiro = NULL;                        // Faz primeiro apontar para NULL
  pLista->Ultimo = NULL;                          // Faz ultimo apontar para NULL

}


int TLista_EhVazia (TLista *pLista)
{
  if ((pLista->Primeiro == NULL) && (pLista->Ultimo == NULL)) return 0;

  else return 1;
}


int TLista_Tamanho (TLista *pLista)
{
  return (pLista->Tamanho);
}


TApontador Cria_Celula (TItem Item)                         // funcao cria celula
{


  TApontador novo;
  novo = (TCelula*) malloc (sizeof(TCelula));               // Aloca espaço para celula
  novo->Ant = NULL;
  novo->Prox = NULL;
  novo->Item = Item;
  return novo;
}


void TLista_Imprime(TLista *pLista)
{

  if((!TLista_EhVazia(pLista))) printf("Lista vazia\n");

  else
  {
    TApontador aux;
    aux = pLista->Primeiro;

    while((aux) != (NULL))
    {
      printf("%d ", aux->Item.Vertice);
      aux = aux->Prox;
    }
  }

  printf("\n");
}


/******************************** FUNCÕES DE INSERÇÃO ********************************/

int TLista_Insere_Comeco (TLista *pLista, TItem Item)
{

  TApontador novo;                                        // Aloca nova celula
  novo = Cria_Celula(Item);


  if((!TLista_EhVazia(pLista)))                          // caso a lista seja vazia
  {
    TApontador novo;                                      // Aloca nova celula
    novo = Cria_Celula(Item);

    pLista->Primeiro = novo;                              // apontador do primeiro da lista aponta para a nova celula
    pLista->Ultimo = novo;                                // apontador do ultimo da lista aponta para a nova celula
    pLista->Tamanho++;                                    // incrementa tamanho da lista
    return 0;
  }

  else if((TLista_EhVazia(pLista)))                       // caso a lista não seja vazia
  {
    novo->Prox = pLista->Primeiro;                        // celula->Prox aponta para primeiro elemento da lista

    pLista->Primeiro->Ant = novo;                         // Antigo primeiro elemento aponta o seu anterior para o novo

    pLista->Primeiro = novo;                              // apontador do primeiro da lista aponta para a nova celula
    pLista->Tamanho++;                                    // incrementa tamanho da lista

    return 0;
  }

  else return 1;
}


int TLista_Insere_Fim (TLista *pLista, TItem Item)
{

  TApontador novo;                                        // Aloca nova celula
  novo = Cria_Celula(Item);

  if((!TLista_EhVazia(pLista)))                          // caso a lista seja vazia
  {
    TApontador novo;                                      // Aloca nova celula
    novo = Cria_Celula(Item);

    pLista->Primeiro = novo;                              // apontador do primeiro da lista aponta para a nova celula
    pLista->Ultimo = novo;                                // apontador do ultimo da lista aponta para a nova celula
    pLista->Tamanho++;                                    // incrementa tamanho da lista
    return 0;
  }

  else if((TLista_EhVazia(pLista)))                       // caso a lista não seja vazia
  {
    novo->Ant = pLista->Ultimo;                           // celula->Ant aponta para ultimo elemento da lista

    pLista->Ultimo->Prox = novo;                          // Antigo ultimo elemento aponta o seu proximo para o novo

    pLista->Ultimo = novo;                                // apontador do ultimo da lista aponta para a nova celula
    pLista->Tamanho++;                                    // incrementa tamanho da lista

    return 0;
  }

  else return 1;
}


int TLista_Insere_Sign (TLista *pLista, TApontador sign, TItem Item)      // insere na posição sign
{

  TApontador novo;                                        // Aloca nova celula
  novo = Cria_Celula(Item);

  if((TLista_EhVazia(pLista)))                             // caso a lista não seja vazia
  {
    novo->Prox = sign;                                   // faz nova->Prox celula apontar para a celula marcada
    novo->Ant = sign->Ant;                               // faz nova->Ant celula apontar para a celula anterior à marcada

    sign->Ant->Prox = novo;                              // faz a celula anterior à marcada (sign->Ant->Prox) apontar para a nova

    sign->Ant = novo;                                     // faz a celula marcada (sign->Ant) apontar para a nova

    pLista->Tamanho++;                                    // incrementa tamanho da lista

    return 0;
  }

  else return 1;
}


int TLista_Insere(TLista *pLista, TApontador sign, TItem Item)
{

    if(sign == (pLista->Primeiro))                        // caso a posição marcada seja igual a primeira
    {
      if((!TLista_Insere_Comeco(pLista, Item))) return 0; // insere elemento no comeco
      else return 1;
    }

    else if(sign == (pLista->Ultimo))                    // caso a posição marcada seja igual a ultima
    {
      if((!TLista_Insere_Fim(pLista, Item))) return 0;   // insere elemento no fim
      else return 1;
    }

    else                                                // caso a posição marcada não seja igual à ultima nem à primeira
    {
      if((!TLista_Insere_Sign(pLista, sign, Item))) return 0;   // insere elemento na posição marcada
      else return 1;
    }
}

/******************************** FUNCÕES DE INSERÇÃO ********************************/
//
//
//
//
//
/******************************** FUNCÕES DE REMOÇÃO  ********************************/

int TLista_Retira_Comeco (TLista *pLista, TItem *Item)
{
  if((TLista_EhVazia(pLista)))                             // Caso a lista não seja vazia
  {
    TApontador aux;
    aux = pLista->Primeiro;                                // Ponteiro auxiliar aponta para marcador
    *Item = aux->Item;                                     // Recebe valor a ser retirado

    if((pLista->Tamanho) == 1)                             // Verifica se lista tem tamanho 1
    {
      pLista->Primeiro = NULL;                             // Faz o primeiro da lista apontar para NULL
      pLista->Ultimo = NULL;                               // Faz o ultimo da lista apontar para NULL
    }

    else                                                   // Caso o tamanho da lista seja maior do que 1
    {
      pLista->Primeiro = aux->Prox;                          // Primeiro da lista passa a ser o segundo elemento

      pLista->Primeiro->Ant = NULL;                          // Anterior da primeira celula aponta para NULL
    }

    free(aux);                                             // Libera celula

    pLista->Tamanho--;                                     // Decrementa o tamanho da lista

    return 0;
  }

  else return 1;
}


int TLista_Retira_Fim (TLista *pLista, TItem *Item)
{
  if((TLista_EhVazia(pLista)))                             // Caso a lista não seja vazia
  {
    TApontador aux;
    aux = pLista->Ultimo;                                  // Ponteiro auxiliar aponta para marcador
    *Item = aux->Item;                                     // Recebe valor a ser retirado

    if((pLista->Tamanho) == 1)                             // Verifica se lista tem tamanho 1
    {
      pLista->Primeiro = NULL;                             // Faz o primeiro da lista apontar para NULL
      pLista->Ultimo = NULL;                               // Faz o ultimo da lista apontar para NULL
    }

    else                                                   // Caso o tamanho da lista seja maior do que 1
    {
      pLista->Ultimo = aux->Ant;                           // Ultimo da lista passa a ser o penultimo elemento

      pLista->Ultimo->Prox = NULL;                         // Prox da ultimo celula aponta para NULLs
    }

    free(aux);                                             // Libera celula

    pLista->Tamanho--;                                     // Decrementa o tamanho da lista

    return 0;
  }

  else return 1;
}


int TLista_Retira_Sign (TLista *pLista, TApontador *sign, TItem *Item)
{
  if((TLista_EhVazia(pLista)))
  {
    TApontador aux;                                        // Apontador auxiliar
    aux = sign;                                            // Aponta para celula a ser retirada
    *Item = aux->Item;                                     // Recebe valor a ser retirado

    aux->Ant->Prox = aux->Prox;                            // Celula anterior à marcada, aponta para a celula seguinte à marcada

    aux->Prox->Ant = aux->Ant;                              // Celula sucessora à marcada, aponta para a celula anterior à marcada

    free(aux);                                             // Libera celula

    pLista->Tamanho--;                                     // Decrementa o tamanho da lista

    return 0;
  }

  else return 1;
}


int TLista_Retira (TLista *pLista, TApontador *sign, TItem *Item)
{
  if((TLista_EhVazia(pLista)))                           // caso a lista não seja vazia
  {
    if(sign == (pLista->Primeiro))                        // caso a posição marcada seja igual a primeira
    {
      if((!TLista_Retira_Comeco(pLista, Item))) return 0; // remove elemento no comeco
      else return 1;
    }

    else if(sign == (pLista->Ultimo))                    // caso a posição marcada seja igual a ultima
    {
      if((!TLista_Retira_Fim(pLista, Item))) return 0;   // Retira elemento no fim
      else return 1;
    }

    else                                                // caso a posição marcada não seja igual à ultima nem à primeira
    {
      if((!TLista_Retira_Sign(pLista, sign, Item))) return 0;   // retira elemento na posição marcada
      else return 1;
    }
  }

  else return 1;
}


int TLista_Sair(TLista *pLista, TItem *Item)
{

  int i=0, tamanho=0;

  tamanho = pLista->Tamanho;

  for(i=0; i<tamanho; i++)
  {
    TLista_Retira_Fim(pLista, Item);
    printf("Elemento %d removido\n", Item->Vertice);
  }
  return 0;
}

/******************************** FUNCÕES DE REMOÇÃO  ********************************/



void TGrafo_Inicia(TGrafo *grafo)                                               // função incia o grafo
{
  int i=0;

  for(i=0; i<grafo->NVertices; i++)
  {
    TLista_Inicia(&grafo->vertices[i]);
  }
}


void TGrafo_Imprime(TGrafo *grafo)                                              // função imprime grafo
{
  int i=0;

  for(i=0; i<grafo->NVertices; i++)                                             // percorre o grafo
  {
    printf("lista %d\n", i);
    TLista_Imprime(&grafo->vertices[i]);
  }
}


int TGrafo_Insere_Vertice(TGrafo *grafo, TItem Item, int sign)
{
  if (grafo->NVertices == MAXVERTICES) return 1;                                // verifica se o grafo ja esta cheio

  else                                                                          // caso não esteja cheio
  {
    TLista_Insere_Fim(&grafo->vertices[sign], Item);                            // insere vertice na posição sign
  }
  return 0;

}


int TGrafo_Busca_Existencia_Vertice(TGrafo *grafo, TItem vertice)
{

  int sign=0;


  while (sign != MAXVERTICES+1)
  {
    if(!TLista_EhVazia(&grafo->vertices[sign]))                                 // caso encontre posição vaga
    {
      TGrafo_Insere_Vertice(grafo, vertice, sign);                              // insere vertice na posicao
      return sign;
    }

    else if(grafo->vertices[sign].Primeiro->Item.Vertice == vertice.Vertice)        // caso encontre elemento igual
    {
      return sign;                                                              // retorna posição do vertice
    }
    else sign++;                                                                // caso contrario, avança sign
  }
}


int TGrafo_Insere_Aresta(TGrafo *grafo, TItem vertice1, TItem vertice2)
{

  int sign1=0, sign2=0;                                                         // posição do vertice 1 e vertice 2, respectivamente

  sign1 = TGrafo_Busca_Existencia_Vertice(grafo, vertice1);                     // verifica a existencia do vertice 1 e retorna sua posição
  sign2 = TGrafo_Busca_Existencia_Vertice(grafo, vertice2);                     // verifica a existencia do vertice 2 e retorna sua posição

  TLista_Insere_Fim(&grafo->vertices[sign1], vertice2);                          // insere vertice 2 na lista do vertice 1
}


void TGrafo_Sair(TGrafo *grafo, TItem *Item)                                              // função imprime grafo
{
  int i=0;

  for(i=0; i<grafo->NVertices; i++)                                             // percorre o grafo
  {
    TLista_Sair(&grafo->vertices[i], Item);
  }
}





int main()
{

TGrafo grafo;
int vertices=0, arestas=0, i=0;
TItem vertice1, vertice2;


printf("Entre com o numero de vertices e arestas:\n");
scanf("%d %d", &vertices, &arestas);

grafo.NVertices = vertices;
grafo.NArestas = arestas;

TGrafo_Inicia(&grafo);                                                          // incia o grafo


TGrafo_Imprime(&grafo);


for (i=0; i<arestas; i++)
{
  printf("insira a aresta %d:\n", i+1);
  scanf("%d %d", &vertice1.Vertice, &vertice2.Vertice);                                         // captura os dois vertices da aresta

  TGrafo_Insere_Aresta(&grafo, vertice1, vertice2);

}

TGrafo_Imprime(&grafo);


TGrafo_Sair(&grafo, &vertice1);                                                     // sair do grafo limpando a memoria alocada

return 0;
}

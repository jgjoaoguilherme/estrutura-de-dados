#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VERTICES 1024


typedef struct                                                                  // Item
{
  char nome[30];
  int index;
}TItem;


typedef struct                                                                  // Lista de elementos
{
  TItem Item[MAX_VERTICES];                                                     // Numero maximo de vertices do grafo
  int indice;                                                                   // Indice do elemento
}TLista;


typedef struct                                                                  // Grafo
{
  TLista lista;
  int matriz[MAX_VERTICES][MAX_VERTICES];                                       // matriz
  int NVertices;                                                                // Numero de vertices
  int NArestas;                                                                 // Numero de arestas
}TGrafo_Matriz_Adj;



int Insere_No(TGrafo_Matriz_Adj *grafo ,char *nome)
{
  if(grafo->lista.indice == MAX_VERTICES) return 1;                            // Grafo possui numero máximo de vertices

  else
  {
    strcpy(grafo->lista.Item[grafo->lista.indice].nome, nome);                       // Copia nome de entrada para a lista

    grafo->lista.Item[grafo->lista.indice].index = grafo->lista.indice;             // recebe valor do indice

    grafo->lista.indice++;                                                     // Incrementa indice

    grafo->NVertices++;                                                         // Incrementa numero de vertices

    return 0;
  }
}



int BuscaNo (TLista *lista, char *nome)
{
  int i=0;

  for(i=0; i<lista->indice; i++)
  {
    if(strcmp(lista->Item[i].nome, nome) == 0)                                  // Caso encontre elemento
      return lista->Item[i].index;                                              // Retorna seu indice
  }

  return -1;                                                                    // RETORNA -1 CASO NÃO ENCONTRE ELEMENTO
}


void inicializaGrafo(TGrafo_Matriz_Adj *grafo)
{
  int i=0, j=0;

  grafo->lista.indice = 0;
  grafo->NVertices = 0;
  grafo->NArestas = 0;

  for(i=0; i<MAX_VERTICES; i++)
  {
    for(j=0; j<MAX_VERTICES; j++)
    {
      grafo->matriz[i][j] = 0;
    }
  }
}


int Insere_Aresta(TGrafo_Matriz_Adj *grafo, char *nome1, char *nome2)
{
  int indice1 = BuscaNo(&grafo->lista, nome1);                                  // bsuca indice do nó 1
  int indice2 = BuscaNo(&grafo->lista, nome2);                                  // busca indice do nó 2

  if(indice1 < 0 || indice2<0) return 1;                                        // erro


  else
  {
  grafo->matriz[indice1][indice2] = 1;
  grafo->matriz[indice2][indice1] = 1;                                          // grafo não direcionado

  grafo->NArestas++;                                                            // Incrementa o numero de arestas

  return 1;
  }
}



void imprime(TGrafo_Matriz_Adj *grafo)
{
  int i=0, j=0;


  for(i=0; i<grafo->NVertices; i++)
  {
    for(j=0; j<grafo->NVertices; j++)
    {
      printf("%d ", grafo->matriz[i][j]);
    }
    printf("\n");

  }
}

int main()
{
TGrafo_Matriz_Adj grafo;
int vertices=0, arestas=0, i=0;
inicializaGrafo(&grafo);

char A= "A", B = "B", C = "C", D = "D", E = "E";

Insere_Aresta(&grafo, "A", "B");

  Insere_No(&grafo, &A);
  Insere_No(&grafo, &B);
  Insere_No(&grafo, &C);
  Insere_No(&grafo, &D);


  Insere_Aresta(&grafo, &A, &B);
  Insere_Aresta(&grafo, &A, &C);
  Insere_Aresta(&grafo, &B, &D);
  Insere_Aresta(&grafo, &C, &D);
  Insere_Aresta(&grafo, &A, &D);




imprime(&grafo);




  return 0;
}

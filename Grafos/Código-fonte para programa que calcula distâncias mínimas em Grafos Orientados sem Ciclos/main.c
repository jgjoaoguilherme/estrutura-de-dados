

/******************* JOAO GUILHERME BRAGA 104108 ******************/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define INF INT_MAX
#define MAX 1025



typedef struct stackItem                                                        // Item
{
    int value;
    struct stackItem *next;
} stackItem;

typedef struct                                                                  // topo da pilha
{
    stackItem *top;
} StackD;

void stackInit(StackD *stack)                                                   // inicia a pilha
{
    stack->top = NULL;
}


int stackEmpty(StackD *stack)                                                   // verifica se pilha é vazia
{
    if (stack->top == NULL)
        return 1;
    return 0;
}


void push(StackD *stack, int ch)                                                // empilha
{
  stackItem *newStackItem = (stackItem*)malloc(sizeof(stackItem));
  if (!newStackItem) {
    exit(-1);
  }
  newStackItem->value = ch;
  newStackItem->next = stack->top;
  stack->top = newStackItem;
}

int pop(StackD *stack)                                                          // desempilha
{
  int c;

  if (stackEmpty(stack)) {
    return -1;
  }

  stackItem *paux;
  paux = stack->top;
  stack->top = paux->next;
  c = paux->value;
  free(paux);

  return c;
}


void showStack(StackD *stack)                                                   // imprime
{
  stackItem *newStackItem;
  newStackItem = stack->top;
  printf("Stack: ");
  while(newStackItem) {
    printf("%d ",newStackItem->value);
    newStackItem = newStackItem->next;
  }
  printf("\n");
}


typedef struct adjlist_node                                                     // lista de adjacencia
 {
  int vert; //Link vertex
  int cost; //Edge weight
  struct adjlist_node *next;
} adjlist;



typedef struct graph_header                                                     // grafo
{
  unsigned int size; //number of vertex used
  adjlist **adj;
  int *info; //any info
} graph;

graph *initGraph(unsigned int nvert)                                            // inicializa grafo
 {
  graph *G;
  int i;
  G = (graph *)malloc(sizeof(graph));
  G->adj = (adjlist **)malloc(nvert * sizeof(adjlist*));
  for (i = 0; i < nvert;i++) G->adj[i] = NULL;
  G->info = (int *)malloc(nvert * sizeof(int));
  G->size = nvert;
  return G;
}


void initVertex(graph *G, unsigned int i, int data)                             // recebe data
{
  G->info[i] = data;
}


void graphAddEdge(graph* G, int v, int w, int weight) {                         // insere aresta
  adjlist *L;
  L = (adjlist*)malloc(sizeof(struct adjlist_node));
  L->vert = w;
  L->cost = weight;
  if (G->adj[v] == NULL) {
    L->next = G->adj[v];
    G->adj[v] = L;  }
  else {
    adjlist *N;
    N = G->adj[v];
    if (L->vert < N->vert) {
      L->next = G->adj[v];
      G->adj[v] = L;
    } else {
      while (N->next) {
	if (L->vert < N->next->vert) {
	  break;
	}
	N = N->next;
      }
      L->next = N->next;
      N->next = L;
    }
  }
}


// A recursive function used by shortestPath. See below link for details
// http://www.geeksforgeeks.org/topological-sorting/
// modified version of DFS
void topologicalSortUtil(graph* G, int v, int visited[], StackD *stack, int R) {
  // Mark the current node as visited
  visited[v] = 1;

  // Recursive procedure for all the vertices adjacent to this vertex
  adjlist *L = G->adj[v];
  while (L) {
    if ((!visited[L->vert]) && (visited[L->vert <= R]))
      topologicalSortUtil(G, L->vert, visited, stack, R);
    L = L->next;
  }

  // Push current vertex to stack which stores topological sort
  push(stack, v);
}

//Relax function: update lowest distance u->v
// u: vertex cost for outcoming edge
// v: vertex cost for incoming edge
// weightEdge: weight for edge u->v
void relax(int u, int v, int weightEdge, int *dist, int R)
{
  if (dist[v] > dist[u] + weightEdge)
    dist[v] = dist[u] + weightEdge;
}


// The function to find shortest paths from given vertex. It uses recursive
// topologicalSortUtil() to get topological sorting of given graph.
void shortestPath(graph* G, int s, int R)
{
  StackD Stack;
  int dist[MAX];

  stackInit(&Stack);

  // Mark all the vertices as not visited
  int visited[MAX];
  int i;
  for (i = 0; i < G->size; i++)
    visited[i] = 0;



  // Call the recursive helper function to store Topological Sort
  // starting from all vertices one by one
  for (i = s; i < G->size; i++)
    if (visited[i] == 0)
      topologicalSortUtil(G, i, visited, &Stack, R);

  //showStack(&Stack);

  // Initialize distances to all vertices as infinite and distance
  // to source as 0
  for (i = 0; i < G->size; i++)
    dist[i] = INF;
  dist[s] = 0;

  adjlist *L;

  // Process vertices in topological order
  while (stackEmpty(&Stack) == 0) {
    // Get the next vertex from topological order
    int u = pop(&Stack);
    L = G->adj[u];

    // Update distances of all adjacent vertices
    if (dist[u] != INF) {
      while (L) {
	// call relax function to update lowest distance

  if (L->cost <= R)
  {
     L = L->next;
   }

	relax(u, L->vert, L->cost, dist,  R);



      }
    }
  }



  for (i = 0; i < G->size; i++)                                                 // Print the calculated shortest distances
    if (dist[i]==INF) printf("INF ");
    else printf("%d ", dist[i]);
  printf("\n");
}


// Driver program to test above functions
int main()
{
  int V=0, R=0, N=0, M=0, i=0, vert1=0, vert2=0, weight=0;

  scanf("%d", &V);                                              // no inicial da busca
  scanf("%d", &R);                                              // restrição
  scanf("%d %d", &N, &M);                                       // numero total de nos  N e arestas M



  graph* g = initGraph(N);


  for(i=0; i<M; i++)
    {
      scanf("%d %d %d", &vert1, &vert2, &weight);
  graphAddEdge(g, vert1, vert2, weight);
  }



  shortestPath(g, V, R);

  return 0;
}

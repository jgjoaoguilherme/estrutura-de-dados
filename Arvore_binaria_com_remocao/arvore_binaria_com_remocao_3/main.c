#include <stdlib.h>
#include <stdio.h>


typedef struct                                                      // item
{
  int Chave;
  // Outros componentes
}TItem;

typedef struct                                                  // Nó da Arvores
{
  TItem Item;
  struct TNo  *esq, *dir;
}TNo;





TNo *Cria_No (TItem Item)                                   // Função cria nó
{
  TNo *no;
  no = (TNo *) malloc (sizeof(TNo));                                            // Aloca novo nó

  no->Item = Item;                                                              // Recebe item

  no->esq = NULL;                                                                // Nó criado aponta esquerda para NULL
  no->dir = NULL;                                                                // Nó criado aponta direita para  NULL

  return no;                                                                    // retorno apontador do novo no criado
}



void TArvBin_Insere(TNo *raiz, TItem Item)                                        // função inserção
{
  if(Item.Chave < (raiz->Item.Chave))                                             // caso elemento inserido seja menor do que o nó
  {
    if( (raiz->esq) != NULL) TArvBin_Insere(raiz->esq, Item);                 // verifica se há nó filho na esquerda

    else raiz->esq = Cria_No(Item);                                 // caso não haja, insere nó filho
  }

  else                                                                          // caso elemento inserido seja maior do que o nó
  {
    if( (raiz->dir) != NULL) TArvBin_Insere(raiz->dir, Item);                   // verifica se há nó filho na direita
    else raiz->dir = Cria_No(Item);                                   // caso não haja, insere nó filho
  }
}

void TArvBin_Imprime(TNo *raiz)
{
  printf("Pre ordem:\n");
  TArvBin_Imprime_PreOrdem(raiz);
  printf("\n");

  printf("Em ordem:\n");
  TArvBin_Imprime_EmOrdem(raiz);
  printf("\n");

  printf("Pos ordem:\n");
  TArvBin_Imprime_PosOrdem(raiz);
  printf("\n");
}


void TArvBin_Imprime_PreOrdem(TNo *raiz)                                        // Função Imprime PreOrdem
{
  if (raiz != NULL)
  {
    printf("%d ", raiz->Item.Chave);
    TArvBin_Imprime_PreOrdem(raiz->esq);
    TArvBin_Imprime_PreOrdem(raiz->dir);
  }
}


void TArvBin_Imprime_EmOrdem(TNo *raiz)                                         // Função Imprime EmOrdem
{                                                                               // Elementos são impressos em orde crescente
  if (raiz != NULL)
  {

    TArvBin_Imprime_EmOrdem(raiz->esq);
    printf("%d ", raiz->Item.Chave);
    TArvBin_Imprime_EmOrdem(raiz->dir);
  }
}


void TArvBin_Imprime_PosOrdem(TNo *raiz)                                        // Função Imprime PosOrdem
{
  if (raiz != NULL)
  {

    TArvBin_Imprime_PosOrdem(raiz->esq);
    TArvBin_Imprime_PosOrdem(raiz->dir);
    printf("%d ", raiz->Item.Chave);
  }
}


TNo *TArvBin_Libera(TNo *raiz)
{
  if(raiz != NULL)
  {
    TArvBin_Libera(raiz->esq);
    TArvBin_Libera(raiz->dir);
    free(raiz);
  }
  return NULL;
}


TNo * minValueNode (TNo* no)
{
  TNo * current = no;

  while(current->esq != NULL) current = current->esq;

  return current;
}


TNo * deleteNode (TNo * root, TItem Item)
{
  if (root == NULL) return root;


  if ((Item.Chave) < (root->Item.Chave)) root->esq = deleteNode(root->esq, Item);

  else if (Item.Chave > root->Item.Chave) root-> dir = deleteNode (root->dir, Item);


  else
  {
    if (root->esq == NULL)
    {
      TNo *temp = root->dir;
      free(root);
      return temp;
    }

    else if(root->dir == NULL)
    {
      TNo* temp = root->esq;
      free(root);
      return temp;
    }


    TNo * temp = minValueNode (root->dir);

    root->Item.Chave = temp->Item.Chave;

    root->dir = deleteNode (root->dir, temp->Item);
  }

  return root;
}







int main()
{

  TNo *Raiz;
  int i=0, n=0, num=0, status=0;
  TItem Item;

  Raiz = NULL;

  printf("entre com a quantidade de elementos:\n");
  scanf("%d", &n);


  for(i=0; i<n; i++)
  {
    printf("entre com o elemento %d:", i+1);
    scanf("%d", &num);
    Item.Chave = num;

    if(Raiz == NULL) Raiz = Cria_No(Item);                            // Caso a árvore esteja vazia

    else  TArvBin_Insere(Raiz, Item);

  }



  TArvBin_Imprime(Raiz);


  printf("entre comc elemento a ser removido:\n");
  scanf("%d", &Item.Chave);

  deleteNode(Raiz, Item);

  TArvBin_Imprime(Raiz);


  TArvBin_Libera(Raiz);


  return 0;
}

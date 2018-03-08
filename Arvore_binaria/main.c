#include <stdio.h>
#include <stdlib.h>

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



void TArvBin_Insere(TNo *no, TItem Item)
{
  if(Item.Chave < (no->Item.Chave))
  {
      if( (no->esq) != NULL) TArvBin_Insere(no->esq, Item);

      else no->esq = Cria_No(Item);
  }

  else
  {
    if( (no->dir) != NULL) TArvBin_Insere(no->dir, Item);

    else no->dir = Cria_No(Item);
  }
}


void TArvBin_Imprime(TNo *raiz)                                                 // Função Imprime percorrendo em pré ordem
{
  if (raiz != NULL)
  {

    TArvBin_Imprime(raiz->esq);
    printf("%d ", raiz->Item.Chave);
    TArvBin_Imprime(raiz->dir);
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




int main()
{

TNo *Raiz;
int i=0, n=0, num=0;
TItem Item;

Raiz = NULL;

printf("entre com a quantidade de elementos:\n");
scanf("%d", &n);


for(i=0; i<n; i++)
{
  printf("entre com o elemento %d:", i+1);
  scanf("%d", &num);
  Item.Chave = num;

  if(Raiz == NULL) Raiz = Cria_No(Item);

  else  TArvBin_Insere(Raiz, Item);



}


TArvBin_Imprime(Raiz);
printf("\n");



TArvBin_Libera(Raiz);


return 0;
}

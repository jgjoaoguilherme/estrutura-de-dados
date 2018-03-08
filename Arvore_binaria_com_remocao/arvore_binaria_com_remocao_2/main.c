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


void removerNo(TNo *p)
{
  TNo *q;


  if((p->esq) == NULL)
  {
    q = p;
    p = p->dir;
    free(q);
  }

  else if((p->dir) == NULL)
  {
    q = p;
    p = p->esq;
    free(q);
  }

  else substituimenoradireita(p, p->dir);

}


void substituimenoradireita(TNo *p, TNo * suc)
{
  TNo* q;


  if((suc->esq) == NULL)
  {
    p->Item.Chave = suc->Item.Chave;
    q = suc;
    suc = suc->dir;
    free(q);
  }

  else substituimenoradireita(p, suc->esq);
}




void busca_remove(TNo* raiz, TItem Item)
{
  if (raiz == NULL) return 1;

  if((raiz->Item.Chave) == Item.Chave)
  {
    removerNo(raiz);
    return 1;
  }

  if((raiz->Item.Chave) < Item.Chave )
  {
     busca_remove(raiz->dir, Item);
  }

  else
  {
     busca_remove(raiz->esq, Item);
  }
}


int Tamanho(TNo *raiz)
{
  int count=0;
    if (raiz != NULL)
    {
      count++;
      Tamanho(raiz->esq);
      Tamanho(raiz->dir);
      return count;
    }

    printf("%d\n", count);
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


  printf("Entre com elemento a ser removido:\n");
  scanf("%d", &Item.Chave);
  busca_remove(Raiz, Item);

  TArvBin_Imprime(Raiz);
  Tamanho(Raiz);

  TArvBin_Libera(Raiz);


  return 0;
}

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





TNo *Cria_No (TItem Item, TNo *esq, TNo *dir)                                   // Função cria nó
{
  TNo *no;
  no = (TNo *) malloc (sizeof(TNo));                                            // Aloca novo nó

  no->Item = Item;                                                              // Recebe item

  no->esq = esq;                                                                // Nó criado aponta esquerda para NULL
  no->dir = dir;                                                                // Nó criado aponta direita para  NULL

  return no;                                                                    // retorno apontador do novo no criado
}



void TArvBin_Insere(TNo *raiz, TItem Item)                                        // função inserção
{
  if(Item.Chave < (raiz->Item.Chave))                                             // caso elemento inserido seja menor do que o nó
  {
      if( (raiz->esq) != NULL) TArvBin_Insere(raiz->esq, Item);                 // verifica se há nó filho na esquerda

      else raiz->esq = Cria_No(Item, NULL, NULL);                                 // caso não haja, insere nó filho
  }

  else                                                                          // caso elemento inserido seja maior do que o nó
  {
    if( (raiz->dir) != NULL) TArvBin_Insere(raiz->dir, Item);                   // verifica se há nó filho na direita
    else raiz->dir = Cria_No(Item, NULL, NULL);                                   // caso não haja, insere nó filho
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


TNo * TArvBin_Busca_Elemento(TNo *raiz, TItem Item)                             // Procura por elemento Item
{
  TNo *sign, *pai;

  pai = raiz;
  sign = raiz;

  while(sign != NULL)                                                           // percorre arvore binária
  {
    if((Item.Chave) < (sign->Item.Chave))                                       // caso elemento procurado seja menor do que o nó
    {
      pai = sign;
      sign = sign->esq;                                                         // avança para a esquerda
    }

    else if ((Item.Chave) > (sign->Item.Chave))                                 // casa elemento procurado seja maior do que o nó
    {
      pai = sign;
      sign = sign->dir;                                                         // avança para a direita
    }

    else if ((Item.Chave) == (sign->Item.Chave))                                // caso elemento procurado seja igual ao nó
    {
      return pai;                                                              // retorna ponteira da posição do nó pai
    }

    else return NULL;                                                           // caso não encontre o elemento, retorna NULL
  }
  return NULL;                                                                  // Caso em que a árvore é vazia
}


void TArvBin_Remove(TNo *raiz, TItem Item)
{
  int referencia=0;
  TNo *pai, *aux;

  pai = TArvBin_Busca_Elemento(raiz, Item);                                     // ponteiro aponta para o nó pai do elemento a ser removido

  if(Item.Chave < (pai->Item.Chave))                                            // verifica se o item é menor que pai, se for, esta na esquerda
  {
    aux = pai->esq;
    referencia=1;
  }

  else                                                                          // caso o item seja maior ou igual, estará na direita do pai
  {
    aux = pai->dir;
  }


  if (pai == raiz)                                                              // caso o ponteiro pai seja igual ao filho, quer dizer que só tem 1 elemento.
  {
    free(pai);                                                                  // libera
    raiz == NULL;                                                               // faz raiz apontar para NULL
  }


  if( ((aux->esq) == NULL) && ((aux->dir) == NULL) )                            // nó folha, sem descendentes
  {
    pai
  }



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

  if(Raiz == NULL) Raiz = Cria_No(Item, NULL, NULL);                            // Caso a árvore esteja vazia

  else  TArvBin_Insere(Raiz, Item);

}



TArvBin_Imprime(Raiz);

TArvBin_Libera(Raiz);


return 0;
}

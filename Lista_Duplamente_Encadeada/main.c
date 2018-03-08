#include <stdio.h>
#include <stdlib.h>

typedef struct                                                                  // Celula
{
  int Chave;
}TItem;

typedef struct SCelula *TApontador;

typedef struct SCelula
{
  TItem Item;
  TApontador Ant, Prox;
}TCelula;

typedef struct
{
  TApontador Primeiro, Ultimo;
  int Tamanho;
}TLista;


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
      printf("%d ", aux->Item.Chave);
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

  int status = 0, i=0, tamanho=0;

  tamanho = pLista->Tamanho;

  for(i=0; i<tamanho; i++)
  {
    status = TLista_Retira_Fim(pLista, Item);
    Imprime_Status(status);
    printf("Elemento %d removido\n", Item->Chave);
  }
  return 0;
}

/******************************** FUNCÕES DE REMOÇÃO  ********************************/


void Imprime_Status(int status)
{
  if (status == 0) printf("ok\n");

  else if(status == 1) printf("erro\n");

  else printf("erro inesperado\n");
}



void menu(TLista *pLista)
{
  TApontador sign;
  TItem Item;
  int opc=1, x=0, status=0, intervalo1=0, N=0, i=0, aux=0;

  do {
    printf("\n");
    printf("*** menu ***\n\n");
    printf("Entre com a opcao:\n");
    printf("01 inserir no inicio:\n");
    printf("02 inserir no fim:\n");
    printf("03 inserir na posicao:\n");
    printf("04 remover no inicio:\n");
    printf("05 remover no fim:\n");
    printf("06 remover na posicao:\n");
    printf("07 imprimir:\n");
    printf("08 tamanho\n");
    printf("09 limpa lista\n");
    printf("10 sair:\n");

    scanf("%d", &x);


    switch (x)
    {
      case 1:
      printf("Entre com o elemento:\n");
      scanf("%d", &Item.Chave);
      status = TLista_Insere_Comeco(pLista, Item);
      Imprime_Status(status);
      TLista_Imprime(pLista);
      break;


      case 2:
      printf("Entre com o elemento:\n");
      scanf("%d", &Item.Chave);
      status = TLista_Insere_Fim(pLista, Item);
      Imprime_Status(status);
      TLista_Imprime(pLista);
      break;


      case 3:
      printf("Entre com o elemento:\n");
      scanf("%d", &Item.Chave);
      intervalo1 = TLista_Tamanho(pLista);
      printf("Em qual posição N gostaria de adicionar? (1 < N < %d)", intervalo1);
      scanf("%d", &N );
      N--;
      sign = pLista->Primeiro;
      for(i=0; i<N; i++)
      {
        sign = sign->Prox;
      }

      status = TLista_Insere_Sign(pLista, sign, Item);
      Imprime_Status(status);
      TLista_Imprime(pLista);
      break;



      case 4:
      status=TLista_Retira_Comeco(pLista, &Item);
      Imprime_Status(status);
      printf("Elemento %d removido", Item.Chave);
      TLista_Imprime(pLista);
      break;

      case 5:
      status=TLista_Retira_Fim(pLista, &Item);
      Imprime_Status(status);
      printf("Elemento %d removido", Item.Chave);
      TLista_Imprime(pLista);
      break;



      case 6:
      intervalo1 = TLista_Tamanho(pLista);
      printf("Em qual posição N gostaria de remover? (1 < N < %d)", intervalo1);
      scanf("%d", &N );
      N--;
      sign = pLista->Primeiro;
      for(i=0; i<N; i++)
      {
        sign = sign->Prox;
      }

      status = TLista_Retira_Sign(pLista, sign, &Item);
      Imprime_Status(status);
      TLista_Imprime(pLista);
      break;

      case 7:
      TLista_Imprime(pLista);
      break;

      case 8:
      aux = TLista_Tamanho(pLista);
      printf("Lista de tamanho:%d\n", aux);
      break;

      case 9:
      TLista_Sair(pLista, &Item);
      TLista_Imprime(pLista);
      break;

      case 10:
      TLista_Sair(pLista, &Item);
      TLista_Imprime(pLista);
      opc=0;
      break;

      default:
      printf("valor invalido!\n");
      break;

    }

  } while(opc == 1);
}



int main()
{
  TLista pLista;
  TLista_Inicia(&pLista);


  menu(&pLista);



  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define TAM 5

typedef struct
{
    int Chave;
    /* outros componentes */
} TItem;


typedef struct SCelula *TApontador;


typedef struct SCelula
{
    TItem ITem;
    TApontador Prox;
} TCelula;


typedef struct
{
    TApontador Frente, Tras;
    int Tamanho;
} TFila;


void TFila_Inicia ( TFila *pFila)
{
    pFila->Frente = NULL;
    pFila->Tras = pFila->Frente;
    pFila->Tamanho = 0;
}

int TFila_EhVazia(TFila *pFila)
{
    if(pFila->Frente == NULL) return 0;

    else return 1;
}


int TFila_Tamanho (TFila *pFila)
{
    return (pFila->Tamanho);
}


int TFila_Enfileira(TFila *pFila, TItem Item)
{
    TApontador aux;
    aux = (TCelula*) malloc (sizeof(TCelula));
    aux->Prox = NULL;

    if (!aux) return 1;

    else
    {

        aux->ITem = Item;

        if(!TFila_EhVazia(pFila))               // Verifica se a fila é vazia para poder fazer frente apontar para a nova celula
        {
            pFila->Frente = aux;
        }

        else                                        // Caso não seja, tras aponta para a nova celula somente, sem alterar inicio
        {
            pFila->Tras->Prox = aux;
        }

            pFila->Tras = aux;
            pFila->Tamanho++;

            return 0;

    }
}


int TFila_Desenfileira (TFila *pFila, TItem *Item)
{
    if(!TFila_EhVazia(pFila)) return 1;

    else
    {
        TApontador aux;
        aux = pFila->Frente;
        pFila->Frente = aux->Prox;

        *Item = aux->ITem;

        free(aux);

        pFila->Tamanho--;

        return 0;
    }


}


int TFila_Limpa(TFila *pFila, TItem *Item)
{
    if (!
        TFila_EhVazia(pFila)) return 1;

    else
        {
    while(pFila->Tamanho > 0) TFila_Desenfileira(pFila, Item);
    return 0;
        }
}


void Imprime(TFila *pFila)
{
    TApontador aux;
    aux = pFila->Frente;

    if(!TFila_EhVazia(pFila)) printf("Fila Vazia!\n");

    else
    {

        while(aux != NULL)
        {
            printf("%d ", aux->ITem.Chave);
            aux = aux->Prox;
        }
        printf("\nPrimeiro elemento:%d\tUlimo elemento:%d", pFila->Frente->ITem.Chave, pFila->Tras->ITem.Chave);
    }
    printf("\n");
}

int main()
{
    TFila Fila;
    TFila_Inicia(&Fila);

    int i=0, aux=0;
    TItem Item;


    for(i=0; i<TAM; i++)
    {
        printf("Entre com elemento %d:\n", i);
        scanf("%d", &aux);
        Item.Chave = aux;
        TFila_Enfileira(&Fila, Item);
    }

    printf("\n\n");
    printf("Imprimindo fila:\n");

    Imprime(&Fila);

    if (!TFila_Limpa(&Fila, &Item)) printf("Lista limpa!\n");
    Imprime(&Fila);


    return 0;
}

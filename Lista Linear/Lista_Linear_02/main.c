#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int Chave;
    int indice;
} TItem;


typedef struct SCelula *TApontador;


typedef struct SCelula
{
    TItem Item;
    TApontador Prox;
} TCelula;


typedef struct
{
    TApontador Primeiro, Ultimo;
    int Tamanho;
} TLista;



void TLista_Inicia(TLista *pLista)
{
    pLista->Primeiro==NULL;
    pLista->Ultimo==NULL;
    pLista->Tamanho=0;
}


int TLista_EhVazia (TLista *pLista)
{
    if (pLista->Tamanho==0) return 0;
    else return 1;
}


int TLista_Insere_Comeco(TLista *pLista, TItem x)
{
    TApontador aux;                                         // Apontador para nova célula
    aux = (TLista*) malloc (sizeof(TLista));


    if(!aux) return 1;

    else
    {
        aux->Item=x;                                    //Recebe o item
        aux->Prox=NULL;

        if(pLista->Tamanho==0)                              // Caso lista tenha tamanho 0
        {
            pLista->Primeiro=aux;                           // Lista aponta Primeiro para aux
            pLista->Ultimo=aux;                             // Lista aponta Ultimo para aux
        }
        else
        {
            aux->Prox= pLista->Primeiro;                        // Célula aponta para primeira elemento
            pLista->Primeiro=aux;                               // Lista aponta Primeiro para aux
        }

        pLista->Tamanho++;                                  // Incrementa 1 no tamanho
        return 0;
    }
}


int TLista_Insere_Fim (TLista *pLista, TItem x)
{
    TApontador aux;                                         // Apontador para nova célula
    aux = (TLista*) malloc (sizeof(TLista));

    if(!aux) return 1;

    else
    {
        aux->Item=x;                                       // Celula aux recebe valor de x
        aux->Prox=NULL;                                    // Celula aux aponta para NULL, indicando fim

        if(pLista->Tamanho==0)                             // Caso a lista não tenha elementos
        {
            pLista->Primeiro=aux;
            pLista->Ultimo=aux;
        }

        else                                               // Caso a lista tenha elementos
        {
            pLista->Ultimo->Prox=aux;                      // Ultima celula da lista aponta para aux
            pLista->Ultimo=aux;                            // Ponteiro de ultimo elemento da lista aponta para aux
        }
        pLista->Tamanho++;                                 // Incerementa 1 no tamanho da lista
        return 0;

    }
}


int TLista_Insere_Posicao (TLista *pLista, TApontador posicao, TItem x)
{
    TApontador anterior, aux;           // Apontadores auxiliares
    anterior = pLista->Primeiro;        // Apontador aponta para primeiro elemento

    while(anterior->Prox!=posicao) anterior=anterior->Prox;                 // Faz apontador anterior avancar até encontrar o apontador marcado

    aux= (TLista*) malloc (sizeof(TLista));

    if (!aux) return 1;

    else
    {
        aux->Prox=NULL;                                                     // Auxiliar aponta para NULL
        aux->Item=x;                                                        // Nova celula recebe elemento
        aux->Prox=posicao;                                                  // Nova celula aponta para posição que ira inserir
        anterior->Prox=aux;                                                 // Ponteiro anterior ao marcado aponta para novo elemento
        pLista->Tamanho++;                                                  // Incrementa tamanho em 1
        return 0;
    }
}


int TLista_Ordenacao(TLista *pLista, TItem item)
{
    TApontador aux;
    aux=pLista->Primeiro;

    int somaT=0, soma1=0, soma2=0;


    while(aux!=NULL)
    {
        if(item.indice > aux->Item.indice)                         // Caso expoente seja maior que o valor verificado, insere elemento
        {
            TLista_Insere(pLista, aux, item);
            return 0;
        }

        else if (item.indice < aux->Item.indice)  aux=aux->Prox;   // Caso seja menor, avança uma poosição

        else if (aux->Item.indice == item.indice)                  // Caso seja igual, realiza soma
        {
            soma1 = item.Chave;
            soma2 = aux->Item.Chave;
            somaT= soma1 + soma2;

            if(somaT==0)                                             // Caso a soma resulte em 0, retira o elemento da lista
            {
                TLista_Retira(pLista, aux, &item);
                return 0;
            }
            else                                                    // Caso seja diferente de 0, insere valor somado
            {
                aux->Item.Chave=somaT;
                return 0;
            }
        }
    }

    TLista_Insere_Fim(pLista, item);                           // Caso não tenha elemento maior, insere no fim
    return 0;

}


int TLista_Insere(TLista *pLista, TApontador posicao, TItem x)
{
    if(pLista->Primeiro==posicao)                                            // Caso ponteiro aponte para primeiro, insere no começo
    {
        TLista_Insere_Comeco(pLista, x);
        return 0;
    }

    else                                                                    // Caso contrário, insisra na posicao indicada
    {
        TLista_Insere_Posicao(pLista, posicao, x);
        return 0;
    }
}




int TLista_Retira(TLista *pLista, TApontador posicao, TItem *px)
{
    if(pLista->Primeiro == posicao)
    {
        TLista_Retira_Comeco(pLista, px);
        return 0;
    }
    else if (pLista->Ultimo == posicao)
    {
        TLista_Retira_Fim(pLista, px);
        return 0;
    }
    else
    {
        TLista_Retira_Posicao(pLista, posicao, px);
        return 0;
    }
}




int TLista_Retira_Comeco(TLista *pLista, TItem *px)
{
    if (pLista->Tamanho==0) return 1;                   // Verifica se a lista esta vazia

    TApontador aux;                                    // Apontador auxiliar
    aux=pLista->Primeiro;                              // Apontador auxiliar aponta para primeiro elemento

    if(pLista->Tamanho==1)
    {
        pLista->Primeiro=NULL;
        pLista->Ultimo=NULL;
    }

    else
    {
        pLista->Primeiro=aux->Prox;                    // Apontador do primeiro elemento da lista aponta para o segundo elemento
    }

    *px=aux->Item;                                 // Item retirado é repassado
    free(aux);                                     // desaloca antigo primeiro elemento
    pLista->Tamanho--;                             // Desincrementa tamanho da lista
    return 0;

}


int TLista_Retira_Fim(TLista *pLista, TItem *px)
{
    if (pLista->Tamanho==0) return 1;                           // Verifica se lista esta vazia


    TApontador aux;

    if(pLista->Tamanho==1)
    {
        aux=pLista->Primeiro;
        pLista->Primeiro=NULL;
        pLista->Ultimo=NULL;
    }

    else
    {
        TApontador anterior;                                    // Apontadores para execução
        anterior=pLista->Primeiro;                              // Faz apontador anterior apontar para primeiro elemento

        while(anterior->Prox!=pLista->Ultimo)   anterior= anterior->Prox; // Faz apontador percorrer lista até achar penúltimo elemento

        aux=pLista->Ultimo;                                     // Grava último elemento da lista
        anterior->Prox=NULL;                                    // Como apontador anterior é o novo último elemento, aponta-o para NULL
        pLista->Ultimo=anterior;                                // Lista grava novo ultimo elemento
    }

    *px=aux->Item;                                          // recebe elemento removido
    free(aux);                                              // Libera espaço do antigo ultimo elemento
    pLista->Tamanho--;                                      // decrementa em 1 unidade o tamanho da lista
    return 0;

}


int TLista_Retira_Posicao(TLista *pLista, TApontador posicao, TItem *px)
{
    if(pLista->Tamanho==0) return 1;

    else
    {
        TApontador anterior, aux;                                               // Apontadores auxiliares
        anterior=pLista->Primeiro;                                              // Faz apontador anterior apontar para primeiro da lista

        while(anterior->Prox!=posicao) anterior=anterior->Prox;                 // Faz apontador anterior avancar até encontrar o apontador marcado

        aux=posicao;
        anterior->Prox=aux->Prox;
        *px=aux->Item;
        free(aux);
        pLista->Tamanho--;
        return 0;
    }
}


TApontador TLista_Compara(TLista *pLista, TItem item)
{
    TApontador aux;
    aux= pLista->Primeiro;

    while(aux!=NULL)                                                        // Percorre vetor ate chegar na ultima posicao
    {
        if(item.indice>aux->Item.indice) return aux;                 // realiza a pesquisa
        aux=aux->Prox;                                                      // Avança uma posicao
    }
    aux=pLista->Ultimo;
    return aux;



}



int TLista_Tamanho(TLista *pLista)
{
    return pLista->Tamanho;
}



TApontador TLista_Procura(TLista *pLista, TItem Item)
{
    if(Item.indice==pLista->Primeiro->Item.indice) return pLista->Primeiro;                // Verifica se item esta na primeira posicao

    else
    {
        TApontador aux;
        aux=pLista->Primeiro->Prox;                                             // Apontador que percorrera a lista inicia na segunda posicao

        while(aux!=NULL)                                                        // Percorre vetor ate chegar na ultima posicao
        {
            if(aux->Item.indice==Item.indice) return aux;                                     // realiza a pesquisa
            aux=aux->Prox;                                                      // Avança uma posicao
        }
        aux=pLista->Primeiro;                                                    // Caso não encontre, aponta para primeiro elemento da lista
        return aux;                                                               // Retorna 1 caso nao encontre elemento

    }
}



void Verifica(status)
{
    if(status!=0)
    {
        printf("Erro!\n");
        exit(0);
    }

    else printf("ok\n");
}


void TLista_Imprime(TLista *pLista)
{
    int indice=1, i=0;
    if(pLista->Tamanho==0) printf("Lista vazia!\n");
    else
    {
        TApontador aux;
        aux=pLista->Primeiro;

        for(i=0; i<pLista->Tamanho; i++)
        {
            printf ("%d [%d]    ", aux->Item.Chave, aux->Item.indice);
            indice++;
            aux=aux->Prox;
        }
        printf("\n");
    }
}


int main()
{
    TLista pLista;
    TLista_Inicia(&pLista);


    int n=0, i=0, status, soma1=0, soma2=0;
    TItem item, ind;
    ind.Chave=0;
    ind.indice=0;
    item.Chave=0;
    item.indice=0;
    TApontador aux;


    n=6;

    for(i=0; i<n; i++)
    {
        item.Chave=i;
        soma1=item.indice;
        soma2= soma1 + 2;
        item.indice=soma2;

        status=TLista_Insere_Comeco(&pLista, item);
        Verifica(status);
        TLista_Imprime(&pLista);
    }



    printf("Inserir valor e posicao desejada:\n");
    scanf("%d %d", &ind.Chave, &ind.indice);


    status=TLista_Ordenacao(&pLista, ind);
    Verifica(status);
    TLista_Imprime(&pLista);







    for(i=0; i<n+1; i++)
    {
        status=TLista_Retira_Comeco(&pLista, &item);
        Verifica(status);
        TLista_Imprime(&pLista);
    }





    return 0;
}


#include <stdio.h>
#include <stdlib.h>


typedef int TChave;

typedef struct                                   // Chave
{
    TChave Chave;
} TItem;

typedef struct SCelula *TApontador;

typedef struct SCelula                          // Célula
{
    TItem Item;
    TApontador Prox;
} TCelula;


typedef struct                                  // Pilha
{
    TApontador Topo;
    int Tamanho;
} TPilha;



void TPilha_Inicia(TPilha *pPilha)                   // Inicia a Pilha
{
    pPilha->Tamanho=0;
    pPilha->Topo=NULL;
}


int TPilha_Ehvazia(TPilha *pPilha)                   // Verifica Pilha Vazia
{
    if(pPilha->Tamanho==0) return 0;
    else return 1;
}


int TPilha_Empilha(TPilha *pPilha, TItem Item)                   // Empilha
{
    TApontador aux;
    aux = (TCelula*) malloc (sizeof(TCelula));                  // Aloca espaço

    if(!aux) return 1;                                          // Caso não aloque, retorna 1

    else{
    aux->Prox = NULL;                                           // Novo apontador aponta para NULL
    aux->Item = Item;                                           // Recebe Item
    aux->Prox = pPilha->Topo;                                   // Aponta para o topo
    pPilha->Topo = aux;                                         // Topo aponta para o novo elemento
    pPilha->Tamanho++;                                          // incrementa o tamanho
    return 1;
    }
}


int TPilha_Desempilha(TPilha *pPilha, TItem *Item)          // Desempilha
{
    if(pPilha->Tamanho == 0) return 1;                          // pilha vazia

    else
    {
        TApontador aux;                                     // Apontador auxiliar
        aux = pPilha->Topo;                                 // Faz aux apontar para o topo
        pPilha->Topo = aux->Prox;                           // Faz o topo apontar para o proximo elemento
        *Item = aux->Item;                                  // REcebe elemento a ser removido
        free(aux);                                          // Libera espaço do aux
        pPilha->Tamanho--;                                       // Diminui tamanho ta pilha
        return 1;
    }

}


int TPilha_Desempilha_Tudo(TPilha *pPilha, TItem *Item)     // Desempilha
{
    if(pPilha->Tamanho == 0) return 1;

    else
    {
        int i=0;
        for (i=0; i<pPilha->Topo; i++) TPilha_Desempilha(pPilha, Item);
    }
}


int TPilha_Tamanho(TPilha *pPilha)                    // Tamanho
{
    return pPilha->Tamanho;
}


void TPilha_Imprime (TPilha *pPilha)
{
    if (pPilha->Topo == 0) printf("Pilha Vazia!\n");

    else{
    TApontador aux;
    aux = pPilha->Topo;

    while(aux!= NULL)
    {
        printf("%d ", aux->Item.Chave);
        aux = aux->Prox;
    }
    }
}

void Menu(TPilha *pPilha)
{
    int opc=0, iteracao=1, aux=0;
    TItem Item;



    while(iteracao == 1)
    {
        printf("Digite o valor da opcao:\n\n");
        printf("1: Empilhar\n");
        printf("2: Desempilhar\n");
        printf("3: Tamanho\n");
        printf("4: Imprime\n");
        printf("5: Limpar pilha\n");
        printf("6: sair\n\n\n");

        scanf("%d", &opc);


        switch(opc)
        {


        case 1:
            printf("Entre com o item:\n");
            scanf("%d", &Item.Chave);
            TPilha_Empilha(pPilha, Item);
            break;


        case 2:
            printf("Desempilhando\n");
            TPilha_Desempilha(pPilha, &Item);
            break;


        case 3:
            aux=TPilha_Tamanho(pPilha);
            printf("Pilha de tamanho: %d", aux);
            break;


        case 4:
            TPilha_Imprime(pPilha);
            break;


        case 5:
            TPilha_Desempilha_Tudo(pPilha, &Item);
            break;


        case 6:
            TPilha_Desempilha_Tudo(pPilha, &Item);
            iteracao=0;
            break;
        }
    }
}




int main()
{

    TPilha pPilha;
    TPilha_Inicia(&pPilha);                              // Inicia a pilha

    Menu(&pPilha);



    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX_TAM 5



typedef struct
{
    int x;
    /* outros componentes */
}TItem;


typedef struct
{
    TItem Item[MAX_TAM];
    int Topo;
}TPilha;




void TPilha_Inicia(TPilha *pPilha)           // inicia uma pilha vazia e zera seus elementos
{
    int i=0;
    pPilha->Topo=-1;

    for(i=0; i<MAX_TAM; i++)
    {
        pPilha->Item[i].x=0;
    }
}


int TPilha_EhVazia(TPilha *pPilha)           // verifica se a pilha é vazia
{
    if (pPilha->Topo==-1) return 0;

    else return 1;
}


int TPilha_Empilha (TPilha *pPilha, TItem Item)
{
    if(pPilha->Topo==MAX_TAM) return 1;

    else
    {
        pPilha->Topo++;
        pPilha->Item[pPilha->Topo]=Item;
        return 0;
    }
}


int TPilha_Desempilha(TPilha *pPilha, TItem *Item)        // Desempilha o item x no topo da pilha
{
    if(pPilha->Topo==-1) return 1;

    else
    {
        *Item=pPilha->Item[pPilha->Topo];
        pPilha->Item[pPilha->Topo].x=0;
        pPilha->Topo--;
        return 0;
    }
}


int TPilha_Tamanho(TPilha *pPilha)          // Retorna o número de itens da pilha
{
    return pPilha->Topo;
}

void TPilha_Imprime(TPilha *pPilha)          // Imprime a pilha
{
    int i=0;
    for(i=0; i<MAX_TAM; i++){
    printf("%d\t", pPilha->Item[i].x);
    }
    printf("\n");
}



int TPilha_Limpa(TPilha *pPilha)
{
    int i=0;

    if (pPilha->Topo == -1) return 1;

    else
    {
    for(i=0; i<MAX_TAM; i++)
    {
    pPilha->Item[i].x=0;
    pPilha->Topo=0;
    }
    return 0;
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
            scanf("%d", &Item.x);
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
            TPilha_Limpa(pPilha);
            break;


        case 6:
            iteracao=0;
            break;
        }
    }
}



int main ()
{

    TPilha pPilha;
    TPilha_Inicia(&pPilha);

    Menu(&pPilha);

    return 0;
}

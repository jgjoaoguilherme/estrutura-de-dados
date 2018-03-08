#include <stdio.h>
#include <stdlib.h>


typedef struct TarvG{
  char info;
  struct TArvG *filho;
  struct TArvG *irmao;
}TArvG;



TArvG * criaNo(char c)
{
  TArvG *novo;
  novo = (TArvG*) malloc (sizeof(TArvG));

  novo->info = c;
  novo->filho = NULL;
  novo->irmao = NULL;

  return novo;
}



void criaArvG(TArvG *root,char c)
{
  root = criaNo;
  root->info = c;
  printf("%c\n", info->info);
  printf("Arvore Generica Criada\n");
}

int main()
{
TArvG *root;
char c = 'A';

root = criaArvG(root, c);



printf("hello wordl!\n");


return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct arvgen {
  int info;
  struct arvgen *prim;
  struct arvgen *prox;
};
typedef struct arvgen ArvGen;


ArvGen* cria (int info)
{
  ArvGen *a =(ArvGen *)malloc(sizeof(ArvGen));
  a->info = info;
  a->prim = NULL;
  a->prox = NULL;
  return a;
}

void insere (ArvGen* a, ArvGen* f)
{
  f->prox = a->prim;
  a->prim = f;
}



void libera (ArvGen* a)
{
  ArvGen* p = a->prim;
  while (p!=NULL) {
    ArvGen* t = p->prox;
    libera(p);
    p = t;
  }
  free(a);
}

void imprime (ArvGen* a)
{
  ArvGen* p;
  printf("%d ",a->info);
  for (p=a->prim; p!=NULL; p=p->prox)
    imprime(p);
}

int busca (ArvGen* a, int c)
{
  ArvGen* p;
  if (a->info==c)
    return 1;
  else {
    for (p=a->prim; p!=NULL; p=p->prox) {
      if (busca(p,c))
        return 1;
    }
  }
  return 0;
}

int main()
{
  /* cria nós como folhas */
  ArvGen* num43 = cria(43);
  ArvGen* num22 = cria(22);
  ArvGen* num66 = cria(66);
  ArvGen* num31 = cria(31);
  ArvGen* num21 = cria(21);
  ArvGen* num58 = cria(58);
  ArvGen* num71 = cria(71);
  ArvGen* num59 = cria(59);
  ArvGen* num12 = cria(12);
  ArvGen* num45 = cria(45);
  ArvGen* num35 = cria(35);

  /* monta a hierarquia */
  insere(num45,num35);
  insere(num58,num12);
  insere(num58,num59);
  insere(num58,num71);
  insere(num22,num31);
  insere(num22,num66);
  insere(num43,num45);
  insere(num43,num58);
  insere(num43,num21);
  insere(num43,num22);

  printf("Arvore binaria pre-ordem: ");
  imprime(num43);
  printf(" ");

  // Busca pelo número 12
  if (busca(num43, 12))
    printf("\nO numero 12 esta na arvore.\n");
  else
    printf("\nO numero 12 nao esta na arvore.\n");

  // Busca pelo número 88
  if (busca(num43, 88))
    printf("O numero 88 esta na arvore.\n");
  else
    printf("O numero 88 nao esta na arvore.\n");


  libera(num43);

  return 0;
}



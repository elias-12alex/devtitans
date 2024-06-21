#include <stdio.h>
#include <stdlib.h>

struct arv {
  int info;
  struct arv* esq;
  struct arv* dir;
};

typedef struct arv Arv;

Arv* inicializa(void)
{
  return NULL;
}

Arv* cria(int c, Arv* sae, Arv* sad)
{
  Arv* p=(Arv*)malloc(sizeof(Arv));
  p->info = c;
  p->esq = sae;
  p->dir = sad;
  return p;
}

int vazia(Arv* a)
{
  return a==NULL;
}

Arv* libera (Arv* a){
  if (!vazia(a)){
    libera(a->esq); /* libera sae */
    libera(a->dir); /* libera sad */
    free(a); /* libera raiz */
  }
  return NULL;
}

void imprime_pre (Arv* a)
{
  if (!vazia(a)){
    printf("%d ", a->info); /* mostra raiz */
    imprime_pre(a->esq); /* mostra sae */
    imprime_pre(a->dir); /* mostra sad */
  }
}

void imprime_in (Arv* a)
{
  if (!vazia(a)){
    imprime_in(a->esq); /* mostra sae */
    printf("%d ", a->info); /* mostra raiz */
    imprime_in(a->dir); /* mostra sad */
  }
}

void imprime_pos (Arv* a)
{
  if (!vazia(a)){
    imprime_pos(a->esq); /* mostra sae */
    imprime_pos(a->dir); /* mostra sad */
    printf("%d ", a->info); /* mostra raiz */
  }
}

int main()
{
  Arv* num67 = cria(67,inicializa(),inicializa());
	Arv* num40 = cria(40,inicializa(),inicializa());
  Arv* num34 = cria(34,inicializa(),num67);
  Arv* num12 = cria(12,inicializa(),inicializa());
  Arv* num80 = cria(80,inicializa(),num40);
  Arv* num5 = cria(5, num12, num34);
  Arv* num45 = cria(45, num5, num80);

  printf("Pre-ordem: ");
  imprime_pre(num45);
  printf("\n");

  printf("Em ordem: ");
  imprime_in(num45);
  printf("\n");

  printf("Pos-ordem: ");
  imprime_pos(num45);
  printf("\n\n");


  //enxerto  
  num45->dir->esq = cria(3,cria(66,inicializa(),inicializa()),cria(31,inicializa(),inicializa()));
  printf("Pre-ordem com enxerto: ");
  imprime_pre(num45);
  printf("\n");

  printf("Em ordem com enxerto: ");
  imprime_in(num45);
  printf("\n");

  printf("Pos-ordem com enxerto: ");
  imprime_pos(num45);
  printf("\n");

  //poda 34
  num45->esq->dir = libera(num45->esq->dir);
  printf("\nPre-ordem com enxerto e poda: ");
  imprime_pre(num45);
  printf("\n");

  printf("Em ordem com enxerto e poda: ");
  imprime_in(num45);
  printf("\n");

  printf("Pos-ordem com enxerto e poda: ");
  imprime_pos(num45);
  printf("\n");

  libera(num45);

  return 0;
}

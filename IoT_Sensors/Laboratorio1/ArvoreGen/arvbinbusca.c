#include <stdio.h>
#include <stdlib.h>

struct arv {
  int info;
  struct arv* esq;
  struct arv* dir;
};

typedef struct arv Arv;

Arv* busca (Arv* r, int v)
{
  if (r == NULL) return NULL;
  else if (r->info > v) return busca(r->esq,v);
  else if (r->info < v) return busca(r->dir,v);
  else return r;
}


Arv* insere (Arv* a, int v)
{
  if (a==NULL) {
    a = (Arv*)malloc(sizeof(Arv));
    a->info = v;
    a->esq = a->dir = NULL;
  }
  else if (v < a->info)
    a->esq = insere(a->esq,v);
  else /* v < a->info */
    a->dir = insere(a->dir,v);
  return a;
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


void imprime_in (Arv* r){
  if (!vazia(r)){
    imprime_in(r->esq); /* mostra sae */
    printf("%d ", r->info); /* mostra raiz */
    imprime_in(r->dir); /* mostra sad */
  }
}



int main(void){

  Arv* raiz = NULL;

  // valores 
  int valores[] = {1, 2, 3, 5, 15, 7};
  for (int i = 0; i < sizeof(valores)/sizeof(valores[0]); i++) {
      raiz = insere(raiz, valores[i]);
      printf("Arvore apos insercao de %d: \n", valores[i]);
      imprime_in(raiz);
      printf("\n");
  }

  // Busca de elementos
  int busca_valores[] = {2, 8};
  for (int i = 0; i < sizeof(busca_valores)/sizeof(busca_valores[0]); i++) {
      Arv* encontrado = busca(raiz, busca_valores[i]);
      if (encontrado)
        printf("Elemento %d encontrado na arvore.\n", busca_valores[i]);
      else
        printf("Elemento %d nao encontrado na arvore.\n", busca_valores[i]);
  }
  libera(raiz);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define LIN 3
#define COL 4

int main(){
/*    //exemplo1
    int v, *pv;
    v = 40;
    pv = &v;
    printf ("%d %p %p\n\n", v, pv, &pv);

    //exemplo2
    int *pi;
    pi=(int *) malloc(sizeof(int));
    *pi = 1001;
    printf("valor = %d\nendereco = %p\ntamanho: %lu\n\n", *pi, pi, sizeof(*pi));

    //exomplo3
    int *pvet,
    *aux;
    pvet=(int *)malloc(10*sizeof(int));
    aux = pvet;
    for (int i=10; i>0;i--) {
    *aux = i; aux++;
    }
    aux = pvet;
    for (int i=0; i<10;i++) {
    printf("%d ", *aux); aux++;
    }
    printf("\n\n"); free(pvet);

    int x[5] = {10,11,12,13,14};
    int i;
    for (i=0; i<5; i++)
        printf("i=%d x[i]=%d *(x+i)=%d &x[i]=%px+i=%p\n", i, x[i], *(x+i), &x[i], x+i);
    */

    //exemplo 4
    int **M, i, j;
    M = (int**) malloc (sizeof(int*) * LIN);
    for (i=0; i<COL; i++)
        M[i] = (int*) malloc (sizeof(int) * COL);
    for (i=0; i<LIN; i++)
        for (j=0; j<COL; j++){
            printf("M[%d][%d] = ", i, j);
            scanf("%d",&M[i][j]);
        }
    for (i=0; i<LIN; i++){
        for (j=0; j<COL; j++)
            printf("%d\t", M[i][j]);
        printf("\n");
    }
    for (i=0; i<LIN; i++){
        free (M[i]); 
        free (M);
    }
    return 0;
}


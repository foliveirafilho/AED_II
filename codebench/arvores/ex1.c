#include <stdio.h>
#include <stdlib.h>

typedef struct no No;

struct no{
    int valor;
    No *esquerdo;
    No *direito;

};

No* criaArvore();
No* criaNo(int valor);
No* insereNo(No *arvoreBinaria, No *no);
void liberaArvore(No *arvoreBinaria);
int qtdeNo(No *arvoreBinaria);

int main(){
    No *arvoreBinaria = criaArvore();
    int valor;

    while(scanf("%d", &valor) != EOF)
       arvoreBinaria = insereNo(arvoreBinaria, criaNo(valor));
    
    printf("Total de elementos: %d\n", qtdeNo(arvoreBinaria));

    liberaArvore(arvoreBinaria);

    return 0; 

}

No* criaArvore(){
    return NULL;

}

No* criaNo(int valor){
    No *no = malloc(sizeof *no);

    no->valor = valor;
    no->esquerdo = NULL;
    no->direito = NULL;

    return no;

}

No* insereNo(No *arvoreBinaria, No *no){
    if(arvoreBinaria == NULL)
        return no;

    if(arvoreBinaria->valor > no->valor)
        arvoreBinaria->esquerdo = insereNo(arvoreBinaria->esquerdo, no);

    else
        arvoreBinaria->direito = insereNo(arvoreBinaria->direito, no);

    return arvoreBinaria;

}

void liberaArvore(No *arvoreBinaria){
    if(arvoreBinaria != NULL){
        liberaArvore(arvoreBinaria->esquerdo);
        liberaArvore(arvoreBinaria->direito);
        free(arvoreBinaria);

    }

}

int qtdeNo(No *arvoreBinaria){
    if(arvoreBinaria == NULL)
        return 0;

    else 
        return (1 + qtdeNo(arvoreBinaria->esquerdo) + qtdeNo(arvoreBinaria->direito));

}
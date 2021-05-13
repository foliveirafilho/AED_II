#include <stdio.h>
#include <stdlib.h>
#define ORDEM 2

typedef struct no No;

struct no{
    int qtdeChaves;
    int chaves[(2 * ORDEM) - 1];
    No *nos[2 * ORDEM];

};

No* buscaChave(No *arvore, int chave);

int main(){


    return 0;

}

No* buscaChave(No *arvore, int chave){
    if(arvore != NULL){
        int i = 0;

        while((i < arvore->qtdeChaves) && (chave > arvore->chaves[i]))
            i++;

        if((i < arvore->qtdeChaves) && (chave == arvore->chaves[i]))
            return arvore; // encontrou a chave

        else if(arvore->nos[i] != NULL)
            return buscaChave(arvore->nos[i], chave); //percorre o filho em que a chave possivelmente se encontra

        else
            return arvore; // chegou na folha e nao encontrou a chave, entao retorna o no atual que e onde a chave deveria estar

    }

    return NULL; // a arvore e NULL, nao ha busca

}
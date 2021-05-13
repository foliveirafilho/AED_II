#include <stdio.h>
#include <stdlib.h>
#define ORDEM 2

typedef struct no No;

struct no{
    int qtdeChaves;
    int chaves[(2 * ORDEM) - 1];
    No *nos[2 * ORDEM];

};

No *criaNo();
No* criaArvore();
No* buscaChave(No *arvore, int chave);
No* divide(No **pai, int indiceFilho);
int ehFolha(No *no);

int main(){


    return 0;

}

No *criaNo(){
    No *no = malloc(sizeof *no);

    no->qtdeChaves = 0;

    for(int i = 0; i < (2 * ORDEM) - 1; i++)
        no->chaves[i] = 0;

    for(int i = 0; i < (2 * ORDEM); i++)
        no->nos[i] = NULL;

    return no;

}

No* criaArvore(){
    return criaNo();

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

No* divide(No **pai, int indiceFilho){
    No *no = criaNo();

    no->qtdeChaves = ORDEM - 1;
    (*pai)->nos[indiceFilho]->qtdeChaves = ORDEM - 1;

    for(int i = 0; i < ORDEM - 1; i++)
        no->chaves[i] = (*pai)->nos[indiceFilho]->chaves[i + ORDEM];

    if(!ehFolha((*pai)->nos[indiceFilho])){
        for(int i = 0; i < ORDEM; i++)
            no->nos[i] = (*pai)->nos[indiceFilho]->nos[i + ORDEM];

    }

    for(int i = (*pai)->qtdeChaves + 1; i > indiceFilho + 1; i--)
        (*pai)->nos[i + 1] = (*pai)->nos[i]; //shift nos filhos

    (*pai)->nos[indiceFilho + 1] = no;

    for(int i = (*pai)->qtdeChaves; i > indiceFilho; i--)
        (*pai)->chaves[i] = (*pai)->chaves[i - 1]; ///shift nas chaves

    (*pai)->chaves[indiceFilho] = (*pai)->nos[indiceFilho]->chaves[ORDEM - 1];
    (*pai)->qtdeChaves++;

    return *pai;

}

int ehFolha(No *no){
    int i = 0;

    while(i < no->qtdeChaves){
        if(no->nos[i] != NULL)
            return 0;

        i++;

    }

    return 1;

}
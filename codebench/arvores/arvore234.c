#include <stdio.h>
#include <stdlib.h>

typedef struct no No;

struct no{
    int chaves[3];
    No *nos[4];
    int qtdeChaves;

};

No* criaArvore();
No* buscaNo(No *raiz, int chave);
No* filhoAPercorrer(No *raiz, int chave);
int existeChave(int *chaves, int chave);

int main(){


    return 0;

}

No* criaArvore(){
    return NULL;

}

No* buscaNo(No *raiz, int chave){
    if((raiz == NULL) || (existeChave(raiz->chaves, chave)))
        return raiz;

    return buscaNo(filhoAPercorrer(raiz, chave), chave);

}

No* filhoAPercorrer(No *raiz, int chave){
    int indice = raiz->qtdeChaves;

    while(indice > 0){
        if(chave > raiz->nos[indice - 1])
            return raiz->nos[indice];
        
        indice--;

    }

    if(chave < raiz->nos[indice])
        return raiz->nos[indice];

}

int existeChave(int *chaves, int chave){
    if((chaves[0] == chave) || (chaves[1] == chave) || (chaves[2] == chave))
        return 1;

    return 0;

}
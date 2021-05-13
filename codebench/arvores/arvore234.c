#include <stdio.h>
#include <stdlib.h>

typedef struct no No;

struct no{
    int chaves[3];
    No *nos[4];
    No *pai;
    int qtdeChaves;

};

No* criaArvore();
No* criaNo(No *pai, int chave);
No* insere(No *raiz, int chave);
No* insereChave(No **raiz, int chave);
No* divide(No **pai, No **filho);
No* insereNo(No **pai, No **filho);
No* removeChave(No **raiz, int indice);
No* buscaChave(No *raiz, int chave);
No* filhoAPercorrer(No *raiz, int chave);
int existeChave(No *raiz, int chave);
int ehFolha(No *no);
void imprime(No *arvore);

int main(){
    No *arvore = criaArvore();
    int numero, chave;

    scanf("%d", &numero);

    for(int i = 0; i < numero; i++){
        scanf("%d", &chave);
        arvore = insere(arvore, chave);

    }

    imprime(arvore);

    return 0;

}

No* criaArvore(){
    return NULL;

}

No* criaNo(No *pai, int chave){
    No *no = malloc(sizeof *no);

    no->pai = pai;
    no->chaves[0] = chave;
    for(int i = 1; i < 3; i++)
        no->chaves[i] = 0;

    for(int i = 0; i < 4; i++)
        no->nos[i] = NULL;
    
    no->qtdeChaves = 1;

    return no;

}

No* insere(No *raiz, int chave){
    if(raiz == NULL){
        printf("entrou1\n");
        return criaNo(NULL, chave);
    }
        
    if(buscaChave(raiz, chave) == NULL){
        printf("entrou2\n");
        if(ehFolha(raiz)){
            printf("entrou2.1\n");
            raiz = insereChave(&raiz, chave);

        }else{
            printf("entrou2.2\n");
            raiz = insere(filhoAPercorrer(raiz, chave), chave);
        }

    }else
        printf("entrou3\n");

    return raiz;

}

No* insereChave(No **raiz, int chave){
    int i = (*raiz)->qtdeChaves;

    if(i == 3)
        divide(NULL, raiz);

    (*raiz)->qtdeChaves++;

    while((i > 0) && ((*raiz)->chaves[i - 1] > chave)){
        (*raiz)->chaves[i] = (*raiz)->chaves[i - 1];
        i--;

    }

    (*raiz)->chaves[i] = chave;

    return *raiz;

}

No* divide(No **pai, No **filho){
    No *no;

    if(pai == NULL){
        printf("entrou split1\n");
        *pai = criaNo(NULL, (*filho)->chaves[1]);
    }else{
        printf("entrou split2\n");
        *pai = insereChave(pai, (*filho)->chaves[1]);
    }
        
    

    no = criaNo(*pai, (*filho)->chaves[0]);
    *filho = removeChave(filho, 1);
    *filho = removeChave(filho, 0);
    *pai = insereNo(pai, &no);
    *pai = insereNo(pai, filho);

    return *pai;

}

No* insereNo(No **pai, No **filho){
    int i = (*pai)->qtdeChaves;

    while((i > 0) && ((*pai)->nos[i - 1] > (*filho)->nos[0]))
        i--;

    (*pai)->nos[i - 1] = *filho;

    return *pai;

}

No* removeChave(No **raiz, int indice){
    (*raiz)->qtdeChaves--;

    while(indice < 2){
        (*raiz)->chaves[indice] = (*raiz)->chaves[indice + 1];
        indice++;

    }

    return *raiz;

}

No* buscaChave(No *raiz, int chave){
    if((raiz == NULL) || (existeChave(raiz, chave)))
        return raiz;
        
    return buscaChave(filhoAPercorrer(raiz, chave), chave);

}

No* filhoAPercorrer(No *raiz, int chave){
    int indice = raiz->qtdeChaves;

    while(indice > 0){
        if(chave > raiz->chaves[indice - 1])
            return raiz->nos[indice];
        
        indice--;

    }

    if(chave < raiz->chaves[indice])
        return raiz->nos[indice];

}

int existeChave(No *raiz, int chave){
    int i = 0;

    while(i < raiz->qtdeChaves){
        if(raiz->chaves[i] == chave)
            return 1;

        i++;

    }

    return 0;

}

int ehFolha(No *no){
    if((no->nos[0] == NULL) && (no->nos[1] == NULL) && (no->nos[2] == NULL) && (no->nos[3] == NULL))
        return 1;

    return 0;

}

void imprime(No *arvore){
    if(arvore != NULL){
        for(int i = 0; i < arvore->qtdeChaves; i++)
            printf("chave %d = %d ", i, arvore->chaves[i]);
            
        printf("\n");
            
        imprime(arvore->nos[0]);
        imprime(arvore->nos[1]);
        imprime(arvore->nos[2]);
        imprime(arvore->nos[3]);

    }

}
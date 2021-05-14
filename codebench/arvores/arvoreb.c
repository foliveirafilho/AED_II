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
No* insere(No **raiz, int chave);
No* percorreInsere(No **arvore, int chave);
No* divide(No **pai, int indiceFilho);
No* exclui(No **arvore, int chave);
void imprime(No *arvore);
int chaveExiste(No *no, int chave);
int ehFolha(No *no);
int noCheio(No *no);

int main(){
    No *arvore = criaArvore();
    int chave;
    int qtdeElementos;

    scanf("%d", &qtdeElementos);

    for(int i = 0; i < qtdeElementos; i++){
        scanf("%d", &chave);
        insere(&arvore, chave);
        imprime(arvore);

    }

    // imprime(arvore);

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

No* insere(No **raiz, int chave){
    No *noParaInserir = buscaChave(*raiz, chave);

    if(!chaveExiste(noParaInserir, chave)){
        if(noCheio(*raiz)){
            printf("no cheio!\n");
            No *novaRaiz = criaNo();

            novaRaiz->qtdeChaves = 0;
            novaRaiz->nos[0] = *raiz;

            *raiz = divide(&novaRaiz, 0);
            printf("divisao feita com sucesso\n");
            percorreInsere(&novaRaiz, chave);

        }else
            percorreInsere(raiz, chave);

    }else
        printf("Chave ja existe, nao eh possivel inserir!\n");

    return *raiz;

}

No* percorreInsere(No **arvore, int chave){
    int i = (*arvore)->qtdeChaves;

    if(ehFolha(*arvore)){ // encontrou a folha a inserir
        while((i >= 0) && (chave < (*arvore)->chaves[i])){ // encontra a posicao onde se deve inserir a chave
            (*arvore)->chaves[i + 1] = (*arvore)->chaves[i];
            i--;

        }

        if(i <= 0)
            (*arvore)->chaves[0] = chave;

        else
            (*arvore)->chaves[i] = chave;

        (*arvore)->qtdeChaves++;

    }else{
        while((i >= 0) && (chave < (*arvore)->chaves[i])) // encontra qual o filho deve ser percorrido
            i = i - 1;

        if(i < 0)
            i++;

        if(noCheio((*arvore)->nos[i])){ // verifica se o filho encontrado esta cheio
            divide(arvore, i);
            if(chave > (*arvore)->chaves[i])
                i++;

        }

        percorreInsere(&((*arvore)->nos[i]), chave);

    }

    return *arvore;

}

No* divide(No **pai, int indiceFilho){
    No *no = criaNo();

    no->qtdeChaves = ORDEM - 1;

    for(int i = 0; i < ORDEM - 1; i++)
        no->chaves[i] = (*pai)->nos[indiceFilho]->chaves[i + ORDEM];

    if(!ehFolha((*pai)->nos[indiceFilho])){
        for(int i = 0; i < ORDEM; i++)
            no->nos[i] = (*pai)->nos[indiceFilho]->nos[i + ORDEM];

    }

    (*pai)->nos[indiceFilho]->qtdeChaves = ORDEM - 1;

    for(int i = (*pai)->qtdeChaves + 1; i > indiceFilho + 1; i--)
        (*pai)->nos[i + 1] = (*pai)->nos[i]; //shift nos filhos

    (*pai)->nos[indiceFilho + 1] = no;

    for(int i = (*pai)->qtdeChaves; i > indiceFilho; i--)
        (*pai)->chaves[i] = (*pai)->chaves[i - 1]; ///shift nas chaves

    (*pai)->chaves[indiceFilho] = (*pai)->nos[indiceFilho]->chaves[ORDEM - 1];
    (*pai)->qtdeChaves++;

    return *pai;

}

void imprime(No *arvore){
    if(arvore != NULL){
        for(int i = 0; i < arvore->qtdeChaves; i++)
            printf("| %d ", arvore->chaves[i]);

        printf("|\n");

        for(int i = 0; i < arvore->qtdeChaves + 1; i++)
            imprime(arvore->nos[i]);

    }

}

No* exclui(No **arvore, int chave){
    

}

int chaveExiste(No *no, int chave){
    int i = 0;
    
    while(i < no->qtdeChaves){
        if(no->chaves[i] == chave)
            return 1;

        i++;

    }

    return 0;

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

int noCheio(No *no){
    if(no->qtdeChaves == (2 * ORDEM) - 1)
        return 1;

    return 0;

}
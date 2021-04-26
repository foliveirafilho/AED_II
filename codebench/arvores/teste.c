#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no No;

struct no{
    int valor;
    int altura;
    No *esquerdo;
    No *direito;

};

No* criaArvore();
No* criaNo(int valor);
No* insereNo(No *arvoreBinaria, No *no);
No* buscaValor(No *arvoreBinaria, int valor);
void imprime(No *arvoreBinaria);
void liberaArvore(No *arvoreBinaria);
int qtdeNo(No *arvoreBinaria);
int qtdeFolha(No *arvoreBinaria);
int qtdeNaoFolha(No *arvoreBinaria);
int altura (No *arvoreBinaria);
int fatorDeBalanceamento(No *arvoreBinaria);
No* removeNo(No** arvoreBinaria, int valor);
No* removePares(No **arvoreBinaria);
No* rotacaoDireita(No **arvoreBinaria);
No* rotacaoEsquerda(No **arvoreBinaria);
No* rotacaoDireitaEsquerda(No **arvoreBinaria);
No* rotacaoEsquerdaDireita(No **arvoreBinaria);

int main(){
    No *arvoreBinaria = criaArvore(), *noProcurado;
    int valor, ehRaiz = 1;

    while(scanf("%d", &valor) != EOF){
        if(!ehRaiz){
            noProcurado = buscaValor(arvoreBinaria, valor);
            
            if(noProcurado == NULL || (noProcurado != NULL && noProcurado->valor != valor)){
                arvoreBinaria = insereNo(arvoreBinaria, criaNo(valor));
            
            }
            
        }else{
            ehRaiz = 0;
            arvoreBinaria = insereNo(arvoreBinaria, criaNo(valor));
            
        }

    }

    imprime(arvoreBinaria);
    removeNo(&arvoreBinaria, 5);
    
    imprime(arvoreBinaria);

    liberaArvore(arvoreBinaria);

    return 0; 

}

No* criaArvore(){
    return NULL;

}

No* criaNo(int valor){
    No *no = malloc(sizeof *no);

    no->valor = valor;
    no->altura = 0;
    no->esquerdo = NULL;
    no->direito = NULL;

    return no;

}

No* insereNo(No *arvoreBinaria, No *no){
    if(arvoreBinaria == NULL)
        return no;

    if(no->valor < arvoreBinaria->valor){
        arvoreBinaria->esquerdo = insereNo(arvoreBinaria->esquerdo, no);
        
        if(fatorDeBalanceamento(arvoreBinaria) >= 2){
            if(no->valor < arvoreBinaria->esquerdo->valor)
                arvoreBinaria = rotacaoDireita(&arvoreBinaria);

            else
                arvoreBinaria = rotacaoEsquerdaDireita(&arvoreBinaria);

        }

    }else{
        arvoreBinaria->direito = insereNo(arvoreBinaria->direito, no);

        if(fatorDeBalanceamento(arvoreBinaria) >= 2){
            if(no->valor < arvoreBinaria->direito->valor)
                arvoreBinaria = rotacaoDireitaEsquerda(&arvoreBinaria);

            else
                arvoreBinaria = rotacaoEsquerda(&arvoreBinaria);

        }
        
    }

    arvoreBinaria->altura = altura(arvoreBinaria);

    return arvoreBinaria;

}

No* buscaValor(No *arvoreBinaria, int valor){
    if((arvoreBinaria == NULL) || (arvoreBinaria->valor == valor))
        return arvoreBinaria;

    if(arvoreBinaria->valor > valor)
        return buscaValor(arvoreBinaria->esquerdo, valor);

    else
        return buscaValor(arvoreBinaria->direito, valor);

}

void imprime(No *arvoreBinaria){
    if(arvoreBinaria != NULL){
        printf("%d altura = %d\n", arvoreBinaria->valor, arvoreBinaria->altura);
        imprime(arvoreBinaria->esquerdo);
        imprime(arvoreBinaria->direito);

    }

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

int qtdeFolha(No *arvoreBinaria){
    if(arvoreBinaria == NULL)
        return 0;

    else if((arvoreBinaria->esquerdo == NULL) && (arvoreBinaria->direito == NULL))
        return 1;
        
    return qtdeFolha(arvoreBinaria->esquerdo) + qtdeFolha(arvoreBinaria->direito);

}

int qtdeNaoFolha(No *arvoreBinaria){
    if(arvoreBinaria == NULL)
        return 0;

    else if((arvoreBinaria->esquerdo != NULL) || (arvoreBinaria->direito != NULL))
        return 1 + qtdeNaoFolha(arvoreBinaria->esquerdo) + qtdeNaoFolha(arvoreBinaria->direito);

}

int altura (No *arvoreBinaria){
    if(arvoreBinaria == NULL)
        return -1;

    int alturaEsquerda = altura(arvoreBinaria->esquerdo);
    int alturaDireita = altura(arvoreBinaria->direito);

    if(alturaDireita > alturaEsquerda)
        return alturaDireita + 1;

    else
        return alturaEsquerda + 1;

}

int fatorDeBalanceamento(No *arvoreBinaria){
    return abs(altura(arvoreBinaria->esquerdo) - altura(arvoreBinaria->direito));
    
}

// fonte: https://www.ic.unicamp.br/~rocha/teaching/2016s1/mc202/aulas/arvore-binaria-busca-01.pdf
No* removeNo(No** arvoreBinaria, int valor){
    if (*arvoreBinaria == NULL)
        return NULL;

    else if ((*arvoreBinaria)->valor > valor){
        (*arvoreBinaria)->esquerdo = removeNo(&((*arvoreBinaria)->esquerdo), valor);

        if(fatorDeBalanceamento(*arvoreBinaria) >= 2){
            if(altura((*arvoreBinaria)->direito->esquerdo) > altura((*arvoreBinaria)->direito->direito))
                *arvoreBinaria = rotacaoDireitaEsquerda(arvoreBinaria);

            else
                *arvoreBinaria = rotacaoEsquerda(arvoreBinaria);

        }

    }else if ((*arvoreBinaria)->valor < valor){
        (*arvoreBinaria)->direito = removeNo(&((*arvoreBinaria)->direito), valor);

        if(fatorDeBalanceamento(*arvoreBinaria) >= 2){
            if(altura((*arvoreBinaria)->esquerdo->direito) < altura((*arvoreBinaria)->esquerdo->esquerdo))
                *arvoreBinaria = rotacaoDireita(arvoreBinaria);

            else
                *arvoreBinaria = rotacaoEsquerdaDireita(arvoreBinaria);

        }

    }else { /* achou o nó a remover */
        /* nó sem filhos */
        if ((*arvoreBinaria)->esquerdo == NULL && (*arvoreBinaria)->direito == NULL) {
            free(*arvoreBinaria);
            
            *arvoreBinaria = NULL;

        }
        /* nó só tem filho à direita */
        else if ((*arvoreBinaria)->esquerdo == NULL) {
            No* t = *arvoreBinaria;
            arvoreBinaria = &((*arvoreBinaria)->direito);
            
            free(t);

        }
        /* só tem filho à esquerda */
        else if ((*arvoreBinaria)->direito == NULL) {
            No* t = *arvoreBinaria;
            arvoreBinaria = &((*arvoreBinaria)->esquerdo);
            
            free(t);

        }
        /* nó tem os dois filhos */
        else {
            No* maiordosMenores = (*arvoreBinaria)->esquerdo;
            
            while (maiordosMenores->direito != NULL) {
                maiordosMenores = maiordosMenores->direito;
            }
            
            (*arvoreBinaria)->valor = maiordosMenores->valor; /* troca as informações */
            maiordosMenores->valor = valor;
            (*arvoreBinaria)->esquerdo = removeNo(&((*arvoreBinaria)->esquerdo), valor);

            if(fatorDeBalanceamento(*arvoreBinaria) >= 2){
                if(altura((*arvoreBinaria)->direito->esquerdo) > altura((*arvoreBinaria)->direito->direito))
                    *arvoreBinaria = rotacaoDireitaEsquerda(arvoreBinaria);

                else
                    *arvoreBinaria = rotacaoEsquerda(arvoreBinaria);

            }

        }

    }

    return *arvoreBinaria;

}

No* removePares(No **arvoreBinaria){
    if(*arvoreBinaria != NULL){
        removePares(&((*arvoreBinaria)->esquerdo));
        removePares(&((*arvoreBinaria)->direito));
        
        if(((*arvoreBinaria)->valor % 2) == 0)
            *arvoreBinaria = removeNo(arvoreBinaria, (*arvoreBinaria)->valor);

    }
    
    return *arvoreBinaria;

}

No* rotacaoDireita(No **arvoreBinaria){
    No *auxRaiz = *arvoreBinaria, *auxEsquerdo = auxRaiz->esquerdo;

    auxRaiz->esquerdo = auxEsquerdo->direito;
    auxEsquerdo->direito = auxRaiz;
    *arvoreBinaria = auxEsquerdo;
    
    auxRaiz->altura = altura(auxRaiz);
    auxEsquerdo->altura = altura(auxEsquerdo);

    return *arvoreBinaria;

}

No* rotacaoEsquerda(No **arvoreBinaria){
    No *auxRaiz = *arvoreBinaria, *auxDireito = auxRaiz->direito;

    auxRaiz->direito = auxDireito->esquerdo;
    auxDireito->esquerdo = auxRaiz;
    *arvoreBinaria = auxDireito;
    
    auxRaiz->altura = altura(auxRaiz);
    auxDireito->altura = altura(auxDireito);

    return *arvoreBinaria;

}

No* rotacaoDireitaEsquerda(No **arvoreBinaria){
    rotacaoDireita(&((*arvoreBinaria)->direito));
    rotacaoEsquerda(arvoreBinaria);

    return *arvoreBinaria;
    
}

No* rotacaoEsquerdaDireita(No **arvoreBinaria){
    rotacaoEsquerda(&((*arvoreBinaria)->esquerdo));
    rotacaoDireita(arvoreBinaria);

    return *arvoreBinaria;
    
}
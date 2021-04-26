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
No* buscaValor(No *arvoreBinaria, int valor);
void liberaArvore(No *arvoreBinaria);
int qtdeNaoFolha(No *arvoreBinaria);
void imprime(No *arvoreBinaria);

int main(){
	No *arvoreBinaria = criaArvore(), *noProcurado;
	int valor, ehRaiz = 1, qtdeElementos;
	
	scanf("%d", &qtdeElementos);
	
	
    
	for(int i = 0; i < qtdeElementos; i++){
	    scanf("%d", &valor);
	    
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

	//imprime(arvoreBinaria);

	//printf("Folhas = %d\n", qtdeFolha(arvoreBinaria));
	printf("Nao folhas = %d\n", qtdeNaoFolha(arvoreBinaria));

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

No* buscaValor(No *arvoreBinaria, int valor){
	if((arvoreBinaria == NULL) || (arvoreBinaria->valor == valor))
		return arvoreBinaria;

	if(arvoreBinaria->valor > valor)
		return buscaValor(arvoreBinaria->esquerdo, valor);

	else
		return buscaValor(arvoreBinaria->direito, valor);

}

void liberaArvore(No *arvoreBinaria){
	if(arvoreBinaria != NULL){
		liberaArvore(arvoreBinaria->esquerdo);
		liberaArvore(arvoreBinaria->direito);
		free(arvoreBinaria);

	}

}

int qtdeNaoFolha(No *arvoreBinaria){
    if(arvoreBinaria == NULL)
        return 0;

    else if((arvoreBinaria->esquerdo != NULL) || (arvoreBinaria->direito != NULL))
        return 1 + qtdeNaoFolha(arvoreBinaria->esquerdo) + qtdeNaoFolha(arvoreBinaria->direito);

	return 0;
	
}

void imprime(No *arvoreBinaria){
    if(arvoreBinaria != NULL){
        imprime(arvoreBinaria->esquerdo);
        printf("%d ", arvoreBinaria->valor);
        imprime(arvoreBinaria->direito);

    }

}
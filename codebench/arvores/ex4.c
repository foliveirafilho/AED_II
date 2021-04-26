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
void imprime(No *arvoreBinaria);
void liberaArvore(No *arvoreBinaria);
No* removeNo(No** arvoreBinaria, int valor);
No* removePares(No **arvoreBinaria);

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
	
	arvoreBinaria = removePares(&arvoreBinaria);

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

void imprime(No *arvoreBinaria){
    if(arvoreBinaria != NULL){
        imprime(arvoreBinaria->esquerdo);
        printf("%d\n", arvoreBinaria->valor);
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

// fonte: https://www.ic.unicamp.br/~rocha/teaching/2016s1/mc202/aulas/arvore-binaria-busca-01.pdf
No* removeNo(No** arvoreBinaria, int valor){
	if (*arvoreBinaria == NULL)
		return NULL;

	else if ((*arvoreBinaria)->valor > valor)
		(*arvoreBinaria)->esquerdo = removeNo(&((*arvoreBinaria)->esquerdo), valor);

	else if ((*arvoreBinaria)->valor < valor)
		(*arvoreBinaria)->direito = removeNo(&((*arvoreBinaria)->direito), valor);

	else {
		if ((*arvoreBinaria)->esquerdo == NULL && (*arvoreBinaria)->direito == NULL) {
			free(*arvoreBinaria);


			*arvoreBinaria = NULL;

		}
		else if ((*arvoreBinaria)->esquerdo == NULL) {
			No* t = *arvoreBinaria;
			arvoreBinaria = &((*arvoreBinaria)->direito);

			free(t);

		}
		else if ((*arvoreBinaria)->direito == NULL) {
			No* t = *arvoreBinaria;
			arvoreBinaria = &((*arvoreBinaria)->esquerdo);

			free(t);

		}
		else {
			No* maiordosMenores = (*arvoreBinaria)->esquerdo;

			while (maiordosMenores->direito != NULL) {
				maiordosMenores = maiordosMenores->direito;
			}

			(*arvoreBinaria)->valor = maiordosMenores->valor;
			maiordosMenores->valor = valor;
			(*arvoreBinaria)->esquerdo = removeNo(&((*arvoreBinaria)->esquerdo), valor);

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
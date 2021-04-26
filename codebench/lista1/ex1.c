#include <stdio.h>
#include <stdlib.h>

typedef struct elemento Elemento;
typedef struct lista Lista;

struct elemento{
    int valor;
    Elemento *prox;

};

struct lista{
    Elemento *primeiro;
    Elemento *ultimo;

};

Lista *criaLista();
void insere(Lista *lista, int valor);
void imprime(Lista *lista);
void uniao(Lista *listaUniao, Elemento *elementoLista1, Elemento *elementoLista2);
void intersecao(Lista *listaIntersecao, Elemento *elementoLista1, Elemento *elementoLista2);
int valorPresente(Elemento *elemento, int valor);

int main(){
    Lista *lista1, *lista2, *listaUniao, *listaIntersecao;
    int valor;

    lista1 = criaLista();
    lista2 = criaLista();
    listaUniao = criaLista();
    listaIntersecao = criaLista();

    scanf("%d", &valor);
    while(valor != 0){
        insere(lista1, valor);

        scanf("%d", &valor);
        
    }

    scanf("%d", &valor);
    while(valor != 0){
        insere(lista2, valor);

        scanf("%d", &valor);
        
    }

    uniao(listaUniao, lista1->primeiro, lista2->primeiro);
    intersecao(listaIntersecao, lista1->primeiro, lista2->primeiro);

    printf("Lista 1: ");
    imprime(lista1);

    printf("Lista 2: ");
    imprime(lista2);

    printf("Uniao: ");
    imprime(listaUniao);

    printf("Intersecao: ");
    imprime(listaIntersecao);

    return 0; 

}

Lista *criaLista(){
    Lista *lista = malloc(sizeof *lista);

    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;

}

void insere(Lista *lista, int valor){
    Elemento *elemento = malloc(sizeof *elemento);
	elemento->valor = valor;

	elemento->prox = NULL;

	if(lista->primeiro != NULL)
		lista->ultimo->prox = elemento;

	else
		lista->primeiro = elemento;

	lista->ultimo = elemento;

}

void imprime(Lista *lista){
    for(Elemento *elemento = lista->primeiro; elemento != NULL; elemento = elemento->prox)
        printf("%d ", elemento->valor);

    printf("\n");

}

void uniao(Lista *listaUniao, Elemento *elementoLista1, Elemento *elementoLista2){
    if((elementoLista1 != NULL) || (elementoLista2 != NULL)){
        if((elementoLista1 != NULL) && (!valorPresente(listaUniao->primeiro, elementoLista1->valor))){
            insere(listaUniao, elementoLista1->valor);
            uniao(listaUniao, elementoLista1->prox, elementoLista2);

        }else if(elementoLista2 != NULL){
            if(!valorPresente(listaUniao->primeiro, elementoLista2->valor))
                insere(listaUniao, elementoLista2->valor);

            uniao(listaUniao, elementoLista1, elementoLista2->prox);

        }

    }

}

void intersecao(Lista *listaIntersecao, Elemento *elementoLista1, Elemento *elementoLista2){
    if((elementoLista1 != NULL) && (elementoLista2 != NULL)){
        if(valorPresente(elementoLista1, elementoLista2->valor))
            insere(listaIntersecao, elementoLista2->valor);

        intersecao(listaIntersecao, elementoLista1->prox, elementoLista2->prox);

    }

}

int valorPresente(Elemento *elemento, int valor){
    int encontrou = 0;

    while(!encontrou && elemento != NULL){
        if(elemento->valor == valor)
            encontrou = 1;

        elemento = elemento->prox;

    }

    return encontrou;

}
#include <stdio.h>
#include <stdlib.h>

typedef struct elemento Elemento;
typedef struct lista Lista;

struct elemento{
	int valor;
	Elemento *prox;
	Elemento *ant;

};

struct lista{
	Elemento *primeiro;
	Elemento *ultimo;

};

Lista* criaLista();
void insere(Lista *lista, int valor);
void imprime(Lista *lista);
void troca(Lista *lista, Elemento *elemento1, Elemento *elemento2);
void inverteValores(Lista *lista, Elemento *comeco, Elemento *fim);

int main(){
	Lista *lista = criaLista();
	int valor, tamanho, tamanhoAtual = 0;
	int *valores = (int*) malloc(tamanho * sizeof(int));

	while(scanf("%d", &valor) != EOF)
		insere(lista, valor);


	inverteValores(lista, lista->primeiro, lista->ultimo);

	imprime(lista);

	return 0;

}

Lista* criaLista(){
	Lista *lista = malloc(sizeof *lista);

	lista->primeiro = NULL;
	lista->ultimo = NULL;

	return lista;

} 

void insere(Lista *lista, int valor){
	Elemento *elemento = malloc(sizeof *elemento);

	elemento->valor = valor;
	elemento->prox = NULL;
	elemento->ant = lista->ultimo;

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

void troca(Lista *lista, Elemento *elemento1, Elemento *elemento2){
	Elemento *auxAnt = elemento1->ant;
	Elemento *auxProx = elemento1->prox;

	if(lista->primeiro == elemento1){
		lista->primeiro = elemento2;
		lista->ultimo = elemento1;
		elemento1->prox->ant = elemento2;
		elemento2->ant->prox = elemento1;

		elemento1->ant = elemento2->ant;
		elemento1->prox = elemento2->prox;
		elemento2->ant = auxAnt;
		elemento2->prox = auxProx;

	}else if(elemento1->prox == elemento2){
		elemento1->ant->prox = elemento2;
		elemento2->prox->ant = elemento1;

		elemento1->ant = elemento2;
		elemento1->prox = elemento2->prox;
		elemento2->ant = elemento1->ant;
		elemento2->prox = elemento1;

	}else{
		elemento1->ant->prox = elemento2;
		elemento1->prox->ant = elemento2;
		elemento2->ant->prox = elemento1;
		elemento2->prox->ant = elemento1;

		elemento1->ant = elemento2->ant;
		elemento1->prox = elemento2->prox;
		elemento2->ant = auxAnt;
		elemento2->prox = auxProx;

	}

}

void inverteValores(Lista *lista, Elemento *comeco, Elemento *fim){
	if((comeco != fim) && (fim->prox != comeco)){
		inverteValores(lista, comeco->prox, fim->ant);

		troca(lista, comeco, fim);

	}

}
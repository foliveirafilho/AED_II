#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define QUALIFY1 10
#define QUALIFY2 8
#define QUALIFY3 5
#define QTDE_PILOTOS 24

typedef struct corrida Corrida;
typedef struct piloto Piloto;


struct piloto{
    char equipe;
    int numero;
    double tempo;
    Piloto *prox;
    Piloto *ant;

};

struct corrida{
    Piloto *primeiro;
    Piloto *ultimo;

};

Corrida* criaCorrida();
void inserePiloto(Corrida *corrida, char equipe, int numero, double tempo);
void troca(Corrida *corrida, Piloto *piloto1, Piloto *piloto2);
double tempoAleatorio();
int qtdeCarrosAleatorio(int limite);
int carroAleatorio(Corrida *volta, Corrida *qualify1, Corrida *qualify2);
int verificaCarro(Corrida *volta, Corrida *qualify1, Corrida *qualify2, int carro);
void guardaMenorTempo(Corrida *corrida, Corrida *volta);
void selectionSort(Corrida *corrida);
Corrida* eliminadosDaEtapa(Corrida *corrida, int etapa);
Piloto* retiraUltimoPiloto(Corrida *corrida);
void imprime(Corrida *corrida);
void liberaCorrida(Corrida *corrida);
void gridLargada(Corrida *volta, Corrida *qualify1, Corrida *qualify2, Corrida *qualify3);

int main(){
	Corrida *corrida;
	Corrida *qualify1, *qualify2, *qualify3;
	int qtdeCarros;

	corrida = criaCorrida();

    srand(time(NULL));

	for(int i = 0; i < QTDE_PILOTOS; i++)
		inserePiloto(corrida, 'A' + i, i + 1, 5);


	//INICIO QUALIFY 1
	qtdeCarros = qtdeCarrosAleatorio(QTDE_PILOTOS);
	for(int i = 0; i < QUALIFY1; i++){
		Corrida *volta = criaCorrida();
		for(int j = 0; j < qtdeCarros; j++){
			int carro = carroAleatorio(volta, NULL, NULL);

			inserePiloto(volta, 'A', carro, tempoAleatorio());

		}
		
		guardaMenorTempo(corrida, volta);
		liberaCorrida(volta);

	}
	
	selectionSort(corrida);
	printf("Q1\n");
	imprime(corrida);
	
	qualify1 = eliminadosDaEtapa(corrida, 1);
	//FIM QUALIFY 1

	//INICIO QUALIFY 2
	qtdeCarros = qtdeCarrosAleatorio(QTDE_PILOTOS - 7);
	for(int i = 0; i < QUALIFY2; i++){
		Corrida *volta = criaCorrida();
		for(int j = 0; j < qtdeCarros; j++){
			int carro = carroAleatorio(volta, qualify1, NULL);

			inserePiloto(volta, 'A', carro, tempoAleatorio());

		}
		
		guardaMenorTempo(corrida, volta);
		liberaCorrida(volta);

	}
	
	selectionSort(corrida);
	printf("Q2\n");
	imprime(corrida);

	qualify2 = eliminadosDaEtapa(corrida, 2);
	//FIM QUALIFY 2

	//INICIO QUALIFY 3
	qtdeCarros = qtdeCarrosAleatorio(QTDE_PILOTOS - 14);
	for(int i = 0; i < QUALIFY3; i++){
		Corrida *volta = criaCorrida();
		for(int j = 0; j < qtdeCarros; j++){
			int carro = carroAleatorio(volta, qualify1, qualify2);

			inserePiloto(volta, 'A', carro, tempoAleatorio());

		}
		
		guardaMenorTempo(corrida, volta);
		liberaCorrida(volta);

	}
	
	selectionSort(corrida);
	printf("Q3\n");
	imprime(corrida);

	qualify3 = eliminadosDaEtapa(corrida, 3);
	//FIM QUALIFY 3

	gridLargada(corrida, qualify1, qualify2, qualify3);

	printf("GRID LARGADA\n");
	imprime(corrida);

	liberaCorrida(corrida);
	
    return 0;

}

Corrida* criaCorrida(){
	Corrida *corrida = malloc(sizeof *corrida);

	corrida->primeiro = NULL;
	corrida->ultimo = NULL;

	return corrida;

}

void inserePiloto(Corrida *corrida, char equipe, int numero, double tempo){
	Piloto *piloto = malloc(sizeof *piloto);

	piloto->equipe = equipe;
	piloto->numero = numero;
	piloto->tempo = tempo;
	piloto->prox = NULL;
	piloto->ant = corrida->ultimo;

	if(corrida->primeiro != NULL)
		corrida->ultimo->prox = piloto;

	else
		corrida->primeiro = piloto;

	corrida->ultimo = piloto;

}

double tempoAleatorio(){
    int tempo = rand() % 5005;

    return tempo / 1000.0;

}

int qtdeCarrosAleatorio(int limite){
	int qtdeCarros = 1 + (rand() % limite);

    return qtdeCarros;

}

int carroAleatorio(Corrida *volta, Corrida *qualify1, Corrida *qualify2){
	int carro = 1 + (rand() % 24);

	while(verificaCarro(volta, qualify1, qualify2, carro))
		carro = 1 + (rand() % 24);

	return carro;

}

int verificaCarro(Corrida *volta, Corrida *qualify1, Corrida *qualify2, int carro){
	int encontrou = 0;
	Piloto *piloto;

	if(volta != NULL){
		piloto = volta->primeiro;
		while(!encontrou && (piloto != NULL)){
			if(piloto->numero == carro)
				encontrou = 1;
			
			piloto = piloto->prox;

		}

	}

	if(!encontrou && qualify1 != NULL){
		piloto = qualify1->primeiro;
		while(!encontrou && (piloto != NULL)){
			if(piloto->numero == carro)
				encontrou = 1;
			
			piloto = piloto->prox;

		}

	}

	if(!encontrou && qualify2 != NULL){
		piloto = qualify2->primeiro;
		while(!encontrou && (piloto != NULL)){
			if(piloto->numero == carro)
				encontrou = 1;
			
			piloto = piloto->prox;

		}

	}

	return encontrou;

}

void guardaMenorTempo(Corrida *corrida, Corrida *volta){
	for(Piloto *i = volta->primeiro; i != NULL; i = i->prox){
		for(Piloto *j = corrida->primeiro; j != NULL; j = j->prox){
			if((i->numero == j->numero) && (i->tempo < j->tempo))
				j->tempo = i->tempo;

		}

	}

}

void selectionSort(Corrida *corrida){
	Piloto *i, *j, *menor;

	i = corrida->primeiro;

	while(i != corrida->ultimo){
		menor = i;
		j = i->prox;

		while(j != NULL){
			if(j->tempo < menor->tempo) 
                menor = j;
			
			j = j->prox;

		}

        if (i != menor)
			troca(corrida, i, menor);

		i = menor->prox;

	}

}

Corrida* eliminadosDaEtapa(Corrida *corrida, int etapa){
	Corrida *eliminados = criaCorrida();
	int qtdeEliminados;

	if((etapa == 1) || (etapa == 2))
		qtdeEliminados = 7;

	else
		qtdeEliminados = 9;

	for(int i = 0; i < qtdeEliminados; i++){
		Piloto *piloto = retiraUltimoPiloto(corrida);

		inserePiloto(eliminados, piloto->equipe, piloto->numero, piloto->tempo);

		free(piloto);

	}

	return eliminados;

}

Piloto* retiraUltimoPiloto(Corrida *corrida){
	Piloto *piloto = corrida->ultimo;

	if(piloto != NULL)
		corrida->ultimo = piloto->ant;

	if(corrida->ultimo != NULL)
		corrida->ultimo->prox = NULL;

	else
		corrida->primeiro = NULL;

	return piloto;

}

void troca(Corrida *corrida, Piloto *piloto1, Piloto *piloto2){
	Piloto *auxAnt = piloto1->ant;
	Piloto *auxProx = piloto1->prox;

	if(corrida->primeiro == piloto1){
		printf("entrou1\n");
		corrida->primeiro = piloto2;

		if(corrida->ultimo == piloto2)
			corrida->ultimo = piloto1;
		
		else
			piloto2->prox->ant = piloto1;

		piloto1->prox->ant = piloto2;
		piloto2->ant->prox = piloto1;

		piloto1->ant = piloto2->ant;
		piloto1->prox = piloto2->prox;
		piloto2->ant = auxAnt;
		piloto2->prox = auxProx;
		

	}else if(corrida->ultimo == piloto2){
		corrida->ultimo = piloto1;

		if(piloto1->prox == piloto2){
			printf("entrou2.1\n");
			piloto1->ant->prox = piloto2;

			piloto1->prox = piloto2->prox;
			piloto2->ant = piloto1->ant;
			piloto1->ant = piloto2;
			piloto2->prox = piloto1;

		}else{
			printf("entrou2.2\n");
			piloto1->ant->prox = piloto2;
			piloto1->prox->ant = piloto2;
			piloto2->ant->prox = piloto1;

			piloto1->ant = piloto2->ant;
			piloto1->prox = piloto2->prox;
			piloto2->ant = auxAnt;
			piloto2->prox = auxProx;

		}

	}else if(piloto1->prox == piloto2){
		printf("entrou3\n");
		piloto1->ant->prox = piloto2;
		piloto2->prox->ant = piloto1;
		
		piloto1->prox = piloto2->prox;
		piloto2->ant = piloto1->ant;
		piloto1->ant = piloto2;
		piloto2->prox = piloto1;

	}else{
		printf("entrou4\n");
		piloto1->ant->prox = piloto2;
		piloto1->prox->ant = piloto2;
		piloto2->ant->prox = piloto1;
		piloto2->prox->ant = piloto1;

		piloto1->ant = piloto2->ant;
		piloto1->prox = piloto2->prox;
		piloto2->ant = auxAnt;
		piloto2->prox = auxProx;

	}

}

void imprime(Corrida *corrida){
	int i = 1;
	double tempo;

	printf("-----------------------------\n");
	printf("| pos. | plto | eqp | tempo |\n");
	for(Piloto *piloto = corrida->primeiro; piloto != NULL; i++, piloto = piloto->prox){
		tempo = piloto->tempo * 10000;

		if(i < 10)
			printf("|  0%d  ", i);

		else
			printf("|  %d  ", i);

		if(piloto->numero < 10)
			printf("|  0%d  ", piloto->numero);

		else
			printf("|  %d  ", piloto->numero);

		printf("|  %c  ", piloto->equipe);

		if(tempo < 10)
			printf("| %.lf     |\n",  tempo);

		else if(tempo < 100)
			printf("| %.lf    |\n",  tempo);

		else if(tempo < 1000)
			printf("| %.lf   |\n",  tempo);

		else if (tempo < 10000)
			printf("| %.lf  |\n",  tempo);

		else
			printf("| %.lf |\n",  tempo);

	}

	printf("-----------------------------\n");

}

void liberaCorrida(Corrida *corrida){
	Piloto *piloto = corrida->primeiro, *aux;

	while(piloto != NULL){
		aux = piloto->prox;

		free(piloto);

		piloto = aux;

	}

	free(corrida);

}

void gridLargada(Corrida *corrida, Corrida *qualify1, Corrida *qualify2, Corrida *qualify3){
	Piloto *piloto;

	piloto = retiraUltimoPiloto(qualify3);
	while(piloto != NULL){
		inserePiloto(corrida, piloto->equipe, piloto->numero, piloto->tempo);

		free(piloto);
		
		piloto = retiraUltimoPiloto(qualify3);

	}

	free(qualify3);

	piloto = retiraUltimoPiloto(qualify2);
	while(piloto != NULL){
		inserePiloto(corrida, piloto->equipe, piloto->numero, piloto->tempo);

		free(piloto);
		
		piloto = retiraUltimoPiloto(qualify2);

	}

	free(qualify2);

	piloto = retiraUltimoPiloto(qualify1);
	while(piloto != NULL){
		inserePiloto(corrida, piloto->equipe, piloto->numero, piloto->tempo);

		free(piloto);
		
		piloto = retiraUltimoPiloto(qualify1);

	}

	free(qualify1);

}
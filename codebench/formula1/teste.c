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
void troca(Corrida *corrida, Piloto *piloto1, Piloto *piloto2, FILE *arq);
double tempoAleatorio();
int qtdeCarrosAleatorio(int limite);
int carroAleatorio(Corrida *volta, Corrida *qualify1, Corrida *qualify2, Corrida *qualify3);
int verificaCarro(Corrida *volta, Corrida *qualify1, Corrida *qualify2, Corrida *qualify3, int carro);
void guardaMenorTempo(Corrida *corrida, Corrida *volta);
void selectionSort(Corrida *corrida, FILE *arq);
Corrida* eliminadosDaEtapa(Corrida *corrida, int etapa);
Piloto* retiraUltimoPiloto(Corrida *corrida);
void imprime(Corrida *corrida, FILE *arq);
void liberaCorrida(Corrida *corrida);
Corrida* criaUmaCorrida();

int main(){
	Corrida *corrida;
	FILE *arq = fopen("PROCURAR.txt", "wt");

	srand(time(NULL));

	for(int i = 0; i < 5; i++)
		inserePiloto(corrida, 'A' + i, i + 1, tempoAleatorio());

	selectionSort(corrida, arq);



	//imprime(corrida);

	/*Corrida *corrida = criaCorrida();
	Corrida *volta, *qualify1, *qualify2, *qualify3;
	int qtdeCarros;

    srand(time(NULL));

	for(int i = 0; i < QTDE_PILOTOS; i++)
		inserePiloto(corrida, 'A', i + 1, 5);

	//QUALIFY 1
	qtdeCarros = qtdeCarrosAleatorio(QTDE_PILOTOS);
	printf("qtdeCarros = %d\n", qtdeCarros);
	for(int i = 0; i < QUALIFY1; i++){
		volta = criaCorrida();
		for(int j = 0; j < qtdeCarros; j++){
			int carro = carroAleatorio(volta, NULL, NULL, NULL);

			inserePiloto(volta, 'A', carro, tempoAleatorio());

		}

		guardaMenorTempo(corrida, volta);
		imprime(volta);
		liberaCorrida(volta);

	}

	selectionSort(corrida);

	imprime(corrida);

	qualify1 = eliminadosDaEtapa(corrida, 1);

	//imprime(qualify1);

	imprime(corrida);*/

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

int carroAleatorio(Corrida *volta, Corrida *qualify1, Corrida *qualify2, Corrida *qualify3){
	int carro = 1 + (rand() % 24);

	while(verificaCarro(volta, qualify1, qualify2, qualify3, carro))
		carro = 1 + (rand() % 24);

	return carro;

}

int verificaCarro(Corrida *volta, Corrida *qualify1, Corrida *qualify2, Corrida *qualify3, int carro){
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

	if(!encontrou && qualify3 != NULL){
		piloto = qualify3->primeiro;
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

void selectionSort(Corrida *corrida, FILE *arq){
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

		printf("ANTES\n");
		fputs("ANTES\n", arq);
		printf("menor - numero = %d tempo = %lf\ni - numero = %d tempo = %lf\n", menor->numero, menor->tempo, i->numero, i->tempo);
		fprintf(arq, "menor - numero = %d tempo = %lf\ni - numero = %d tempo = %lf\n", menor->numero, menor->tempo, i->numero, i->tempo);
		imprime(corrida, arq);

        if (i != menor) {
			troca(corrida, i, menor, arq);			

        }

		i = menor->prox;

		imprime(corrida, arq);

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

	//imprime(eliminados);

	return eliminados;

}

Piloto* retiraUltimoPiloto(Corrida *corrida){
	Piloto *piloto = corrida->ultimo;

	corrida->ultimo = piloto->ant;
	corrida->ultimo->prox = NULL;

	return piloto;

}

void troca(Corrida *corrida, Piloto *piloto1, Piloto *piloto2, FILE *arq){
	Piloto *auxAnt = piloto1->ant;
	Piloto *auxProx = piloto1->prox;

	if(corrida->primeiro == piloto1){
		printf("entrou1\n");
		fputs("entrou1\n", arq);
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
			fputs("entrou2.1\n", arq);
			piloto1->ant->prox = piloto2;
			//piloto2->prox->ant = piloto1;

			piloto1->ant = piloto2;
			piloto1->prox = piloto2->prox;
			piloto2->ant = piloto1->ant;
			piloto2->prox = piloto1;

		}else{
			printf("entrou2.2\n");
			fputs("entrou2.2\n", arq);
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
		fputs("entrou3\n", arq);
		piloto1->ant->prox = piloto2;
		piloto2->prox->ant = piloto1;

		piloto1->ant = piloto2;
		piloto1->prox = piloto2->prox;
		piloto2->ant = piloto1->ant;
		piloto2->prox = piloto1;

	}else{
		printf("entrou4\n");
		fputs("entrou4\n", arq);
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

void imprime(Corrida *corrida, FILE *arq){
	int i = 1;

	printf("-----------------------------\n");
	fputs("-----------------------------\n", arq);
	printf("| pos. | plto | eqp | tempo |\n");
	fputs("| pos. | plto | eqp | tempo |\n", arq);
	for(Piloto *piloto = corrida->primeiro; piloto != NULL; i++, piloto = piloto->prox){
		if(i < 10){
			printf("|  0%d  ", i);
			fprintf(arq, "|  0%d  ", i);

		}else{
			printf("|  %d  ", i);
			fprintf(arq, "|  %d  ", i);

		}

		if(piloto->numero < 10){
			printf("|  0%d  ", piloto->numero);
			fprintf(arq, "|  0%d  ", piloto->numero);

		}else{
			printf("|  %d  ", piloto->numero);
			fprintf(arq, "|  %d  ", piloto->numero);
		}

		printf("|  %c  | %.lf |\n", piloto->equipe, piloto->tempo * 10000);
		fprintf(arq, "|  %c  | %.lf |\n", piloto->equipe, piloto->tempo * 10000);

	}

	printf("-----------------------------\n");
	fputs("-----------------------------\n", arq);

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

Corrida* criaUmaCorrida(){
	Corrida *corrida = criaCorrida();

	for(int i = 0; i < QTDE_PILOTOS; i++)
		inserePiloto(corrida, 'A' + i, i + 1, 5);
	
	return corrida;

}
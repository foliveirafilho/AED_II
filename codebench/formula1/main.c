#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define QUALIFY1 10
#define QUALIFY2 8
#define QUALIFY3 5
#define NUMERO_PILOTOS 24
#define TEMPO_MAX 99999

typedef struct piloto Piloto;
typedef struct lista Lista;

struct piloto{
    int tempo;
    int numero;
    char equipe;
    int vai_correr;
    Piloto *proximo;
};

struct lista{
    Piloto *primeiro;
    Piloto *ultimo;
};

Lista* criaLista(){
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    if(!lista){
        exit(1);
    }
    lista->primeiro = lista->ultimo = NULL;
}

void inserePilotoInicio(Lista *lista, int tempo, int numero, char equipe){
    Piloto *novo = (Piloto *)malloc(sizeof(Piloto));
    if(!novo){
        exit(1);
    }
    novo->numero = numero;
    novo->equipe = equipe;
    novo->tempo = tempo;
    novo->vai_correr = 0;
    if(lista->primeiro == NULL){
        lista->ultimo = novo;
    }
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
}

void inserePilotoFim(Lista *lista, int tempo, int numero, char equipe){
    Piloto *novo = (Piloto *)malloc(sizeof(Piloto));
    Piloto *count;
    if(!novo){
        exit(1);
    }
    novo->numero = numero;
    novo->equipe = equipe;
    novo->tempo = tempo;
    novo->vai_correr = 0;
    if(lista->ultimo == NULL){
        lista->primeiro = novo;
    }else{
        lista->ultimo->proximo = novo;
    }
    lista->ultimo = novo;
    novo->proximo = NULL;
}

void inserePonteiroInicio(Lista *lista, Piloto *piloto){
    if(lista->primeiro == NULL){
        lista->ultimo = piloto;
    }
    piloto->proximo = lista->primeiro;
    lista->primeiro = piloto;
}

Piloto* removeUltimo(Lista *lista){
    Piloto* count = lista->primeiro;
    if(lista->primeiro == lista->ultimo){
        lista->primeiro = lista->ultimo = NULL;
        return count;
    }else{
        while (count->proximo != lista->ultimo){
            count = count->proximo;
        }
        Piloto *ultimoPiloto = count->proximo;
        count->proximo = NULL;
        lista->ultimo = count;
        lista->ultimo->proximo = NULL;
        return ultimoPiloto;
    }
}

void zerarTempo(Lista *lista){
    Piloto *pilotos = lista->primeiro;
    while(pilotos != NULL){
        pilotos->tempo = 0;
        pilotos = pilotos->proximo;
    }
}

void resetaVaiCorrer(Lista *lista){
    Piloto *pilotos = lista->primeiro;
    while(pilotos != NULL){
        pilotos->vai_correr = 0;
        pilotos = pilotos->proximo;
    }
}

int gerarTempo(){
    int maior = 99999;
    int menor = 10000;
    int aleatorio = rand()%(maior-menor+1) + menor;
    return aleatorio;
}

int gerarPiloto(){
    return rand()%NUMERO_PILOTOS + 1;
}

void trocaPilotos(Lista *lista, Piloto *posterior, Piloto *anterior){

    Piloto *count1, *count2;
    Piloto *aux;
    count1 = count2 = lista->primeiro;

    if(lista->primeiro != posterior){
        while(count1->proximo != posterior){
            count1 = count1->proximo;
        }
    }

    while(count2->proximo != anterior){
        count2 = count2->proximo;
    }

    if(lista->primeiro != posterior){
        aux = posterior->proximo;
        posterior->proximo = anterior->proximo;
        anterior->proximo = aux;
        count1->proximo = anterior;
        count2->proximo = posterior;
    }else{
        aux = posterior->proximo;
        posterior->proximo = anterior->proximo;
        anterior->proximo = aux;
        lista->primeiro = anterior;
        count2->proximo = posterior;
    }

    if(lista->ultimo == anterior){
        lista->ultimo = posterior;
    }

}

void ordenarLista(Lista* lista){
    int tempoAux;
    int numeroAux;
    char equipeAux;
    for (Piloto* i=lista->primeiro; i!=NULL; i=i->proximo) {
        Piloto* i_menor = i;
        for (Piloto* j = i->proximo; j!=NULL; j=j->proximo){
            if (j->tempo < i_menor->tempo){
                i_menor = j;
            }
        }
        tempoAux = i->tempo;
        numeroAux = i->numero;
        equipeAux = i->equipe;
        
        i->tempo = i_menor->tempo;
        i->numero = i_menor->numero;
        i->equipe = i_menor->equipe;
        
        i_menor->tempo = tempoAux;
        i_menor->numero = numeroAux;
        i_menor->equipe = equipeAux;
    }
}

bool vaiCorrer(Lista *lista, int numero){
    Piloto *count = lista->primeiro;
    while(count != NULL){
        if(count->numero == numero){
            if(count->vai_correr == 0){
                count->vai_correr = 1;
                return true;
            }else{
                return false;
            }
        }
        count = count->proximo;
    }
    printf(" ");
}

void guardaMenorTempo(Lista *lista, int numeroPiloto, int novoTempo){
    Piloto *count = lista->primeiro;
    while(count != NULL){
        if(count->numero == numeroPiloto){
            if(novoTempo < count->tempo){
                count->tempo = novoTempo;
            }
        }
        count = count->proximo;
    }
}

void qualify(Lista *lista, int voltas){
    int numeroVoltas = 0;
    int aux = 0;
    int qtdPilotos, numeroPiloto;
    while(numeroVoltas < voltas){
        qtdPilotos = gerarPiloto();
        while(aux < qtdPilotos){
            numeroPiloto = gerarPiloto();
            if(vaiCorrer(lista, numeroPiloto)){
                guardaMenorTempo(lista, numeroPiloto, gerarTempo());
                aux++;
            }  
        }
        resetaVaiCorrer(lista);
        numeroVoltas++;
    }
}

void retiraUltimos(Lista *lista, Lista *listaFinal, int qtd){
    int aux = 0;
    while(aux < qtd){
        inserePonteiroInicio(listaFinal, removeUltimo(lista));
        aux++;
    }
}

void imprime(Lista *lista){
    Piloto *count = lista->primeiro;
    int pos = 1;
    printf("| pos. | plto | eqp |  tempo  |\n");
    while(count != NULL){
        printf("|  %.2d  |  %.2d  |  %c  |  %d  |\n", pos, count->numero, count->equipe, count->tempo);
        count = count->proximo;
        pos++;
    }
}

int equipe(int numero){
    if(numero < 12){
        numero += 65;
    }else{
        numero += 53;
    }
    return numero;
}

void classificatorias(Lista *corrida, Lista *corridaFinal){
    //Qualify 1
    qualify(corrida, QUALIFY1);
    ordenarLista(corrida);
    printf("Q1\n\n");
    imprime(corrida);
    
    //Qualify 2
    retiraUltimos(corrida, corridaFinal, 7);
    qualify(corrida, QUALIFY2);
    ordenarLista(corrida);
    printf("\nQ2\n\n");
    imprime(corrida);
    
    //Qualify 3
    retiraUltimos(corrida, corridaFinal, 7);
    qualify(corrida, QUALIFY3);
    ordenarLista(corrida);
    printf("\nQ3\n\n");
    imprime(corrida);

    retiraUltimos(corrida, corridaFinal, 10);
    printf("\nGRID LARGADA\n\n");
    imprime(corridaFinal);
}

int main(){
    srand((unsigned int)time(NULL));
    Lista *corrida = criaLista();
    Lista *corridaFinal = criaLista();

    for(int i = 0; i < 24; i++){
        inserePilotoFim(corrida, TEMPO_MAX, i+1, equipe(i));
    }

    classificatorias(corrida, corridaFinal);

    return 0;
}
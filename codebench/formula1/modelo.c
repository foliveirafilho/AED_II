#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define QUALIFY1 10
#define QUALIFY2 8
#define QUALIFY3 5
#define NUMERO_PILOTOS 24

struct Pilotos
{
    int    tempo;
    int    numero;
	char   equipe;
    int    vai_correr;
    struct Pilotos *nextPtr;
};

typedef struct Pilotos TpPilotos;
typedef TpPilotos *PtrPilotos;
/*****************************************************************************************************************************/
/*PROTÓTIPOS*/
void excluiLista(PtrPilotos *sPtr);
void listaInicial(PtrPilotos *inicio);
void zeraCorrida(TpPilotos *auxiliarPtr);
void tempo_da_volta(TpPilotos *auxiliarPtr);
void procura_piloto(PtrPilotos *auxiliarPtr);
void imprime(PtrPilotos startPtr, int treino);
void ordena(PtrPilotos *sPtr, PtrPilotos *piloto);
void zeraTempo(TpPilotos *inicio, int maximo_de_pilotos);
void desata_no(PtrPilotos sPtr, PtrPilotos *auxiliarPtr);
void junta_listas(PtrPilotos *sPtr, PtrPilotos *auxiliar1Ptr);
int  numero_pilotos(int voltas, int qualify, int maximo_de_pilotos);
void quem_corre(int voltas, int maximo_de_pilotos, PtrPilotos *auxiliarPtr);
void listaOrdenada(pilotosPtr *startPtr, TpPilotos *inicio, int max_de_pilotos);
void chama_piloto(TpPilotos *inicio, PtrPilotos *auxiliarPtr,int voltas, int maximo_de_pilotos);
void qualify(TpPilotos *inicio, PtrPilotos *startPtr, int voltas_max,int max_de_pilotos, int treino);
/*****************************************************************************************************************************/

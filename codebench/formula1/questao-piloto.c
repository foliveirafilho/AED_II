#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define QUALIFY1 10
#define QUALIFY2 8
#define QUALIFY3 5
#define NUMERO_PILOTOS 24

typedef struct lista Lista;
typedef struct pilotos Pilotos;

struct pilotos {
    int    tempo;
    int    numero;
	char   equipe;
    int    vai_correr;
    struct pilotos *nextPtr;
};

struct lista {
    struct pilotos* inicio;
    struct pilotos* fim;
};

// criando lista de pilotos 
Lista* cria_lista_pilotos(){
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    
    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

// insere pilotos no fim 
void insere_piloto_fim(Lista* lista, int tempo, int num, char equipe){

    Pilotos* novo = (Pilotos*)malloc(sizeof(Pilotos));
    
    novo->tempo = tempo;
    novo->numero = num;
    novo->equipe = equipe;
    novo->vai_correr = 0;

    
    if(lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;

    }else {
        lista->fim->nextPtr = novo; 
        lista->fim = novo;
        
    }
    novo->nextPtr = NULL;
    
}
// lista pilotos que vao correr  -> lista total de pilotos 24 ok 
// criar uma listaVolta ---  (pilotos que vao dar a volta eu acho)* ok
// cada carro gera um num Func gerarnum ok 
// nao pode ter piloto repetido --- func verificaigualdade --- ok ?? teste 
// gerar numero aleatorio da qtd de pilotos que correm --ok 
// tem que guardar o piloto que tem o menor tempo ok 

// insere no inicio 
void insere_inicio(Lista* lis, Pilotos* ptr){
    if(lis->inicio == NULL){
        lis->fim = ptr;
    }
    ptr->nextPtr = lis->inicio;
    lis->inicio = ptr;
}


// gerador piloto 
int gerar_piloto(){
    return rand()%NUMERO_PILOTOS + 1;
}

//piloto que vai correr
bool plto_vai_correr(Lista* listaPiloto, int num){
    Pilotos* ptr = listaPiloto->inicio;
    while (ptr != NULL)
    {
        if(ptr->numero == num){
            if(ptr->vai_correr == 0){
                ptr->vai_correr = 1;
                return true;

            }else{
                return false;
            }
           
        }
        ptr = ptr->nextPtr;
    }
    printf(" ");

}
//guardar o menor tempo 
void guardar_menor_tempo(Lista* piloto, int numPiloto, int novotempo){ 
    Pilotos* ptr = piloto->inicio;
    while (ptr != NULL){
        if(ptr->numero == numPiloto){
            if(ptr->tempo > novotempo){
                ptr->tempo = novotempo;
            }

        }
        ptr = ptr->nextPtr;
    }
    
   

}

// gerador de numero 
int gerar_numero(){
    
    int maior = 99999;
    int menor = 10000;
    int aleatorio = rand()%(maior-menor+1) + menor;
    return aleatorio;

}
// verifica igualdade 

void verifica_igualdade(Lista* listaPiloto){
    Pilotos* ptr1 = listaPiloto->inicio;
    Pilotos* ptr2 = listaPiloto->inicio->nextPtr;

    
}

void imprimir_lista(Lista* lista){
    Pilotos* ptr;
    ptr = lista->inicio;
    int cont = 1;
    printf("| pos. | plto | eqp |  tempo  |\n");
    while(ptr != NULL){
        printf("|  %.2d  |  %.2d  |  %c  |  %d  |\n", cont, ptr->numero, ptr->equipe, ptr->tempo);
        ptr = ptr->nextPtr;
        cont++;
    }
    
}

int definir_equipe(int total){
    if(total < 12){
        total = total + 65;
    }else{
        total = total -12 + 65;
    }

    return total; 
}
// zerar a lista dos que vao correr 
void zera_lista_corres(Lista* lis){
    Pilotos* ptr = lis->inicio;

    while (ptr != NULL)
    {
        ptr->vai_correr = 0;
        ptr = ptr->nextPtr;
    }
    
}
// remove ultimo

Pilotos* remove_ultimo(Lista* lista){
    Pilotos* ptr = lista->inicio;

    if(lista->inicio == lista->fim){
        lista->inicio = lista->fim = NULL;
        return ptr;
    }else {
        while (ptr->nextPtr != lista->fim)
        {
            ptr = ptr->nextPtr;
        }

        Pilotos* ult = ptr->nextPtr;
        ptr->nextPtr = NULL;
        lista->fim = ptr;
        lista->fim->nextPtr = NULL;
        return ult;
        
    }


}
// retira os 7 ultimos 

void retira_ultimos(Lista* lista, Lista* lista_total, int qtd){
    int seteultimos = 0;
    while (seteultimos < 7 )
    {
        insere_inicio(lista_total, remove_ultimo(lista));
        seteultimos++;
    }
}

// qualify 10 voltas
// ele sortear qtd pilotos nessas 10 voltas 
// ele vai atribuir tempo de cada piloto dos que irao correr 
void qualify_topezera(Lista* lis, int numvoltas){
    int cont = 0;
    int i = 0;
    int numPiloto;
    int qtdPilotos;

    while (cont < numvoltas)
    {
       qtdPilotos = gerar_piloto(); // 1 a 24
       while (i < qtdPilotos) // quantos foram sorteados
       {
           numPiloto = gerar_piloto(); //num do piloto sortudissimo
           if (plto_vai_correr(lis, numPiloto))
           {
               guardar_menor_tempo(lis, numPiloto, gerar_numero());
               i++;
           }
       }
       zera_lista_corres(lis);
       cont++;
    }
    


}
void ordena(Lista* lista){
    int tempoAux;
    int numeroAux;
    char equipeAux;
    for (Pilotos* i=lista->inicio; i!=NULL; i=i->nextPtr) {
        Pilotos* i_menor = i;
        for (Pilotos* j = i->nextPtr; j!=NULL; j=j->nextPtr){
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

int main(){
    Lista* lista1 = cria_lista_pilotos();
     srand((unsigned int)time(NULL));
    char equipe;
    int num = 99999;
    for (int i = 0; i < 24; i++)
    {
        equipe = definir_equipe(i);
        insere_piloto_fim(lista1, num, i + 1, equipe);
    }
   

    Lista* lista2 = cria_lista_pilotos();

    qualify_topezera(lista1, QUALIFY1);
    printf("\nQ1\n -----------------------------\n");
    ordena(lista1);
    imprimir_lista(lista1);
   

    retira_ultimos(lista1,lista2, 7);
    qualify_topezera(lista1, QUALIFY2);
    printf("\nQ2\n -----------------------------\n");
    ordena(lista1);
    imprimir_lista(lista1);
    

    retira_ultimos(lista1,lista2, 7);
    qualify_topezera(lista1, QUALIFY3);
    printf("\nQ3\n -----------------------------\n");
    ordena(lista1);
    imprimir_lista(lista1);

     retira_ultimos(lista1,lista2, 10);
     printf("\nGRID LARGADA\n -----------------------------\n");
     imprimir_lista(lista2);
     printf(" -----------------------------\n");




  
}






#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAX_VAGA 1024
#define HORA 60
#define PLACA 15
#define VALOR_MINUTO 0.05

typedef struct cliente Cliente;
typedef struct vaga Vaga;

struct cliente{
    char *placa;
    int horaEntrada;
    int minutoEntrada;
    int horaSaida;
    int minutoSaida;

};

struct vaga{
    int numero;
    char classe;
    float tempoOcupado;
    Cliente *cliente;
    int altura;
    Vaga *esquerda;
    Vaga *direita;

};

Vaga* criaEstacionamento();
Vaga* criaVaga(int numero, char classe, float tempoOcupado, Cliente *cliente);
Cliente* criaCliente(char *placa, int entrada, int saida);
Vaga* insereEstacionamento(Vaga *estacionamento, Vaga *vaga);
Vaga* removeVaga(Vaga **estacionamento, Vaga *vaga);
Vaga* finalizaVaga(Vaga *estacionamento);
Vaga* buscaVaga(Vaga *estacionamento, int numero);
Vaga* buscaVagaRemocao(Vaga *estacionamento, int numero);
int altura (Vaga *estacionamento);
int fatorDeBalanceamento(Vaga *estacionamento);
Vaga* rotacaoDireita(Vaga **estacionamento);
Vaga* rotacaoEsquerda(Vaga **estacionamento);
Vaga* rotacaoDireitaEsquerda(Vaga **estacionamento);
Vaga* rotacaoEsquerdaDireita(Vaga **estacionamento);
void imprime(Vaga *estacionamento);
void liberaArvore(Vaga *estacionamento);
Vaga* terminaDia(Vaga **estacionamento, Vaga **saida);
int tempoOcupacaoTotal(Vaga *estacionamento);
void horaMaiorOcupacao(Vaga *estacionamento, int *ocupacaoHora);
void vagasPorClasse(Vaga *estacionamento, int *qtdeVagasClasse);
int qtdeVagasSaida(Vaga *estacionamento);
int maior(int *vetor, int tamanho);
int geraVaga();
int geraTempo();
char geraClasse(int *qtdeVagasClasse);
char* geraPlaca();

int main(){
    Vaga *estacionamento = criaEstacionamento(), *saida = criaEstacionamento(), *vagaProcurada;
    Cliente *cliente;
    int numero, ehRaiz = 1, qtdeVagas, tempoMedio, horaMaisOcupada, vaga, vagasSaida, qtdeVagasOcupadas = 0;
    int ocupacaoHora[24] = {0}, qtdeVagasClasse[4] = {0};

    srand(time(NULL));

    do{
        printf("Capacidade: %d Ocupacao atual: %d\nQuantidade de carro(s) a ser inserida (digite -1 para sair): ", MAX_VAGA, qtdeVagasOcupadas);
        scanf("%d", &qtdeVagas);

        qtdeVagasOcupadas += qtdeVagas;

        if(qtdeVagasOcupadas > MAX_VAGA){
            printf("Limite atingido. Serao inseridos somente %d carro(s).\n", MAX_VAGA - (qtdeVagasOcupadas - qtdeVagas));

            qtdeVagasOcupadas = MAX_VAGA;

        }

        for(int i = 0; i < qtdeVagas; i++){
            numero = geraVaga();

            if(!ehRaiz){
                vagaProcurada = buscaVaga(estacionamento, numero);
                
                if(vagaProcurada == NULL || (vagaProcurada != NULL && vagaProcurada->numero != numero)){
                    estacionamento = insereEstacionamento(estacionamento, criaVaga(numero, geraClasse(qtdeVagasClasse), 0, criaCliente(geraPlaca(), geraTempo(), 0)));
                
                }
                
            }else{
                ehRaiz = 0;
                estacionamento = insereEstacionamento(estacionamento, criaVaga(numero, geraClasse(qtdeVagasClasse), 0, criaCliente(geraPlaca(), geraTempo(), 0)));
                
            }

        }
            

    }while((qtdeVagasOcupadas < MAX_VAGA) && (qtdeVagas != -1));

    if(qtdeVagasOcupadas > 0){
        do{
            printf("Vaga a ser removida (digite -1 para sair ou 0 para remover todas as vagas): ");
            scanf("%d", &vaga);

            if(vaga == 0){
                saida = terminaDia(&estacionamento, &saida);

            }else if(vaga != -1){
                vagaProcurada = buscaVagaRemocao(estacionamento, vaga);
                vagaProcurada = finalizaVaga(vagaProcurada);

                saida = insereEstacionamento(saida, criaVaga(vagaProcurada->numero, vagaProcurada->classe, vagaProcurada->tempoOcupado, criaCliente(vagaProcurada->cliente->placa, vagaProcurada->cliente->horaEntrada * 60 + vagaProcurada->cliente->minutoEntrada, vagaProcurada->cliente->horaSaida * 60 + vagaProcurada->cliente->minutoSaida)));
                removeVaga(&estacionamento, vagaProcurada);

            }

        }while((vaga != -1) && (vaga != 0));

    }

    printf("\n---------------Vagas desocupadas------------------\n");
    if(saida != NULL)
        imprime(saida);

    else
        printf("Nao ha vagas desocupadas\n");
    
    if(saida != NULL){
        vagasSaida = qtdeVagasSaida(saida);
        tempoMedio = tempoOcupacaoTotal(saida) / vagasSaida;

        horaMaiorOcupacao(saida, ocupacaoHora);
        horaMaisOcupada = maior(ocupacaoHora, 24);

        printf("\n---------------Relatorio--------------------------\n");
        printf("\nMedia de vagas ocupadas: %d\n", vagasSaida);
        printf("     Classe A (moto): %d vaga(s)\n", qtdeVagasClasse[0]);
        printf("     Classe B (normal): %d vaga(s)\n", qtdeVagasClasse[1]);
        printf("     Classe C (VIP): %d vaga(s)\n", qtdeVagasClasse[2]);
        printf("     Classe D (especial): %d vaga(s)\n", qtdeVagasClasse[3]);
        printf("Tempo medio de ocupacao: %dh %dmin\n", tempoMedio / 60, tempoMedio % 60);
        printf("Hora com maior ocupacao: %dh Total de clientes: %d\n", horaMaisOcupada, ocupacaoHora[horaMaisOcupada]);

    }

    printf("\n---------------Vagas ocupadas---------------------\n");
    if(estacionamento != NULL)
        imprime(estacionamento);

    else
        printf("Nao ha vagas ocupadas\n");

    liberaArvore(estacionamento);
    liberaArvore(saida);

    return 0;

}

Cliente* criaSaida(){
    return NULL;

}

Vaga* criaEstacionamento(){
    return NULL;

}

Vaga* criaVaga(int numero, char classe, float tempoOcupado, Cliente *cliente){
    Vaga *vaga = malloc(sizeof *vaga);

    vaga->numero = numero;
    vaga->classe = classe;
    vaga->tempoOcupado = tempoOcupado;
    vaga->cliente = cliente;
    vaga->esquerda = NULL;
    vaga->direita = NULL;

    return vaga;

}

Cliente* criaCliente(char *placa, int entrada, int saida){
    Cliente *cliente = malloc(sizeof *cliente);
    cliente->placa = malloc(PLACA * sizeof *(cliente->placa));
    
    strcpy(cliente->placa, placa);
    cliente->horaEntrada = entrada / 60;
    cliente->minutoEntrada = entrada % 60;
    cliente->horaSaida = saida / 60;
    cliente->minutoSaida = saida % 60;

    return cliente;

}

Vaga* insereEstacionamento(Vaga *estacionamento, Vaga *vaga){
    if(estacionamento == NULL)
        return vaga;

    if(vaga->numero < estacionamento->numero){
        estacionamento->esquerda = insereEstacionamento(estacionamento->esquerda, vaga);
        
        if(fatorDeBalanceamento(estacionamento) >= 2){
            if(vaga->numero < estacionamento->esquerda->numero)
                estacionamento = rotacaoDireita(&estacionamento);

            else
                estacionamento = rotacaoEsquerdaDireita(&estacionamento);

        }

    }else{
        estacionamento->direita = insereEstacionamento(estacionamento->direita, vaga);

        if(fatorDeBalanceamento(estacionamento) >= 2){
            if(vaga->numero < estacionamento->direita->numero)
                estacionamento = rotacaoDireitaEsquerda(&estacionamento);

            else
                estacionamento = rotacaoEsquerda(&estacionamento);

        }
        
    }

    estacionamento->altura = altura(estacionamento);

    return estacionamento;

}

Vaga* removeVaga(Vaga** estacionamento, Vaga *vaga){
    if (*estacionamento == NULL)
        return NULL;

    else if ((*estacionamento)->numero > vaga->numero){
        (*estacionamento)->esquerda = removeVaga(&((*estacionamento)->esquerda), vaga);

        if(fatorDeBalanceamento(*estacionamento) >= 2){
            if(altura((*estacionamento)->direita->esquerda) > altura((*estacionamento)->direita->direita))
                *estacionamento = rotacaoDireitaEsquerda(estacionamento);

            else
                *estacionamento = rotacaoEsquerda(estacionamento);

        }

    }else if ((*estacionamento)->numero < vaga->numero){
        (*estacionamento)->direita = removeVaga(&((*estacionamento)->direita), vaga);

        if(fatorDeBalanceamento(*estacionamento) >= 2){
            if(altura((*estacionamento)->esquerda->direita) < altura((*estacionamento)->esquerda->esquerda))
                *estacionamento = rotacaoDireita(estacionamento);

            else
                *estacionamento = rotacaoEsquerdaDireita(estacionamento);

        }

    }else { /* achou o nó a remover */
        if ((*estacionamento)->esquerda == NULL && (*estacionamento)->direita == NULL) { /* nó sem filhos */
            free((*estacionamento)->cliente);
            free(*estacionamento);
            
            *estacionamento = NULL;

        }else if ((*estacionamento)->esquerda == NULL) { /* nó só tem filho à direita */
            Vaga* t = *estacionamento;
            estacionamento = &((*estacionamento)->direita);
            
            free(t->cliente);
            free(t);

        }else if ((*estacionamento)->direita == NULL) { /* só tem filho à esquerda */
            Vaga* t = *estacionamento;
            estacionamento = &((*estacionamento)->esquerda);
            
            free(t->cliente);
            free(t);

        }else { /* nó tem os dois filhos */
            Vaga* maiorDosMenores = (*estacionamento)->esquerda;
            
            while (maiorDosMenores->direita != NULL) {
                maiorDosMenores = maiorDosMenores->direita;
            }
            
            /* troca as informações */
            (*estacionamento)->numero = maiorDosMenores->numero; 
            (*estacionamento)->cliente = maiorDosMenores->cliente;
            (*estacionamento)->classe = maiorDosMenores->classe;
            (*estacionamento)->tempoOcupado = maiorDosMenores->tempoOcupado;

            maiorDosMenores->numero = vaga->numero;

            (*estacionamento)->esquerda = removeVaga(&((*estacionamento)->esquerda), vaga);

            if(fatorDeBalanceamento(*estacionamento) >= 2){
                if(altura((*estacionamento)->direita->esquerda) > altura((*estacionamento)->direita->direita))
                    *estacionamento = rotacaoDireitaEsquerda(estacionamento);

                else
                    *estacionamento = rotacaoEsquerda(estacionamento);

            }

        }

    }

    return *estacionamento;

}

Vaga* finalizaVaga(Vaga* estacionamento){
    if(estacionamento != NULL){
        int saida = geraTempo();
        
        while(saida <= ((estacionamento->cliente->horaEntrada * 60) + (estacionamento->cliente->minutoEntrada))){
            saida = geraTempo();

        }

        estacionamento->cliente->horaSaida = saida / 60;
        estacionamento->cliente->minutoSaida = saida % 60;

        estacionamento->tempoOcupado = saida - ((estacionamento->cliente->horaEntrada * 60) + estacionamento->cliente->minutoEntrada);

    }

    return estacionamento;

}

Vaga* buscaVaga(Vaga *estacionamento, int numero){
    if((estacionamento == NULL) || (estacionamento->numero == numero))
        return estacionamento;

    if(estacionamento->numero > numero)
        return buscaVaga(estacionamento->esquerda, numero);

    else
        return buscaVaga(estacionamento->direita, numero);

}

Vaga* buscaVagaRemocao(Vaga *estacionamento, int numero){
    if((estacionamento == NULL) || (estacionamento->numero == numero))
        return estacionamento;

    if(estacionamento->numero > numero){
        if((estacionamento->esquerda == NULL) || ((estacionamento->esquerda != NULL) && (estacionamento->esquerda->numero < numero)))
            return estacionamento;
            
        else
            return buscaVagaRemocao(estacionamento->esquerda, numero);

    }else{
        if((estacionamento->direita == NULL) || ((estacionamento->direita != NULL) && (estacionamento->direita->numero > numero)))
            return estacionamento;
            
        else
            return buscaVagaRemocao(estacionamento->direita, numero);

    }

}

int altura (Vaga *estacionamento){
    if(estacionamento == NULL)
        return -1;

    int alturaEsquerda = altura(estacionamento->esquerda);
    int alturaDireita = altura(estacionamento->direita);

    if(alturaDireita > alturaEsquerda)
        return alturaDireita + 1;

    else
        return alturaEsquerda + 1;

}

int fatorDeBalanceamento(Vaga *estacionamento){
    return abs(altura(estacionamento->esquerda) - altura(estacionamento->direita));
    
}

Vaga* rotacaoDireita(Vaga **estacionamento){
    Vaga *auxRaiz = *estacionamento, *auxEsquerda = auxRaiz->esquerda;

    auxRaiz->esquerda = auxEsquerda->direita;
    auxEsquerda->direita = auxRaiz;
    *estacionamento = auxEsquerda;
    
    auxRaiz->altura = altura(auxRaiz);
    auxEsquerda->altura = altura(auxEsquerda);

    return *estacionamento;

}

Vaga* rotacaoEsquerda(Vaga **estacionamento){
    Vaga *auxRaiz = *estacionamento, *auxDireita = auxRaiz->direita;

    auxRaiz->direita = auxDireita->esquerda;
    auxDireita->esquerda = auxRaiz;
    *estacionamento = auxDireita;
    
    auxRaiz->altura = altura(auxRaiz);
    auxDireita->altura = altura(auxDireita);

    return *estacionamento;

}

Vaga* rotacaoDireitaEsquerda(Vaga **estacionamento){
    rotacaoDireita(&((*estacionamento)->direita));
    rotacaoEsquerda(estacionamento);

    return *estacionamento;
    
}

Vaga* rotacaoEsquerdaDireita(Vaga **estacionamento){
    rotacaoEsquerda(&((*estacionamento)->esquerda));
    rotacaoDireita(estacionamento);

    return *estacionamento;
    
}

void imprime(Vaga *estacionamento){
    if(estacionamento != NULL){
        printf("\nPlaca: %s\n", estacionamento->cliente->placa);
        printf("     Piso: %d Vaga: %d Classe = %c Numero = %d\n", estacionamento->numero / 128, estacionamento->numero % 128, estacionamento->classe, estacionamento->numero);
        printf("     Entrada: %dh %dmin Saida: %dh %dmin\n", estacionamento->cliente->horaEntrada, estacionamento->cliente->minutoEntrada, estacionamento->cliente->horaSaida, estacionamento->cliente->minutoSaida);
        printf("     Valor pago: R$ %.2f\n", estacionamento->tempoOcupado * VALOR_MINUTO);
        imprime(estacionamento->esquerda);
        imprime(estacionamento->direita);

    }

}

void liberaArvore(Vaga *estacionamento){
    if(estacionamento != NULL){
        liberaArvore(estacionamento->esquerda);
        liberaArvore(estacionamento->direita);
        free(estacionamento->cliente);
        free(estacionamento);

    }

}

Vaga* terminaDia(Vaga **estacionamento, Vaga **saida){
    if(*estacionamento != NULL){
        terminaDia(&((*estacionamento)->esquerda), saida);
        terminaDia(&((*estacionamento)->direita), saida);
        *estacionamento = finalizaVaga(*estacionamento);
        *saida = insereEstacionamento(*saida, criaVaga((*estacionamento)->numero, (*estacionamento)->classe, (*estacionamento)->tempoOcupado, criaCliente((*estacionamento)->cliente->placa, (*estacionamento)->cliente->horaEntrada * 60 + (*estacionamento)->cliente->minutoEntrada, (*estacionamento)->cliente->horaSaida * 60 + (*estacionamento)->cliente->minutoSaida)));
        *estacionamento = removeVaga(estacionamento, *estacionamento);

    }

    return *saida;

}

int tempoOcupacaoTotal(Vaga* estacionamento){
    if(estacionamento != NULL){
        int saida = estacionamento->cliente->horaSaida * 60 + estacionamento->cliente->minutoSaida;
        int entrada = estacionamento->cliente->horaEntrada * 60 + estacionamento->cliente->minutoEntrada;
        int duracao = saida - entrada;

        return duracao + tempoOcupacaoTotal(estacionamento->esquerda) + tempoOcupacaoTotal(estacionamento->direita);

    }

    return 0;

}

void horaMaiorOcupacao(Vaga *estacionamento, int *ocupacaoHora){
    if(estacionamento != NULL){
        horaMaiorOcupacao(estacionamento->esquerda, ocupacaoHora);
        horaMaiorOcupacao(estacionamento->direita, ocupacaoHora);

        ocupacaoHora[estacionamento->cliente->horaEntrada]++;

    }

}

void vagasPorClasse(Vaga *estacionamento, int *qtdeVagasClasse){
    if(estacionamento != NULL){
        vagasPorClasse(estacionamento->esquerda, qtdeVagasClasse);
        vagasPorClasse(estacionamento->direita, qtdeVagasClasse);

        switch(estacionamento->classe){
            case 'A':
                qtdeVagasClasse[0]++;
                break;

            case 'B':
                qtdeVagasClasse[1]++;
                break;

            case 'C':
                qtdeVagasClasse[2]++;
                break;

            case 'D':
                qtdeVagasClasse[3]++;
                break;

        }

    }

}

int qtdeVagasSaida(Vaga *estacionamento){
    if(estacionamento == NULL)
        return 0;

    else 
        return (1 + qtdeVagasSaida(estacionamento->esquerda) + qtdeVagasSaida(estacionamento->direita));

}

int maior(int *vetor, int tamanho){
    int maior = 0;

    for(int i = 1; i < tamanho; i++){
        if(vetor[i] > vetor[maior])
            maior = i;

    }

    return maior;

}

int geraVaga(){
    return 1 + (rand() % MAX_VAGA);

}

int geraTempo(){
    int hora = (rand() % 24) * 60;
    int minuto = (1 + (rand() % 60));

    return hora + minuto;

}

char geraClasse(int *qtdeVagasClasse){
    int classe;
    int limite;

    do{
        classe = 1 + (rand() % 4);

        switch(classe){
            case 1:
                limite = 0.2 * MAX_VAGA; 
                break;

            case 2:
                limite = 0.5 * MAX_VAGA; 
                break;

            case 3:
                limite = 0.1 * MAX_VAGA; 
                break;

            case 4: 
                limite = 0.2 * MAX_VAGA; 
                break;

        }

    }while(qtdeVagasClasse[classe - 1] > limite);

    switch(classe){
        case 1:
            qtdeVagasClasse[0]++;
            return 'A';

        case 2:
            qtdeVagasClasse[1]++;
            return 'B';

        case 3:
            qtdeVagasClasse[2]++;
            return 'C';

        case 4:
            qtdeVagasClasse[3]++;
            return 'D';

    }

}

char *geraPlaca(){
    char *placa = malloc(8 * sizeof *placa);
    char caracter;
    
    caracter = 'A' + (char) (rand() % 26);
    placa[0] = caracter;
    
    caracter = 'A' + (char) (rand() % 26);
    placa[1] = caracter;
    
    caracter = 'A' + (char) (rand() % 26);
    placa[2] = caracter;
    
    caracter = '0' + (char) (rand() % 10);
    placa[3] = caracter;
    
    caracter = '0' + (char) (rand() % 10);
    placa[4] = caracter;
    
    caracter = '0' + (char) (rand() % 10);
    placa[5] = caracter;
    
    caracter = '0' + (char) (rand() % 10);
    placa[6] = caracter;
    
    placa[7] = '\0';

    return placa;

}
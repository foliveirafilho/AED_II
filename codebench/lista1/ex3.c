#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_PALAVRA 50

typedef struct palavra Palavra;
typedef struct frase Frase;

struct palavra{
	char *palavra;
	int ocorrencias;
	Palavra *prox;

};

struct frase{
	Palavra *primeira;
	Palavra *ultima;

};

Frase* criaFrase();
void insere(Frase *frase, char *string);
void imprime(Frase *frase);
int stringsIguais(char *string1, char *string2);
Palavra* procuraPalavra(Frase *frase, char *string);
Palavra* maiorOcorrencia(Frase *frase);
int totalPalavras(Frase *frase);
int verificaPalavra(char caracter);
int fraseVazia(Frase *frase);

int main(){
	Frase *frase = criaFrase();
	char *palavra = malloc(TAM_PALAVRA * sizeof *palavra);
	char caracter;

	while(scanf("%c", &caracter) != EOF){
		if(verificaPalavra(caracter) && (strlen(palavra) != 0)){
			Palavra *palavraEncontrada = procuraPalavra(frase, palavra);

			if(palavraEncontrada != NULL)
				palavraEncontrada->ocorrencias++;

			else if(caracter != '\n')
				insere(frase, palavra);

			free(palavra);
			palavra = malloc(TAM_PALAVRA * sizeof *palavra);

		}else if(caracter != ' '){
			int tamanho = strlen(palavra);
			palavra[tamanho] = caracter;
			palavra[tamanho + 1] = '\0';

		}

	}

	if(!fraseVazia(frase))
		imprime(frase);

	return 0;

}

Frase* criaFrase(){
	Frase *frase = malloc(sizeof *frase);

	frase->primeira = NULL;
	frase->ultima = NULL;

	return frase;

} 

void insere(Frase *frase, char *string){
	Palavra *palavra = malloc(sizeof *palavra);
	palavra->palavra = malloc(TAM_PALAVRA * sizeof *palavra->palavra);

	strcpy(palavra->palavra, string);
	palavra->prox = NULL;
	palavra->ocorrencias = 1;

	if(frase->primeira != NULL)
		frase->ultima->prox = palavra;

	else
		frase->primeira = palavra;

	frase->ultima = palavra;

}

void imprime(Frase *frase){
	Palavra *palavra;

	for(palavra = frase->primeira; palavra != NULL; palavra = palavra->prox)
		printf("%s (%d)\n", palavra->palavra, palavra->ocorrencias);
	
	palavra = maiorOcorrencia(frase);
	printf("Total de palavras: %d\n", totalPalavras(frase));
	printf("Maior incidencia: %s - %d vezes\n", palavra->palavra, palavra->ocorrencias);

}

int stringsIguais(char *string1, char *string2){
	return !strcmp(string1, string2);

}

Palavra* procuraPalavra(Frase *frase, char *string){
	for(Palavra *palavra = frase->primeira; palavra != NULL; palavra = palavra->prox){
		if(stringsIguais(palavra->palavra, string))
			return palavra;

	}

	return NULL;

}

Palavra* maiorOcorrencia(Frase *frase){
	Palavra *maior = frase->primeira;

	for(Palavra *palavra = frase->primeira->prox; palavra != NULL; palavra = palavra->prox){
		if(palavra->ocorrencias > maior->ocorrencias)
			maior = palavra;

	}

	return maior;

}

int totalPalavras(Frase *frase){
	int qtdePalavras = 0;

	for(Palavra *palavra = frase->primeira; palavra != NULL; palavra = palavra->prox)
		qtdePalavras++;

	return qtdePalavras;

}

int verificaPalavra(char caracter){
	if((caracter == '\n') || (caracter == ' ') || (caracter == ':') || (caracter == ',') || (caracter == '.') || (caracter == '-') || (caracter == '?') || (caracter == '!'))
		return 1;

	return 0;

}

int fraseVazia(Frase *frase){
	if(frase->primeira == NULL)
		return 1;
	
	return 0;
	
}
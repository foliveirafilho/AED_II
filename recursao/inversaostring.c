#include <stdio.h>
#include <stdlib.h>

void inverteStringImprime(char *string, int caracter);

int main(){
    char string[20], copia[20];
    int i;

    scanf("%20s", string);

    inverteStringImprime(string, 0); 
    printf("\n");

    system("pause");

    return 0;

}

void inverteStringImprime(char *string, int caracter){
    if(string[caracter] != 0)
        inverteStringImprime(string, caracter + 1);

    else
        return;

    printf("%c", string[caracter]);

}
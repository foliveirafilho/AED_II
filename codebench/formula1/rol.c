#include <stdio.h>

void selection_sort(int num[], int tam) { 
  int i, j, min, aux;
  for (i = 0; i < (tam-1); i++) 
  {
     min = i;
     for (j = (i+1); j < tam; j++) {
       if(num[j] < num[min]) 
         min = j;
     }
     if (i != min) {
       aux = num[i];
       num[i] = num[min];
       num[min] = aux;
     }
  }
}

int main(){
    int num[50];

    for(int i = 0; i < 50; i++){
        scanf("%d", &num[i]);

    }

    selection_sort(num, 50);

    for(int i = 0; i < 50; i++){
        
        printf("%d ", num[i]);

        if((i + 1) % 20 == 0)
            printf("\n");

    }

    

    return 0;

}
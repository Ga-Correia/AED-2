/* Programa: Bubble sort
Autor: Gabriel Correia Granja
Versao 1.0   AED-2   01/11/2021 */

#include <stdio.h>
#include <stdlib.h>

/*Função swap para a troca de valores*/
void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

/*Função bubble sort*/
int bubble_sort(int v[], int n){
  int j;
  int k;
  int cont=0; //contador para indicar quem ganhou o jogo
  for(k=1; k<n; k++){
    for(j=0; j<n-1; j++){
      if(v[j]>v[j+1]){
        swap(&v[j], &v[j+1]);
        cont++;
      }
    }
  }
  return cont;
}

/*Função main*/
int main(void){
  int N;    //número de casos testes
  scanf("%d", &N);
  int vetor[N];    //vetor que representa a sequência N interos distintos
  int i;   //contador de casos testes
  int bubble;  //variável para receber o return da função bubble_sort
  for(i=0; i<N; i++){
    scanf("%d", &vetor[i]);
  }
  bubble = bubble_sort(vetor, N); //recebe o return cont da função bubble_sort
  for(i=0; i<N; i++){
    printf("%d ", vetor[i]);
  }
  if(bubble % 2 == 0){   //se o valor de bubble for par, Carlo ganhou, se não, Marcelo ganhou
    printf("\nCarlos\n");
  }else{
    printf("\nMarcelo\n");
  }
  return 0;
}
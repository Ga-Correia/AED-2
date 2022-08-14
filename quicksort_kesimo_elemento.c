/* Programa: Quick Sort
Autor: Gabriel Correia Granja
AED-2   14/11/2021 */

#include <stdio.h>
#include <stdlib.h>

/*Função swap para fazer a troca*/
void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

/*Função partition para escolher um pivô do vetor passado como parâmetro e colocar os números menores que o pivô ao seu lado esquerdo e os maiores ao seu lado direito.*/
int partition(int V[], int comeco, int fim){
  int pivo, i, j;
  pivo=V[fim]; //o pivô escolhido será o último número-chave do vetor.
  i=comeco-1;
  /*laço para comparar cada número-chave do vetor com o pivô e verificar se é maior ou menor que ele.*/
  for(j=comeco; j<=fim-1; j++){ 
    if(V[j]<=pivo){
      i++;
      swap(&V[i], &V[j]); //faz a troca, separando os números menores que o pivô dos maiores.
    }
  }
  swap(&V[i+1], &V[fim]); //faz a troca de modo que todos os números menores que o pivô estarão a sua esquerda e os maiores a sua direita.
  return(i+1); //retorna a atual posição do pivô depois da troca. 
}

/*Função QuickSort para ordenar o vetor de acordo com o problema.*/
void QuickSort(int V[], int comeco, int fim, int K){
  if(comeco<fim){
    int q = partition(V, comeco, fim); //recebe a atual posição do pivô.
    if(K<q){ //se a posição digitada pelo o usuário, de um vetor dado, for menor que o pivô, será organizado o lado esquerdo, em que estão os menores números-chaves em relação ao primeiro pivô.
      QuickSort(V, comeco, q-1, K);
    }
    if(K>q){ //se a posição digitada pelo o usuário, de um vetor dado, for maior que o pivô, será organizado o lado direito, em que estão os maiores números-chaves em relação ao primeiro pivô.
      QuickSort(V, q+1, fim, K);
    }
  }
}

/*Função main*/
int main(void){
  int k;     //posição do número-chave a ser descoberto.
  scanf("%d", &k);
  int N;     //quantidade de números-chaves que o vetor vai possuir.
  scanf("%d", &N);
  int vetor[N];  //vetor com o total de números-chaves correspondente à variável N.
  int i;  //variável para a contagem em laços.

  if(0<N && N<=1000 && k<=N){
    for(i=0; i<N; i++){ //laço para leitura dos números-chaves do vetor. 
      scanf("%d", &vetor[i]);
    }
    QuickSort(vetor, 0, N-1, k-1); //chamada da função QuickSort.
    printf("%do menor elemento eh o %d\n", k, vetor[k-1]);
    for(i=0; i<N; i++){ //laço para a impressão do vetor.
      printf("%d ", vetor[i]);
    }
    printf("\n");
  }else{

  }
  return 0;
}

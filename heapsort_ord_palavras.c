/* Programa: Heap Sort
Autor: Gabriel Correia Granja
AED-2   22/11/2021 */

#include <stdio.h>
#include <string.h>

/*Função para criar o heap*/
void criaheap(char str[][20], int i, int n){
  char aux[20];
  int j = i*2+1;
  strcpy(aux, str[i]); // A varíavel aux recebe a string na posicão pai
  while(j<=n){
    if(j<n){
      if((strcmp(str[j+1], str[j]))>0){ //Compara qual dos 2 filhos de uma determinada string, posicionada como pai, possui valor lexograficamente maior. Se str[j+1] for maior, ou seja, (strcmp(str[j+1], str[j]))>0, o if é executado.
        j=j+1;
      }
    }
    if((strcmp(str[j], aux))>0){  // Verifica se o filho, str[j], é maior que a posição pai, aux. Caso sim, o if é executado.
      strcpy(str[i], str[j]);   // A string da posição filho é copiado para dentro da posição pai.
      i=j;  
      j=2*i+1;
    }else{
      j=n+1;
    }
  }
  strcpy(str[i], aux); // Antigo pai ocupa lugar do último filho analisado.
}

/*Função para o heap sort*/
void heapsort(char str[][20], int n){
  int i;
  char aux[20];
  for(i=(n-1)/2; i>=0; i--){  //Cria o heap a partir dos parâmetros passados.
    criaheap(str, i, n-1);
  }
  for(i=n-1; i>=1; i--){
    // Pega a string de maior valor lexograficamente do heap e coloca na sua posicao correspondente do vetor.
    strcpy(aux, str[0]);
    strcpy(str[0], str[i]);
    strcpy(str[i], aux);

    criaheap(str, 0, i-1); // Reconstrói o heap.
  }
}

int main(){
  int N;   // número do primeiro conjunto de palavras informadas pelo primeiro jogador.
  scanf("%d", &N);
	char vetor[N][20];   // matriz de strings que terá N palavras de 20 caracteres informada pelo segundo jogador.
  int M;   // nova quantidade de palavras informadas pelo terceiro jogador. 
	int i;   // variáveis de contagem.
  int j;   // variáveis de contagem.
  int cont=0;   //contador para verificar caracteres maiúsculos ou com acentos.
  char erro[20];  // string que recebe palavra invalidada.

  for(i=0; i<N; i++){
    scanf("%s", vetor[i]);
  }
  scanf("%d", &M);

  char Array2 [M][20];  // nova matriz de strings que terá M palavras de 20 caracteres.
  int indice;   // índices das palavras do conjunto anterior que irão compor o novo conjunto corresponte ao Array [M][20].

  for(i=0; i<M; i++){
    scanf("%d", &indice);
    strcpy(Array2[i], vetor[indice]); //Recebe as palavras de acordo com o índice da matriz anterior.
  }

  /*Loop que verifica se as palavras do primeiro conjunto possuem algum caracter maiúsculo ou com acento. Realiza o loop até a primeira palavra que se enquadra na exigência, adiciona +1 à variavel cont e salva a palavra na string erro.*/
  for(i=0; i<N; i++){
    for(j=0; vetor[i][j] != '\0'; j++){
      /*Os números presentes nos ifs representam os valores do caracteres de acordo com a tabela ASCII*/
      if(vetor[i][j]>=33 && vetor[i][j]<=64){ 

      }else if(vetor[i][j]>= 65 && vetor[i][j]<= 90){
        cont++;
        strcpy(erro, vetor[i]);
      }else if(vetor[i][j]>=91 && vetor[i][j]<=127){

      }else{
        cont++;
        strcpy(erro, vetor[i]);
      }
    }
    if(cont>0){
      break;
    }
  }

  /*Saídas de acordo com a execução do código*/
  if(cont>0){
    printf("a palavra %s eh invalida\n", erro);
  }else{
    printf("build_heap: ");
    for(i=0; i<M; i++){
      printf("%s ", Array2[i]);
    }
    printf("\n");
    printf("palavras: ");
    heapsort(Array2, M);   // Chamada da função heapsort, tendo como parâmetros o segundo conjunto de palavras e o seu tamanho.
    for(i=0; i<M; i++){
      printf("%s ", Array2[i]);
    }
    printf("\n");
  }
	return 0;
}
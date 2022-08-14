/* Programa: Recursão
Autor: Gabriel Correia Granja
Versao 1.0   AED-2   28/10/2021 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Função recursiva*/
float recursiva(float n, float v){
  if(n<v){
    return n;
  }else{
    return (n+recursiva(n/v, v));
  }
}

int main(){
  int N;   //número de casos testes
  int d;   //dinheiro que tem
  int p;   //preço de cada unidade de livro
  float v;   //vale-compras para obter um livro
  int i;   //contador de casos testes
  float n;   // número de vales obtido pelos livros.
  int Livros;  //Total de livros obtidos
  
  scanf("%d", &N);
  if(N>=1 && N<=10){
    for(i=0; i<N; i++){
      scanf("%d %d %f", &d, &p, &v);
      if(d>0){
        n = (d/p);
        Livros = round(recursiva(n, v));
        printf("%d\n", Livros);
      }else{
        Livros=0;
        printf("%d\n", Livros);
      }
    }
  }
  return 0;
}
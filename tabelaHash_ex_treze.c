/* Programa: Tabela Hash
Autor: Gabriel Correia Granja
AED-2   09/01/2022 */

#include <stdio.h>
#include <stdlib.h>

/*Struct para a tabela Hash*/
typedef struct No{
  int valor;
  struct No* proximo;
}tableHash;

/*Inicializa a tabela*/
void inicializa(tableHash **Hash, int tamanho){
  int i;
  for(i=0; i<tamanho; i++){
    Hash[i]= NULL;
  }
}

/*Funcao hash que calcula o resto da divisao do valor passado como parametro, pelo tamanho da tabela. O resultado corresponde a um determinado indice da tabela em que será criado uma lista encadeada ou ocorrerá alocacoes caso a lista ja exista*/
int funcaoHash(int k, int tamanho){
  int x = k % tamanho;
  return x;
}

/*Funcao de insercao na tabela Hash*/
void insercaoHash(tableHash **Hash, int chave, int tamanho){
  int posicao= funcaoHash(chave, tamanho); //calcula do indice da tabela hash
  tableHash **List= &Hash[posicao]; //ponteiro que aponta para uma lista encadeada, localizada na posicao da tabela que foi calculada para a chave passada como parametro

  if(*List==NULL){   //caso a lista da determinado indice for nula, o elemento inserido se torna o primeiro da lista
    *List= (tableHash *)malloc(sizeof(tableHash));
    (*List)->valor= chave;
    (*List)->proximo= NULL;
  }else{  //se a lista nao for nula, ocorreu um caso de colisao. O elemento será encadeado no indice indicado da tabela hash, ocupando a posicao nula da lista
    tableHash *colisao= Hash[posicao];
    while((*List)->proximo != NULL){
      *List= (*List)->proximo;
    }

    (*List)->proximo= (tableHash *) malloc(sizeof(tableHash));
    *List= (*List)->proximo;
    (*List)->valor= chave;
    (*List)->proximo= NULL;
    Hash[posicao]= colisao;
  }
}

/*Funcao de busca na tabela Hash*/
int buscaHash(tableHash **Hash, int chave, int tamanho){
  int posicao= funcaoHash(chave, tamanho); //calcula do indice da tabela hash
  tableHash *List= Hash[posicao]; //ponteiro que aponta para uma lista encadeada, localizada na posicao da tabela que foi calculada para a chave passada como parametro
  while (List != NULL){
    if (List->valor==chave){
      return 1;
    }
    List= List->proximo; 
	}
  return 0;
}

/*Funcao que ira percorrer e imprimir a lista encadeada que esta alocada em determinado indice ou posicao da tabela Hash*/
void percorreIndiceHash(tableHash **Hash, int posicao){
  tableHash *List= Hash[posicao];  //ponteiro que aponta para uma lista encadeada, localizada na posicao da tabela que foi passada como parametro
  printf("[%d] ", posicao);
  while(List != NULL){
    printf("%d ",List->valor);
		List = List->proximo;
  }
}

/*Funcao de remocao na tabela Hash*/
void remocaoHash(tableHash **Hash, int chave, int tamanho){
  if(buscaHash(Hash, chave, tamanho)==0){  //verifica se chave passada como parametrro está na tabela hash para ser removida
	  return;
  }else{  //se funcao buscaHash retorna valor diferente de 0 (return 1), entao a chave existe na tabela, sendo possivel remove-la
    int posicao= funcaoHash(chave, tamanho);  //calcula do indice da tabela hash
    tableHash **List= &Hash[posicao];
    tableHash *Anterior= *List;
    tableHash *Prox= (*List)->proximo;
    tableHash *guard= Hash[posicao];

    while(*List!=NULL){ 
      if((*List)->valor==chave){
        if(*List==Anterior){    //remocao do elemento localizado no inicio da lista
          if((*List)->proximo==NULL){
            free(*List);
            Hash[posicao]=NULL;
          }else{
            (*List)->proximo= Prox->proximo;
            (*List)->valor= Prox->valor;
            Hash[posicao]=guard;
          }
        }else{  //O elemento se encontra no meio ou final da lista. Procura ele e remove
          Anterior->proximo=Prox;
          free(*List);
          Hash[posicao]=guard;
        }
        return;
      }
      Anterior = *List;
      *List= (*List)->proximo;
      Prox= (*List)->proximo;
    }
    Hash[posicao]=guard;
    free(Anterior);
    free(Prox);
    free(guard);
  }
}


/*Funcao principal*/
int main(void){
  int tamanho;
  scanf("%d", &tamanho);   //leitura do tamanho para a tabela hash
  tableHash *HASH[tamanho];   //ponteiro da tabela Hash
  int number;
  int posicao;
  int busca;
  int i;

  /*execucao do codigo*/
  inicializa(HASH, tamanho);
  for(i=0; i>=0 ;i++){
    scanf("%d", &number);
    if(number>=0){
      insercaoHash(HASH, number, tamanho);
    }else{
      break;
    }
  }

  scanf("%d", &number);
  scanf("%d", &posicao);
  busca=buscaHash(HASH, number, tamanho);
  if(busca==0){
    printf("Valor nao encontrado\n");
    percorreIndiceHash(HASH, posicao);
  }else{
    remocaoHash(HASH, number, tamanho);
    percorreIndiceHash(HASH, posicao);
  }

  return 0;
}
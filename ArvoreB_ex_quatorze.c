/* Programa: ÁrvoreB
Autor: Gabriel Correia Granja
AED-2   17/01/2022 */

#include <stdio.h>
#include <stdlib.h>

/*Minimo de itens que a ArvoreB possui, lembrando que se o minimo de itens corresponde a M, entao o minimo de descendentes sera M + 1*/
#define M 2
/*Maximo de itens que a ArvoreB possui,  lembrando que se o maximo de itens corresponde a MM, entao o maximo de descendentes sera MM + 1, ou seja, 2M + 1*/
#define MM (M*2)


/*Estrutura da chave que sera armazenada*/
typedef struct ItemChave {
  int info;
}ItChave;  

/*Estrutura da arvoreB*/
typedef struct Pagina* ArvoreB;  
typedef struct Pagina {
  int indice;
  ItChave chaves[MM];
  ArvoreB pag[MM + 1];
}TPagina;

/*Funcao que inicializa a arvoreB*/
void Inicializa(ArvoreB *Node){  
  *Node = NULL; 
}

/*Sub-Funcao da Sub-Funcao de insere, que ira inserir o item na pagina, consequentemente reorganizando a posicao dos outros itens ja presentes, por causa deste*/
void insercaoNaPagina(ArvoreB Node, ItChave Item, ArvoreB NodeDir){
  int PosicaoEsgotada;
  int z;
  z= Node->indice;
  PosicaoEsgotada= (z>0);
  while(PosicaoEsgotada){
    if(Item.info >= Node->chaves[z-1].info){
      PosicaoEsgotada= 0;
      break;
    }
    /*Insere o item na pagina e reorganiza a posicao dos outros items ja presentes, mantendo a ordem crescente*/
    Node->chaves[z]= Node->chaves[z-1];
    Node->pag[z+1]= Node->pag[z];
    z--;
    if(z<1){
      PosicaoEsgotada= 0;
    }
  }
  Node->chaves[z]= Item;
  Node->pag[z+1]= NodeDir;
  Node->indice++;
}

/*Sub-Funcao da Funcao de InsercaoArvoreB, sendo responsavel pela quebra de paginas (split) e por definir em qual pagina sera inserido o item*/
void insere(ArvoreB Node, ItChave Item, ArvoreB *NodeReturn, ItChave *ItemReturn, int *aumento){
  int i= 1;
  int j;
  ArvoreB NodeAux;
  if(Node==NULL){
    *aumento= 1;
    *ItemReturn= Item;
    *NodeReturn= NULL;
    return;
  }
  /*Itera sobre todos os itens da pagina para encontrar a posicao correta para a insercao do novo item*/
  while((i< Node->indice) && (Item.info> Node->chaves[i-1].info)){
    i++;
  }
  /*O item ja exite na pagina, a funcao entao é retornada sem ter feito a insercao*/
  if(Item.info==Node->chaves[i-1].info){
    *aumento= 0;
    return;
  }
  if(Item.info< Node->chaves[i-1].info){
    i--;
  }
  insere(Node->pag[i], Item, NodeReturn, ItemReturn, aumento);

  if(!*aumento){
    return;
  }
  /*Existe espaco vazio na pagina, entao o item é inserido nesta pagina*/
  if(Node->indice< MM){
    insercaoNaPagina(Node, *ItemReturn, *NodeReturn);
    *aumento = 0;
    return;
  }

  /*A pagina esta cheia, logo devera ser feito o split, ou seja, a quebra da pagina em duas de tamanho 2M cada, para realizar a insercao*/
  NodeAux= (ArvoreB)malloc(sizeof(TPagina));
  NodeAux->indice = 0;
  NodeAux->pag[0]=NULL;

  if(i<M+1){
    insercaoNaPagina(NodeAux, Node->chaves[MM-1], Node->pag[MM]);
    Node->indice--;
    insercaoNaPagina(Node, *ItemReturn, *NodeReturn);
  }else{
    insercaoNaPagina(NodeAux, *ItemReturn, *NodeReturn);
  }
  for(j= M+2; j<=MM; j++){
    insercaoNaPagina(NodeAux, Node->chaves[j-1], Node->pag[j]);
  }
  Node->indice= M;
  NodeAux->pag[0]= Node->pag[M+1];
  *ItemReturn= Node->chaves[M];
  *NodeReturn= NodeAux;
}

/*Funcao de Insercao*/
void InsercaoArvoreB(ArvoreB *Node, ItChave Item){
  int aumento;
  ArvoreB NodeReturn, NodeAux; 
  ItChave ItemReturn;
  insere(*Node, Item, &NodeReturn, &ItemReturn, &aumento);

  if(aumento){
    NodeAux= (ArvoreB)malloc(sizeof(TPagina));   //Criacao da pagina que sera a raiz
    NodeAux->indice= 1;    //Apenas 1 item na pagina da raiz
    NodeAux->chaves[0]= ItemReturn;    //Item que estara presente na pagina da raiz
    NodeAux->pag[0]= *Node;     //Pagina à esquerda da raiz
    NodeAux->pag[1]= NodeReturn;   //Pagina à direita da raiz
    *Node= NodeAux;
  }
}

/*Funcao que conta a quantidade de itens que uma pagina possui*/
void QtdElementosPag(ArvoreB Node){
  int i= 0;
  if (Node==NULL){
    return;
  }
  /*Itera sobre todos os itens da pagina*/
  while(i< Node->indice){
    i++;
  }
  printf("%d\n", i);  //Informa quantos ela possui
}

/*Funcao que pesquisa se o item existe na arvoreB e automaticamente, caso exista, chama a Funcao  QtdElementosPag, informando a quantidade de itens que a pagina, aonde foi encontrado o item pesquisado, possui*/
int BuscaB(ArvoreB Node, ItChave *Item){
  int i = 1;
  if (Node==NULL){ 
    printf("Valor nao encontrado\n");
    return 0;
  }
  /*Itera sobre todos os itens da pagina até terminar ou achar o item que foi pesquisado*/
  while((i< Node->indice) && (Item->info> Node->chaves[i-1].info)){ 
    i++;
  }
  if(Item->info==Node->chaves[i-1].info){
    QtdElementosPag(Node);   //Achado o item, é passado a pagina em que ele está como parametro para a Funcao QtdElementosPag dizer quantos itens existem nesta pagina 
    return 1;   
  }
  if(Item->info< Node->chaves[i-1].info){
    return BuscaB(Node->pag[i-1], Item);
  }else{
    return BuscaB(Node->pag[i], Item);
  }
}

/*Funcao principal*/
int main(void){
  /*Variaveis*/
  ItChave item_valor;
  ArvoreB ArvB;
  int i;

  /*Execucao do codigo*/
  Inicializa(&ArvB);
  for(i=0; i>=0 ;i++){
    scanf("%d", &item_valor.info);
    if(item_valor.info>=0){
      InsercaoArvoreB(&ArvB, item_valor);  //primeira linha de entrada
    }else{
      break;
    }
  }
  QtdElementosPag(ArvB);  //primeira linha de saida
  scanf("%d", &item_valor.info);  //segunda linha de entrada
  BuscaB(ArvB, &item_valor);   //segunda linha de saida
  return 0;
}
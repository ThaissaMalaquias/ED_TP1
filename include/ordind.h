#ifndef ORD_IND_H
#define ORD_IND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct OrdInd{
    //quantidade de dados
    int num_registros;
    //quantidade de atributos
    int num_atributos;
    //vai armazenar os dados para cada atributo
    char** Nomes;
    char** CPFs;
    char** Ends;
    char** Outros;
    //vetor de indices, para cada um dos atributos
    int **Indices;
} OrdInd_t, *OrdInd_ptr;

//Funções dadas pelo enunciado do TP

//Contrutor da estrutura
OrdInd_ptr Cria();
//Destrutor da estrutura.
int Destroi (OrdInd_ptr poi);
//Carrega os dados e armazena de acordo com a estrutura.
int CarregaArquivo(OrdInd_ptr poi, char * nomeentrada);
//Retorna o numero de atributos dos registros.
int NumAtributos(OrdInd_ptr poi);
//Retorna o nome do atributo ao qual o codigo indicado por pos está relacionado.
int NomeAtributo(OrdInd_ptr poi, int pos, char* nome);
//Aloca e inicializa o vetor de índices para o atributo específico.
int CriaIndice (OrdInd_ptr poi, int atribid);
/*Compara 2 elementos de um atributo a partir de indices de referencia. 
Para maior escala, deve ser chamada em loop.*/
int Comparacao_Elementos(OrdInd_ptr poi, int thanku, int next, int atribid);
/*Função para o particionamento do vetor de entrada. Uma melhoria para o algoritmo
clássico aplicada aqui é a escolha do pivô por meio da mediana de três.*/
int Particao_QS(int esq, int dir, OrdInd_ptr poi, int atribid);
//Função Recursiva do QuickSOrt.
int QuickSort_rec(OrdInd_ptr poi, int esq, int dir, int atribid);
/*Função geral do QuickSort.*/
int OrdenaIndice_QuickSort(OrdInd_ptr poi, int atribid);
/*Selecao aplicado do final para o inicio, ou seja:
Seleciona o maior elemento e troca com o último.*/
int OrdenaIndice_Selecao(OrdInd_ptr poi, int atribid);
/*Combina os "Subvetores gerados" ao decorrer de Merge, ordenando-os.    
Melhoria aplicada: parar se o vetor já está ordenado, ou seja: se o último 
elemento da primeira metade é menor ou igual ao da segunda metade.*/
void Merge(int* ind_espec,int esq,int meio,int dir,OrdInd_ptr poi,int atribid);
//Funcao Recursiva do MergeSort.
void MergeSort_rec(OrdInd_ptr poi, int* ind_espec, int esq, int dir, int atribid);
//Funcao Geral do MergeSort.
int OrdenaIndice_MergeSort(OrdInd_ptr poi, int atribid);
//Impressão dos dados ordenados começando pelo atributo associado ao código dado.
int ImprimeOrdenadoIndice (OrdInd_ptr poi, int atribid);

#endif
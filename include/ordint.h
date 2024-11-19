#ifndef ORD_INT_H
#define ORD_INT_H

#include <stdio.h>
#include <stdlib.h>
//a biblioteca string é usada p/ manipulacao de arquivos.
#include <string.h>

typedef struct OrdInd{
    //quantidade de dados
    int num_linhas;
    //quantidade de atributos
    int num_colunas;
    //vai armazenar os primeiros dados (nome,cpf,endereço)
    char** Nomes;
    int* CPFs;
    char** Ends;
    //vetor de indices, para cada um dos atributos
    int **Indices;
} OrdInd_t, *OrdInd_ptr;

// Exemplos de funcoes
//Dado pelo enunciado do TP
OrdInd_ptr Cria();
int Destroi (OrdInd_ptr poi);
int CarregaArquivo(OrdInd_ptr poi, char * nomeentrada);
int NumAtributos(OrdInd_ptr poi);
char* NomeAtributo(OrdInd_ptr poi, int pos, char * nome);
int CriaIndice (OrdInd_ptr poi, int atribid);
int OrdenaIndice_QuickSort(OrdInd_ptr poi, int atribid);
int OrdenaIndice_InsertionSort(OrdInd_ptr poi, int atribuid);
int OrdenaIndice_MergeSort(OrdInd_ptr poi, int atribuid);
int ImprimeOrdenadoIndice (OrdInd_ptr poi, int atribid);

#endif;
#include "../include/ordint.h"
#include "../include/excecoes.h"

OrdInd_ptr Cria(){
    OrdInd_ptr ord_ptr = (OrdInd_ptr*) malloc(1000*sizeof(OrdInd_ptr));
    checar_alocacao(ord_ptr, "ord_ptr (construtor)");

    ord_ptr->Nomes = (char*) malloc(1000*sizeof(char));
    checar_alocacao(ord_ptr->Nomes, "Nomes");
    ord_ptr->CPFs = (int*) malloc(1000*sizeof(int));
    checar_alocacao(ord_ptr->CPFs, "CPFs");
    ord_ptr->Ends = (char*) malloc(1000*sizeof(char));
    checar_alocacao(ord_ptr->Ends, "Enderecos");

    ord_ptr->num_linhas = 0;
    ord_ptr->num_colunas = 0;
};

int Destroi (OrdInd_ptr poi){
    free(poi->Nomes);
    free(poi->CPFs);
    free(poi->Ends);
    free(poi);
};

int CarregaArquivo(OrdInd_ptr poi, char * nomeentrada);

int NumAtributos(OrdInd_ptr poi);

int NomeAtributo(OrdInd_ptr poi, int pos, char * nome);

int CriaIndice (OrdInd_ptr poi, int atribid);

int OrdenaIndice (OrdInd_ptr poi, int atribid);

int ImprimeOrdenadoIndice (OrdInd_ptr poi, int atribid);
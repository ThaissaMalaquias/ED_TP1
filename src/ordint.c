#include "../include/ordint.h"

OrdInd_ptr Cria();
int Destroi (OrdInd_ptr poi);
int CarregaArquivo(OrdInd_ptr poi, char * nomeentrada);
int NumAtributos(OrdInd_ptr poi);
int NomeAtributo(OrdInd_ptr poi, int pos, char * nome);
int CriaIndice (OrdInd_ptr poi, int atribid);
int OrdenaIndice (OrdInd_ptr poi, int atribid);
int ImprimeOrdenadoIndice (OrdInd_ptr poi, int atribid);
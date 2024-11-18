typedef struct OrdInd{
// a definir
} OrdInd_t, *OrdInd_ptr;

// Exemplos de funcoes
OrdInd_ptr Cria();
int Destroi (OrdInd_ptr poi);
int CarregaArquivo(OrdInd_ptr poi, char * nomeentrada);
int NumAtributos(OrdInd_ptr poi);
int NomeAtributo(OrdInd_ptr poi, int pos, char * nome);
int CriaIndice (OrdInd_ptr poi, int atribid);
int OrdenaIndice_QuickSort(OrdInd_ptr poi, int atribid);
int OrdenaIndice_InsertionSort(OrdInd_ptr poi, int atribuid);
int OrdenaIndice_MergeSort(OrdInd_ptr poi, int atribuid);
int ImprimeOrdenadoIndice (OrdInd_ptr poi, int atribid);
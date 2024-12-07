#include "../include/ordind.h"
#include "../include/load.h"

int main(int argc, char** argv){

    char* nome_arq = argv[1];
    char aux[100] = "";
    OrdInd_ptr poi = Cria();
    CarregaArquivo(poi,nome_arq);
    int numatrib = NumAtributos(poi);
    for (int i = 0; i<numatrib; i++){
        if (NomeAtributo(poi,i,aux)>0){
            if (!strcmp(aux,"Nome")||!strcmp(aux,"CPF")||!strcmp(aux,"End")){
                CriaIndice(poi,i);
                OrdenaIndice_QuickSort(poi,i);
                ImprimeOrdenadoIndice (poi,i);
            }
        }
    }
    for (int i = 0; i<numatrib; i++){
        if (NomeAtributo(poi,i,aux)>0){
            if (!strcmp(aux,"Nome")||!strcmp(aux,"CPF")||!strcmp(aux,"End")){
                CriaIndice(poi,i);
                OrdenaIndice_MergeSort(poi,i);
                ImprimeOrdenadoIndice (poi,i);
            }
        }
    }
    for (int i = 0; i<numatrib; i++){
        if (NomeAtributo(poi,i,aux)>0){
            if (!strcmp(aux,"Nome")||!strcmp(aux,"CPF")||!strcmp(aux,"End")){
                CriaIndice(poi,i);
                OrdenaIndice_Selecao(poi,i);
                ImprimeOrdenadoIndice (poi,i);
            }
        }
    }
    Destroi(poi);
}
#include "../include/ordint.h"

int main(){
    /*OrdInd_ptr ord_main;

    ord_main = Cria();

    CarregaArquivo(ord_main, "dados.csv");

    for(int i = 0; i < ord_main->num_linhas; i++){
        printf("\n Nome: %s, Cpf: %d, Endereco: %s \n", 
                ord_main->Nomes[i], ord_main->CPFs[i], ord_main->Ends[i] );
    }

    printf("\nnumero de linhas: %d \n", ord_main->num_linhas);
    printf("\nnumero de colunas: %d \n", ord_main->num_colunas);

    Destroi(ord_main);
    */

    char aux[100];
    OrdInd_ptr poi = Cria();
    CarregaArquivo(poi,"entrada.xcsv");
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
    Destroi(poi);
}
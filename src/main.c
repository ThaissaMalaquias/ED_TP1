#include "../include/ordint.h"

int main(){
    OrdInd_ptr ord_main;

    ord_main = Cria();

    CarregaArquivo(ord_main, "dados.csv");

    for(int i = 0; i < ord_main->num_linhas; i++){
        printf("\n Nome: %s, Cpf: %d, Endereco: %s \n", 
                ord_main->Nomes[i], ord_main->CPFs[i], ord_main->Ends[i] );
    }

    printf("\nnumero de linhas: %d \n", ord_main->num_linhas);
    printf("\nnumero de colunas: %d \n", ord_main->num_colunas);

    Destroi(ord_main);
}
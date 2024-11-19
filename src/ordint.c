#include "../include/ordint.h"
#include "../include/excecoes.h"

//Construtor
OrdInd_ptr Cria(){
    OrdInd_ptr ord_ptr = (OrdInd_ptr) malloc(1000*sizeof(OrdInd_t));
    checar_alocacao(ord_ptr, "ord_ptr (construtor)");

    //ponteiro para ponteiro, ponteiro para strings.
    ord_ptr->Nomes = (char**) malloc(1000*sizeof(char*));
    checar_alocacao(ord_ptr->Nomes, "Nomes");
    ord_ptr->CPFs = (int*) malloc(1000*sizeof(int));
    checar_alocacao(ord_ptr->CPFs, "CPFs");
    ord_ptr->Ends = (char**) malloc(1000*sizeof(char*));
    checar_alocacao(ord_ptr->Ends, "Enderecos");

    ord_ptr->num_linhas = 0;
    //num_colunas é iniciado com 1 para considerar o ultimo dado na logica de CarregaArquivo.
    ord_ptr->num_colunas = 1;
    
    return ord_ptr;
};

//Destrutor para liberar a memória.
int Destroi (OrdInd_ptr poi){
    free(poi->Nomes);
    free(poi->CPFs);
    free(poi->Ends);
    free(poi);
    return 0;
};

//Carrega os dados para armazenar na estrutura.
int CarregaArquivo(OrdInd_ptr poi, char * nomeentrada){
    FILE* arquivo = fopen(nomeentrada, "r");
    checar_abertura_arquivo(arquivo, nomeentrada);

    char* linha = malloc(512*sizeof(char));
    /*define a linha com maior numero de colunas para definir Num_colunas, 
    pois no arq .csv pode ser que haja dados com campos vazios não representados com vírgulas seguidas. 
    como não há como prever essa disposição, o numero de colunas será o numero de 
    atributos da(s) linha(s) com maior quantidade de dados*/ 
    int max_colunas = 0;

    while(fgets(linha, 512, arquivo))
    {
        //Primeiro, vamos setar num_linhas e montar uma lógica para setar num_colunas.
        poi->num_linhas += 1;

        int cont_colunas = 0;
        for(char* ln = linha; *ln != '\0'; ln++){
            if(*ln == ','){
                cont_colunas++;
            }
        }

        if(cont_colunas>max_colunas) max_colunas = cont_colunas;

        // Agora a lógica para setar poi->Nomes, poi->CPFs ,poi->Ends.
        
        //divide linha em substrings delimitadas por ','.
        char* token = strtok(linha, ",");
        int coluna = 0;
        
        //enquanto ainda há subtrings
        while(token!=NULL){
            switch (coluna)
            {
            case 0:
                //armazena o nome, ou seja, a substring armazenada em token.
                poi->Nomes[poi->num_linhas-1] = strdup(token);
                break;
            case 1:
                //convertendo a substring armazenada por token em inteiro.
                poi->CPFs[poi->num_linhas-1] = atoi(token);
                break;
            case 2:
                poi->Ends[poi->num_linhas-1] = strdup(token);
                break;
            default:
                break;
            }
            coluna++;
            //passa para a próxima substring
            token = strtok(NULL,",");
        }
    }

    //set num_colunas. += é utilizado, pois OrdInd_ptr é inicializado com num_coluna = 1.
    poi->num_colunas += max_colunas;

    fclose(arquivo);
    free(linha);

    return 0;
};

int NumAtributos(OrdInd_ptr poi){

};

int NomeAtributo(OrdInd_ptr poi, int pos, char * nome){

};

int CriaIndice (OrdInd_ptr poi, int atribid){

};

int OrdenaIndice (OrdInd_ptr poi, int atribid){

};

int ImprimeOrdenadoIndice (OrdInd_ptr poi, int atribid){

};
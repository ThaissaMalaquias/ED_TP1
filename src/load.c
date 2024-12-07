#include "../include/load.h"

//Carrega os dados para armazenar na estrutura OrdInd.
int CarregaArquivo(OrdInd_ptr poi, char * nomeentrada){
    FILE* arquivo = fopen(nomeentrada, "r");
    checar_abertura_arquivo(arquivo, nomeentrada);

    char* linha = malloc(8192*sizeof(char));
    checar_alocacao(linha, "Linha para Leitura de Arquivo");
    
    //pegar o número de atributos
    if(fgets(linha, 8192, arquivo)){
        poi->num_atributos = atoi(linha);
    }

    //para copiar os dados de cabecalho do arquivo
    poi->Cabecalho = (char**) malloc((poi->num_atributos*2)*sizeof(char*));
    checar_alocacao(poi->Cabecalho, "cabecalho do arquivo");
    poi->Cabecalho[0] = strdup(linha);
    

    //copiando os dados de cabeçalho e etc.
    for(int i=1; i <= poi->num_atributos; i++){
        fgets(linha, 8192, arquivo);
        poi->Cabecalho[i] = strdup(linha);
    }

    //pegar o número de registros
    int num_registros = 0;
    if(fgets(linha, 8192, arquivo)){
        num_registros = atoi(linha);
        poi->Cabecalho[poi->num_atributos+1] = strdup(linha);
    }
    poi->num_registros = num_registros;

    //pegar o número de caracteres de payload
    /*
    int num_outros = 0;
    char* nomeentrada_copia = strdup(nomeentrada);
    char* token = strtok(nomeentrada_copia,"p");
    if(token!=NULL){
        token = strtok(NULL, ".");
        num_outros = atoi(token);
    }
    */

    //alocação para os dados.
    poi->Nomes = (char**) malloc(num_registros*sizeof(char*));
    checar_alocacao(poi->Nomes, "Nomes");
    poi->CPFs = (char**) malloc(num_registros*sizeof(char*));
    checar_alocacao(poi->CPFs, "CPFs");
    poi->Ends = (char**) malloc(num_registros*sizeof(char*));
    checar_alocacao(poi->Ends, "Enderecos");
    poi->Outros = (char**) malloc(num_registros*sizeof(char*));
    checar_alocacao(poi->Outros, "Outros");

    //copiando os dados para a estrutura.
    int reg = 0;
    while(fgets(linha, 8192, arquivo) && reg < num_registros){
        char* nome = strtok(linha, ",");
        char* cpf = strtok(NULL, ",");
        char* end = strtok(NULL, ",");
        char* otrs = strtok(NULL, "\n");

        poi->Nomes[reg] = strdup(nome);
        poi->CPFs[reg] = strdup(cpf);
        poi->Ends[reg] = strdup(end);
        poi->Outros[reg] = strdup(otrs);

        reg++;
    }

    fclose(arquivo);
    free(linha);

    return 0;
}

#include "../include/excecoes.h"

/*void* é utilizado para que uma variável de qualquer tipo seja aceita.
Isso é considerado uma boa alternativa para evitar ambiguidades, já que 
ordind.c inclui excecoes.h */


void checar_alocacao(void* ptr, char* msg){
    if(ptr==NULL){
        fprintf(stderr, "Erro de Alocação: %s\n", msg);
        abort();
    }
};

void checar_abertura_arquivo(FILE* arquivo, char* nome_arq){
    if(arquivo==NULL){
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", nome_arq);
        abort();
    }
};

void checar_codigo_atributo(int pos, int numeroatributos){
    if(pos<0 || pos>=numeroatributos){
        fprintf(stderr, "O codigo fornecido do atributo e invalido.\n");
        abort();
    }
};

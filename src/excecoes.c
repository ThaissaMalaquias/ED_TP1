#include "../include/excecoes.h"

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


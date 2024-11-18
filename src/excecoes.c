#include "../include/excecoes.h"

int checar_alocacao(void* ptr, char* msg){
    if(ptr==NULL){
        fprintf(stderr, "Erro de Alocação: %s\n", msg);
        abort();
    }
};
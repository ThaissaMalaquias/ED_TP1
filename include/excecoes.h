#ifndef EXCECOES_ORDINT_H
#define EXCECOES_ORDINT_H

#include <stdio.h>
#include <stdlib.h>

//Checa se a alocacao dinâmica foi bem sucedida.
void checar_alocacao(void* ptr, char* msg);
//Checa se um arquivo foi aberto com sucesso.
void checar_abertura_arquivo(FILE* arquivo, char* nome_arq);

#endif
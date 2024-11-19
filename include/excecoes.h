#ifndef EXCECOES_ORDINT_H
#define EXCECOES_ORDINT_H

#include <stdio.h>
#include <stdlib.h>

//Checa se a alocacao dinâmica foi bem sucedida.
void checar_alocacao(void* ptr, char* msg);
//Checa se um arquivo foi aberto com sucesso.
void checar_abertura_arquivo(FILE* arquivo, char* nome_arq);
//Checa se uma posicao é negativa ou maior que o numero de colunas.
//void* é usado para não ter ambiguidades, já que ordind.c inclui excecoes.h.
void checar_posicao(int pos, int numerocolunas);

#endif
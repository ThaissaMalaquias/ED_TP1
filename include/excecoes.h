#ifndef EXCECOES_ORDINT_H
#define EXCECOES_ORDINT_H

#include <stdio.h>
#include <stdlib.h>

//Checa se a alocacao dinâmica foi bem sucedida.
void checar_alocacao(void* ptr, char* msg);
//Checa se um arquivo foi aberto com sucesso.
void checar_abertura_arquivo(FILE* arquivo, char* nome_arq);
/*Checa se um código para um atributo é negativo ou maior que o numero de atributos.
Nos dois casos o código é considerado inválido.*/
void checar_codigo_atributo(int pos, int numerocolunas);

#endif
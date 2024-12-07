#ifndef LOAD_H
#define LOAD_H

#include "./ordind.h"
#include <time.h>

int CarregaArquivo(OrdInd_ptr poi, char * nomeentrada);
//Para registrar acessos de memória.
void log_mem_access(const char* filename, clock_t time, void* addr);

#endif

#include "../include/ordind.h"

//Construtor
OrdInd_ptr Cria(){
    //retorna um  tipo OrdIndptr que é um ponteiro para um tipo Ordint_t.
    OrdInd_ptr ord_ptr = (OrdInd_ptr) malloc(1*sizeof(OrdInd_t));
    checar_alocacao(ord_ptr, "ord_ptr (construtor)");

    log_mem_access("Q_mem_access.csv", clock(), ord_ptr);
    log_mem_access("M_mem_access.csv", clock(), ord_ptr);
    log_mem_access("S_mem_access.csv", clock(), ord_ptr);

    //Os ponteiros para ponteiros são inicializados com NULL e
    //só são alocados quando necessário.
    ord_ptr->Nomes = NULL;
    ord_ptr->CPFs = NULL;
    ord_ptr->Ends = NULL;
    ord_ptr->Outros = NULL;

    ord_ptr->num_registros = 0;
    ord_ptr->num_atributos = 0;

    ord_ptr->Indices = NULL;
    ord_ptr->Cabecalho = NULL;

    return ord_ptr;
}

//Destrutor para liberar a memória.
int Destroi (OrdInd_ptr poi){
    log_mem_access("Q_mem_access.csv", clock(), poi->Nomes);
    log_mem_access("M_mem_access.csv", clock(), poi->Nomes);
    log_mem_access("S_mem_access.csv", clock(), poi->Nomes);
    free(poi->Nomes);
    log_mem_access("Q_mem_access.csv", clock(), poi->CPFs);
    log_mem_access("M_mem_access.csv", clock(), poi->CPFs);
    log_mem_access("S_mem_access.csv", clock(), poi->CPFs);
    free(poi->CPFs);
    log_mem_access("Q_mem_access.csv", clock(), poi->Ends);
    log_mem_access("M_mem_access.csv", clock(), poi->Ends);
    log_mem_access("S_mem_access.csv", clock(), poi->Ends);
    free(poi->Ends);
    log_mem_access("Q_mem_access.csv", clock(), poi->Outros);
    log_mem_access("M_mem_access.csv", clock(), poi->Outros);
    log_mem_access("S_mem_access.csv", clock(), poi->Outros);
    free(poi->Outros);
    log_mem_access("Q_mem_access.csv", clock(), poi->Indices[0]);
    log_mem_access("M_mem_access.csv", clock(), poi->Indices[0]);
    log_mem_access("S_mem_access.csv", clock(), poi->Indices[0]);
    free(poi->Indices[0]);
    log_mem_access("Q_mem_access.csv", clock(), poi->Indices[1]);
    log_mem_access("M_mem_access.csv", clock(), poi->Indices[1]);
    log_mem_access("S_mem_access.csv", clock(), poi->Indices[1]);
    free(poi->Indices[1]);
    log_mem_access("Q_mem_access.csv", clock(), poi->Indices[2]);
    log_mem_access("M_mem_access.csv", clock(), poi->Indices[2]);
    log_mem_access("S_mem_access.csv", clock(), poi->Indices[2]);
    free(poi->Indices[2]);
    log_mem_access("Q_mem_access.csv", clock(), poi->Indices);
    log_mem_access("M_mem_access.csv", clock(), poi->Indices);
    log_mem_access("S_mem_access.csv", clock(), poi->Indices);
    free(poi->Indices);
    free(poi->Cabecalho);
    log_mem_access("Q_mem_access.csv", clock(), poi);
    log_mem_access("M_mem_access.csv", clock(), poi);
    log_mem_access("S_mem_access.csv", clock(), poi);
    free(poi);
    return 0;
}

int NumAtributos(OrdInd_ptr poi){
    return poi->num_atributos;
}

int NomeAtributo(OrdInd_ptr poi, int pos, char* nome){

    checar_codigo_atributo(pos, poi->num_atributos);

    //seta o parâmetro nome com o atributo correspondente;
    switch (pos)
    {
    case 0:
        strcpy(nome, "Nome");
        break;
    case 1:
        strcpy(nome, "CPF");
        break;
    case 2:
        strcpy(nome, "End");
        break;
    default:
        strcpy(nome, "Outros");
        break;
    }
    
    /*precisa retornar um valor maior que 0, segundo o main dado pelo enunciado.
    checar_codigo_atributo sempre garante a validade do atributo.*/
    return 1;
}

int CriaIndice (OrdInd_ptr poi, int atribid){

    checar_codigo_atributo(atribid, poi->num_atributos);

    /*se Indices ainda está no estagio inicial de não apontar para
    nenhuma posição válida da memória, aloca.*/
    if(poi->Indices==NULL){
        poi->Indices = (int**) malloc(poi->num_atributos*sizeof(int*));
        checar_alocacao(poi->Indices, "Indices para cada Atributo");
        log_mem_access("Q_mem_access.csv", clock(), poi->Indices);
        log_mem_access("M_mem_access.csv", clock(), poi->Indices);
        log_mem_access("S_mem_access.csv", clock(), poi->Indices);
    }

    //Alocação para o vetor de Indices de um atributo específico.
    poi->Indices[atribid] = (int *) malloc(poi->num_registros*sizeof(int));
    checar_alocacao(poi->Indices[atribid], "Indices de um atributo especifico");
    log_mem_access("Q_mem_access.csv", clock(), poi->Indices[atribid]);
    log_mem_access("M_mem_access.csv", clock(), poi->Indices[atribid]);
    log_mem_access("S_mem_access.csv", clock(), poi->Indices[atribid]);

    //inicialização dos índices de um atributo específico.
    for(int i=0; i<poi->num_registros; i++){
        poi->Indices[atribid] [i] = i;
    }

    return 0;
}

int Comparacao_Elementos(OrdInd_ptr poi, int thanku, int next, int atribid/*, char** file_mem_access*/){

    checar_codigo_atributo(atribid, poi->num_atributos);

    switch (atribid)
    {
    case 0:
        /*log_mem_access(file_mem_access, clock(), poi->Nomes);
        log_mem_access(file_mem_access, clock(), poi->Nomes[thanku]);
        log_mem_access(file_mem_access, clock(), poi->Nomes[next]);*/       
        return strcmp(poi->Nomes[thanku], poi->Nomes[next]);
        break;
    case 1:
        /*log_mem_access(file_mem_access, clock(), poi->CPFs);
        log_mem_access(file_mem_access, clock(), poi->CPFs[thanku]);
        log_mem_access(file_mem_access, clock(), poi->CPFs[next]);*/
        return strcmp(poi->CPFs[thanku], poi->CPFs[next]);
        break;
    case 2:
        /*log_mem_access(file_mem_access, clock(), poi->Ends);
        log_mem_access(file_mem_access, clock(), poi->Ends[thanku]);
        log_mem_access(file_mem_access, clock(), poi->Ends[next]);*/
        return strcmp(poi->Ends[thanku], poi->Ends[next]);
        break;
    default:
        return -1;
        break;
    }
}

int Particao_QS(int esq, int dir, OrdInd_ptr poi, int atribid){
    //indices relacionados ao atributo específico.
    int* inds_espec = poi->Indices[atribid];
    log_mem_access("Q_mem_access.csv", clock(), inds_espec);
    /*Aplicando a mediana de três para a escolha do pivô.
    o primeiro, o último e o elemento do meio são comparados de forma
    que sejam ordenados crescentemente, obtendo a mediana no meio.*/
    
    //pegando o primeiro, último e o elemento do meio.
    int meio = (esq+dir) / 2;
    int pivo = meio;

    int aux = 0;

    //comparando e trocando de forma a obter o  no meio.
    if((Comparacao_Elementos(poi,inds_espec[esq],inds_espec[meio],atribid/*,"Q_mem_access.csv"*/))>0){
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[esq]);
        aux = inds_espec[esq];
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[meio]);
        inds_espec[esq] = inds_espec[meio];
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[esq]);
        inds_espec[meio] = aux;
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[meio]);
    }
    if((Comparacao_Elementos(poi,inds_espec[esq],inds_espec[dir],atribid/*,"Q_mem_access.csv"*/))>0){
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[esq]);
        aux = inds_espec[esq];
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[dir]);
        inds_espec[esq] = inds_espec[dir];
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[esq]);
        inds_espec[dir] = aux;
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[dir]);
    }
    if((Comparacao_Elementos(poi,inds_espec[meio],inds_espec[dir],atribid/*,"Q_mem_access.csv"*/))>0){
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[meio]);
        aux = inds_espec[meio];
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[dir]);
        inds_espec[meio] = inds_espec[dir];
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[meio]);
        inds_espec[dir] = aux;
        log_mem_access("Q_mem_access.csv", clock(), inds_espec[dir]);
    }
                
    pivo = inds_espec[meio];

    inds_espec[meio] = pivo;
    log_mem_access("Q_mem_access.csv", clock(), inds_espec[meio]);

    //após escolha do pivô
 
    //inicializando os indices de partição
    int i = esq;
    int j = dir;

    int temp = 0;

    while(i <= j){
        //comparando os elementos com o pivô até encontrar um elemento no local inapropriado. 
        while((Comparacao_Elementos(poi, inds_espec[i], pivo, atribid/*, "Q_mem_access.csv"*/)) < 0) i++;
        while((Comparacao_Elementos(poi, inds_espec[j], pivo, atribid/*, "Q_mem_access.csv"*/)) > 0) j--;

        //quando uma troca é necessária
        if(i <= j){
            log_mem_access("Q_mem_access.csv", clock(), inds_espec[i]);
            temp = inds_espec[i];
            log_mem_access("Q_mem_access.csv", clock(), inds_espec[j]);
            inds_espec[i] = inds_espec[j];
            log_mem_access("Q_mem_access.csv", clock(), inds_espec[i]);            
            inds_espec[j] = temp;
            log_mem_access("Q_mem_access.csv", clock(), inds_espec[j]);
            i++;
            j--;
        }
    }

    //ponto de partição é retornado.
    return i;
}

int QuickSort_rec(OrdInd_ptr poi, int esq, int dir, int atribid){

    if((esq < dir)){
        /*O meio vai ser o ponto de partição retornado pela função de particionamento*/
        int meio = Particao_QS(esq,dir,poi,atribid);

        /* Ordenando as duas metades recursivamente de forma a fazer mais particionamentos até que 
        hajam apenas dois elementos ordenados entre si. neste ponto, a ordenação está completa.*/
        QuickSort_rec(poi, esq, meio-1, atribid);
        QuickSort_rec(poi,meio,dir,atribid);

    }

    return 0;
}

int OrdenaIndice_QuickSort(OrdInd_ptr poi, int atribid){
    //Checa se o vetor de indices já está alocado e inicilizado.
    checar_alocacao(poi->Indices, "Vetor de Indices para cada atributo nao alocado.");
    checar_alocacao(poi->Indices[atribid], "Vetor de Indices para atributo especifico nao alocado.");

    //começa a ordenação dos dados.
    QuickSort_rec(poi, 0, (poi->num_registros)-1, atribid);

    return 0;
}

int OrdenaIndice_Selecao(OrdInd_ptr poi, int atribid){
    checar_codigo_atributo(atribid, poi->num_atributos);

    //obtendo o vetor de índices de um atributo específico.
    int* ind_espec = poi->Indices[atribid];
    int aux = 0;

    //percorrendo do fim para o início
    for(int i = poi->num_registros - 1; i>0; i--){
        int max_elem = i;
        
        //percorrendo o subvetor ainda não ordenado.
        for(int j = 0; j<i; j++){
            if(Comparacao_Elementos(poi,ind_espec[j],ind_espec[max_elem],atribid/*, "S_mem_access.csv"*/)>0){
                max_elem = j;
            }
        }

        //troca o maior elemento com o último.
        if(max_elem!=i){
            log_mem_access("S_mem_access.csv", clock(), ind_espec[i]);
            aux = ind_espec[i];
            log_mem_access("S_mem_access.csv", clock(), ind_espec[max_elem]);
            ind_espec[i] = ind_espec[max_elem];
            log_mem_access("S_mem_access.csv", clock(), ind_espec[i]);
            ind_espec[max_elem] = aux;
            log_mem_access("S_mem_access.csv", clock(), ind_espec[max_elem]);
        }
    }

    return 0;
}

void Merge(int* ind_espec,int esq,int meio,int dir,OrdInd_ptr poi,int atribid){
    //Mede a quantidade de elementos em cada metade.
    int quant_esq = (meio - esq) + 1;
    int quant_dir = dir - meio;

    //criando e alocando vetores temporários.
    int* E = malloc(quant_esq * sizeof(int));
    checar_alocacao(E, "Merge - Vetor temporario esquerda");
    log_mem_access("M_mem_access.csv", clock(), E);
    int* D = malloc(quant_dir * sizeof(int));
    checar_alocacao(D, "Merge - Vetor Temporario direita");
    log_mem_access("M_mem_access.csv", clock(), D);

    //inicializando os vetores temporários com os índices do atributo específico.
    for(int i = 0; i < quant_esq; i++){
        log_mem_access("M_mem_access.csv", clock(), ind_espec[esq + i]);
        E[i] = ind_espec[esq + i];
        log_mem_access("M_mem_access.csv", clock(), E[i]);
    }
    for(int j = 0; j < quant_dir; j++){
        log_mem_access("M_mem_access.csv", clock(), ind_espec[meio + 1 + j]);
        D[j] = ind_espec[meio + 1 + j];
        log_mem_access("M_mem_access.csv", clock(), D[j]);
    }

    int i = 0, j = 0, k = esq;

    /*melhoria no merge sort: parar se o vetor já está ordenado, ou seja:
    se o último elemento da primeira metade é menor igual ao da segunda metade.*/
    if((Comparacao_Elementos(poi, ind_espec[meio],ind_espec[meio+1], atribid/*, "M_mem_access.csv"*/))>0){    
    /*copiando os índices de volta, ordenados.
    termina quando pelo menos um dos vetores já teve seus elementos copiados para ind_espec.*/
    while((i < quant_esq) && (j < quant_dir)){
        if(Comparacao_Elementos(poi, E[i], D[j], atribid/*, "M_mem_access.csv"*/) <= 0){
            log_mem_access("M_mem_access.csv", clock(), E[i]);
            ind_espec[k] = E[i];
            log_mem_access("M_mem_access.csv", clock(), ind_espec[k]);
            i++;
        }
        else{
            log_mem_access("M_mem_access.csv", clock(), D[j]);
            ind_espec[k] = D[j];
            log_mem_access("M_mem_access.csv", clock(), ind_espec[k]);
            j++;
        }
        k++;
    }

    //copiando os possíveis elementos que restaram em um dos vetores temporários.
    while(i < quant_esq){
        log_mem_access("M_mem_access.csv", clock(), E[i]);
        ind_espec[k] = E[i];
        log_mem_access("M_mem_access.csv", clock(), ind_espec[k]);
        i++;
        k++;
    }
    while (j < quant_dir){
        log_mem_access("M_mem_access.csv", clock(), D[j]);
        ind_espec[k] = D[j];
        log_mem_access("M_mem_access.csv", clock(), ind_espec[k]);
        j++;
        k++;
    }
    }

    log_mem_access("M_mem_access.csv", clock(), E);
    free(E);

    log_mem_access("M_mem_access.csv", clock(), D);
    free(D);
}

void MergeSort_rec(OrdInd_ptr poi, int* ind_espec, int esq, int dir, int atribid){
    if(esq < dir){
        int meio = esq + (dir-esq)/2; //evita overflow. 
    
        //particionando a primeira metade.
        MergeSort_rec(poi, ind_espec, esq, meio, atribid);
        //particionando a segunda metade.
        MergeSort_rec(poi, ind_espec, meio+1, dir, atribid);

        //junta tudo ordenando.
        Merge(ind_espec, esq, meio, dir, poi, atribid);
    }
}

int OrdenaIndice_MergeSort(OrdInd_ptr poi, int atribid){
    checar_codigo_atributo(atribid, poi->num_atributos);

    int* ind_espec = poi->Indices[atribid];
    int n = poi->num_registros;
    
    MergeSort_rec(poi,ind_espec,0,n-1,atribid);

    return 0;
}

int ImprimeOrdenadoIndice (OrdInd_ptr poi, int atribid/*, char* file_mem_access*/){
    checar_codigo_atributo(atribid, poi->num_atributos);
    checar_alocacao(poi->Indices, "Vetor de Indices para cada atributo");
    checar_alocacao(poi->Indices[atribid], "Vetor de Indices para atributo especifico");

    int* ind_espec = poi->Indices[atribid];

    for(int i = 0; i!=6; i++){
        printf("%s", poi->Cabecalho[i]);
    }

    int ind = 0;
    for(int i = 0; i < poi->num_registros; i++){
        ind = ind_espec[i];
        
        /*log_mem_access(file_mem_access, clock(), ind_espec[i]);

        log_mem_access(file_mem_access, clock(), poi->Nomes[ind]);
        log_mem_access(file_mem_access, clock(), poi->CPFs[ind]);
        log_mem_access(file_mem_access, clock(), poi->Ends[ind]);
        log_mem_access(file_mem_access, clock(), poi->Outros[ind]);*/

        printf("%s,%s,%s\n", poi->Nomes[ind], poi->CPFs[ind], poi->Ends[ind]/*, poi->Outros[ind]*/);
    }

    return 0;
}


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

    ord_ptr->Indices = NULL;

    return ord_ptr;
};

//Destrutor para liberar a memória.
int Destroi (OrdInd_ptr poi){
    free(poi->Nomes);
    free(poi->CPFs);
    free(poi->Ends);
    free(poi->Indices);
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
    return poi->num_colunas;
};

char* NomeAtributo(OrdInd_ptr poi, int pos, char * nome){
    char* nome_colunas = {"Nome", "CPF", "Endereco", "Outros"};
    //se a posicao é inválida
    checar_posicao(pos, poi->num_colunas);
    //Outros e Default para os demais atributos do aarquivo.
    if(pos>=3) nome = nome_colunas[3];
    else nome = nome_colunas[pos];
    return nome;
};

int CriaIndice (OrdInd_ptr poi, int atribid){
    //se a posicao e invalida.
    checar_posicao(atribid, poi->num_colunas);

    //se  Indices ainda esta no estagio inicial de nao apontar para
    //nenhuma posicao valida da memoria.
    if(poi->Indices==NULL){
        //aloca e inicializa.
        poi->Indices = (int**) malloc(poi->num_colunas*sizeof(int*));
        checar_alocacao(poi->Indices, "Indices para cada Atributo");

        for(int i=0; i<poi->num_colunas; i++){
            poi->Indices[i] = NULL;
        }
    }
    
    //se o vetor de indices daquele atributo especifico já aponta para alguma
    //posicao da memoria, é liberado para ser realocado.
    if(poi->Indices[atribid]!=NULL){
        free(poi->Indices[atribid]);
    }

    //alocacao para o vetor de indices de um atributo especifico.
    poi->Indices[atribid] = (int *) malloc(poi->num_linhas*sizeof(int));
    checar_alocacao(poi->Indices[atribid], "Indices de um atributo especifico");

    //inicialização dos indices de um atributo especifico.
    for(int i=0; i<poi->num_linhas; i++){
        poi->Indices[atribid] [i] = i;
    }
};

int Comparacao_Elementos(OrdInd_ptr poi, int thanku, int next, int atribid){

    checar_atributo(atribid);

    //Para 'strings' e inteiros, o modo como a comparação é feita deve ser distinta.
    switch (atribid)
    {
    case 0:
        return strcmp(poi->Nomes[thanku], poi->Nomes[next]);
        break;
    case 1:
        return (poi->CPFs[thanku] - poi->CPFs[next]);
        break;
    case 2:
        return strcmp(poi->Ends[thanku], poi->Ends[next]);
        break;
    default:
        break;
    }
};

int Particao_QS(int esq, int dir, OrdInd_ptr poi, int atribid){
    //indices relacionados ao atributo especifico.
    int* inds_espec = poi->Indices[atribid];
    //elemento do meio é o pivo.
    int pivo = inds_espec[(esq+dir)/2];
    int i = esq;
    int j = dir;

    int aux = 0;

    while(i <= j){
        //
        while(Comparacao_Elementos(poi, inds_espec[i], pivo, atribid) < 0) i++;
        while(Comparacao_Elementos(poi, inds_espec[j], pivo, atribid) > 0) j--;

        //quando uma troca é necessária
        if(i <= j){
            aux = inds_espec[i];
            inds_espec[i] = inds_espec[j];
            inds_espec[j] = aux;
            i++;
            j--;
        }
    }

    //ponto de particao é retornado.
    return i;

};

int QuickSort_rec(OrdInd_ptr poi, int esq, int dir, int atribid){
    if(esq < dir){
        //particiona e retorna o indice de separacao.
        int meio = Particao_QS(esq,dir,poi,atribid);

        //Ordana recursivamente as metades.
        QuickSort_rec(poi, esq, meio-1, atribid);
        QuickSort_rec(poi,meio,dir,atribid);
    }
};

int OrdenaIndice_QuickSort(OrdInd_ptr poi, int atribid){
    //checa de o vetor de indices já está alocado e inicilizado.
    checar_alocacao(poi->Indices, "Vetor de Indices para cada atributo nao alocado.");
    checar_alocacao(poi->Indices[atribid], "Vetor de Indices para atributo especifico nao alocado.");

    //começa a ordenacao dos dados.
    QuickSort_rec(poi, 0, poi->num_linhas-1, atribid);
    
    return 0;
};

int OrdenaIndice_Selecao(OrdInd_ptr poi, int atribid){
    checar_atributo(atribid);

    //obtendo o vetor de indices de um atributo especifico.
    int* ind_espec = poi->Indices[atribid];
    int aux = 0;

    //percorrendo do fim para o inicio
    for(int i = poi->num_linhas - 1; i>0; i--){
        int max_elem = 0;
        
        //percorrendo o subetor nao ordenado.
        for(int j = 0; j<i; j++){
            if(Comparacao_Elementos(poi,ind_espec[j],ind_espec[max_elem],atribid)>0){
                max_elem = j;
            }
        }

        //troca o maior elemento com o ultimo.
        if(max_elem!=i){
            aux = ind_espec[i];
            ind_espec[i] = ind_espec[max_elem];
            ind_espec[max_elem] = aux;
        }
    }

    return 0;
};

void Merge(int* ind_espec,int esq,int meio,int dir,OrdInd_ptr poi,int atribid){
    //Mede a quantidade de elementos em cada metade.
    int quant_esq = (meio - esq) + 1;
    int quant_dir = meio + dir;

    //criando e alocando vetores temporarios.
    int* E = malloc(quant_esq * sizeof(int));
    checar_alocacao(E, "Merge - Vetor temporario esquerda");
    int* D = malloc(quant_dir * sizeof(int));
    checar_alocacao(D, "Merge - Vetor Temporario direita");

    //inicializando os vetores temporarios com os indices do atributo especifico.
    for(int i = 0; i < quant_esq; i++){
        E[i] = ind_espec[esq + i];
    }
    for(int j = 0; j < quant_dir; j++){
        D[j] = ind_espec[meio + 1 + j];
    }

    int i = 0, j = 0, k = esq;

    //copiando os índices de volta ordenados.
    //termina quando pelo meno um dos vetores já teve seus elementos copiados para ind_espec. 
    while((i < quant_esq) && (j < quant_dir)){
        if(Comparacao_Elementos(poi, E[i], D[j], atribid) <= 0){
            ind_espec[k] = E[i];
            i++;
     
        }
        else{
            ind_espec[k] = D[i];
            j++;
        }
        k++;
    }

    //copiando os possíveis elementos que restaram em um dos vetores temporários.
    while(i < quant_esq){
        ind_espec[k] = E[i];
        i++;
        k++;
    }
    while (j < quant_dir){
        ind_espec[k] = D[j];
        j++;
        k++;
    }

    free(E);
    free(D);
};

void MergeSort_rec(OrdInd_ptr poi, int* ind_espec, int esq, int dir, int atribid){
    if(esq < dir){
        int meio = esq + (dir-esq)/2;

        //ordenando a primeira metade
        MergeSort_rec(poi, ind_espec, esq, meio, atribid);
        //ordenando a segunda metade
        MergeSort_rec(poi, ind_espec, meio+1, dir, atribid);

        Merge(ind_espec, esq, meio, dir, poi, atribid);
    }
};

int OrdenaIndice_MergeSort(OrdInd_ptr poi, int atribid){
    checar_atributo(atribid);

    int* ind_espec = poi->Indices[atribid];
    int n = poi->num_linhas;
    
    MergeSort_rec(poi,ind_espec,0,n-1,atribid);
};

int ImprimeOrdenadoIndice (OrdInd_ptr poi, int atribid){
    checar_atributo(atribid);
    checar_alocacao(poi->Indices, "Vetor de Indices para cada atributo");
    checar_alocacao(poi->Indices[atribid], "Vetor de Indices para atributo especifico");

    int* ind_espec = poi->Indices[atribid];

    char* atributo = NULL;
    NomeAtributo(poi,atribid,atributo);
    printf("Dados ordenados pelo atributo %s", atributo);
    printf("%s, %s, %s", "Nome", "CPF", "Endereco");

    int ind = 0;
    for(int i = 0; i < poi->num_linhas; i++){
        ind = ind_espec[i];
        printf("%s, %d, %s\n", poi->Nomes[ind], poi->CPFs[ind], poi->Ends[ind]);
    }

    return 0;
};
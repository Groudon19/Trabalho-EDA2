#include "arvoreB.h"

ArvoreB* criaArvoreB(int ordem){
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNoB(a);

    return a;
}

NoB* criaNoB(ArvoreB* arvore){
    int max = arvore->ordem * 2;
    NoB* no = malloc(sizeof(NoB));

    no->pai = NULL;

    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(NoB) * (max + 2)); // não teria que ser um sizeof(NoB*)? n sei
    no->total_chaves = 0;

    for(int i = 0; i < max + 2; i++){
        no->filhos[i] = NULL;
    }

    return no;
}

void percorreArvoreB(NoB* no, void (visita)(int chave)){
    if(no != NULL) {
        for (int i = 0; i < no->total_chaves; i++){
            percorreArvoreB(no->filhos[i], visita);

            visita(no->chaves[i]);
        }

        percorreArvoreB(no->filhos[no->total_chaves], visita);
    }
}

int loclizaChave(ArvoreB* arvore, int chave){
    NoB*  no = arvore->raiz;

    while (no != NULL){
        int i = pesquisaBinaria(no, chave);

        if (i < no->total_chaves && no->chaves[i] == chave){
            return 1; // encontrou
        } else {
            no = no->filhos[i];
        }
    }
    return 0; // não encontrou
}

int pesquisaBinaria(NoB* no, int chave){
    int inicio = 0, fim = no->total_chaves - 1, meio;
    while(inicio <= fim){
        meio = (inicio + fim)/2;
        if(no->chaves[meio] == chave){
            return meio; // encontrou
        } else if (no->chaves[meio] > chave){
            fim = meio -1;
        } else {
            inicio = meio + 1;
        }
    }
    return inicio; // não encontrou
}

NoB* localizaNoB(ArvoreB* arvore, int chave){
    NoB* no = arvore->raiz;

    while(no != NULL){
        int i = pesquisaBinaria(no, chave);

        if (no->filhos[i] == NULL)
            return no; // encontroub nó
        else
            no = no->filhos[i];
    }

    return NULL; // não encontrou nenhum nó
}

void adicionaChaveNo(NoB* no, NoB* direita, int chave){
    int i = pesquisaBinaria(no, chave);

    for (int j = no->total_chaves - 1; j >= i; j--){
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
    }

    no->chaves[i] = chave;
    no->filhos[i + 1] = direita;

    no-> total_chaves++;
}

int transbordo(ArvoreB* arvore, NoB* no){
    return no->total_chaves > arvore->ordem * 2;
}

NoB* divideNoB(ArvoreB* arvore, NoB* no){
    int meio = no->total_chaves / 2;
    NoB* novo = criaNoB(arvore);
    novo->pai = no->pai;

    for (int i = meio + 1; i < no->total_chaves; i++){
        novo->filhos[novo->total_chaves] = no->filhos[i];
        novo->chaves[novo->total_chaves] = no->chaves[i];
        if(novo->filhos[novo->total_chaves] != NULL)
            novo->filhos[novo->total_chaves]->pai = novo;
        novo->total_chaves++;
    }

    novo->filhos[novo->total_chaves] = no->filhos[no->total_chaves];
    if(novo->filhos[novo->total_chaves] != NULL)
        novo->filhos[novo->total_chaves]->pai = novo;
    no->total_chaves = meio;
    return novo;
}

void adicionaChave(ArvoreB* arvore, int chave){
    NoB* no = localizaNoB(arvore, chave);

    adicionaChaveRecursivo(arvore, no, NULL, chave);
}

void adicionaChaveRecursivo(ArvoreB* arvore, NoB* no, NoB* novo, int chave){
    adicionaChaveNo(no, novo, chave);
    if (transbordo(arvore, no)){
        int promovido = no->chaves[arvore->ordem];
        NoB* novo = divideNoB(arvore, no);

        if(no->pai == NULL){
            NoB* raiz = criaNoB(arvore);
            raiz->filhos[0] = no;
            adicionaChaveNo(raiz, novo, promovido);// diferente do slide

            no->pai = raiz;
            novo->pai = raiz;
            arvore->raiz = raiz;
        } else {
            adicionaChaveRecursivo(arvore, no->pai, novo, promovido);
        }
    }
}
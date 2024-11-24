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
    no->filhos = malloc(sizeof(NoB*) * (max + 2)); // não teria que ser um sizeof(NoB*)? n sei, aparentemente n
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

void imprime(int chave){
    printf("%d ", chave);
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

void removeChaveFolha(NoB* no, int chave){
    int i = pesquisaBinaria(no, chave);

    for(int j = i + 1; j < no->total_chaves; j++){
        no->chaves[j - 1] = no->chaves[j];
    }
    
    no->chaves[no->total_chaves-1] = 0;
    no->total_chaves--;
}

void removeChave(ArvoreB* arvore, int chave){
    NoB* raiz = arvore->raiz;
    if(raiz == NULL)
        printf("A arvore esta vazia\n");
    
    removeChaveRecursivo(arvore, raiz, chave);

    if(raiz->total_chaves == 0){
        if(raiz->filhos[0] != NULL){
            arvore->raiz = raiz->filhos[0];
            free(raiz);
        }else{
            arvore->raiz = NULL;
        }
    }
}

void removeChaveRecursivo(ArvoreB* arvore, NoB* no, int chave){
    int i = pesquisaBinaria(no, chave);
    printf("\npercorreu!\n");
    
    if(no->filhos[0] == NULL){
        if(i < no->total_chaves && no->chaves[i] == chave){
            printf("\nfolha\n");
            removeChaveFolha(no, chave);
        }   else{
                printf("Chave nao encontrada!\n");  
            }
        return;
    } 
    //nao remove os nos folha?
    //caso 2: nó interno
    if(i < no->total_chaves && no->chaves[i] == chave){
        printf("caso 2:\n");
        NoB* filhoEsq = no->filhos[i];
        NoB* filhoDir = no->filhos[i+1];    
        if(filhoEsq->total_chaves >= arvore->ordem){
            //predecessor 2a
            int predecessor = encontraPredecessor(filhoEsq);
            printf("Predecessor: %i\n", predecessor);
            no->chaves[i] = predecessor;
            removeChaveRecursivo(arvore, filhoEsq, predecessor);
        }else if(filhoDir->total_chaves >= arvore->ordem){
            //sucessor 2b
            int sucessor =  encontraSucessor(filhoDir);
            printf("Sucessor: %i\n", sucessor);
            no->chaves[i] = sucessor;
            removeChaveRecursivo(arvore, filhoDir, sucessor);
        }else{
            //fusao dos nós
            fundirNos(arvore, no, i);
            
            printf("Fundiu?\n");
        }
        return;
    }

    //caso 3: chave nao esta no Nó
    NoB* filho = no->filhos[i];
    if(filho->total_chaves == (arvore->ordem) - 1){
        printf("Caso 3:\n");
        NoB* irmaoEsq = (i > 0) ? no->filhos[i-1] : NULL;
        NoB* irmaoDir = (i < no->total_chaves) ? no->filhos[i+1] : NULL;
        
        // imprimeDetalhesNo(no, 0);
        // imprimeDetalhesNo(filho, 0);
        // imprimeDetalhesNo(irmaoEsq, 0);
        // printf("irmao dir: \n");
        // imprimeDetalhesNo(irmaoDir, 0);
        if (irmaoEsq == NULL && irmaoDir == NULL) {
            printf("Erro: Nenhum irmão disponível para fusão.\n");
            exit(EXIT_FAILURE);
        }
        if(irmaoEsq != NULL && irmaoEsq->total_chaves >= arvore->ordem){
            //redistribuir do irmao esquerdo 
            //printf("Caso 3a\n");
            redistribuirEsquerda(no, filho, irmaoEsq, i);
            printf("redistribuiu!\n");
        } else if(irmaoDir != NULL && irmaoDir->total_chaves >= arvore->ordem && irmaoDir){
            //printf("Caso 3ab\n");
            redistribuirDireita(no, filho, irmaoDir, i);
        } else{
            if(irmaoEsq != NULL){
                printf("Caso 3b\n");
                fundirNos(arvore, no, i-1);
                filho = irmaoEsq;
            }else{
                printf("Caso 3bb\n");
                fundirNos(arvore, no, i);
            }
        }
        
    }

    printf("desceu nivel!\n");
    removeChaveRecursivo(arvore, filho, chave);
}

int encontraPredecessor(NoB* no){
    if (no == NULL || no->total_chaves == 0) {
        printf("Erro: Nó vazio ao buscar predecessor.\n");
        exit(EXIT_FAILURE);
    }

    while(no->filhos[no->total_chaves] != NULL){
        no = no->filhos[no->total_chaves];
    }
    return no->chaves[no->total_chaves-1];
}

int encontraSucessor(NoB* no){
    while(no->filhos[0] != NULL){
        no = no->filhos[0];
    }
    return no->chaves[0];
}

void fundirNos(ArvoreB* tree, NoB* no, int indice) {
    if (!tree || !no || indice < 0 || indice >= no->total_chaves) {
        printf("Erro: Parâmetros inválidos.\n");
        return;
    }
    

    NoB* filhoEsq = no->filhos[indice];
    NoB* filhoDir = no->filhos[indice + 1];

    if (!filhoEsq || !filhoDir) {
        printf("Erro: Filhos ausentes no índice %d.\n", indice);
        return;
    }

    // Inserir chave do nó atual no filho esquerdo
    filhoEsq->chaves[filhoEsq->total_chaves] = no->chaves[indice];

    // Copiar chaves e filhos do filho direito para o filho esquerdo
    for (int i = 0; i < filhoDir->total_chaves; i++) {
        filhoEsq->chaves[filhoEsq->total_chaves + 1 + i] = filhoDir->chaves[i];
        filhoEsq->filhos[filhoEsq->total_chaves + 1 + i] = filhoDir->filhos[i];
    }

    // Copiar último ponteiro de filhos
    filhoEsq->filhos[filhoEsq->total_chaves + 1 + filhoDir->total_chaves] = filhoDir->filhos[filhoDir->total_chaves];

    // Atualizar total de chaves no filho esquerdo
    filhoEsq->total_chaves += filhoDir->total_chaves + 1;

    // Ajustar o nó pai
    for (int i = indice + 1; i < no->total_chaves; i++) {
        no->chaves[i - 1] = no->chaves[i];
        no->filhos[i] = no->filhos[i + 1];
    }

    no->total_chaves--;

    // Liberar memória do filho direito
    free(filhoDir);

    // Se o nó pai ficou vazio e é a raiz
    if (no->total_chaves == 0 && no->pai == NULL) {
        tree->raiz = filhoEsq;
        filhoEsq->pai = NULL;
        free(no);
    }
}


void redistribuirEsquerda(NoB* pai, NoB* filho, NoB* irmao, int indice) {
    // Empurrar as chaves e os filhos do nó atual para a direita
    for (int i = filho->total_chaves; i > 0; i--) {
        filho->chaves[i] = filho->chaves[i - 1];
        filho->filhos[i + 1] = filho->filhos[i];
    }

    // Atualizar o filho mais à esquerda
    filho->filhos[1] = filho->filhos[0];
    filho->filhos[0] = irmao->filhos[irmao->total_chaves];
    if (filho->filhos[0] != NULL) {
        filho->filhos[0]->pai = filho;
    }

    // Transferir a chave do pai para o nó filho
    filho->chaves[0] = pai->chaves[indice - 1];

    // Transferir a última chave do irmão para o pai
    pai->chaves[indice - 1] = irmao->chaves[irmao->total_chaves - 1];

    // Atualizar contadores de chaves
    filho->total_chaves++;
    irmao->total_chaves--;
}



void redistribuirDireita(NoB* pai, NoB* filho, NoB* irmao, int indice) {
    filho->chaves[filho->total_chaves] = pai->chaves[indice];
    filho->filhos[filho->total_chaves + 1] = irmao->filhos[0];

    pai->chaves[indice] = irmao->chaves[0];

    for (int i = 1; i < irmao->total_chaves; i++) {
        irmao->chaves[i - 1] = irmao->chaves[i];
        irmao->filhos[i - 1] = irmao->filhos[i];
    }

    irmao->filhos[irmao->total_chaves - 1] = irmao->filhos[irmao->total_chaves];

    irmao->total_chaves--;
    filho->total_chaves++;
}





void imprimeDetalhesNo(NoB* no, int nivel) {
    if (no == NULL) {
        return;
    }

    // Imprimir as chaves do nó
    printf("Nível %d: Nó com %d chave(s): [", nivel, no->total_chaves);
    for (int i = 0; i < no->total_chaves; i++) {
        printf("%d", no->chaves[i]);
        if (i < no->total_chaves - 1)
            printf(", ");
    }
    printf("]\n");

    

    // Recursivamente imprimir os filhos
    for (int i = 0; i <= no->total_chaves; i++) {
        imprimeDetalhesNo(no->filhos[i], nivel + 1);
    }
}

// Função para imprimir a partir da raiz
void imprimeDetalhesArvore(ArvoreB* arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("A árvore está vazia.\n");
        return;
    }

    printf("------ Detalhes da Árvore ------\n");
    imprimeDetalhesNo(arvore->raiz, 0);
    printf("--------------------------------\n");
}

// verifica a existencia do valor no vetor
int existe_no_vetor(int* vet, int tam, int valor){

    for(int i = 0; i < tam; i++){
        if(vet[i] == valor){
            return 1;
        }
    }
    return 0;
}


#include "avl.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

int altura(No*);

int fb(No*);

No* rsd(Arvore*, No*);
No* rse(Arvore*, No*);
No* rdd(Arvore*, No*);
No* rde(Arvore*, No*);

int maximo(int a, int b) {
    return a > b ? a : b;
}

void destruir_no(No* no) {
    if (no == NULL) {
        return;
    }

    // Recursivamente destruir os filhos
    destruir_no(no->esquerda);
    destruir_no(no->direita);

    // Liberar o nó atual
    free(no);
}

void destruir_avl(Arvore* arvore) {
    if (arvore == NULL) {
        return;
    }

    // Destruir a árvore começando pela raiz
    destruir_no(arvore->raiz);

    // Liberar a estrutura da árvore em si
    free(arvore);
}


Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
  
    return arvore;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

void adicionar(Arvore* arvore, int valor, int* contadores) {
    No* no = arvore->raiz;

    while (no != NULL) {
        contadores[0]++; // cada comparacao de chave é contabilizada
        if (valor > no->valor) {
            if (no->direita != NULL) {
                no = no->direita;
            } else {
                break;
            }
        } else {
            if (no->esquerda != NULL) {
                no = no->esquerda;
            } else {
                break;
            }
        }
    }

    printf("Adicionando %d\n", valor);
    No* novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->pai = no;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1;

    if (no == NULL) {    
        arvore->raiz = novo;
    } else {
        if (valor > no->valor) {
            no->direita = novo;
        } else {
            no->esquerda = novo;
        }
        
        balanceamento(arvore, no, contadores);
    }
}


void remover(Arvore* arvore, int valor, int* contador_rem){

    int filho_esq;
    int filho_dir;

    if(arvore->raiz == NULL){
        printf("Arvore vazia!\n");
        return;
    }

    No* no = arvore->raiz; 
    No* pai = NULL;  

    //inicio da busca pelo no a ser removido
    while (no != NULL && no->valor != valor) {
        contador_rem[0]++; // cada iteracao de busca é contabilizada
        pai = no;
        if (valor > no->valor) {
            no = no->direita;    
        } else {
            no = no->esquerda;
        }
    }
    
    //ve se achou ou nao o no procurado
    if(no == NULL){
        printf("A chave nao foi encontrada na arvore!\n");
        return;
    }

    // caso 1 de remocao: o no a ser removido eh uma folha
    if(no->esquerda == NULL && no->direita == NULL){
        contador_rem[0]++; // Verificação se o nó tem filhos (neste caso, não tem)
        if(pai == NULL){ // o no que vai ser removido eh a raiz
            arvore->raiz = NULL;
        }else if(pai->esquerda == no){ // remover o no da esquerda do pai
            pai->esquerda = NULL;
        }else{  // remover o no da direita do pai
            pai->direita = NULL;
        }
        free(no);

    // caso 2 de remocao: o no a ser removido tem apenas um filho    
    }else if ((no->esquerda == NULL && no->direita != NULL)||( no->direita == NULL && no->esquerda != NULL)){
        contador_rem[0]++; // Verificação se o nó tem filhos (neste caso, um filho)
        No* filho;
        // verificando onde que esta o unico no filho
        if(no->esquerda != NULL){
            filho = no->esquerda;
        }else{
            filho = no->direita;
        }

        if(pai == NULL){ // o no removido era a raiz
            arvore->raiz = filho;
        } else if ( pai->esquerda == no){
            pai->esquerda = filho;
        }else{
            pai->direita = filho;
        }

        filho->pai = pai;
        contador_rem[0]++; // Atualização do ponteiro do pai para o filho
        free(no);

    // caso 3 de remocao: o no a ser removido tem 2 filhos
    }else{
        contador_rem[0]++; // Verificação se o nó tem filhos (neste caso, dois filhos)

        // substituir o no pelo sucessor em ordem
        No* sucessor = no->direita;
        while (sucessor->esquerda != NULL){
            sucessor = sucessor->esquerda;
        }

        //trocar o atual pelo sucessor
        no->valor = sucessor->valor;

        // remover o sucessor que tem um filho
        if(sucessor->pai->esquerda == sucessor){
            sucessor->pai->esquerda = sucessor->direita;
        }else{
            sucessor->pai->direita = sucessor->direita;
        } 
        
        if(sucessor->direita != NULL){
            sucessor->direita->pai = sucessor->pai;
        }

        contador_rem[0]++; // Atualização do ponteiro do pai para o filho
        free(sucessor);

    }

    // rebalancear a arvore toda
    No* atual;
    if(pai != NULL){
        atual = pai;
    }else{
        atual = arvore->raiz;
    }

    while(atual != NULL){
        atual->altura = maximo(altura(atual->esquerda), altura(atual->direita) + 1);
        contador_rem[0]++; // Cada atualização de altura é contabilizada
        int fator = fb(atual);

        // checar e aplicar rotacoes
        if(fator > 1){ // desbalanceou na esquerda
            
            if(fb(atual->esquerda) >= 0 ){
                rsd(arvore, atual);
                contador_rem[0]++; // Contabiliza a rotação
            }else{
                rdd(arvore, atual);
                contador_rem[0]++; // Contabiliza a rotação

            }

        }else if(fator < -1){ // desbalanceou para direita
            if(fb(atual->direita) <= 0){
                rse(arvore, atual);
                contador_rem[0]++; // Contabiliza a rotação            
            }else{
                rde(arvore, atual);
                contador_rem[0]++; // Contabiliza a rotação
            }
        }

        // ir subindo na arvore para rebalancea-la totalmente
        atual = atual->pai;
    }

}





No* localizar(No* no, int valor) {
    while (no != NULL) {
        if (no->valor == valor) {
            return no;
        }
        
        no = valor < no->valor ? no->esquerda : no->direita;
    }

    return NULL;
}

void percorrer(No* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrer(no->esquerda,callback);
        callback(no->valor);
        percorrer(no->direita,callback);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

void balanceamento(Arvore* arvore, No* no, int* contadores) {
    while (no != NULL) {
        no->altura = maximo(altura(no->esquerda), altura(no->direita)) + 1;
        contadores[0]++; // cada atualização da altura é contabilizada
        int fator = fb(no);

        if (fator > 1) { //árvore mais pesada para esquerda
            //rotação para a direita
            if (fb(no->esquerda) > 0) {
                printf("RSD(%d)\n",no->valor);
                rsd(arvore, no); //rotação simples a direita, pois o FB do filho tem sinal igual
                contadores[0]++;
            } else {
                printf("RDD(%d)\n",no->valor);
                rdd(arvore, no); //rotação dupla a direita, pois o FB do filho tem sinal diferente
                contadores[0]++;
            }
        } else if (fator < -1) { //árvore mais pesada para a direita
            //rotação para a esquerda
            if (fb(no->direita) < 0) {
                printf("RSE(%d)\n",no->valor);
                rse(arvore, no); //rotação simples a esquerda, pois o FB do filho tem sinal igual
                contadores[0]++;
            } else {
                printf("RDE(%d)\n",no->valor);
                rde(arvore, no); //rotação dupla a esquerda, pois o FB do filho tem sinal diferente
                contadores[0]++;
            }
        }

        no = no->pai; 
    }
}

int altura(No* no){
    return no != NULL ? no->altura : 0;
}

int fb(No* no) {
    int esquerda = 0,direita = 0;
  
    if (no->esquerda != NULL) {
        esquerda = no->esquerda->altura;
    }

    if (no->direita != NULL) {
        direita = no->direita->altura;
    }
  
    return esquerda - direita;
}

No* rse(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* direita = no->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    no->altura = maximo(altura(no->esquerda), altura(no->direita)) + 1;
    direita->altura = maximo(altura(direita->esquerda), altura(direita->direita)) + 1;

    return direita;
}

No* rsd(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* esquerda = no->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    no->altura = maximo(altura(no->esquerda), altura(no->direita)) + 1;
    esquerda->altura = maximo(altura(esquerda->esquerda), altura(esquerda->direita)) + 1;

    return esquerda;
}

No* rde(Arvore* arvore, No* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

No* rdd(Arvore* arvore, No* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}

void imprimir_por_altura(Arvore* arvore) {

    if (arvore == NULL || arvore->raiz == NULL) {
        printf("A árvore está vazia.\n");
        return;
    }
    
    int num = 10000; // ajustar conforme o numero de testes cresce
    
    No** fila = malloc(sizeof(No*) * num); // fila para ate num numeros
    int inicio = 0, fim = 0; // indices para fim e inicio da fila
    
    fila[fim++] = arvore->raiz;
    fila[fim++] = NULL; // marcador
    
    printf("\n--- EXIBICAO DA AVL ---\n");

    int nivel_atual = 0;
    printf("Nível %d: ", nivel_atual); // printa a raiz no nivel 0
    
    while (inicio < fim) {
        No* no_atual = fila[inicio++];

        if (no_atual == NULL) { // mudanca de nivel para impressao
            if (inicio < fim) {
                fila[fim++] = NULL; // marcador de nivel
                nivel_atual++;
                printf("\nNível %d: ", nivel_atual);
            }
        } else {
            // print do valor do no e o fator de balanceamento
            printf(GREEN "%d" RESET "(fb=%d) ", no_atual->valor, fb(no_atual));

            // add os filhos do no atual na fila
            if (no_atual->esquerda != NULL) fila[fim++] = no_atual->esquerda;
            if (no_atual->direita != NULL) fila[fim++] = no_atual->direita;
        }
    }

    printf("\n");
    free(fila);

}
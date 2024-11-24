#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
    int altura;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

No* rsd(Arvore*, No*);
No* rse(Arvore*, No*);
No* rdd(Arvore*, No*);
No* rde(Arvore*, No*);
No* localizar(No* no, int valor);
Arvore* criar();
int maximo(int a, int b);
int vazia(Arvore* arvore);
void remover(Arvore* arvore, int valor, int* contador_rem);
void adicionar(Arvore* arvore, int valor, int* contadores);
void percorrer(No* no, void (*callback)(int));
void visitar(int valor); 
void balanceamento(Arvore* arvore, No* no, int* contadores);
int altura(No* no);
int fb(No* no);
void imprimir_por_altura(Arvore* arvore);
void destruir_avl(Arvore* arvore);
void destruir_no(No* no);
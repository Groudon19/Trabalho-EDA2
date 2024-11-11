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


//demais funcoes
/*
void balanceamento(Arvore*, No*);
int altura(No*);
int fb(No*);
*/
No* rsd(Arvore*, No*);
No* rse(Arvore*, No*);
No* rdd(Arvore*, No*);
No* rde(Arvore*, No*);
No* localizar(No* no, int valor);
Arvore* criar();
int maximo(int a, int b);
int vazia(Arvore* arvore);
void adicionar(Arvore* arvore, int valor);
void percorrer(No* no, void (*callback)(int));
void visitar(int valor); 
void balanceamento(Arvore* arvore, No* no);
int altura(No* no);
int fb(No* no);
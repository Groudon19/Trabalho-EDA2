#ifndef FUNCAO_H
#define FUNCAO_H

#include <stdlib.h>
#include <stdio.h>

typedef enum { Vermelho, Preto } Cor;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    Cor cor;
    int valor;
} No;

typedef struct arvore {
    No* raiz;
    No* nulo; 
} Arvore;

// Declaração de funções
Arvore* criar();
int vazia(Arvore* arvore);
No* adicionar(Arvore* arvore, int valor);
void percorrerProfundidadeInOrder(Arvore* arvore, No* no, void (*callback)(int));
void visitar(int valor);
void remover(Arvore* arvore, int valor);
No* criarNo(Arvore* arvore, No* pai, int valor);
void balancear(Arvore* arvore, No* no);
void rotacionarEsquerda(Arvore* arvore, No* no);
void rotacionarDireita(Arvore* arvore, No* no);

#endif
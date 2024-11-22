#include <stdio.h>
#include <stdlib.h>

typedef struct noB {
    int total_chaves;
    int* chaves;
    struct noB** filhos;
    struct noB* pai;
} NoB;

typedef struct arvoreB {
    NoB* raiz;
    int ordem;
} ArvoreB;

ArvoreB* criaArvoreB(int ordem);
NoB* criaNoB(ArvoreB* arvore);
void percorreArvoreB(NoB* no, void (visita)(int chave));
void imprime(int chave);
int loclizaChave(ArvoreB* arvore, int chave);
int pesquisaBinaria(NoB* no, int chave);
NoB* localizaNoB(ArvoreB* arvore, int chave);
void adicionaChaveNo(NoB* no, NoB* direita, int chave);
int transbordo(ArvoreB* arvore, NoB* no);
NoB* divideNoB(ArvoreB* arvore, NoB* no);
void adicionaChave(ArvoreB* arvore, int chave);
void adicionaChaveRecursivo(ArvoreB* arvore, NoB* no, NoB* novo, int chave);
void removeChave(ArvoreB* arvore, int chave);
void removeChaveRecursivo(ArvoreB* arvore, NoB* no, int chave);
int encontraPredecessor(NoB* no);
int encontraSucessor(NoB* no);
void fundirNos(ArvoreB* arvore, NoB* no, int indice);
void redistribuirEsquerda(NoB* pai, NoB* filho, NoB* irmao, int indice);
void redistribuirDireita(NoB* pai, NoB* filho, NoB* irmao, int indice);
void imprimeDetalhesNo(NoB* no, int nivel);
void imprimeDetalhesArvore(ArvoreB* arvore);
int existe_no_vetor(int* vet, int tam, int valor);


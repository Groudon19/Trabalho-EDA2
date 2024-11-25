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
NoB* localizaNoB(ArvoreB* arvore, int chave, int* contadores);
void adicionaChaveNo(NoB* no, NoB* direita, int chave, int* contadores);
int transbordo(ArvoreB* arvore, NoB* no);
NoB* divideNoB(ArvoreB* arvore, NoB* no, int* contadores);
void adicionaChave(ArvoreB* arvore, int chave, int* contadores);
void adicionaChaveRecursivo(ArvoreB* arvore, NoB* no, NoB* novo, int chave, int* contadores);
void removeChaveFolha(NoB* no, int chave, int* contadores);
void removeChave(ArvoreB* arvore, int chave, int* contadores);
void removeChaveRecursivo(ArvoreB* arvore, NoB* no, int chave, int* contadores);
int encontraPredecessor(NoB* no, int* contadores);
int encontraSucessor(NoB* no, int* contadores);
void fundirNos(ArvoreB* arvore, NoB* no, int indice, int* contadores);
void redistribuirEsquerda(NoB* pai, NoB* filho, NoB* irmao, int indice, int* contadores);
void redistribuirDireita(NoB* pai, NoB* filho, NoB* irmao, int indice, int* contadores);
void imprimeDetalhesNo(NoB* no, int nivel);
void imprimeDetalhesArvore(ArvoreB* arvore);
int existe_no_vetor(int* vet, int tam, int valor);
void tira_vetor(int* vet, int* tam, int valor);



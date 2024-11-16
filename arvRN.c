#include <stdlib.h>
#include <stdio.h>

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    Cor cor;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
    struct no* nulo; 
} Arvore;

No* criarNo(Arvore*, No*, int);
void balancear(Arvore*, No*);
void rotacionarEsquerda(Arvore*, No*);
void rotacionarDireita(Arvore*, No*);

Arvore* criar();
int vazia(Arvore*);
No* adicionar(Arvore*, int);
No* localizar(Arvore* arvore, int valor);

Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->nulo = NULL;
    arvore->raiz = NULL;

    arvore->nulo = criarNo(arvore, NULL, 0);
    arvore->nulo->cor = Preto;

    return arvore;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* criarNo(Arvore* arvore, No* pai, int valor) {
    No* no = malloc(sizeof(No));

    no->pai = pai;    
    no->valor = valor;
    no->direita = arvore->nulo;
    no->esquerda = arvore->nulo;

    return no;
}

No* adicionarNo(Arvore* arvore, No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == arvore->nulo) {
            no->direita = criarNo(arvore, no, valor);     
            no->direita->cor = Vermelho;       
        		
            return no->direita;
        } else {
            return adicionarNo(arvore, no->direita, valor);
        }
    } else {
        if (no->esquerda == arvore->nulo) {
            no->esquerda = criarNo(arvore, no, valor);
            no->esquerda->cor = Vermelho;
            
            return no->esquerda;
        } else {
            return adicionarNo(arvore, no->esquerda, valor);
        }
    }
}

No* adicionar(Arvore* arvore, int valor) {
    if (vazia(arvore)) {
        arvore->raiz = criarNo(arvore, arvore->nulo, valor);
        arvore->raiz->cor = Preto;
        	
        return arvore->raiz;
    } else {
        No* no = adicionarNo(arvore, arvore->raiz, valor);
        balancear(arvore, no);
        
        return no;
    }
}

No* localizar(Arvore* arvore, int valor) {
    if (!vazia(arvore)) {
        No* no = arvore->raiz;

        while (no != arvore->nulo) {
            if (no->valor == valor) {
                return no;
            } else {
                no = valor < no->valor ? no->esquerda : no->direita;
            }
        }
    }

    return NULL;
}

void percorrerProfundidadeInOrder(Arvore* arvore, No* no, void (*callback)(int)) {
    if (no != arvore->nulo) {
        
        
        percorrerProfundidadeInOrder(arvore, no->esquerda,callback);
        callback(no->valor);
        percorrerProfundidadeInOrder(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePreOrder(Arvore* arvore, No* no, void (*callback)(int)) {
    if (no != arvore->nulo) {
        callback(no->valor);
        percorrerProfundidadePreOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePreOrder(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePosOrder(Arvore* arvore, No* no, void (callback)(int)) {
    if (no != arvore->nulo) {
        percorrerProfundidadePosOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePosOrder(arvore, no->direita,callback);
        callback(no->valor);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

void balancear(Arvore* arvore, No* no) {
    while (no->pai->cor == Vermelho) {
        if (no->pai == no->pai->pai->esquerda) {
            No *tio = no->pai->pai->direita;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                if (no == no->pai->direita) {
                    no = no->pai; //Caso 2
                    rotacionarEsquerda(arvore, no); //Caso 2
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarDireita(arvore, no->pai->pai); //Caso 3
                }
            }
        } else {
            No *tio = no->pai->pai->esquerda;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai; //Caso 2
                    rotacionarDireita(arvore, no); //Caso 2
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarEsquerda(arvore, no->pai->pai); //Caso 3
                }
            }
        }
    }
    arvore->raiz->cor = Preto; //Conserta possível quebra regra 2
}

void rotacionarEsquerda(Arvore* arvore, No* no) {
    No* direita = no->direita;
    no->direita = direita->esquerda; 

    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
    }

    direita->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        arvore->raiz = direita;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = direita;
    } else {
        no->pai->direita = direita;
    }

    direita->esquerda = no;
    no->pai = direita;
}

void rotacionarDireita(Arvore* arvore, No* no) {
    No* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;
    
    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
    }
    
    esquerda->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        arvore->raiz = esquerda;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = esquerda;
    } else {
        no->pai->direita = esquerda;
    }
    
    esquerda->direita = no;
    no->pai = esquerda;
}

void transplante(Arvore* arvore, No* u, No* v) {
    if (u->pai == arvore->nulo) {
        arvore->raiz = v;
    } else if (u == u->pai->esquerda) {
        u->pai->esquerda = v;
    } else {
        u->pai->direita = v;
    }
    v->pai = u->pai;
}

No* minimoSubarvore(Arvore* arvore, No* no) {
    while (no->esquerda != arvore->nulo) {
        no = no->esquerda;
    }
    return no;
}

void correcaoRemocao(Arvore* arvore, No* x) {
    while (x != arvore->raiz && x->cor == Preto) {
        if (x == x->pai->esquerda) {
            No* w = x->pai->direita;
            if (w->cor == Vermelho) {
                w->cor = Preto;
                x->pai->cor = Vermelho;
                rotacionarEsquerda(arvore, x->pai);
                w = x->pai->direita;
            }
            if (w->esquerda->cor == Preto && w->direita->cor == Preto) {
                w->cor = Vermelho;
                x = x->pai;
            } else {
                if (w->direita->cor == Preto) {
                    w->esquerda->cor = Preto;
                    w->cor = Vermelho;
                    rotacionarDireita(arvore, w);
                    w = x->pai->direita;
                }
                w->cor = x->pai->cor;
                x->pai->cor = Preto;
                w->direita->cor = Preto;
                rotacionarEsquerda(arvore, x->pai);
                x = arvore->raiz;
            }
        } else {
            No* w = x->pai->esquerda;
            if (w->cor == Vermelho) {
                w->cor = Preto;
                x->pai->cor = Vermelho;
                rotacionarDireita(arvore, x->pai);
                w = x->pai->esquerda;
            }
            if (w->direita->cor == Preto && w->esquerda->cor == Preto) {
                w->cor = Vermelho;
                x = x->pai;
            } else {
                if (w->esquerda->cor == Preto) {
                    w->direita->cor = Preto;
                    w->cor = Vermelho;
                    rotacionarEsquerda(arvore, w);
                    w = x->pai->esquerda;
                }
                w->cor = x->pai->cor;
                x->pai->cor = Preto;
                w->esquerda->cor = Preto;
                rotacionarDireita(arvore, x->pai);
                x = arvore->raiz;
            }
        }
    }
    x->cor = Preto;
}

void remover(Arvore* arvore, int valor) {
    // Procurar o nó com o valor especificado
    No* z = arvore->raiz;
    while (z != arvore->nulo && z->valor != valor) {
        z = (valor < z->valor) ? z->esquerda : z->direita;
    }

    // Se o nó não foi encontrado, retornar
    if (z == arvore->nulo) {
        printf("Valor %d não encontrado na árvore.\n", valor);
        return;
    }

    // Início do processo de remoção
    No* y = z;
    No* x;
    Cor corOriginal = y->cor;

    if (z->esquerda == arvore->nulo) {
        x = z->direita;
        transplante(arvore, z, z->direita);
    } else if (z->direita == arvore->nulo) {
        x = z->esquerda;
        transplante(arvore, z, z->esquerda);
    } else {
        y = minimoSubarvore(arvore, z->direita);
        corOriginal = y->cor;
        x = y->direita;
        if (y->pai == z) {
            x->pai = y;
        } else {
            transplante(arvore, y, y->direita);
            y->direita = z->direita;
            y->direita->pai = y;
        }
        transplante(arvore, z, y);
        y->esquerda = z->esquerda;
        y->esquerda->pai = y;
        y->cor = z->cor;
    }
    if (corOriginal == Preto) {
        correcaoRemocao(arvore, x);
    }
    free(z);
}



int main() {
    Arvore* a = criar();

    adicionar(a,7);
    adicionar(a,6);
    adicionar(a,5);
    adicionar(a,4);
    adicionar(a,3);
    adicionar(a,2);
    adicionar(a,1);
    adicionar(a,40);
    adicionar(a,8);
    adicionar(a,-5);

    printf("In-order: ");
    percorrerProfundidadeInOrder(a, a->raiz,visitar);
    printf("\n");

    remover(a, 7);
    remover(a, 1);
    remover(a, 3);

    printf("In-order: ");
    percorrerProfundidadeInOrder(a, a->raiz,visitar);
    printf("\n");
}
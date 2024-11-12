#include "avl.h"

int main() {
    Arvore* a = criar();

    adicionar(a,3);
    adicionar(a,1);
    adicionar(a,2);
    adicionar(a,5);
    adicionar(a,4);
    adicionar(a,7);
    adicionar(a,6);

    printf("In-order: ");
    percorrer(a->raiz,visitar);
    printf("\n");
    printf("Altura: %d\n", altura(a->raiz));   

    remover(a, 5);
    printf("In-order: ");
    percorrer(a->raiz,visitar);
    printf("\n");
    printf("Altura: %d\n", altura(a->raiz));
     
    remover(a, 3);
    printf("In-order: ");
    percorrer(a->raiz,visitar);
    printf("\n");
    printf("Altura: %d\n", altura(a->raiz));
    
    remover(a, 7);
    printf("In-order: ");
    percorrer(a->raiz,visitar);
    printf("\n");
    printf("Altura: %d\n", altura(a->raiz));
    

    remover(a, 1);
    printf("In-order: ");
    percorrer(a->raiz,visitar);
    printf("\n");
    printf("Altura: %d\n", altura(a->raiz));


    remover(a, 2);
    printf("In-order: ");
    percorrer(a->raiz,visitar);
    printf("\n");
    printf("Altura: %d\n", altura(a->raiz));
    
    

}
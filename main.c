#include "avl.h"
#include <time.h>

// funcao para verificar se o numero gerado aleatoriamente ja foi criado
int existe_no_vetor(int *vet, int tam, int valor){
    
    for(int i = 0; i < tam; i++){
        if(vet[i] == valor){
            return 1;
        }
    }

    return 0;
}

int main() {

    int tam = 1000;
    int vet_add[tam];
    int min = 0;
    int max = 10000;
    int num;
    srand(time(NULL));

    // gerando e printando valores aleatorios para inserir na avl
    printf("\n--- VALORES PARA INSERIR NA ARVORE ---\n");
    for(int i = 0; i < tam; i++){
        num = rand() % (max - min + 1) + min;
        while( existe_no_vetor(vet_add, i, num) ){
            num = rand() % (max - min + 1) + min;            
        }

        vet_add[i] = num;
        printf("%d ", vet_add[i]);
    }
    printf("\n");

    Arvore* a = criar();    

    for(int i = 0; i < tam; i++){
        adicionar(a, vet_add[i]);
    }

    printf("In-order: ");
    percorrer(a->raiz,visitar);
    printf("\n");
    printf("Altura: %d\n", altura(a->raiz));   

    imprimir_por_altura(a);

}
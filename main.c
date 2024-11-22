#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"
#include <time.h>

int main() {
    int tam = 10;
    int vet_add[tam];
    int min = 0;
    int max = 10;
    int num;
    srand(time(NULL));

    // gerando e printando valores aleatorios para inserir na arvoreB
    // printf("\n--- VALORES PARA INSERIR NA ARVORE ---\n");
    // for(int i = 0; i < tam; i++){
    //     num = rand() % (max - min + 1) + min;
    //     while( existe_no_vetor(vet_add, i, num) ){
    //         num = rand() % (max - min + 1) + min;            
    //     }

    //     vet_add[i] = num;
    //     printf("%d ", vet_add[i]);
    // }
    // printf("\n");


    ArvoreB* arvore = criaArvoreB(2);    
    adicionaChave(arvore, 0);
    // adicionaChave(arvore, 1);
    // adicionaChave(arvore, 2);
    adicionaChave(arvore, 3);
    adicionaChave(arvore, 4);
    adicionaChave(arvore, 5);
    adicionaChave(arvore, 6);
    adicionaChave(arvore, 7);
    adicionaChave(arvore, 8);
    adicionaChave(arvore, 9);
    adicionaChave(arvore, 10);
    adicionaChave(arvore, 11);
    adicionaChave(arvore, 12);
    adicionaChave(arvore, 13);
    adicionaChave(arvore, 14);

    // for(int i = 0; i < tam; i++){
    //     adicionaChave(arvore, vet_add[i]);
    // }
    imprimeDetalhesArvore(arvore);
    
    

    int opcao = -1;
    int chave = 0;
    while(opcao != 0){
        scanf("%i", &opcao);
        printf("Digite a chave para remocao: ");
        scanf("%i", &chave);
        removeChave(arvore, chave);
        imprimeDetalhesArvore(arvore);
    }



    return 0;
}

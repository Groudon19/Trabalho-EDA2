#include "rubNeg.h"
#include <time.h>

// compilar com gcc main.c rubNeg.c && ./a.out

int existe_no_vetor(int *vet, int tam, int valor){
    
    for(int i = 0; i < tam; i++){
        if(vet[i] == valor){
            return 1;
        }
    }

    return 0;
}

int main() {

    int tam = 10000;
    int vet_add[tam];
    int min = 0;
    int max = 10000;
    int num;
    srand(time(NULL));

    int cont_add_med[tam], cont_rem_med[tam];

    for(int i =0; i<tam; i++){
        cont_add_med[i] = 0;
        cont_rem_med[i] = 0;
    }


    int add = 0, rem =0;
    int cont_add[tam];
    int cont_rem[tam];
    

    for(int j=0; j<10; j++){
        for(int i =0; i<tam; i++){
            cont_add[i] = 0;
            cont_rem[i] = 0;
            vet_add[i] = 0;
        }


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
            adicionar(a, vet_add[i], cont_add, i);
            cont_add_med[i] += cont_add[i];
        }
        for(int i =0; i< tam; i++){
            remover(a, vet_add[i], cont_rem, i);
            cont_rem_med[i] += cont_rem[i];
    }

    }
    for(int i=0; i<tam; i++){
        cont_add_med[i] /= 10;
        cont_rem_med[i] /= 10;
    }

    for(int i=0; i<tam; i++){
        printf("%i ", cont_add_med[i]);
    }
    printf("\n\n");
    for(int i=0; i<tam; i++){
        printf("%i ", cont_rem_med[i]);
    }
    printf("\n\n");

    //criando arquivo CSV para plotar o grafico

    FILE *arquivo_adicao, *arquivo_remocao;

    const char *nome_arquivo_adicao = "resultados_adicao.csv";
    const char *nome_arquivo_remocao = "resultados_remocao.csv";

    arquivo_adicao = fopen(nome_arquivo_adicao, "w");
    arquivo_remocao = fopen(nome_arquivo_remocao, "w");
    if (arquivo_adicao == NULL || arquivo_remocao == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return 1;
    }

    for(int i=0; i<tam; i++){
        fprintf(arquivo_adicao, "%i", cont_add_med[i]);
        fprintf(arquivo_adicao, "\n");
    }
    for(int i = tam-1; i>=0; i--){
        fprintf(arquivo_remocao, "%i", cont_rem_med[i]);
        fprintf(arquivo_remocao, "\n");
    }

    fclose(arquivo_adicao);
    fclose(arquivo_remocao);

    int total_add = 0, total_rem = 0;
    for(int i=0; i< tam; i++){
        total_add += cont_add_med[i];
        total_rem += cont_rem_med[i];
    }

    printf("\n\n%i\n\n%i\n\n", total_add, total_rem);

    return 0;
}

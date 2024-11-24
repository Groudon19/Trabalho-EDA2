#include "avl.h"
#include <time.h>

#define tam_max 10000 // numero maximo de elementos em cada arvore
#define num_testes 10 // numero de vezes que rodará cada conjunto
#define intervalo 100 // tamanho do intervalo para acrescimo da quantidade de elementos

// funcao para verificar se o numero gerado aleatoriamente ja foi criado
int existe_no_vetor(int *vet, int tam, int valor){
    
    for(int i = 0; i < tam; i++){
        if(vet[i] == valor){
            return 1;
        }
    }

    return 0;
}

void rodar_teste(Arvore* a, int tam, int* somatorio_add, int* somatorio_rem) {
    
    int vet_add[tam];
    int vet_rem[tam];
    int min = 0;
    int max = 10000;
    int num;

    // Gerar valores aleatórios para adicionar e remover
    for(int i = 0; i < tam; i++) {
        num = rand() % (max - min + 1) + min;
        while (existe_no_vetor(vet_add, i, num)) {
            num = rand() % (max - min + 1) + min;
        }
        vet_add[i] = num;
        vet_rem[i] = vet_add[i]; // os valores da remocao serão os mesmos
    }

    int contador_add[3] = {0, 0, 0}; // Contagem de comparações para adicao
    int contador_rem[3] = {0, 0, 0}; // Contagem de comparações para remocao

    
    for(int i = 0; i < tam; i++) {
        adicionar(a, vet_add[i], contador_add);
    }

    // Acumular os resultados
    somatorio_add[0] += contador_add[0];
    somatorio_add[1] += contador_add[1];
    somatorio_add[2] += contador_add[2];

    for(int i = 0; i < tam; i++) {
        remover(a, vet_rem[i], contador_rem);
    }

     // Acumular os resultados
    somatorio_rem[0] += contador_rem[0];
    somatorio_rem[1] += contador_rem[1];
    somatorio_rem[2] += contador_rem[2];

}

// função que rodará o exeperimento com diferentes tamanhos de conjuntos
void rodar_experimento(FILE* arquivo_adicao, FILE* arquivo_remocao) {

    for (int tam = intervalo; tam <= tam_max; tam += intervalo) {
        // Inicializando os acumuladores para os 10000 testes
        int total_add[3] = {0, 0, 0}; // Para acumular os contadores de adição
        int total_rem[3] = {0, 0, 0}; // Para acumular os contadores de remocao

        for (int i = 0; i < num_testes; i++) {
            Arvore* a = criar(); // cria a AVL
            rodar_teste(a, tam, total_add, total_rem); // roda o teste para AVL
            destruir_avl(a); // destrói a árvore AVL
        }

        // Calculando a média dos resultados
        int media_add[3];
        int media_rem[3];
        for (int i = 0; i < 3; i++) {
            media_add[i] = total_add[i] / num_testes;
            media_rem[i] = total_rem[i] / num_testes;
        }

        fprintf(arquivo_adicao, "%d,%d,%d,%d\n", tam, media_add[0], media_add[1], media_add[2]);

        fprintf(arquivo_remocao, "%d,%d,%d,%d\n", tam, media_rem[0], media_rem[1], media_rem[2]);

    }
}



int main() {

    FILE *arquivo_adicao, *arquivo_remocao;

    const char *nome_arquivo_adicao = "resultados_adicao.csv";
    const char *nome_arquivo_remocao = "resultados_remocao.csv";

    arquivo_adicao = fopen(nome_arquivo_adicao, "w");
    arquivo_remocao = fopen(nome_arquivo_remocao, "w");
    if (arquivo_adicao == NULL || arquivo_remocao == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return 1;
    }

    // Cabeçalho dos CSVs
    fprintf(arquivo_adicao, "Tamanho da árvore, Comparações Adição AVL, Comparações Adição RN, Comparações Adição B\n");

    fprintf(arquivo_remocao, "Tamanho da árvore, Comparações Remoção AVL, Comparações Remoção RN, Comparações Remoção B\n");

    srand(time(NULL));

    rodar_experimento(arquivo_adicao, arquivo_remocao);

    fclose(arquivo_adicao);
    fclose(arquivo_remocao);
    
    printf("Experimento concluído! Resultados gravados em %s e %s\n", nome_arquivo_adicao, nome_arquivo_remocao);
    
    return 0;
}
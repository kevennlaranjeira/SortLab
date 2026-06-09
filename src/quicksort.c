#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "auxiliar.h"

// Função de partição para QuickSort
void particao(int* vetor, int esq, int dir, int* i, int* j) {
    int x, w;
    *i = esq;
    *j = dir;
    x = vetor[esq];
    do {
        while (vetor[*i] < x) (*i)++;
        while (vetor[*j] > x) (*j)--;
        if (*i <= *j) {
            w = vetor[*i];
            vetor[*i] = vetor[*j];
            vetor[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

// Função de ordenação recursiva
void ordena(int* vetor, int esq, int dir) {
    if (esq >= dir) return;

    int i, j;
    particao(vetor, esq, dir, &i, &j);

    if (esq < j) {
        ordena(vetor, esq, j);
    }
    if (i < dir) {
        ordena(vetor, i, dir);
    }
}

// Quicksort com pivô inicial
void quicksort_pivo_inicial(int* vetor, int inicio, int fim) {
    ordena(vetor, inicio, fim);
}

// Quicksort com pivô médio
void quicksort_pivo_medio(int* vetor, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        int temp = vetor[inicio];
        vetor[inicio] = vetor[meio];
        vetor[meio] = temp;

        ordena(vetor, inicio, fim);
    }
}

// Quicksort com pivô aleatório
void quicksort_pivo_aleatorio(int* vetor, int inicio, int fim) {
    if (inicio < fim) {
        int aleatorio = inicio + rand() % (fim - inicio + 1);
        int temp = vetor[inicio];
        vetor[inicio] = vetor[aleatorio];
        vetor[aleatorio] = temp;

        ordena(vetor, inicio, fim);
    }
}

// Função segura para alocar memória
int* alocar_memoria_segura(size_t tamanho) {
    int* vetor = (int*)malloc(tamanho * sizeof(int));
    if (!vetor) {
        fprintf(stderr, "Erro: Falha ao alocar memória para um vetor de tamanho %zu.\n", tamanho);
        exit(EXIT_FAILURE);
    }
    return vetor;
}

// Função para executar e medir o tempo do Quicksort
void executar_quicksort(const char* nome_algoritmo, void (*quicksort)(int*, int, int)) {
    setlocale(LC_ALL, "Portuguese");
    char tipo = ler_tipo_entrada();
    int tamanho = ler_tamanho_entrada();

    // Criar pastas principais
    char pasta_principal[50];
    snprintf(pasta_principal, sizeof(pasta_principal), "%s", nome_algoritmo);
    criar_pasta(pasta_principal);

    char entrada_pasta[50], saida_pasta[50], tempo_pasta[50];
    snprintf(entrada_pasta, sizeof(entrada_pasta), "%s/arquivodeentrada", pasta_principal);
    snprintf(saida_pasta, sizeof(saida_pasta), "%s/arquivodesaida", pasta_principal);
    snprintf(tempo_pasta, sizeof(tempo_pasta), "%s/arquivotempo", pasta_principal);

    criar_pasta(entrada_pasta);
    criar_pasta(saida_pasta);
    criar_pasta(tempo_pasta);

    const char* tipo_nome = nome_tipo_entrada(tipo);

    // Criar subpastas baseadas no tipo de entrada
    char pasta_entrada_tipo[100], pasta_saida_tipo[100], pasta_tempo_tipo[100];
    snprintf(pasta_entrada_tipo, sizeof(pasta_entrada_tipo), "%s/%s", entrada_pasta, tipo_nome);
    snprintf(pasta_saida_tipo, sizeof(pasta_saida_tipo), "%s/%s", saida_pasta, tipo_nome);
    snprintf(pasta_tempo_tipo, sizeof(pasta_tempo_tipo), "%s/%s", tempo_pasta, tipo_nome);

    criar_pasta(pasta_entrada_tipo);
    criar_pasta(pasta_saida_tipo);
    criar_pasta(pasta_tempo_tipo);

    // Gerar nomes de arquivos
    char nome_entrada[100], nome_saida[100], nome_tempo[100];
    snprintf(nome_entrada, sizeof(nome_entrada), "%s/entrada%c%d.txt", pasta_entrada_tipo, tipo, tamanho);
    snprintf(nome_saida, sizeof(nome_saida), "%s/saida%c%d.txt", pasta_saida_tipo, tipo, tamanho);
    snprintf(nome_tempo, sizeof(nome_tempo), "%s/tempo%c%d.txt", pasta_tempo_tipo, tipo, tamanho);

    // Gerar arquivo de entrada
    gerar_arquivo_entrada(nome_entrada, tamanho, tipo);

    // Alocar memória segura para o vetor
    int* vetor = alocar_memoria_segura(tamanho);

    carregar_dados(nome_entrada, vetor, tamanho);

    // Medir tempo de execução
    clock_t inicio = clock();
    quicksort(vetor, 0, tamanho - 1);
    clock_t fim = clock();

    double tempo_gasto = tempo_decorrido(inicio, fim);
    printf("Tempo gasto: %.6f segundos\n", tempo_gasto);

    salvar_saida(nome_saida, vetor, tamanho);
    salvar_tempo(nome_tempo, tempo_gasto);

    printf("Ordenação concluída. Resultados salvos em %s e tempo em %s.\n", nome_saida, nome_tempo);

    // Liberar memória alocada
    free(vetor);
}

// Execução do Quicksort com Pivô Inicial
void executar_quicksort_pivo_inicial() {
    executar_quicksort("Quicksort_Pivo_Inicial", quicksort_pivo_inicial);
}

// Execução do Quicksort com Pivô Médio
void executar_quicksort_pivo_medio() {
    executar_quicksort("Quicksort_Pivo_Medio", quicksort_pivo_medio);
}

// Execução do Quicksort com Pivô Aleatório
void executar_quicksort_pivo_aleatorio() {
    executar_quicksort("Quicksort_Pivo_Aleatorio", quicksort_pivo_aleatorio);
}

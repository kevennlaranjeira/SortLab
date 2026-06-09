#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "auxiliar.h"

// Função de mesclagem usada no Merge Sort
void merge(int* vetor, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = vetor[inicio + i];
    for (int j = 0; j < n2; j++)
        R[j] = vetor[meio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor[k] = L[i];
            i++;
        } else {
            vetor[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Função recursiva do Merge Sort
void merge_sort(int* vetor, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        merge_sort(vetor, inicio, meio);
        merge_sort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

// Função para executar o Merge Sort
void executar_merge_sort() {
    setlocale(LC_ALL, "Portuguese");
    char tipo = ler_tipo_entrada();
    int tamanho = ler_tamanho_entrada();

    // Criar pastas
    char pasta_principal[] = "MergeSort";
    criar_pasta(pasta_principal);

    char entrada_pasta[50], saida_pasta[50], tempo_pasta[50];
    sprintf(entrada_pasta, "%s/arquivodeentrada", pasta_principal);
    sprintf(saida_pasta, "%s/arquivodesaida", pasta_principal);
    sprintf(tempo_pasta, "%s/arquivotempo", pasta_principal);

    criar_pasta(entrada_pasta);
    criar_pasta(saida_pasta);
    criar_pasta(tempo_pasta);

    const char* tipo_nome = nome_tipo_entrada(tipo);
    char pasta_entrada_tipo[100], pasta_saida_tipo[100], pasta_tempo_tipo[100];
    snprintf(pasta_entrada_tipo, sizeof(pasta_entrada_tipo), "%s/%s", entrada_pasta, tipo_nome);
    snprintf(pasta_saida_tipo, sizeof(pasta_saida_tipo), "%s/%s", saida_pasta, tipo_nome);
    snprintf(pasta_tempo_tipo, sizeof(pasta_tempo_tipo), "%s/%s", tempo_pasta, tipo_nome);

    criar_pasta(pasta_entrada_tipo);
    criar_pasta(pasta_saida_tipo);
    criar_pasta(pasta_tempo_tipo);

    // Criar arquivos
    char nome_entrada[100], nome_saida[100], nome_tempo[100];
    snprintf(nome_entrada, sizeof(nome_entrada), "%s/entrada%c%d.txt", pasta_entrada_tipo, tipo, tamanho);
    snprintf(nome_saida, sizeof(nome_saida), "%s/saida%c%d.txt", pasta_saida_tipo, tipo, tamanho);
    snprintf(nome_tempo, sizeof(nome_tempo), "%s/tempo%c%d.txt", pasta_tempo_tipo, tipo, tamanho);

    // Gerar arquivo de entrada
    gerar_arquivo_entrada(nome_entrada, tamanho, tipo);

    int* vetor = (int*)malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memória para o vetor\n");
        return;
    }

    carregar_dados(nome_entrada, vetor, tamanho);

    // Medição de tempo usando clock()
    clock_t inicio = clock();

    printf("Iniciando a ordenação...\n");
    merge_sort(vetor, 0, tamanho - 1);

    clock_t fim = clock();
    double tempo_gasto = tempo_decorrido(inicio, fim);
    printf("Tempo gasto: %.6f segundos\n", tempo_gasto);

    salvar_saida(nome_saida, vetor, tamanho);
    salvar_tempo(nome_tempo, tempo_gasto);

    printf("Ordenação concluída. Resultados salvos em %s e tempo em %s.\n", nome_saida, nome_tempo);
    free(vetor);
}

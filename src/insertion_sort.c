#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "auxiliar.h"

// Insertion Sort
void insertion_sort(int* vetor, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int key = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > key) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = key;
    }
}

// execução do Insertion Sort com as opções de geração de dados e pastas de destino
void executar_insertion_sort() {
    setlocale(LC_ALL, "Portuguese");
    char tipo = ler_tipo_entrada();
    int tamanho = ler_tamanho_entrada();

    // definir as pastas necessárias
    char pasta_principal[] = "InsertionSort";
    criar_pasta(pasta_principal);

    char entrada_pasta[50], saida_pasta[50], tempo_pasta[50];
    sprintf(entrada_pasta, "%s/arquivodeentrada", pasta_principal);
    sprintf(saida_pasta, "%s/arquivodesaida", pasta_principal);
    sprintf(tempo_pasta, "%s/arquivotempo", pasta_principal);

    criar_pasta(entrada_pasta);
    criar_pasta(saida_pasta);
    criar_pasta(tempo_pasta);

    const char* tipo_nome = nome_tipo_entrada(tipo);

    // criar diretorios
    char pasta_entrada_tipo[100], pasta_saida_tipo[100], pasta_tempo_tipo[100];
    snprintf(pasta_entrada_tipo, sizeof(pasta_entrada_tipo), "%s/%s", entrada_pasta, tipo_nome);
    snprintf(pasta_saida_tipo, sizeof(pasta_saida_tipo), "%s/%s", saida_pasta, tipo_nome);
    snprintf(pasta_tempo_tipo, sizeof(pasta_tempo_tipo), "%s/%s", tempo_pasta, tipo_nome);

    criar_pasta(pasta_entrada_tipo);
    criar_pasta(pasta_saida_tipo);
    criar_pasta(pasta_tempo_tipo);

    // nome de arquivos
    char nome_entrada[100], nome_saida[100], nome_tempo[100];
    snprintf(nome_entrada, sizeof(nome_entrada), "%s/entrada%c%d.txt", pasta_entrada_tipo, tipo, tamanho);
    snprintf(nome_saida, sizeof(nome_saida), "%s/saida%c%d.txt", pasta_saida_tipo, tipo, tamanho);
    snprintf(nome_tempo, sizeof(nome_tempo), "%s/tempo%c%d.txt", pasta_tempo_tipo, tipo, tamanho);

    // arquivo de entrada
    gerar_arquivo_entrada(nome_entrada, tamanho, tipo);

    int* vetor = (int*)malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memória para o vetor\n");
        return;
    }
    carregar_dados(nome_entrada, vetor, tamanho);
    clock_t inicio = clock();

    printf("Iniciando a ordenação...\n");
    insertion_sort(vetor, tamanho);

    clock_t fim = clock();
    double tempo_gasto = tempo_decorrido(inicio, fim);
    printf("Tempo gasto: %.6f segundos\n", tempo_gasto);

    salvar_saida(nome_saida, vetor, tamanho);
    salvar_tempo(nome_tempo, tempo_gasto);

    printf("Ordenação concluída. Resultados salvos em %s e tempo em %s.\n", nome_saida, nome_tempo);
    free(vetor);
}

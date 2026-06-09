#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "auxiliar.h"

// Função Bubble Sort
void bubble_sort(int* vetor, int tamanho) {
    // Iteração sobre os elementos do vetor para ordenar
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            // Comparação de elementos adjacentes
            if (vetor[j] > vetor[j + 1]) {
                // Troca de posição caso estejam fora de ordem
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

// funcao para executar o Bubble sort
void executar_bubble_sort() {
    setlocale(LC_ALL, "Portuguese");
    char tipo = ler_tipo_entrada();
    int tamanho = ler_tamanho_entrada();

    // Cria estrutura de pastas para salvar arquivos
    char pasta_principal[] = "BubbleSort";
    criar_pasta(pasta_principal);

    char entrada_pasta[50], saida_pasta[50], tempo_pasta[50];
    sprintf(entrada_pasta, "%s/arquivodeentrada", pasta_principal);
    sprintf(saida_pasta, "%s/arquivodesaida", pasta_principal);
    sprintf(tempo_pasta, "%s/arquivotempo", pasta_principal);

    criar_pasta(entrada_pasta);
    criar_pasta(saida_pasta);
    criar_pasta(tempo_pasta);

    // Define o nome da subpasta com base no tipo de entrada
    const char* tipo_nome = nome_tipo_entrada(tipo);

    // Cria subpastas para o tipo de entrada
    char pasta_entrada_tipo[100], pasta_saida_tipo[100], pasta_tempo_tipo[100];
    snprintf(pasta_entrada_tipo, sizeof(pasta_entrada_tipo), "%s/%s", entrada_pasta, tipo_nome);
    snprintf(pasta_saida_tipo, sizeof(pasta_saida_tipo), "%s/%s", saida_pasta, tipo_nome);
    snprintf(pasta_tempo_tipo, sizeof(pasta_tempo_tipo), "%s/%s", tempo_pasta, tipo_nome);

    criar_pasta(pasta_entrada_tipo);
    criar_pasta(pasta_saida_tipo);
    criar_pasta(pasta_tempo_tipo);

    // Define os nomes dos arquivos de entrada, saída e tempo
    char nome_entrada[100], nome_saida[100], nome_tempo[100];
    snprintf(nome_entrada, sizeof(nome_entrada), "%s/entrada%c%d.txt", pasta_entrada_tipo, tipo, tamanho);
    snprintf(nome_saida, sizeof(nome_saida), "%s/saida%c%d.txt", pasta_saida_tipo, tipo, tamanho);
    snprintf(nome_tempo, sizeof(nome_tempo), "%s/tempo%c%d.txt", pasta_tempo_tipo, tipo, tamanho);

    gerar_arquivo_entrada(nome_entrada, tamanho, tipo);  // Gera o arquivo de entrada com os dados iniciais

    // Aloca memória para o vetor
    int* vetor = (int*)malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memória para o vetor\n");
        return;
    }
    carregar_dados(nome_entrada, vetor, tamanho);   //dados do arquivo de entrada no vetor

    clock_t inicio = clock();

    printf("Iniciando a ordenação...\n");
    bubble_sort(vetor, tamanho);  // Ordena o vetor usando Bubble Sort

    clock_t fim = clock();
    double tempo_gasto = tempo_decorrido(inicio, fim);
    printf("Tempo gasto: %.6f segundos\n", tempo_gasto);

    salvar_saida(nome_saida, vetor, tamanho);  // Salva o vetor ordenado no arquivo de saída
    salvar_tempo(nome_tempo, tempo_gasto);    // Salva o tempo de execução no arquivo de tempo

    printf("Ordenação concluída. Resultados salvos em %s e tempo em %s.\n", nome_saida, nome_tempo);
    free(vetor);
}

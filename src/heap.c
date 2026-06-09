#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "auxiliar.h"

static void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(int* vetor, int tamanho, int indice) {
    int maior = indice;
    int esquerda = 2 * indice + 1;
    int direita = 2 * indice + 2;

    if (esquerda < tamanho && vetor[esquerda] > vetor[maior]) {
        maior = esquerda;
    }
    if (direita < tamanho && vetor[direita] > vetor[maior]) {
        maior = direita;
    }
    if (maior != indice) {
        trocar(&vetor[indice], &vetor[maior]);
        max_heapify(vetor, tamanho, maior);
    }
}

void build_max_heap(int* vetor, int tamanho) {
    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        max_heapify(vetor, tamanho, i);
    }
}

void heap_sort(int* vetor, int tamanho) {
    build_max_heap(vetor, tamanho);
    for (int i = tamanho - 1; i > 0; i--) {
        trocar(&vetor[0], &vetor[i]);
        max_heapify(vetor, i, 0);
    }
}

int heap_maximum(int* vetor) {
    return vetor[0];
}

int heap_extract_max(int* vetor, int* tamanho) {
    if (*tamanho < 1) {
        printf("Erro: heap underflow\n");
        return -1;
    }

    int maximo = vetor[0];
    vetor[0] = vetor[*tamanho - 1];
    (*tamanho)--;
    max_heapify(vetor, *tamanho, 0);
    return maximo;
}

void heap_increase_key(int* vetor, int indice, int chave) {
    if (chave < vetor[indice]) {
        printf("Erro: nova chave e menor que a atual\n");
        return;
    }

    vetor[indice] = chave;
    while (indice > 0 && vetor[(indice - 1) / 2] < vetor[indice]) {
        trocar(&vetor[indice], &vetor[(indice - 1) / 2]);
        indice = (indice - 1) / 2;
    }
}

void max_heap_insert(int* vetor, int* tamanho, int capacidade, int chave) {
    if (*tamanho >= capacidade) {
        printf("Erro: capacidade maxima do heap atingida\n");
        return;
    }

    (*tamanho)++;
    vetor[*tamanho - 1] = chave;
    heap_increase_key(vetor, *tamanho - 1, chave);
}

void executar_heap_sort() {
    setlocale(LC_ALL, "Portuguese");

    char tipo = ler_tipo_entrada();
    int tamanho = ler_tamanho_entrada();

    char pasta_principal[] = "HeapSort";
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

    char nome_entrada[100], nome_saida[100], nome_tempo[100];
    snprintf(nome_entrada, sizeof(nome_entrada), "%s/entrada%c%d.txt", pasta_entrada_tipo, tipo, tamanho);
    snprintf(nome_saida, sizeof(nome_saida), "%s/saida%c%d.txt", pasta_saida_tipo, tipo, tamanho);
    snprintf(nome_tempo, sizeof(nome_tempo), "%s/tempo%c%d.txt", pasta_tempo_tipo, tipo, tamanho);

    gerar_arquivo_entrada(nome_entrada, tamanho, tipo);

    int* vetor = (int*)malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria para o vetor\n");
        return;
    }
    carregar_dados(nome_entrada, vetor, tamanho);

    clock_t inicio = clock();

    printf("Iniciando a ordenacao com Heapsort...\n");
    heap_sort(vetor, tamanho);

    clock_t fim = clock();
    double tempo_gasto = tempo_decorrido(inicio, fim);
    printf("Tempo gasto: %.6f segundos\n", tempo_gasto);

    salvar_saida(nome_saida, vetor, tamanho);
    salvar_tempo(nome_tempo, tempo_gasto);

    printf("Ordenacao concluida. Resultados salvos em %s e tempo em %s.\n", nome_saida, nome_tempo);

    printf("\nDemonstracao das operacoes de heap:\n");
    int heap_demo[8] = {5, 3, 8, 1, 2};
    int heap_tamanho = 5;
    int heap_capacidade = 8;

    printf("Array original: ");
    for (int i = 0; i < heap_tamanho; i++) printf("%d ", heap_demo[i]);
    printf("\n");

    build_max_heap(heap_demo, heap_tamanho);
    printf("Max-Heap construido: ");
    for (int i = 0; i < heap_tamanho; i++) printf("%d ", heap_demo[i]);
    printf("\nHEAP_MAXIMUM: %d\n", heap_maximum(heap_demo));

    int maximo = heap_extract_max(heap_demo, &heap_tamanho);
    printf("Elemento maximo extraido: %d\nHeap apos extracao: ", maximo);
    for (int i = 0; i < heap_tamanho; i++) printf("%d ", heap_demo[i]);
    printf("\n");

    heap_increase_key(heap_demo, 2, 1000);
    printf("Apos HEAP_INCREASE_KEY(2, 1000): ");
    for (int i = 0; i < heap_tamanho; i++) printf("%d ", heap_demo[i]);
    printf("\n");

    max_heap_insert(heap_demo, &heap_tamanho, heap_capacidade, 42);
    printf("Apos MAX_HEAP_INSERT(42): ");
    for (int i = 0; i < heap_tamanho; i++) printf("%d ", heap_demo[i]);
    printf("\n");

    free(vetor);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "auxiliar.h"

static void limpar_entrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

// Cria uma pasta se não existir
void criar_pasta(const char* nome_pasta) {
    struct stat st = {0};
    if (stat(nome_pasta, &st) == -1) { // verifica se a pasta não existe
        #ifdef _WIN32
            mkdir(nome_pasta);
        #else
            mkdir(nome_pasta, 0777);
        #endif
        printf("Pasta criada: %s\n", nome_pasta);
    }
}

// Verifica a entrada de tamanho
int validar_tamanho(int tamanho) {
    int tamanhos_permitidos[] = {10, 100, 1000, 10000, 100000, 1000000};
    for (int i = 0; i < 6; i++) {
        if (tamanho == tamanhos_permitidos[i]) return 1;
    }
    return 0;
}

int validar_tipo(char tipo) {
    return tipo == 'c' || tipo == 'd' || tipo == 'r';
}

char ler_tipo_entrada(void) {
    char tipo;
    do {
        printf("Escolha o tipo de entrada:\n");
        printf("  'c' para crescente\n");
        printf("  'd' para decrescente\n");
        printf("  'r' para randomico\n");
        printf("Opcao: ");
        scanf(" %c", &tipo);
        if (!validar_tipo(tipo)) {
            printf("Tipo invalido! Escolha 'c', 'd' ou 'r'.\n");
            limpar_entrada();
        }
    } while (!validar_tipo(tipo));

    return tipo;
}

int ler_tamanho_entrada(void) {
    int tamanho;
    do {
        printf("Escolha o tamanho da entrada (10, 100, 1000, 10000, 100000, 1000000): ");
        if (scanf("%d", &tamanho) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            limpar_entrada();
            tamanho = 0;
            continue;
        }
        if (!validar_tamanho(tamanho)) {
            printf("Tamanho invalido! Escolha um dos valores permitidos.\n");
        }
    } while (!validar_tamanho(tamanho));

    return tamanho;
}

const char* nome_tipo_entrada(char tipo) {
    if (tipo == 'c') return "crescente";
    if (tipo == 'd') return "decrescente";
    return "randomico";
}

double tempo_decorrido(clock_t inicio, clock_t fim) {
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// Gera um arquivo de entrada com valores em ordem crescente, decrescente ou randômica
void gerar_arquivo_entrada(const char* nome_arquivo, int tamanho, char tipo) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo %s\n", nome_arquivo);
        return;
    }
    fprintf(arquivo, "%d\n", tamanho);
    static int semente_inicializada = 0;
    if (!semente_inicializada) {
        srand((unsigned int)time(NULL));
        semente_inicializada = 1;
    }
    for (int i = 0; i < tamanho; i++) {
        int valor;
        switch (tipo) {
            case 'c': valor = i; break; // Crescente
            case 'd': valor = tamanho - i - 1; break; // Decrescente
            case 'r': valor = rand() % 10000; break; // Randômico
            default: valor = rand() % 10000; break;
        }
        fprintf(arquivo, "%d\n", valor);
    }
    fclose(arquivo);
}

// Salva o vetor ordenado em um arquivo
void salvar_saida(const char* nome_arquivo, int* vetor, int tamanho) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo %s\n", nome_arquivo);
        return;
    }
    fprintf(arquivo, "%d\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d\n", vetor[i]);
    }
    fclose(arquivo);
}

// Salva o tempo de execução em um arquivo
void salvar_tempo(const char* nome_arquivo, double tempo) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de tempo %s\n", nome_arquivo);
        return;
    }
    fprintf(arquivo, "Tempo gasto: %.6f segundos\n", tempo);
    fclose(arquivo);
}

// Carrega os dados de um arquivo em um vetor
void carregar_dados(const char* nome_arquivo, int* vetor, int tamanho) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }
    int ignora; // Ignora a primeira linha
    fscanf(arquivo, "%d", &ignora);
    for (int i = 0; i < tamanho; i++) {
        fscanf(arquivo, "%d", &vetor[i]);
    }
    fclose(arquivo);
}

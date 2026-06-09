#ifndef AUXILIAR_H
#define AUXILIAR_H

#include <time.h>

void criar_pasta(const char* nome_pasta);
int validar_tamanho(int tamanho);
int validar_tipo(char tipo);
char ler_tipo_entrada(void);
int ler_tamanho_entrada(void);
const char* nome_tipo_entrada(char tipo);
double tempo_decorrido(clock_t inicio, clock_t fim);
void gerar_arquivo_entrada(const char* nome_arquivo, int tamanho, char tipo);
void salvar_saida(const char* nome_arquivo, int* vetor, int tamanho);
void salvar_tempo(const char* nome_arquivo, double tempo);
void carregar_dados(const char* nome_arquivo, int* vetor, int tamanho);

void executar_insertion_sort();
void executar_bubble_sort();
void executar_shell_sort();
void executar_selection_sort();
void executar_merge_sort();
void executar_quicksort_pivo_inicial();
void executar_quicksort_pivo_medio();
void executar_quicksort_pivo_aleatorio();
void executar_heap_sort();

#endif

#include <stdio.h>
#include <locale.h>
#include "auxiliar.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1: Insertion Sort\n");
        printf("2: Bubble Sort\n");
        printf("3: Shell Sort\n");
        printf("4: Selection Sort\n");
        printf("5: Merge Sort\n");
        printf("6: Quicksort - Pivô Inicial\n");
        printf("7: Quicksort - Pivô Médio\n");
        printf("8: Quicksort - Pivô Aleatório\n");
        printf("9: Heapsort\n");
        printf("10: Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Digite um numero de 1 a 10.\n");
            int caractere;
            while ((caractere = getchar()) != '\n' && caractere != EOF) {
            }
            opcao = 0;
            continue;
        }

        switch (opcao) {
            case 1: executar_insertion_sort(); break;
            case 2: executar_bubble_sort(); break;
            case 3: executar_shell_sort(); break;
            case 4: executar_selection_sort(); break;
            case 5: executar_merge_sort(); break;
            case 6: executar_quicksort_pivo_inicial(); break;
            case 7: executar_quicksort_pivo_medio(); break;
            case 8: executar_quicksort_pivo_aleatorio(); break;
            case 9: executar_heap_sort(); break;
            case 10: printf("Saindo do programa.\n"); break;
            default: printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 10);

    return 0;
}

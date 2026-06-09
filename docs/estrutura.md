# Estrutura do repositorio

```text
SortLab/
  src/          codigo-fonte em C
  include/      cabecalhos
  data/         exemplos pequenos de entrada e saida
  docs/         documentacao e imagens
  relatorios/   relatorio final preservado
```

## Fonte principal

- `src/main.c`: menu interativo.
- `src/auxiliar.c`: criacao de pastas, geracao/carregamento de dados, validacoes e medicao de tempo.
- `src/*_sort.c`: implementacoes e rotinas de execucao dos algoritmos.
- `src/quicksort.c`: tres variacoes de QuickSort.
- `src/heap.c`: Heap Sort e demonstracao de operacoes basicas de heap.

## Padrao dos arquivos de dados

O programa grava a quantidade de elementos na primeira linha e, em seguida, um numero por linha:

```text
10
42
7
19
...
```

As saidas ordenadas seguem o mesmo formato.

## Versoes anteriores

As pastas locais das entregas anteriores foram analisadas para identificar a base mais completa. A versao publicada prioriza a entrega final de codigo, evitando duplicar arquivos gerados muito grandes dentro do repositorio.

// Copyright Cretu Mihnea Tudor 315CAa 2022 - 2023
#include <stdio.h>
#include <stdlib.h>

int ***alocare_matrice_in_vector(int ***a, int linie, int coloana, int size);
void afisare_matrice(int ***vector_of_matrixes, int *linie_i, int *coloana_j, int size);
int *alocare_permutare_linii(int nr_linii);
int *alocare_permutare_coloane(int nr_coloane);
int **realocare_matrice(int ***vector_of_matrixes, int index_matrice, int nr_permutare_linii, int nr_permutare_coloane, int *permutare_linii, int *permutare_coloane);
void matrice_inmultita(int ***vector_of_matrixes, int **matrice1, int **matrice2, int *linie_i, int *coloana_j, int index_matrice1, int index_matrice2, int size);
void sortare_matrice(int *suma_matrice, int size, int ***vector_of_matrixes, int *linie_i, int *coloana_j);
void stergere_matrice(int **matrice, int linie);
void multiplicare_matrice_patratica(int **mat1, int **mat2, int nr_linii_coloane);
void ridicare_la_putere(int **mat, int nr_linii_coloane, int putere);


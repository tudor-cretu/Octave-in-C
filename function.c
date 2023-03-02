// Copyright Cretu Mihnea Tudor 315CAa 2022 - 2023
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

// functia adauga si aloca in memorie o matrice in vectorul de matrici si il realoca dinamic de fiecare data cand o noua matrice este adaugata
int ***alocare_matrice_in_vector(int ***temp_vector, int linie, int coloana, int size)
{
    int i;
    temp_vector = realloc(temp_vector, (size) * sizeof(int **));
    if (!temp_vector)
    {
        free(temp_vector);
        return NULL;
    }
    i = size - 1;
    temp_vector[i] = (int **)malloc(linie * sizeof(int *));
    if (!temp_vector[i])
    {
        free(temp_vector[i]);
        return NULL;
    }
    for (int j = 0; j < linie; j++)
    {
        temp_vector[i][j] = (int *)malloc(coloana * sizeof(int));
        if (!temp_vector[i][j])
        {
            fprintf(stderr, "malloc() failed\n");
            while (--j >= 0)
            {
                free(temp_vector[i][j]);
            }
            free(temp_vector[i]);
            free(temp_vector);
            return NULL;
        }
    }
    return temp_vector;
}

// functia afiseza matricea de la pozitia data din vectorul de matrici
void afisare_matrice(int ***vector_of_matrixes, int *linie_i, int *coloana_j, int size)
{
    int index_matrice;
    scanf("%d", &index_matrice);
    if (index_matrice >= size - 1 || index_matrice < 0)
        printf("No matrix with the given index\n");
    else
    {
        for (int i = 0; i < linie_i[index_matrice]; i++)
        {
            for (int j = 0; j < coloana_j[index_matrice]; j++)
                printf("%d ", vector_of_matrixes[index_matrice][i][j]);
            printf("\n");
        }
    }
}

// aloca dinamic vectorul care precizeaza permutarile liniilor la redimensionarea unei matrici si citeste aceste linii
int *alocare_permutare_linii(int nr_linii)
{
    int *temp_permutare_linii = (int *)malloc(nr_linii * sizeof(int));
    if (!temp_permutare_linii)
    {
        fprintf(stderr, "permutare_linii malloc() failled\n");
        return NULL;
    }
    for (int i = 0; i < nr_linii; i++)
    {
        scanf("%d", &temp_permutare_linii[i]);
    }
    return temp_permutare_linii;
}

// aloca dinamic vectorul care precizeaza permutarile coloanelor la redimensionarea unei matrici si citeste aceste coloane
int *alocare_permutare_coloane(int nr_coloane)
{
    int *temp_permutare_coloane = (int *)malloc(nr_coloane * sizeof(int));
    if (!temp_permutare_coloane)
    {
        fprintf(stderr, "permutare_coloane malloc() failled\n");
        return NULL;
    }
    for (int i = 0; i < nr_coloane; i++)
    {
        scanf("%d", &temp_permutare_coloane[i]);
    }
    return temp_permutare_coloane;
}

//functia redimensioneaza matricea de la pozitia data din vectorul de matrici in functie de permutarile liniilor si a coloanelor
int **realocare_matrice(int ***vector_of_matrixes, int index_matrice, int nr_permutare_linii, int nr_permutare_coloane, int *permutare_linii, int *permutare_coloane)
{
    int **temp_matrice = (int **)malloc(nr_permutare_linii * sizeof(int *));
    if (!temp_matrice)
    {
        fprintf(stderr, "temp_matrice malloc() failed\n");
        return NULL;
    }
    for (int i = 0; i < nr_permutare_linii; i++)
    {
        temp_matrice[i] = (int *)malloc(nr_permutare_coloane * sizeof(int));
        if (!temp_matrice[i])
        {
            fprintf(stderr, "temp_matrice malloc() failed\n");
            while (--i >= 0)
            {
                free(temp_matrice[i]);
            }
            free(temp_matrice);
            return NULL;
        }
        for (int j = 0; j < nr_permutare_coloane; j++)
        {
            temp_matrice[i][j] = vector_of_matrixes[index_matrice][permutare_linii[i]][permutare_coloane[j]];
        }
    }
    return temp_matrice;
}

// functia inmulteste 2 matrici aflate la 2 pozitii date din vectorul de matrici si adauga matricea inmultita la finalul vectorului
void matrice_inmultita(int ***vector_of_matrixes, int **temp_matrice, int **matrice2, int *linie_i, int *coloana_j, int index_temp_matrice, int index_matrice2, int size) {
    for(int i = 0; i < linie_i[index_temp_matrice]; i++) {
        for (int j = 0; j < coloana_j[index_matrice2]; j++) {
            vector_of_matrixes[size-1][i][j] = 0;
            for (int k = 0; k < linie_i[index_matrice2]; k++) {
                if(temp_matrice[i][k] * matrice2[k][j] >= 0) vector_of_matrixes[size-1][i][j] += (temp_matrice[i][k] * matrice2[k][j] % 10007);
                else vector_of_matrixes[size-1][i][j] += (temp_matrice[i][k] * matrice2[k][j] % 10007 + 10007);
            }
        }
    }
    for(int i = 0; i < linie_i[index_temp_matrice]; i++) 
        for (int j = 0; j < coloana_j[index_matrice2]; j++) vector_of_matrixes[size-1][i][j] %= 10007;
}

// calculeaza suma elementelor fiecarei matrice intr-un vector de sume, iar mai apoi sorteaza matricile din vector in ordinea crescatoare a sumelor
void sortare_matrice(int *suma_matrice, int size, int ***vector_of_matrixes, int *linie_i, int *coloana_j) {
    for(int i = 0; i < size - 1; i++) {
        suma_matrice[i] = 0;
        for(int j = 0; j < linie_i[i]; j++) {
            for(int k = 0; k < coloana_j[i]; k++) {
                if(vector_of_matrixes[i][j][k] >= 0) suma_matrice[i] = suma_matrice[i] + (vector_of_matrixes[i][j][k] % 10007);
                else suma_matrice[i] = suma_matrice[i] + (vector_of_matrixes[i][j][k] % 10007 + 10007);
            }
        }
        suma_matrice[i] = suma_matrice[i] % 10007;
    }
    //BubbleSort
    for (int contor1 = 0; contor1 < size - 2; contor1++)
    {
        for (int contor2 = 0; contor2 < size - contor1 - 2; contor2++)
        {
            if (suma_matrice[contor2] > suma_matrice[contor2+1])
            {
                //interschimbarea sumelor, matricelor si a numarului de linii, coloane corespunzatoare matricelor
                int temp_value = suma_matrice[contor2];
                int **temp_value2 = vector_of_matrixes[contor2];
                int temp_value_linie = linie_i[contor2];
                int temp_value_coloana = coloana_j[contor2]; 
                suma_matrice[contor2] = suma_matrice[contor2 + 1];
                vector_of_matrixes[contor2] = vector_of_matrixes[contor2 + 1];
                linie_i[contor2] = linie_i[contor2 + 1];
                coloana_j[contor2] = coloana_j[contor2 + 1];
                suma_matrice[contor2 + 1] = temp_value;
                vector_of_matrixes[contor2 + 1] = temp_value2;
                linie_i[contor2 + 1] = temp_value_linie;
                coloana_j[contor2 + 1] = temp_value_coloana;
            }
        }
    }
}

// functia elibereaza o matrice din memorie 
void stergere_matrice(int **matrice, int linie)
{
    for (int i = 0; i < linie; i++)
        free(matrice[i]);
    free(matrice);
}

// functia inmulteste 2 matrici patratice
void multiplicare_matrice_patratica(int **mat1, int **mat2, int nr_linii_coloane) {
    int **temp_matrice = NULL;
    temp_matrice = (int **)malloc(nr_linii_coloane * sizeof(int *));
    if (!temp_matrice) {
        fprintf(stderr, "malloc() failed\n");
        exit(0);
    }
    for(int i = 0; i < nr_linii_coloane; i++) {
        temp_matrice[i] = (int *)malloc(nr_linii_coloane * sizeof(int));
        if(!temp_matrice[i]) {
            fprintf(stderr, "malloc() failed\n");
            while(--i >= 0) {
                free(temp_matrice[i]);
            }
            free(temp_matrice);
            exit(0);
        }
    }
    for(int i = 0 ; i < nr_linii_coloane; i++)
        for(int j = 0; j < nr_linii_coloane; j++) {
            temp_matrice[i][j] = 0;
            for(int k = 0; k < nr_linii_coloane; k++) {
                if(mat1[i][k] * mat2[k][j] >= 0)
                    temp_matrice[i][j] += (mat1[i][k] * mat2[k][j] % 10007);
                else {
                    temp_matrice[i][j] += (mat1[i][k] * mat2[k][j] % 10007 + 10007);
                }
            }
        }
    for(int i = 0; i < nr_linii_coloane; i++)
        for(int j = 0; j < nr_linii_coloane; j++) {
            temp_matrice[i][j] %= 10007;
            // prima matrice folosita la inmultire devine matricea inmultita
            mat1[i][j] = temp_matrice[i][j];
        }
    stergere_matrice(temp_matrice, nr_linii_coloane);
}

// functia ridica matricea la o putere in timp logaritmic, apeland functia precedenta care inmulteste 2 matrici patratice
void ridicare_la_putere(int **mat, int nr_linii_coloane, int putere) {
    int **matrice = NULL;
    matrice = (int **)malloc(nr_linii_coloane * sizeof(int *));
    if (!matrice) {
        fprintf(stderr, "malloc() failed\n");
        exit(0);
    }
    for(int i = 0; i < nr_linii_coloane; i++) {
        matrice[i] = (int *)malloc(nr_linii_coloane * sizeof(int));
        if(!matrice[i]) {
            fprintf(stderr, "malloc() failed\n");
            while(--i >= 0) {
                free(matrice[i]);
            }
            free(matrice);
            exit(0);
        }
    }
    for(int i = 0; i < nr_linii_coloane; i++)
        for(int j = 0; j < nr_linii_coloane; j++) {
            matrice[i][j] = mat[i][j];
        }
    putere--;
    while(putere > 0) {
        if(putere % 2 == 1) {
            multiplicare_matrice_patratica(mat, matrice, nr_linii_coloane);
        }
        multiplicare_matrice_patratica(matrice, matrice, nr_linii_coloane);
        putere /= 2;
    }
    stergere_matrice(matrice, nr_linii_coloane);
}

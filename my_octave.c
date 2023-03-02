// Copyright Cretu Mihnea Tudor 315CAa 2022 - 2023
#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main()
{

    char litera;
    int ***vector_of_matrixes = NULL;
    // se declara vectorii corespunzatori numarului de linii, respectiv coloane a matricelor (linie_i, coloana_j)
    int *linie_i = NULL;
    int *coloana_j = NULL;
    int *suma_matrice = NULL;
    int linie, coloana;
    int size = 1;

    while (1) //iesirea din while se produce dupa ce se elibereaza toata memoria 
    {
        scanf(" %c", &litera); 
        if (litera == 'L')
        {
            scanf("%d %d", &linie, &coloana);
            // se realoca memorie pentru vectorul de matrici, suma unei matrice si pentru vectorii de linii si coloane a matricelor  
            linie_i = realloc(linie_i, size * sizeof(int));
            linie_i[size - 1] = linie;
            coloana_j = realloc(coloana_j, size * sizeof(int));
            coloana_j[size - 1] = coloana;
            suma_matrice = realloc(suma_matrice, size * sizeof(int));
            vector_of_matrixes = alocare_matrice_in_vector(vector_of_matrixes, linie, coloana, size);
            for (int i = 0; i < linie; i++)
            {
                for (int j = 0; j < coloana; j++)
                {
                    int element;
                    scanf("%d", &element);
                    vector_of_matrixes[size - 1][i][j] = element;
                }
            }
            size++;
        }

        else if (litera == 'D')
        {
            // se afiseaza dimensiunile matricei de la pozitia data in vectorul de matrici
            int index_matrice;
            scanf("%d", &index_matrice);
            if (index_matrice >= size - 1 || index_matrice < 0)
                printf("No matrix with the given index\n");
            else
                printf("%d %d\n", linie_i[index_matrice], coloana_j[index_matrice]);
        }

        else if (litera == 'P')
        {
            // se apeleaza functia care afiseaza elementele unei matrice
            afisare_matrice(vector_of_matrixes, linie_i, coloana_j, size);
        }

        else if (litera == 'C')
        {
            // se redimensioneaza matricea de la pozitia data in vector
            int index_matrice, nr_permutare_linii, nr_permutare_coloane;
            int *permutare_linii = NULL;
            int *permutare_coloane = NULL;
            scanf("%d", &index_matrice);
            if (index_matrice >= size - 1 || index_matrice < 0)
                printf("No matrix with the given index\n");
            else
            {
                int **temp_matrice = vector_of_matrixes[index_matrice];
                scanf("%d", &nr_permutare_linii);
                permutare_linii = alocare_permutare_linii(nr_permutare_linii);
                scanf("%d", &nr_permutare_coloane);
                permutare_coloane = alocare_permutare_coloane(nr_permutare_coloane);
                vector_of_matrixes[index_matrice] = realocare_matrice(vector_of_matrixes, index_matrice, nr_permutare_linii, nr_permutare_coloane, permutare_linii, permutare_coloane);
                // elibereaza zona de memorie  amatricei inainte de realocarea sa
                stergere_matrice(temp_matrice, linie_i[index_matrice]);
                // schimba numarul de linii si coloane corespunzatoare matricei dupa realocare
                linie_i[index_matrice] = nr_permutare_linii;
                coloana_j[index_matrice] = nr_permutare_coloane;
                free(permutare_coloane);
                free(permutare_linii);
            }
        }

        else if (litera == 'M')
        {
            // se inmultesc 2 matrici si se adauga matricea inmultita la finalul vectorului de matrici
            int index_matrice1, index_matrice2;
            scanf("%d", &index_matrice1);
            scanf("%d", &index_matrice2);
            if (index_matrice1 >= size - 1 || index_matrice1 < 0)
                printf("No matrix with the given index\n");
            else if (index_matrice2 >= size - 1 || index_matrice2 < 0)
                printf("No matrix with the given index\n");
            else if (coloana_j[index_matrice1] != linie_i[index_matrice2]) printf("Cannot perform matrix multiplication\n");
            else 
            {
                // se realoca memorie pentru matricea inmultita, adaugata la finalul vectorului
                linie_i = realloc(linie_i, size * sizeof(int));
                linie_i[size - 1] = linie_i[index_matrice1];
                coloana_j = realloc(coloana_j, size * sizeof(int));
                coloana_j[size - 1] = coloana_j[index_matrice2];
                suma_matrice = realloc(suma_matrice, size * sizeof(int));
                vector_of_matrixes = alocare_matrice_in_vector(vector_of_matrixes, linie_i[index_matrice1], coloana_j[index_matrice2], size);
                matrice_inmultita(vector_of_matrixes, vector_of_matrixes[index_matrice1], vector_of_matrixes[index_matrice2], linie_i, coloana_j, index_matrice1, index_matrice2, size);
                size++;
            }
        }

        else if(litera == 'O') {
            // se sorteaza matricile din vector in ordine crescatoare in functie de suma elementelor matricei
            sortare_matrice(suma_matrice, size, vector_of_matrixes, linie_i, coloana_j);
        }

        else if(litera == 'T') {
            // se face transpunerea unei matrici de la pozitia data in vectorul de matrici
            int index_matrice;
            scanf("%d", &index_matrice);
            if (index_matrice >= size - 1 || index_matrice < 0)
                printf("No matrix with the given index\n");
            else {
                int linie_transpusa = coloana_j[index_matrice];
                int coloana_transpusa = linie_i[index_matrice];
                int **mat_aux = NULL;
                mat_aux = (int **)malloc(linie_transpusa * sizeof(int *));
                if (!mat_aux) {
                    fprintf(stderr, "malloc() failed\n");
                    return 0;
                }
                for(int i = 0; i < linie_transpusa; i++) {
                    mat_aux[i] = (int *)malloc(coloana_transpusa * sizeof(int));
                    if(!mat_aux[i]) {
                        fprintf(stderr, "malloc() failed\n");
                        while(--i >= 0) {
                            free(mat_aux[i]);
                        }
                        free(mat_aux);
                        return 0;
                    }
                }
                int **temp_matrice = vector_of_matrixes[index_matrice];
                // transpunerea matricei
                for(int i = 0; i < linie_transpusa; i++)
                    for(int j = 0; j < coloana_transpusa; j++) {
                        mat_aux[i][j] = temp_matrice[j][i];
                    }
                vector_of_matrixes[index_matrice] = mat_aux;
                // se elibereaza zona de memorie pentru matricea din vector inainte de transpunerea sa
                stergere_matrice(temp_matrice, linie_i[index_matrice]);
                // se inverseaza numarul de linii si coloane corespunzator matricei, conform definitiei transpunerii
                linie_i[index_matrice] = linie_transpusa;
                coloana_j[index_matrice] = coloana_transpusa;
            }
        }

        else if(litera == 'R') {
            // calculeaza ridicarea la putere in timp logaritmic a unei matrici de la pozitia data din vector
            int index_matrice, putere;
            scanf("%d %d", &index_matrice, &putere);
            if (index_matrice >= size - 1 || index_matrice < 0)
                printf("No matrix with the given index\n");
            if(putere < 0) printf("Power should be positive\n");
            if(linie_i[index_matrice] != coloana_j[index_matrice]) printf("Cannot perform matrix multiplication\n");
            if(index_matrice < size - 1 && index_matrice >= 0 && putere >= 0 && linie_i[index_matrice] == coloana_j[index_matrice]) {
                ridicare_la_putere(vector_of_matrixes[index_matrice], linie_i[index_matrice], putere);
            }
        }

        else if(litera == 'F') {
            // se sterge matricea de la pozitia data in vector si se elibereaza zona de memorie corespunzatoare matricei
            int index_matrice;
            scanf("%d", &index_matrice);
            if (index_matrice >= size - 1 || index_matrice < 0)
                printf("No matrix with the given index\n");
            else {
                stergere_matrice(vector_of_matrixes[index_matrice], linie_i[index_matrice]);
                for(int i = index_matrice; i < size - 2; i++) {
                    vector_of_matrixes[i] = vector_of_matrixes[i+1];
                    linie_i[i] = linie_i[i+1];
                    coloana_j[i] = coloana_j[i+1];
                }
                // realocarea necesara dupa stergerea matricei
                vector_of_matrixes = (int ***)realloc(vector_of_matrixes, (size - 1) * sizeof(int **));
                linie_i = (int *)realloc(linie_i, (size - 1) * sizeof(int));
                coloana_j = (int *)realloc(coloana_j, (size - 1) * sizeof(int));
                suma_matrice = (int *)realloc(suma_matrice, (size - 1) * sizeof(int));
                size -= 1;
            }
        }

        else if (litera == 'Q')
        {
            // se elibereaza memoria folosita si programul se termina
            for (int i = 0; i < size - 1; i++)
            {
                stergere_matrice(vector_of_matrixes[i], linie_i[i]);
            }
            free(vector_of_matrixes);
            free(linie_i);
            free(coloana_j);
            free(suma_matrice);
            break;
        }
        // cazul in care se citeste o litera diferita fata de cele folosite pentru procesele efectuate asupra matricei si a vectorului de matrici
        else if(litera >= 'A' && litera <= 'Z') printf("Unrecognized command\n"); 
    }

    return 0;
}
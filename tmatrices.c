#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdbool.h>


int main() {

    printf("tmatrices.c compilé\n");

    matrice* mat1 = mat_create(3, 5, -1.0);

    double array1[15] = {1, 2, 3, 4 ,5 ,6 ,7 ,8 ,9 ,10, 11, 12, 13, 14, 15};

    printf("%d %d\n", mat_ligne(mat1), mat_colonne(mat1));

    matrice* mat2 = mat_create(5, 3, -5.0);

    mat_array_en_matrice(mat1, array1);

    printf("\n");
    mat_affiche(mat1);
    printf("\n");
    mat_affiche(mat2);

    matrice* mat3 = mat_produit(mat2, mat1);

    printf("\n");
    mat_affiche(mat3);

    
    mat_free(mat1);
    mat_free(mat2);
    mat_free(mat3);

    double array2[4] = {0, 1, 0, 0};
    double array3[4] = {0, 0, 1, 0};
    double array4[4] = {5, 5, 5, 5};

    matrice* mat4 = mat_create(2, 2, -5.0);
    mat_array_en_matrice(mat4, array2);
    matrice* mat5 = mat_create(2, 2, -5.0);
    mat_array_en_matrice(mat5, array3);
    matrice* mat6 = mat_create(2, 2, -5.0);
    mat_array_en_matrice(mat6, array4);

    matrice* mat7 = mat_produit(mat4, mat6);
    matrice* mat8 = mat_produit(mat7, mat5);

    mat_affiche(mat8);

    mat_free(mat4);
    mat_free(mat5);
    mat_free(mat6);
    mat_free(mat7);
    mat_free(mat8);

    //free(array1);

    return EXIT_SUCCESS;
}

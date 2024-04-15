#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


int main() {
    
    double array1[15] = {1, 2, 3, 4 ,5 ,6 ,7 ,8 ,9 ,10, 11, 12, 13, 14, 15};

    matrice* mat1 = mat_create(5, 3, -1.0);

    printf("%d %d\n", mat_longueur(mat1), mat_largeur(mat1));

    matrice* mat2 = mat_create(3, 5, -3.0);

    mat_array_en_matrice(mat1, array1);

    mat_affiche(mat1);
    mat_affiche(mat2);

    matrice* mat3 = mat_produit(mat2, mat1);

    mat_affiche(mat3);

    mat_free(mat1);
    mat_free(mat2);
    mat_free(mat3);

    //free(array1);

    return EXIT_SUCCESS;
}
#include "matrice.h"

// gcc tmatrices.c matrice.c matrice.h -o exe -lm -Wall -Wextra -Wvla -Wall -Wextra -pedantic -fsanitize=address --std=c17


/* Création, conversion, suppression */

matrice* mat_create(int n, int p, double val) {
    /*
    (a1,1  a1,2  ......  a1,p)    
    (a2,1  a2,2  ......      )
    ( .     ..               )
    ( .     ..               )
    ( .     ..               )
    (an,1  an,2  ....... an,p)
    
    */

    double** mat = malloc(p * sizeof(double*));

    for (int i = 0; i < p; i++) {
        mat[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            mat[i][j] = val;
        }
    }

    matrice* matr = malloc(sizeof(matrice));
    matr->n = n;
    matr->p = p;
    matr->tab = mat;

    return matr;
}

void mat_free(matrice* mat) {
    // leak mémoire selon AddressSanitizer :c (mais pas toujours)

    for (int i = 0; i < mat->p; i++) {
        free((mat->tab)[i]);
    }
    free(mat->tab);
    free(mat);
}

/* Accesseurs */

int mat_longueur(matrice* mat) {
    return mat->p;
}


int mat_largeur(matrice* mat) {
    return mat->n;
}


/* Mutateurs */

void mat_array_en_matrice(matrice* mat, double* array) {

    // TODO: a voir comment arranger ça : 
    //https://stackoverflow.com/questions/25680014/find-the-size-of-integer-array-received-as-an-argument-to-a-function-in-c
    // assert((sizeof(array)/sizeof(double)) == (mat->n)*(mat->p));
    
    int taille = (mat->n)*(mat->p);
    int divi = mat->n;

    for (int i = 0; i < taille; i++) {
        (mat->tab)[i/divi][i%divi] = array[i];
    }

}


/* Misceleanous */

void arr_affiche(double array[], int taille) {
    printf("[");
    for (int i = 0; i < taille; i++) {
        printf("%.2f", roundf(array[i] * 100) / 100); // Arrondi à deux décimales
        if (i < taille - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void mat_affiche(matrice const* mat) {

    for (int i = 0; i < mat->p; i++) {
        arr_affiche(mat->tab[i], mat->n);
    }
}



/* Opérations */

matrice* mat_operation(matrice* mat1, matrice* mat2, double (*point_func)(double, double)) {

    // TODO: si les matrcies ne sont pas de même taille, je met un assert pour le moment

    assert(mat1->n == mat2->n);
    assert(mat1->p == mat2->p);

    matrice* mat3 = mat_create(mat2->p, mat2->n, 0);

    for (int i = 0; i < mat3->n; i++) {
        for (int j = 0; j < mat3->p; j++) {
            mat3->tab[i][j] = (*point_func)(mat1->tab[i][j], mat2->tab[i][j]);
        }
    }

    return mat3;
}

double somme(double a, double b) {
    return a + b;
}

matrice* mat_somme(matrice* mat1, matrice* mat2) {
    return mat_operation(mat1, mat2, &somme);
}

double difference(double a, double b) {
    return a - b;
}

matrice* mat_difference(matrice* mat1, matrice* mat2) {
    return mat_operation(mat1, mat2, &difference);
}



matrice* mat_produit(matrice* mat1, matrice* mat2) {

    printf("%d %d\n", mat1->n, mat2->p);
    printf("%d\n", mat1->p == mat2->n);

    assert(mat1->p == mat2->n);

    matrice* mat = mat_create(mat1->p, mat2->n, 0);

    for (int i = 0; i < mat1->p; i++) {
        for (int j = 0; j < mat2->n; j++) { 
            for (int k = 0; k < mat2->p; k++) {
                mat->tab[i][j] += mat1->tab[i][k] * mat2->tab[k][j];
            }
        }
    }

    return mat;
}
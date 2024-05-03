#include "matrice.h"

// gcc tmatrices.c matrice.c matrice.h -o exe -lm -Wall -Wextra -Wvla -Wall -Wextra -pedantic -fsanitize=address --std=c17

// gcc tmatrices.c matrice.c matrice.h -o exe -lm -Wall -Wextra -Wvla -Wall -Wextra -pedantic --std=c17


/* Création, conversion, suppression */

matrice* mat_create(int ligne, int colonne, double val) {
    /*
    (a1,1  a1,2  ......  a1,p)    
    (a2,1  a2,2  ......      )
    ( .     ..               )
    ( .     ..               )
    ( .     ..               )
    (an,1  an,2  ....... an,p)
    */

    double** mat = malloc(ligne * sizeof(double*));

    for (int i = 0; i < ligne; i++) {
        mat[i] = malloc(colonne * sizeof(double));
        for (int j = 0; j < colonne; j++) {
            mat[i][j] = val;
        }
    }

    matrice* matr = malloc(sizeof(matrice));
    matr->col = colonne;
    matr->lig = ligne;
    matr->tab = mat;

    return matr;
}


matrice* mat_create_identite(int taille) {

    matrice* id = mat_create(taille, taille, 0);
    
    for (int i = 0; i < taille; i++) {
        (id->tab)[i][i] = 1;
    }

    return id;
}

/* TODO

matrice* mat_create_random_int(int ligne, int colonne, int debut, int fin);

matrice* mat_create_random_double(int ligne, int colonne, int debut, int fin);


*/


void mat_free(matrice* mat) {

    for (int i = 0; i < mat->lig; i++) {
        free((mat->tab)[i]);
    }
    free(mat->tab);
    free(mat);
}

/* Accesseurs */

int mat_colonne(matrice* mat) {
    return mat->col;
}


int mat_ligne(matrice* mat) {
    return mat->lig;
}


/* Mutateurs */

void mat_array_en_matrice(matrice* mat, double* array) {

    // TODO: a voir comment arranger ça : 
    //https://stackoverflow.com/questions/25680014/find-the-size-of-integer-array-received-as-an-argument-to-a-function-in-c
    // assert((sizeof(array)/sizeof(double)) == (mat->n)*(mat->p));
    // voir metadonne de gcc array[-1]
    // ATTENTION : SE METTRE D'ACCORD VERSION GCC AVEC KEVEN

    int taille = (mat->lig)*(mat->col);
    int divi = mat->col;

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

    for (int i = 0; i < mat->lig; i++) {
        arr_affiche(mat->tab[i], mat->col);
    }
}



/* Opérations */

matrice* mat_operation(matrice* mat1, matrice* mat2, double (*point_func)(double, double)) {

    // TODO: si les matrcies ne sont pas de même taille, je met un assert pour le moment

    assert(mat1->lig == mat2->lig);
    assert(mat1->col == mat2->col);

    matrice* mat3 = mat_create(mat2->lig, mat2->col, 0);

    for (int i = 0; i < mat3->lig; i++) {
        for (int j = 0; j < mat3->col; j++) {
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

    assert(mat2->col == mat1->lig);

    matrice* mat = mat_create(mat2->lig, mat1->col, 0);

    for (int i = 0; i < mat2->lig; i++) {
        for (int j = 0; j < mat1->col; j++) {
            for (int k = 0; k < mat2->col; k++) {
                mat->tab[i][j] += mat2->tab[i][k] * mat1->tab[k][j];
            }
        }
    }

    return mat;
}




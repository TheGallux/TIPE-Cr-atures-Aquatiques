#include "matrice.h"


/* Création, conversion, suppression */

// Crée une matrice de taille (colonne X ligne) remplie de val.
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

// Crée la matrice identitée.
matrice* mat_create_identite(int taille) {

    matrice* id = mat_create(taille, taille, 0);
    
    for (int i = 0; i < taille; i++) {
        (id->tab)[i][i] = 1;
    }

    return id;
}


// Crée une matrice d'entier aléatoire entre [debut, fin[. De taille colonne X ligne.
matrice* mat_create_random_int(int ligne, int colonne, int debut, int fin) {

    assert(fin > debut);
    srand(time(NULL));

    matrice* mat = mat_create(ligne, colonne, 0); 

    for (int i = 0; i < ligne; i++ ){ 
        for (int j = 0; j < colonne; j++){
            (mat->tab)[i][j] = (rand() % (fin - debut) + debut);
        }
    } 
    
    return mat;
}

// Créer la fonction aléatoire pour les doubles.
double randfrom(double min, double max){
    double range =(max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

// Créer une matrice de double aléatoire entre [debut, fin[. De taille colonne X ligne.
matrice* mat_create_random_double(int ligne, int colonne, double debut, double fin){
    assert(fin > debut);
    srand(time(NULL));

    matrice* mat = mat_create(ligne, colonne, 0); 

    for (int i = 0; i < ligne; i++ ){ 
        for (int j = 0; j < colonne; j++){
            (mat->tab)[i][j] = randfrom(debut, fin); 
        }
    } 
    
    return mat;
}


// Libère la matrice donnée.
void mat_free(matrice* mat) {

    for (int i = 0; i < mat->lig; i++) {
        free((mat->tab)[i]);
    }
    free(mat->tab);
    free(mat);
}


/* Accesseurs */

// Renvoie le nombre de colonnes d'une matrice donnée.
int mat_colonne(matrice* mat) {
    return mat->col;
}

// Renvoie le nombre de lignes d'une matrice donnée.
int mat_ligne(matrice* mat) {
    return mat->lig;
}


/* Mutateurs */

// Prends un argument un matrice de taille (colonne X ligne) et un array de longueur taille*colonne
// 
// Matrice :                        Array :
// (a1,1  a1,2  ......  a1,p)       [| x1, x2, ..., x(n*p)|]
// (a2,1  a2,2  ......      )
// ( .     ..               )
// ( .     ..               )
// ( .     ..               )
// (an,1  an,2  ....... an,p)
//
// On obtient la matrice : 
//
// (  x1    x2   ......   xp )
// ( xp+1  xp+2  ......      )
// (  .     ..               )
// (  .     ..               )
// (  .     ..               )
// (  .     ..  .......  xn*p)
void mat_array_en_matrice(matrice* mat, double* array) {

    // TODO: a voir comment arranger ça : 
    // https://stackoverflow.com/questions/25680014/find-the-size-of-integer-array-received-as-an-argument-to-a-function-in-c
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

// Affiche un array de double de taille donné.
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

// Affiche une matrice.
void mat_affiche(matrice const* mat) {

    for (int i = 0; i < mat->lig; i++) {
        arr_affiche(mat->tab[i], mat->col);
    }
}



/* Opérations */

// A une fonction f et deux matrices de même taille M et N, associce f(M, N)
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

// Renvoie la somme de deux matrices.
matrice* mat_somme(matrice* mat1, matrice* mat2) {
    return mat_operation(mat1, mat2, &somme);
}


double difference(double a, double b) {
    return a - b;
}


// Renvoie la différence de deux matrices.
matrice* mat_difference(matrice* mat1, matrice* mat2) {
    return mat_operation(mat1, mat2, &difference);
}



// Renvoie le produit de deux matrices.
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

// Pour tout entier naturel n, renvoie M^n
matrice* mat_puissance(matrice* mat, int n) {
    if (n == 0) {
        return mat_create_identite(mat_ligne(mat));
    }
    if (n == 1) {
        return mat;
    }
    matrice* matn = mat_produit(mat, mat);
    for (int i = 0; i < n - 2; i++) {
        matn = mat_produit(matn, mat);
    }

    return matn;
}


matrice* mat_sigmoide(matrice* mat) {
    matrice* mat2 = mat_create(mat->lig, mat->col, 0);

    for (int i = 0; i < mat->lig; i++) {
        mat2->tab[0][i] = 1.0 / (1.0 + exp(-mat->tab[0][i]));
    }

    return mat2;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

struct matrice {
 double** tab; // pointeur vers les cases du tableau dynamique
 int n;    // longueur du tableau
 int p;  // largeur du tableau
};
typedef struct matrice matrice;


/* Création, conversion, suppression */

/** Crée un tableau dynamique de longueur len initialisé à x.*/
matrice* mat_create(int n, int p, double val);

void mat_free(matrice* mat);


/* Accesseurs */

int mat_longueur(matrice* mat);

int mat_largeur(matrice* mat);

/* Mutateurs */

void mat_array_en_matrice(matrice* mat, double* array);

/* Misceleanous */

/** Affiche un tableau dynamique */
void mat_affiche(matrice const* a);


/* Opéatations */

matrice* mat_operation(matrice* mat1, matrice* mat2, double (*point_func)(double, double));

matrice* mat_somme(matrice* mat1, matrice* mat2);

matrice* mat_difference(matrice* mat1, matrice* mat2);

matrice* mat_produit(matrice* mat1, matrice* mat2);

matrice* mat_puissance(matrice* mat1, int expo);
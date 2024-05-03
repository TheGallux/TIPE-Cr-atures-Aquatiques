#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

struct matrice {
 double** tab; // pointeur vers les cases du tableau dynamique
 int col;      // colonnes du tableau
 int lig;      // lignes du tableau
};
typedef struct matrice matrice;


/* Création, conversion, suppression */

/** Crée un tableau dynamique de longueur len initialisé à x.*/
matrice* mat_create(int ligne, int colonne, double val);

matrice* mat_create_identite(int taille);

matrice* mat_create_random_int(int ligne, int colonne, int debut, int fin);

matrice* mat_create_random_double(int ligne, int colonne, int debut, int fin);

void mat_free(matrice* mat);


/* Accesseurs */

int mat_ligne(matrice* mat);

int mat_colonne(matrice* mat);

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
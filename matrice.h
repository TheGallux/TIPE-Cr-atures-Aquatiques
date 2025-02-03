#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <time.h>

struct matrice {
 double** tab; // pointeur vers les cases du tableau dynamique
 int col;      // colonnes du tableau
 int lig;      // lignes du tableau
};
typedef struct matrice matrice;



//* Création, suppression *//

// Crée une matrice de taille (colonne X ligne) remplie de val.
matrice* mat_create(int ligne, int colonne, double val);

// Crée la matrice identitée.
matrice* mat_create_identite(int taille);

// Crée une matrice d'entier aléatoire entre [debut, fin[. De taille colonne X ligne.
matrice* mat_create_random_int(int ligne, int colonne, int debut, int fin);

// Créer une matrice de double aléatoire entre [debut, fin[. De taille colonne X ligne.
matrice* mat_create_random_double(int ligne, int colonne, double debut, double fin);

// Libère la matrice donnée.
void mat_free(matrice* mat);


/* Accesseurs */

// Renvoie le nombre de lignes d'une matrice donnée.
int mat_ligne(matrice* mat);

// Renvoie le nombre de colonnes d'une matrice donnée.
int mat_colonne(matrice* mat);

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
void mat_array_en_matrice(matrice* mat, double* array);

/* Misceleanous */

// Affiche une matrice.
void mat_affiche(matrice const* a);


/* Opérations */

// A une fonction f et deux matrices de même taille M et N, associce f(M, N)
matrice* mat_operation(matrice* mat1, matrice* mat2, double (*point_func)(double, double));

// Renvoie la somme de deux matrices.
matrice* mat_somme(matrice* mat1, matrice* mat2);

// Renvoie la différence de deux matrices.
matrice* mat_difference(matrice* mat1, matrice* mat2);

// Renvoie le produit de deux matrices.
matrice* mat_produit(matrice* mat1, matrice* mat2);

// Pour tout entier naturel n, renvoie M^n
matrice* mat_puissance(matrice* mat1, int n);

// Prends une matrice colonne en entrée, et renvoie une nouvelle matrice, qui est remplie des sigmoides des valeurs données en entrée
matrice* mat_sigmoide(matrice* mat);
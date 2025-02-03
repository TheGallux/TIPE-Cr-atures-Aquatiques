#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <time.h>

struct reseau_de_neurones {
 matrice** couches; // pointeur vers les couches du réseau
 matrice** biais; // pointeur vers les biais du réseau
 int longueur;      // nombre de couches
};
typedef struct reseau_de_neurones reseau;

//* Création, suppression *//

// Crée un reseau de neurones de n couches de tailles [C_1, ..., C_n] rempli de x
reseau* res_create(int n, int* C, double x);

// Libère un réseau
void res_free(reseau* res);

reseau* res_importer(char* fichier);

void res_exporter(reseau* res, char* fichier);


//* Acceseurs *//

// Renvoie le nombre de cases des matrices
int res_nombre_liens(reseau const* res);

//* Mutateurs *//

// TODO
void res_array_en_reseau_couches(reseau* res, double* array);

// TODO
void res_array_en_reseau_biais(reseau* res, double* array);

// TODO
void res_aleatoire(reseau* res, int debut, int fin, bool biais);


//* Misceleanous *//

// Affiche un réseau.
void res_affiche(reseau const* res);

// 
matrice* res_calculer(reseau const* res, matrice* mat);

//
double res_evaluer_reseau(reseau* res, matrice** jeu_donnes, int longeur, double (*point_func)(reseau*, matrice*));

//
void res_representer(reseau* res, char* fichier);
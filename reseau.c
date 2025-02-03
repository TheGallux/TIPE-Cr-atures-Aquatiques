#include "reseau.h"

//* Création, suppression *//

// Crée un reseau de neurones de n couches de tailles [C_1, ..., C_n] rempli de x
reseau* res_create(int n, int* C, double x) {
    
    matrice** mat_liste = malloc((n - 1) * sizeof(matrice*));
    matrice** biais_liste = malloc((n - 1) * sizeof(matrice*));

    for (int i = 0; i < n - 1; i++) {
        mat_liste[i] = mat_create(C[i + 1], C[i], x);
        biais_liste[i] = mat_create(C[i + 1], 1, 0);
    }
    printf("\n");

    reseau* res = malloc(sizeof(int) + sizeof(mat_liste) + sizeof(biais_liste));
    res -> couches = mat_liste;
    res -> biais = biais_liste;
    res -> longueur = n - 1;

    return res;
}

// Libère un réseau
void res_free(reseau* res) {
    
    for (int i = 0; i < res->longueur; i++) {
        mat_free(res->couches[i]);
        mat_free(res->biais[i]);
    }
    free(res->couches);
    free(res->biais);

    return;
}

reseau* res_importer(char* fichier) {
    FILE* fptr = fopen(fichier, "r");

    int n;
    fscanf(fptr, "%d", &n);

    matrice** couches = malloc(n * sizeof(matrice*));
    matrice** biais = malloc(n * sizeof(matrice*));

    for (int i = 0; i < n; i++) {
        int lo, la;
        fscanf(fptr, "%d %d", &lo, &la); 

        matrice* mat_i = mat_create(lo, la, 0);
        for (int j = 0; j < lo; j++) {
            for (int k = 0; k < la; k++) {
                fscanf(fptr, "%lf", &mat_i->tab[j][k]);
            }
        }
        couches[i] = mat_i;
    }

    for (int i = 0; i < n; i++) {
        int lo, la;
        fscanf(fptr, "%d %d", &lo, &la); 

        matrice* mat_i = mat_create(lo, la, 0);
        for (int j = 0; j < lo; j++) {
            for (int k = 0; k < la; k++) {
                fscanf(fptr, "%lf", &mat_i->tab[j][k]);
            }
        }
        biais[i] = mat_i;
    }

    fclose(fptr);  // Close the file

    reseau* res = malloc(sizeof(reseau*));
    res->biais = biais;
    res->couches = couches;
    res->longueur = n;

    return res;
}

void res_exporter(reseau* res, char* fichier) {
    FILE *fptr;
    fptr = fopen(fichier, "w");  // Open a file in writing mode

    fprintf(fptr, "%d\n", res->longueur);
    for (int i =0 ; i < res->longueur; i++) {
        fprintf(fptr, "%d %d\n", res->couches[i]->lig, res->couches[i]->col);
        for (int j = 0; j < res->couches[i]->lig; j++) {
            for (int k = 0; k < res->couches[i]->col; k++) {
                fprintf(fptr, "%lf ", res->couches[i]->tab[j][k]);
            }
            fprintf(fptr, "\n");
        }
    }
    
    for (int i =0 ; i < res->longueur; i++) {
        fprintf(fptr, "%d %d\n", res->biais[i]->lig, 1);
        for (int k = 0; k < res->biais[i]->lig; k++) {
            fprintf(fptr, "%lf\n", res->biais[i]->tab[k][0]);
        }
    }

    fclose(fptr);  // Close the file
    
    return;
}


//* Acceseurs *//

int res_nombre_liens(reseau const* res) {
    int S = 0;

    for (int i = 0; i < res->longueur; i++) {
        S = S + (res->couches[i]->col * res->couches[i]->lig);
    }

    return S;
}



//* Mutateurs *//
void res_array_en_reseau_couches(reseau* res, double* array) {

    int pointeur_matrice = 0;

    for (int i = 0; i < res->longueur; i++) {

        double* arr = malloc(sizeof(double) * res->couches[i]->col * res->couches[i]->lig);
        for (int j = 0; j < res->couches[i]->col * res->couches[i]->lig; j++) {
            arr[j] = array[pointeur_matrice + j];
        }
        mat_array_en_matrice(res->couches[i], arr);
        free(arr);
        pointeur_matrice = pointeur_matrice + res->couches[i]->col * res->couches[i]->lig;

    }

    return;
}


void res_array_en_reseau_biais(reseau* res, double* array) {

    int pointeur_matrice = 0;

    for (int i = 0; i < res->longueur; i++) {

        double* arr = malloc(sizeof(double) * res->biais[i]->lig);
        for (int j = 0; j < res->biais[i]->lig; j++) {
            arr[j] = array[pointeur_matrice + j];
        }
        mat_array_en_matrice(res->biais[i], arr);
        free(arr);
        pointeur_matrice = pointeur_matrice + res->biais[i]->lig;

    }

    return;
}

// Créer la fonction aléatoire pour les doubles.
double randfrom2(double min, double max){
    double range =(max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void res_aleatoire(reseau* res, int debut, int fin, bool biais) {
    assert(fin > debut);
    srand(time(NULL));

    for (int i = 0; i < res->longueur; i++) {
        for (int j = 0; j < res->couches[i]->lig; j++) {
            for (int k = 0; k < res->couches[i]->col; k++) {
                res->couches[i]->tab[j][k] = randfrom2(debut, fin);
            }
        }

        if (biais) {
            for (int j = 0; j < res->biais[i]->lig; j++) {
                res->biais[i]->tab[j][0] = randfrom2(debut, fin);
            }
        }
    }

    return;
}

//* Misceleanous *//


// Affiche un réseau.
void res_affiche(reseau const* res) {
    printf("════════════\n");
    for (int i = 0; i < res->longueur; i++) {
        printf("Matrice %d :\n", i);
        mat_affiche(res->couches[i]);
        printf("Biais %d :\n", i);
        mat_affiche(res->biais[i]);
        printf("════════════\n");
    }

    return ;
}


matrice* res_calculer(reseau const* res, matrice* mat) {

    /*printf("%d, %d\n", res->couches[0]->lig, res->couches[0]->col);
    printf("%d, %d\n", mat->col, mat-> lig);*/

    assert(res->couches[0]->col == mat->lig); // on peut bien effectuer une manipulation
    assert(mat->col == 1); // on a bien un vecteur

    for (int i = 0; i < res->longueur; i++) {
        mat = mat_sigmoide(mat_somme(mat_produit(mat, res->couches[i]), res->biais[i]));
    }
    return mat;
}

double res_evaluer_reseau(reseau* res, matrice** jeu_donnes, int longeur, double (*point_func)(reseau*, matrice*)) {

    double S = 0;

    for (int i = 0; i < longeur; i++) {
        //printf("%f | ", (*point_func)(res, jeu_donnes[i]));
        S = S + (*point_func)(res, jeu_donnes[i]);
    }

    return S / longeur;
}



void res_representer(reseau* res, char* fichier) {
    FILE *fptr;
    fptr = fopen(fichier, "w");  // Open a file in writing mode


    // NOEUDS
    fprintf(fptr, "digraph a {\nrankdir = LR;\nsplines=line\nnode [fixedsize=true];\n\nsubgraph cluster_0 {\ncolor=white;\nnode [style=solid,color=blue4, shape=circle];\n");  // Write some text to the file
    for (int i = 0; i < res->couches[0]->col; i++) {
        fprintf(fptr, "x%d ", i+1);
    } fprintf(fptr, ";\n");
    fprintf(fptr, "label = \"Couche d'entrée\";\n}\n\n");


    for (int i = 1; i < res->longueur; i++) {
        fprintf(fptr, "subgraph cluster_%d {\ncolor=white;\nnode [style=solid,color=red2, shape=circle];\n", i);
        for (int j = 0; j < res->couches[i]->col; j++) {
            fprintf(fptr, "a%d%d ", i, j+1);
        } fprintf(fptr, ";\n");
        fprintf(fptr, "label = \"Couche cachée n°%d\";\n}\n\n", i);
    }

    fprintf(fptr,"subgraph cluster_%d {\ncolor=white;\nnode [style=solid,color=seagreen2, shape=circle];\n", res->longueur);
    for (int i = 0; i < res->couches[res->longueur-1]->lig; i++) {
        fprintf(fptr, "y%d ", i+1);
    } fprintf(fptr, ";\n");
    fprintf(fptr, "label = \"Couche de sortie\";\n}\n\n");


    // LIENS
    for (int i = 1; i < res->couches[0]->col + 1; i++) {
        for (int j = 1; j < res->couches[0]->lig + 1; j++) {
            fprintf(fptr, "x%d -> a1%d;\n", i, j);
        }
    }

    for (int i = 1; i < res->longueur - 1; i++) {
        for (int j = 0; j < res->couches[i]->col; j++) {
            for (int k = 0; k < res->couches[i+1]->col; k++) {
                fprintf(fptr, "a%d%d -> a%d%d;\n", i, j + 1, i + 1, k + 1);
            }
        }
    }

    for (int i = 0; i < res->couches[res->longueur - 1]->col; i++) {
        for (int j = 0; j < res->couches[res->longueur - 1]->lig; j++) {
            fprintf(fptr, "a%d%d -> y%d;\n", res->longueur - 1, i + 1, j + 1);
        }
    }
    

    fprintf(fptr, "}");
    fclose(fptr);  // Close the file
    
}
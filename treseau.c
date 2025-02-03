#include "reseau.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdbool.h>
#include <stdbool.h>


// AFFICHER LES DONNES D'ENTRAINEMENT DE CHIFFRES MNIST












double sigmoide(double x) {
    return 1.0 / (1.0 + exp(-x));
}


double heuristique_or(reseau* res, matrice* mat) {
    assert(mat->lig = 2);
    assert(mat->col = 1);

    int comp = 0;
    if (mat->tab[0][0] || mat->tab[1][0]) {
        comp = 1;
    }

    if (comp == (int)round(res_calculer(res, mat)->tab[0][0])) {
        return 1;
    } else {
        return 0;
    }
}


double heuristique_and(reseau* res, matrice* mat) {
    assert(mat->lig = 2);
    assert(mat->col = 1);

    int comp = 0;
    if (mat->tab[0][0] && mat->tab[1][0]) {
        comp = 1;
    }
    if (comp == (int)round(res_calculer(res, mat)->tab[0][0])) {
        return 1;
    } else {
        return 0;
    }
}

int main() {

    printf("treseau.c compilé\n");

    //
    int T[3] = {3, 2, 3};
    reseau* res1 = res_create(3, T, 5.0);

    //
    res_affiche(res1);

    //
    printf("Nombre cases : %d\n", res_nombre_liens(res1));


    //
    double arr[17] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    for (int i = 0; i < 17; i++) {
        printf("%f |", arr[i]);
    } printf("\n");
    res_array_en_reseau_couches(res1, arr);
    res_affiche(res1);

    //
    matrice* mat1 = mat_create(3, 1, 3);
    mat_affiche(mat1);
    matrice* mat2 = res_calculer(res1, mat1);
    mat_affiche(mat2);

    // PREMIER EXEMPLE
    int l_couches[3] = {2, 2, 1};
    reseau* res_and = res_create(3, l_couches, 0);
    double couches_cachees[6] = {2, 2, 2, 2, 2, 2};
    double biais[3] = {-3, -3, -1};
    res_array_en_reseau_biais(res_and, biais);
    res_array_en_reseau_couches(res_and, couches_cachees);
    res_affiche(res_and);
    matrice* mat_test = mat_create(2, 1, 0);
    double boolens[2] = {0, 0};
    mat_array_en_matrice(mat_test, boolens);
    // heuristique du réseau
    matrice** jeu = malloc(sizeof(matrice*) * 4);
    for (int i = 0; i < 4; i++) {
        jeu[i] = mat_create(2, 1, 0);
        jeu[i]->tab[0][0] = i / 2;
        jeu[i]->tab[1][0] = i % 2;

        printf("| %lf\n", res_calculer(res_and, jeu[i])->tab[0][0]);
    }
    printf("Heuristique du réseau AND (avec heuristique_and) : %f\n", res_evaluer_reseau(res_and, jeu, 4, heuristique_and));
    printf("Heuristique du réseau AND (avec heuristique_or) : %f\n", res_evaluer_reseau(res_and, jeu, 4, heuristique_or));

    int couches_cachees2[3] = {2, 2, 1};
    reseau* res_or = res_create(3, couches_cachees2, 0);
    res_affiche(res_or);
    res_aleatoire(res_or, -10, 10, true);
    res_affiche(res_or);


    //
    int couches_nombres[5] = {5, 4, 3, 4, 5};
    reseau* res_graphviz = res_create(5, couches_nombres, 0);
    res_aleatoire(res_graphviz, -1, 10, true);

    //
    /*res_representer(res_graphviz, "res_graphviz.txt");
    res_exporter(res_graphviz, "test.txt");

    //
    reseau* res_xor = res_importer("res_xor.txt");
    res_affiche(res_xor);
    printf("Heuristique du réseau XOR (avec heuristique_or) : %f\n", res_evaluer_reseau(res_xor, jeu, 4, heuristique_or));
    for (int i = 0; i < 4; i++) {
        mat_affiche(res_calculer(res_xor, jeu[i]));
    }

    //
    reseau* res2 = res_importer("test.txt");
    res_affiche(res2);
    res_representer(res2, "test2.txt");*/


    //
    res_free(res1);
    res_free(res_and);
    mat_free(mat_test);
    mat_free(mat1);
    mat_free(mat2);
    for (int i = 0; i < 4; i++) {
        mat_free(jeu[i]);
    } free(jeu);
    res_free(res_or);
    res_free(res_graphviz);
    //res_free(res_xor);
    //res_free(res2);

    return EXIT_SUCCESS;
}
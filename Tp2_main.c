#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "hash.h"
#include "hash_fun.h"

#define TAILLE_MAX 256

/* Compte le nombre de mots dans un fichier*/
int compter_lignes(const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "r");
    assert(f != NULL);
    int lignes = 0;
    char buffer[TAILLE_MAX];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        lignes++;
    }
    fclose(f);
    return lignes;
}


void afficher_stats(const hash *ht, int nb_mots, const char *nom_fichier,
                    const char *nom_fonction) {
    int collisions      = 0;
    int indices_occupes = 0;

    for (int i = 0; i < ht->capacity; i++) {
        int count = 0;
        node *cur = ht->h[i];
        while (cur) { count++; cur = cur->next; }
        if (count > 1) collisions += count - 1;
        if (count > 0) indices_occupes++;
    }

    printf("\n--- Statistiques [%s | %s] ---\n", nom_fichier, nom_fonction);
    printf("Taille table       : %d\n", ht->capacity);
    printf("Mots insérés       : %d\n", nb_mots);
    printf("Collisions         : %d (%.1f%%)\n", collisions, nb_mots ? collisions * 100.0 / nb_mots : 0.0);
    printf("Taux d'occupation  : %.2f%%\n", (float)indices_occupes / ht->capacity * 100.0f);
}



int remplir_table(hash *ht, const char *nom_fichier,
                  hash_func_t hash_func) {
    FILE *f = fopen(nom_fichier, "r");
    assert(f != NULL);
    char ligne[TAILLE_MAX];
    int nb_mots = 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        ligne[strcspn(ligne, "\n")] = '\0'; /* supprimer '\n' */
        if (ligne[0] == '\0') continue;     /* ignorer lignes vides */
        hash_add(ht, ligne, hash_func);
        nb_mots++;
    }
    fclose(f);
    return nb_mots;
}


int calculer_intersection(const hash *ht, const char *nom_fichier2,
                           hash_func_t hash_func) {
    FILE *f = fopen(nom_fichier2, "r");
    assert(f != NULL);
    char ligne[TAILLE_MAX];
    int communs = 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        ligne[strcspn(ligne, "\n")] = '\0';
        if (ligne[0] == '\0') continue;

        if (is_member((hash *)ht, ligne, hash_func)) {
            printf("%s\n", ligne);
            communs++;
        }
    }
    fclose(f);
    return communs;
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage : %s <fichier1> <fichier2>\n", argv[0]);
        return 1;
    }

    const char *fichier1 = argv[1];
    const char *fichier2 = argv[2];

    /* Taille de la table = prochain premier >= 5 × nb mots fichier 1  */
    int nb_lignes = compter_lignes(fichier1);
    int capacite  = prochain_premier(nb_lignes * 5);

    /*Partie du code a modifier pour tester d'autres fonctions de hash*/
    hash_func_t hash_func      = bryan_bon_hachage;
    const char *nom_hash_func  = "bryan_bon_hachage";

    /* Construire la table avec les mots du fichier 1 */
    hash *ht      = hash_init(capacite);
    int nb_mots   = remplir_table(ht, fichier1, hash_func);

    /* Afficher les stats de la table */
    afficher_stats(ht, nb_mots, fichier1, nom_hash_func);

    /* Calculer et afficher l'intersection */
    printf("\n=== Mots communs aux deux fichiers ===\n");
    int nb_communs = calculer_intersection(ht, fichier2, hash_func);
    printf("\nNombre de mots communs : %d\n", nb_communs);

    /* Libération mémoire */
    hash_free(ht);
    return 0;
}
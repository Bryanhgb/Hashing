#ifndef HASH_FUN_H
#define HASH_FUN_H

#include <stdbool.h>  // pour le type bool

/* Utilitaires */
bool est_premier(int n);
int  prochain_premier(int n);
 
/* Fonctions de hachage */
 
/* djb2 classique */
unsigned int hash_string(const char *str, int len);
 
/* Jenkins one-at-a-time */
int jenkins_one_at_a_time_hash(const char *key, int len);
 
/* Fonction perso */
int bryan_bon_hachage(const char *str, int len);
 
/* Imonde */
int random_from_string(const char *str, int len);
 
/* Chaos */
unsigned int chaos_hash(const char *str, int len);

#endif

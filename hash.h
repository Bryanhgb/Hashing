#ifndef HASH_H
#define HASH_H

#include <stdbool.h> 

// Structure d'un nœud de la liste 
typedef struct node {
    char* value;          
    struct node *next;
} node;

// Structure de la table de hachage
typedef struct {
    int capacity;       // taille de la table
    node **h;           // tableau de listes chaînées
} hash;

//On fait le type pour les fonctions de hachage
typedef int (*hash_func_t)(const char*, int);

// Prototypes des fonctions
hash *hash_init(int capacity);
node *node_init(char* value);
void node_delete(node *n);
void hash_free(hash *ht);
void hash_add(hash *ht, char *value,hash_func_t hash_func);
bool is_member(hash *ht, char *value,hash_func_t hash_func);

#endif
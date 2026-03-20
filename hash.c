#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "hash.h"

/* Fonctions de gestion de la table de hachage par chaînage (adressage ouvert) */

hash *hash_init(int capacity) {
    hash *ht = malloc(sizeof(hash));
    assert(ht != NULL);
    ht->h = malloc(sizeof(node *) * capacity);
    assert(ht->h != NULL);
    for (int i = 0; i < capacity; i++) {
        ht->h[i] = NULL;
    }
    ht->capacity = capacity;
    return ht;
}

node *node_init(char *value) {
    node *n = malloc(sizeof(node));
    assert(n != NULL);
    n->value = strdup(value); /* Copie profonde : on possède la chaîne */
    assert(n->value != NULL);
    n->next = NULL;
    return n;
}

void node_delete(node *n) {
    node *current = n;
    node *pred = NULL;
    while (current != NULL) {
        pred = current;
        current = current->next;
        free(pred->value); /* Libère la chaîne copiée par strdup */
        free(pred);
    }
}

void hash_free(hash *ht) {
    for (int i = 0; i < ht->capacity; i++) {
        node_delete(ht->h[i]);
    }
    free(ht->h);
    free(ht);
}

void hash_add(hash *ht, char *value, hash_func_t hash_func) {
    int index = hash_func(value, ht->capacity);
    node *n = node_init(value);
    /* Insertion en tête de liste */
    n->next = ht->h[index];
    ht->h[index] = n;
}

bool is_member(hash *ht, char *value, hash_func_t hash_func) {
    int index = hash_func(value, ht->capacity);
    node *current = ht->h[index];
    while (current != NULL) {
        if (strcmp(current->value, value) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}
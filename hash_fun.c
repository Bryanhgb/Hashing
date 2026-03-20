#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>  
#include <assert.h>
#include <math.h>

bool est_premier(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int prochain_premier(int n) {
    int candidat = (n % 2 == 0) ? n + 1 : n + 2;
    while (!est_premier(candidat)) {
        candidat += 2;
    }
    return candidat;
}


//fonctions de hashage

unsigned int hash_string(const char *str,int len) {
    unsigned int hash = 5381;
    int c = len;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}
int jenkins_one_at_a_time_hash(const char *key,int len) {
    uint32_t hash = 0;
    while (*key) {
        hash += (unsigned char)(*key++);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash%len;
}

int bryan_bon_hachage(const char *str, int len) {
    unsigned int hash = len; 
    int c;

    while ((c = *str++)) {
        hash ^= (unsigned int)c;
        hash *= 16777619; 
        hash = (hash << 13) | (hash >> 19);
    }

    hash ^= hash >> 16;
    hash ^= hash >> 13;

    return hash % len;
}

int random_from_string(const char *str,int len) {
    unsigned int seed = hash_string(str,len);
    srand(seed);               
    return rand() % len;              
}


unsigned int chaos_hash(const char *str, int len) {
    if (len <= 0) return 42; // La réponse à tout

    double infusion_de_chaos = 0.0;
    int i = 1;

    while (*str) {
        // On multiplie le code ASCII par le sinus de sa position
        infusion_de_chaos += (double)(*str) * sin((double)i);
        // On ajoute un malus si le caractère est une voyelle
        if (strchr("aeiouyAEIOUY", *str)) {
            infusion_de_chaos *= 1.01; 
        }
        str++;
        i++;
    }

    // On transforme le tout en entier en utilisant PI ( utilisé à la 15e décimale comme pour pour la  navigation interplanétaire (NASA)) 
    // et on applique un décalage de bits basé sur la longueur originale
    unsigned int resultat = (unsigned int)(fabs(infusion_de_chaos) * 3.141592653589793);
    
    //Le XOR est l'opérateur que j'ai le moins utilisé durant ma scolarité, donc autant l'utiliser
    resultat ^= (len * len);

    return resultat % len;
}

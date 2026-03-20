## TP2 — Intersection de fichiers par table de hachage 
## HONGBO Bryan

### Fichiers sources
- `hash.h / hash.c`       : table de hachage par chaînage (adressage ouvert)
- `hash_fun.h / hash_fun.c`: fonctions de hachage et utilitaires 
- `Tp2_main.c`            : programme principal

### Compilation

Avec le Makefile fourni :

    make

Ou manuellement :

    gcc -Wall -Wextra  -o tp2 Tp2_main.c hash.c hash_fun.c -lm

### Utilisation

    ./tp2 <fichier1> <fichier2>

Le programme affiche d'abord les statistiques de la table de hachage
construite sur `fichier1`, puis fait l'intersection et donne le nombre de mots en commun.

### Exemple

    ./tp2 words1.txt words2.txt

### Changer la fonction de hachage

Dans `Tp2_main.c`, ligne `hash_func_t hash_func = bryan_bon_hachage;`
remplacer par l'une des fonctions disponibles :
- `hash_string`                  (djb2)
- `jenkins_one_at_a_time_hash`   (Jenkins)
- `bryan_bon_hachage`            ( **défaut**)
- `chaos_hash`                   

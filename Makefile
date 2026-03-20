# Compilateur utilisé
CC      = gcc

# Flags de compilation pour developeur:
#CFLAGS  = -Wall -Wextra -fsanitize=address -g 
#   -Wall -Wextra       : active tous les avertissements
#   -g                  : infos debug pour gdb
#   -fsanitize=address  : détecte les bugs mémoire (AddressSanitizer)


#Flag de compilation pour la performance
CFLAGS  = -Wall -Wextra  -O2

# Librairies à linker 
LDFLAGS = -lm 

# Nom de l'exécutable final
TARGET  = tp2

# Fichiers sources
SRCS    = Tp2_main.c hash.c hash_fun.c

# Fichiers objets (auto-généré depuis SRCS : .c → .o)
OBJS    = $(SRCS:.c=.o)

# Règle par défaut : construit l'exécutable
all: $(TARGET)

# Linkage de tous les .o en un exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation de chaque .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Supprime les fichiers compilés
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
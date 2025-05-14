#nom de l'exécutable final
TARGET = build/programme

#compilateur
CC = gcc

#options par défaut
CFLAGS = -Wall -Wextra -Iinclude

#tous les fichiers .c dans src/
SRC = $(wildcard src/*.c)

#les fichiers objets .o correspondants dans build/
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))


#règle principale : compilation normale
all: CFLAGS += -O2
all: $(TARGET)

#règle debug : compilation avec -g

debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

#lier les objets pour créer l'exécutable
$(TARGET): $(OBJ)
	@mkdir -p build
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)


#compiler les .c en .o
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

#nettoyage
clean:
	rm -rf build/*

.PHONY: all clean debug
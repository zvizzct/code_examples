# Nombre del ejecutable
EXE = prepreprocesor

# Nombre del archivo fuente
SRC = preprocesor.c

# Nombre del archivo de encabezado
INC = src/utilsFiles.h

# Comando de compilación
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -Wextra

# Regla para construir el ejecutable
$(EXE): $(SRC) $(INC)
	$(CC) $(SRC) $(INC) $(CFLAGS) -o $(EXE)

clean:
	rm -f $(EXE)
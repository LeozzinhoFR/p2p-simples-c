CC=gcc
CFLAGS=-Wall -g

# O nome do executável final
TARGET=peer

# Lista de arquivos-fonte (.c)
SOURCES=main.c subscriber.c

# Lista de arquivos-objeto (.o) gerados a partir dos fontes
OBJECTS=$(SOURCES:.c=.o)

# Regra principal: compila tudo
all: $(TARGET)

# Regra para linkar e criar o executável final
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regra para compilar cada arquivo .c em seu respectivo .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados (objetos e executável)
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
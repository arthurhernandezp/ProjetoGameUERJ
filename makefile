# Compilador e flags
CC = gcc
CC_FLAGS = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Flags de compilação específicas para cada modo
DEBUG_FLAGS = -DDEBUG -g
RELEASE_FLAGS = -O2

# Targets principais
all: release

debug: CFLAGS = $(DEBUG_FLAGS)
debug: jogo

release: CFLAGS = $(RELEASE_FLAGS)
release: jogo

# Compilação do jogo
jogo: ProjetoFinal.c
	$(CC) -o c.exe ProjetoFinal.c $(CFLAGS) $(CC_FLAGS)

# Limpeza
clean:
	rm -f c.exe

CC_FLAGS = -lSDL2\
	   -lSDL2_gfx\
	   -lSDL2_image\
	   -lSDL2_mixer\
	   -lSDL2_ttf

all: jogo

jogo: 
	gcc -o c.exe ProjetoFinal.c $(CC_FLAGS)

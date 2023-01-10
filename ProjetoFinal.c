#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <SDL2/SDL_mixer.h>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))


typedef struct dadosPlayer{
	SDL_Rect rect;
	SDL_Rect corte;
	SDL_Texture* texture;
	unsigned short int state;
	//state 0 idle;  1 walking  ; 2 remando   ; 3 fishing
	unsigned short int lugar;
	// lugar 0 onGround; 1 onBoat
}dadosPlayer;

typedef struct dadosBarco{
	SDL_Rect rect;
	SDL_Texture* texture;
}dadosBarco;

typedef struct dadosBotao{
	SDL_Rect rect;
	SDL_Texture* texture;
	unsigned short int state;
}dadosBotao;

typedef struct dadosMouse{
	SDL_Rect rect;
	SDL_Point point;
	SDL_Texture *texture;
	unsigned short int state;
	//state 0: cursor padrao do windows// state 1: cursor de pesca
}dadosMouse;

typedef struct dadosCeu{
	SDL_Texture* texture;
	unsigned short int fundoAux;
}dadosCeu;

enum lugarPlayer {onGround = 0,onBoat};
enum estadoPlayer {idle = 0,walking,noBarco,remando,fishing};

typedef struct dadosItem{
	SDL_Rect r;
	bool state;
	SDL_Texture* img;
}dadosItem;

typedef struct dadosInventario{
    dadosItem matrizItens[6][2];
	short int n;//Numeros de itens inseridos
	SDL_Texture* texture;
	SDL_Rect rect;
	unsigned short int state;//fechado/ aberto
	short int i;
	short int j;
	
}dadosInventario;

enum stateInventario {fechado = 0,aberto};
#include "inventario.c"

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    //SDL_FlushEvent(SDL_MOUSEMOTION);
    if (SDL_WaitEventTimeout(evt, *ms)) {
		*ms = MAX(0, *ms - (int)(SDL_GetTicks() - antes));
		return 1;
    } return 0;
}

SDL_Window* create_window(void) {
    SDL_Window* win = SDL_CreateWindow("ProjetoP2",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         1000, 600, SDL_WINDOW_SHOWN
                      );

    if(win==NULL) {
        printf("Janela não foi criada.\nSDL_Error: %s\n", SDL_GetError());
    }

    return win;
}

SDL_Renderer* create_renderer(SDL_Window* win) {
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    if(win==NULL) {
        printf("Janela não foi criada.\nSDL_Error: %s\n", SDL_GetError());
    }

    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    return ren;
}
#include "game.c"
#include "menu.c"

int main (int argc, char* args[]){
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);   
    SDL_Window* win = create_window();
    SDL_Renderer* ren = create_renderer(win);
    bool selecionado = false;
    bool gameIsRunning = true;
    bool playing = false;
    bool menu = true; 
    
    dadosPlayer player;
    player.rect = (SDL_Rect) {0,460,100,80};
    player.corte = (SDL_Rect) { 0,0, 48,48 };
    player.state = idle;
    player.lugar = onGround;
	player.texture = IMG_LoadTexture(ren, "imgs/fisherman2.png");
	assert(player.texture != NULL); 
	dadosCeu ceu;
	ceu.texture = IMG_LoadTexture(ren, "imgs/bg7.png");
	ceu.fundoAux = 5;
	assert(ceu.texture != NULL); 
	
	dadosBarco barco;
	barco.rect = (SDL_Rect) { 564,513, 148,36 };
	barco.texture = IMG_LoadTexture(ren, "imgs/Boat.png");
	assert(barco.texture != NULL); 
	dadosInventario inventario;
    constroi(ren,&inventario,850,60);
    
    	
	char * listaItens[7];
	listaItens[0] = "imgs/Icons_04.png";
	listaItens[1] = "imgs/Icons_05.png";
	listaItens[2] = "imgs/Icons_06.png";
	listaItens[3] = "imgs/Icons_07.png";
	listaItens[4] = "imgs/Icons_08.png";
	listaItens[5] = "imgs/Icons_09.png";
	listaItens[6] = "imgs/Icons_10.png";
	for(int i = 0;i < 7;i++) assert(listaItens[i] != NULL); 
    /* EXECUÇÃO */
    while(gameIsRunning){
		//while(menu) chamaMenu(SDL_Renderer* ren,bool* gameIsRunning,bool* playing){	
   		chamaMenu(ren,&menu,&gameIsRunning,&playing);
   		//while(playing) rodaJogo(ren,&menu,&gameIsRunning,&playing,&player,&ceu);
   		rodaJogo(ren,&menu,&gameIsRunning,&playing,&player,&ceu,&barco,&inventario,listaItens);
	}
    /* FINALIZACAO */
  	SDL_DestroyTexture(player.texture);
  	SDL_DestroyTexture(barco.texture);
  	SDL_DestroyTexture(ceu.texture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

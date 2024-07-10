#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <SDL2/SDL_mixer.h>
#include <stdint.h>
#ifdef JOYSTICK
	#include <stdlib.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <termios.h>
#endif
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define CONTADOR_DEFAULT 20
#define VELOCIDADE_CONTADOR 5

enum lugarPlayer {onGround = 0,onBoat};
enum playerStates {idle = 0,walking,noBarco,remando,fishing, pulling,dormindo};
enum inventarioStates {fechado = 0,aberto};
enum telaStates {menu=0,jogo,casa,telaFinal,fim};
enum mouseStates {ready=0,cancelled,clicked,dropped,dragging,clicking}; 
enum minigameState {cancelado = 0, emjogo, concluido};
enum dialogoState {off = 0,on};

struct dadosPlayer;

// Definição do tipo de função
typedef void (*MudaTexturaFunc)(SDL_Renderer*, struct dadosPlayer*);

typedef struct dadosMinigame{
	SDL_Rect rIsca;
	SDL_Rect rPeixe;
	SDL_Rect rect;
	SDL_Texture* texture;
	SDL_Texture* peixeMG;
	SDL_Texture* isca;
	uint8_t iscaSpeed;
	uint8_t peixeSpeed;
    uint8_t state;
}dadosMinigame;


typedef struct dadosVendedor{
	SDL_Rect rect;
	SDL_Texture *texture;
	SDL_Rect dialogoRect;
	SDL_Texture *dialogo;
}dadosVendedor;

typedef struct dadosBuff{
	SDL_Texture *texture;
	SDL_Rect rect;
	uint8_t contador;
	bool ativo;
	uint8_t velocidade;
}dadosBuff;

typedef struct dadosPlayer{
	SDL_Rect rect;
	SDL_Rect corte;
	SDL_Texture* texture;
	uint8_t state;
	//state 0 idle;  1 walking  ; 2 remando   ; 3 fishing
    uint8_t lugar;
	// lugar 0 onGround; 1 onBoat
	dadosBuff buff;
	MudaTexturaFunc mudaTextura;
}dadosPlayer;

typedef struct dadosBarco{
	SDL_Rect rect;
	SDL_Texture* texture;
}dadosBarco;

typedef struct dadosBotao{
	SDL_Rect rect;
	SDL_Texture* texture;
	uint8_t state;
}dadosBotao;

typedef struct dadosMouse{
	SDL_Rect rect;
	SDL_Point point;
	SDL_Texture *texture;
	uint8_t state;
	//state 0: cursor padrao do windows// state 1: cursor de pesca
}dadosMouse;

typedef struct dadosCeu{
	SDL_Texture* texture;
	uint8_t fundoAux;
}dadosCeu;

typedef struct dadosItem{
	SDL_Rect r;
	bool state;
	SDL_Texture* img;
}dadosItem;

typedef struct dadosInventario{
    dadosItem matrizItens[3][4];
    int8_t n;//Numeros de itens inseridos
	SDL_Texture* texture;
	SDL_Rect rect;
	unsigned short int state;//fechado/ aberto
    uint8_t i;
	uint8_t j;
	
}dadosInventario;


int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    //SDL_FlushEvent(SDL_MOUSEMOTION);
    if (SDL_WaitEventTimeout(evt, *ms)) {
		*ms = MAX(0, *ms - (int)(SDL_GetTicks() - antes));
		return 1;
    } return 0;
}

// Função auxiliar para debug
const char *nomeTecla(SDL_Keycode tecla) {
    switch (tecla) {
        case SDLK_RETURN: return "ENTER";
        case SDLK_ESCAPE: return "ESC";
        case SDLK_SPACE: return "ESPAÇO";
        case SDLK_RIGHT: return "SETA PARA DIREITA";
        case SDLK_LEFT: return "SETA PARA ESQUERDA";
        case SDLK_e: return "E";
        case SDLK_d: return "D";
        case SDLK_i: return "I";
        // Adicionar mais casos 
        default: return "TECLA DESCONHECIDA";
    }
}

const char *nomeScreen(uint8_t screen) {
    switch (screen) {
        case 0: return "menu";
        case 1: return "jogo";
        case 2: return "casa";
        case 3: return "tela final";
        case 4: return "Fim";
        // Adicionar mais casos 
        default: return "TECLA DESCONHECIDA";
    }
}

void mudaTextura(SDL_Renderer* ren,dadosPlayer *personagem){
	if(personagem->state == idle && personagem->lugar == onGround) personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_idle.png");
	else if(personagem->state == walking && personagem->lugar == onGround ){
		 personagem->texture = IMG_LoadTexture(ren, "imgs/fisherman2.png");
	}
	else if(personagem->lugar == onBoat && personagem->state == remando) {
		personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_row.png");
		personagem->rect.y = 473;
	}
	else if(personagem->lugar == onBoat && personagem->state == fishing){
		personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_fish.png");
		personagem->rect.y = 467;
		personagem->corte.y = 0;
	}
	else if(personagem->lugar == onBoat && personagem->state == pulling){
		personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_hook.png");
	}
	else if(personagem->state == dormindo){
		personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_dormir.png");
	}
}


SDL_Window* create_window(void) {
    SDL_Window* win = SDL_CreateWindow("ProjetoP2",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         1000, 600, SDL_WINDOW_SHOWN
                      );

    if(win==NULL) {
		#ifdef DEBUG
        	printf("Janela não foi criada.\nSDL_Error: %s\n", SDL_GetError());
        #endif
    }else{
		#ifdef DEBUG
    		printf("Win Criada\n");
		#endif
	}

    return win;
}

SDL_Renderer* create_renderer(SDL_Window* win) {
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    if(win==NULL) {
    	#ifdef DEBUBG
        	printf("Janela não foi criada.\nSDL_Error: %s\n", SDL_GetError());
		#endif
    }else{
   		#ifdef DEBUG
    		printf("Renderer Criado\n");
		#endif
    }

    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    return ren;
}

#include "inventario.c"
#include "game.c"
#include "menu.c"
#include "telaFinal.c"
#include "interiorCasa.c"

int main (int argc, char* args[]){
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);   
    SDL_Window* win = create_window();
    SDL_Renderer* ren = create_renderer(win);
    //Criação do menu e menu anterior para manipulação da transição de ( (jogo->menu && menu->jogo) || (casa->menu && menu-> casa) )
    uint8_t screen = menu;
    uint8_t screenAnterior = menu;
    //Criação do personagem
    dadosPlayer player;
    player.rect = (SDL_Rect) {0,460,100,80};
    player.corte = (SDL_Rect) { 0,0, 48,48 };
    player.state = idle;
    player.lugar = onGround;
	player.texture = IMG_LoadTexture(ren, "imgs/fisherman2.png");
	player.mudaTextura = mudaTextura;
	assert(player.texture != NULL); 
	
	//Criação do buff de pesca
	player.buff.texture = IMG_LoadTexture(ren,"imgs/minigameIsca.png");
	player.buff.rect = (SDL_Rect) {220,20,45,60};
	player.buff.ativo = false;
	player.buff.velocidade = 0;
	player.buff.contador = CONTADOR_DEFAULT;
	#ifdef DEBUG
		printf("\nPersonagem criado na memoria!");
	#endif
	dadosCeu ceu;
	ceu.texture = IMG_LoadTexture(ren, "imgs/bg7.png");
	ceu.fundoAux = 5;
	assert(ceu.texture != NULL); 
	#ifdef DEBUG
		printf("\nFundo de tela criado na memoria");
	#endif
	dadosBarco barco;
	barco.rect = (SDL_Rect) { 564,513, 148,36 };
	barco.texture = IMG_LoadTexture(ren, "imgs/Boat.png");
	assert(barco.texture != NULL); 
	
	#ifdef DEBUG
		printf("\nBarco criado na memoria");
	#endif
	dadosInventario inventario;
    constroi(ren,&inventario,690,150); 
	char * listaItens[7];
	listaItens[0] = "imgs/Icons_04.png";
	listaItens[1] = "imgs/Icons_05.png";
	listaItens[2] = "imgs/Icons_06.png";
	listaItens[3] = "imgs/Icons_07.png";
	listaItens[4] = "imgs/Icons_08.png";
	listaItens[5] = "imgs/Icons_09.png";
	listaItens[6] = "imgs/Icons_10.png";
	//for(uint8_t i = 0;i < 7;i++) assert(listaItens[i] != NULL);
	#ifdef DEBUG
		printf("\nLista de itens criado");
	#endif
	
	//CRIA MINIGAME
	dadosMinigame minigame;
	minigame.state = cancelado;
	minigame.rIsca = (SDL_Rect){ 774,357, 45,60 };
    minigame.rPeixe = (SDL_Rect){ 655,425, 26,19 };
	minigame.isca = IMG_LoadTexture(ren, "imgs/minigameIsca.png");
	minigame.peixeMG = IMG_LoadTexture(ren, "imgs/minigamePeixe.png");
	minigame.texture = IMG_LoadTexture(ren, "imgs/minigamepesca.png");
	minigame.rect = (SDL_Rect){ 620,380,308,66};
	minigame.iscaSpeed = 5;
	minigame.peixeSpeed = 0;
	#ifdef DEBUG
		printf("\nMiniGame criado na memoria");
	#endif
	
	
	
	#ifdef DEBUG
		printf("\nInicio do tratamento da porta serial");
	#endif
	#ifdef JOYSTICK
	    // Configuração da porta serial
    int serialPort = open("/dev/ttyACM0", O_RDWR);
    if (serialPort < 0) {
        perror("Erro ao abrir a porta serial");
        return 1;
    }

    struct termios tty;
    if (tcgetattr(serialPort, &tty) != 0) {
        perror("Erro ao obter atributos da porta serial");
        close(serialPort);
        return 1;
    }

		cfsetispeed(&tty, B9600);
		cfsetospeed(&tty, B9600);

		tty.c_cflag |= (CLOCAL | CREAD); // Enable the receiver and set local mode
		tty.c_cflag &= ~CSIZE;
		tty.c_cflag |= CS8; // Set 8 data bits
		tty.c_cflag &= ~PARENB; // No parity
		tty.c_cflag &= ~CSTOPB; // 1 stop bit
		tty.c_cflag &= ~CRTSCTS; // No hardware flow control

		tty.c_cc[VMIN] = 1; // Read at least 1 character
		tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout

		if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
		    perror("Erro ao definir atributos da porta serial");
		    close(serialPort);
		    return 1;
		}
	#endif
    /* EXECUÇÃO */
    while(screen != fim){
    	switch (screen) {
            case menu:
                chamaMenu(ren,&screen,&screenAnterior);
                break;
            case jogo:  
            	#ifdef JOYSTICK
					rodaJogo(ren, &player, &ceu, &barco, &inventario, listaItens, &screen, &minigame, &serialPort);
				#else
					rodaJogo(ren, &player, &ceu, &barco, &inventario, listaItens, &screen, &minigame);
				#endif
                screenAnterior = jogo;
                break;
            case casa:
            	#ifdef JOYSTICK
            		interiorCasa(ren,&player,&inventario,&ceu,&screen,&serialPort);
				#else
        			interiorCasa(ren,&player,&inventario,&ceu,&screen);	
        		#endif
                screenAnterior = casa;
            	break;
            case telaFinal:
            	rodaTelaFinal(ren,&player,&barco,&ceu,&screen);
            	break;
        } 
	}
    /* FINALIZACAO */
  	SDL_DestroyTexture(player.texture);
  	SDL_DestroyTexture(barco.texture);
  	SDL_DestroyTexture(ceu.texture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

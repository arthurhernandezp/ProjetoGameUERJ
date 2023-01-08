#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
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
	SDL_Rect corte;
	SDL_Texture* texture;
}dadosBarco;

enum lugar {onGround = 0,onBoat};
enum estado {idle = 0,walking,noBarco,remando,fishing};

void mudaCor(SDL_Renderer* ren,SDL_Surface* listaS[],SDL_Texture* listaT[],SDL_Color cor,int i,char* nome,TTF_Font *ourFont){
	listaS[i] = TTF_RenderText_Solid(ourFont, nome,cor);  
	listaT[i] = SDL_CreateTextureFromSurface(ren,listaS[i]);
}

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    //SDL_FlushEvent(SDL_MOUSEMOTION);
    if (SDL_WaitEventTimeout(evt, *ms)) {
		*ms = MAX(0, *ms - (int)(SDL_GetTicks() - antes));
		return 1;
    } return 0;
}

void rodaJogo(SDL_Renderer* ren,bool* menu,bool* gameIsRunning,bool* playing,dadosPlayer *personagem,SDL_Texture** ceu,dadosBarco *barco){

	int i = 0; int contFundo = 0;
	
    SDL_Texture* agua = IMG_LoadTexture(ren, "imgs/Water.png");
    SDL_Texture* grama = IMG_LoadTexture(ren, "imgs/grass.png");
	SDL_Texture* cabana = IMG_LoadTexture(ren, "imgs/cabana.png");
	
	struct SDL_Texture* listaDec[5];
	listaDec[0] = IMG_LoadTexture(ren, "imgs/Grass1.png");
	listaDec[1] = IMG_LoadTexture(ren, "imgs/Grass2.png");
	listaDec[2] = IMG_LoadTexture(ren, "imgs/Grass3.png");
	listaDec[3] = IMG_LoadTexture(ren, "imgs/Grass4.png");
	listaDec[4] = IMG_LoadTexture(ren, "imgs/arvores.png");
	
	for(i = 0; i <= 3; i++){
		assert(listaDec[i] != NULL);
	}
    assert(agua != NULL);
    assert(grama != NULL);
    assert(cabana != NULL);
    
    unsigned short int fundoAux = 0;
    short int frame = 1;
    int espera = 0;    
    SDL_Rect gDec = {0,507,32,33};
    SDL_Rect g = {0,536,484,64};
    SDL_Rect w = {444,540,584,64};
    SDL_Rect h = {300,370,384,244};
    SDL_Rect arvore = {130,324,179.2,224};
	SDL_Rect cW = (SDL_Rect) {0,0, 584,64 };
	SDL_Rect cG = (SDL_Rect) {0,0, 484,64 };
	SDL_Rect cH = (SDL_Rect) {0,0, 192,122 };
	SDL_Rect cGD = (SDL_Rect) {0,0, 32,33 };
	SDL_Rect cArv = (SDL_Rect) {89.6,0, 89.6,132 };
	Uint32 antes = 0;
	int var = 1;
	while (*playing) {	
		espera = MAX(espera - (int)(SDL_GetTicks() - antes), 0);
	  	SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt,&espera);    
	  	antes = SDL_GetTicks();
	  	
	  	if(isevt){       
			switch (evt.type) {
				case SDL_WINDOWEVENT:
                	if (SDL_WINDOWEVENT_CLOSE == evt.window.event){
					    *playing = false;
					    *menu = false;
					    *gameIsRunning = false;
					} break;	
				case SDL_KEYDOWN:
					switch (evt.key.keysym.sym){  
						case SDLK_RIGHT:
							if(personagem->lugar == onGround){
								if(personagem->rect.x < 625){
									if(personagem->corte.x < 240) personagem->corte.x += 48;
									else personagem->corte.x = 0;
									if(personagem->corte.y != 0) personagem->corte.y = 0;
									
									if(personagem->rect.x < 280 || personagem->rect.y <= 417) personagem->rect.x += 10;
									else if (personagem->rect.x >= 280 && personagem->rect.y > 417){
										personagem->rect.x+=8; 
										personagem->rect.y-=5;
									} 
									personagem->state = walking;
								}
							}
							else if(personagem->lugar == onBoat){
								
								if(personagem->rect.x < 852){
									if(personagem->corte.x < 144) personagem->corte.x += 48;
									else personagem->corte.x = 0;
									if(personagem->corte.y != 0) personagem->corte.y = 0;
									personagem->rect.x+=4;
									barco->rect.x += 4;
									personagem->state = remando;
								}
							}
						break;
						case SDLK_LEFT:		
							if(personagem->lugar == onGround){
								if(personagem->corte.x < 240) personagem->corte.x +=48;
								else personagem->corte.x = 0;
								if(personagem->corte.y != 48) personagem->corte.y = 48;
								
								if(personagem->rect.x >0){	
									if(personagem->rect.x <=285 || personagem->rect.x > 360) personagem->rect.x -= 10;
									else{
										personagem->rect.x-=8; 
										personagem->rect.y+=5;
									}
									personagem->state = walking;
								}
							}
							else if(personagem->lugar == onBoat){
								if(personagem->rect.x > 554 ){
									if(personagem->corte.x < 144) personagem->corte.x +=48;
									else personagem->corte.x = 0;
									if(personagem->corte.y != 48) personagem->corte.y = 48;		
										personagem->state = remando;
										personagem->rect.x -= 4;
										barco->rect.x -= 4;
								}
							}
						break;
						case SDLK_SPACE:
							fundoAux++;
							break;
						case SDLK_ESCAPE:
							*menu = true;
							*playing = false;
							SDL_RenderPresent(ren);
							break;
						case SDLK_e:
							if(personagem->rect.x >= barco->rect.x && personagem->lugar == onGround){
								personagem->lugar = onBoat;
								personagem->rect.y = 473;
								personagem->rect.x = (barco->rect.w)/2 + barco->rect.x;
								personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_row.png");
								personagem->corte.x = 0;

							}
							else if(personagem->rect.x <= 652 && personagem->lugar == onBoat){
								personagem->lugar = onGround;	
								personagem->rect.x =  632;
								personagem->rect.y = 415;
								personagem->corte.x = 0;
								personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_idle.png");
							}
							break;
						default:
							SDL_FlushEvent(evt.type);
							break;
		 		}
		 		default:
					SDL_FlushEvent(evt.type);
					break;
			}
		} else {   
  			contFundo += 1;
 			if (contFundo == 60){
				fundoAux++;
				contFundo = 0;
			}
			w.y = w.y + 1 * (var);
			var *= -1;
			if(personagem->lugar == onGround){
				personagem->state = idle;
				if (personagem->corte.x < 240) personagem->corte.x +=48;
				else personagem->corte.x = 0;
			}
			espera = 500;
		}
		if(fundoAux >= 9) fundoAux = 1;
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, *ceu, NULL, NULL);		
		SDL_RenderCopy(ren, cabana, &cH, &h);
		SDL_RenderCopy(ren, grama, &cG, &g);
		SDL_RenderCopy(ren, listaDec[4], &cArv, &arvore);
		for(i = 0; i <= 3;i++){
			SDL_RenderCopy(ren, listaDec[i], &cGD, &gDec);
			gDec.x+=100;
		} gDec.x = 0;
		
		if(personagem->state == idle && personagem->lugar == onGround) personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_idle.png");
		else if(personagem->state == walking && personagem->lugar == onGround ) personagem->texture = IMG_LoadTexture(ren, "imgs/fisherman2.png");
		else if(personagem->lugar == onBoat ) personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_row.png");
		
		
		SDL_RenderCopy(ren, barco->texture, &barco->corte, &barco->rect);		
		SDL_RenderCopy(ren, personagem->texture, &personagem->corte, &personagem->rect);
		SDL_RenderCopy(ren, agua, &cW, &w);
		SDL_RenderCopy(ren, grama, &cG, &g);
		switch(fundoAux){
			case 1:
				*ceu = IMG_LoadTexture(ren, "imgs/bg2.png");
			break;
			case 2: 
				*ceu = IMG_LoadTexture(ren, "imgs/bg3.png");
			break;
			case 3:
				*ceu = IMG_LoadTexture(ren, "imgs/bg4.png");
			break;
			case 4:
				*ceu = IMG_LoadTexture(ren, "imgs/bg5.png");
			break;
			case 5:
				*ceu = IMG_LoadTexture(ren, "imgs/bg6.png");
			break;
			case 6:
				*ceu = IMG_LoadTexture(ren, "imgs/bg7.png");
			break;
			case 7:
				*ceu = IMG_LoadTexture(ren, "imgs/bg8.png");
			break;
			case 8:
				*ceu = IMG_LoadTexture(ren, "imgs/bg1.png");			
			break;
		}
		
		SDL_RenderPresent(ren);
		
	}	
	
	SDL_DestroyTexture(agua);
	SDL_DestroyTexture(grama);
	SDL_DestroyTexture(cabana);
	for(i = 0; i < 4; i++)
		SDL_DestroyTexture(listaDec[i]);
	
}

void chamaMenu(SDL_Renderer* ren,bool* menu,bool* gameIsRunning,bool* playing){
    TTF_Init();
    SDL_Color padrao = { 0,0,0,255 };
    SDL_Color focus = { 0,157,231,255 };
    char fonte[23] = "imgs/ArcadeClassic.ttf";
    TTF_Font *ourFont = TTF_OpenFont(fonte,40);
    SDL_Texture* bgmenu = IMG_LoadTexture(ren, "imgs/bgmenu.png");
    struct SDL_Surface* listaSurfaceText[3];
    listaSurfaceText[0] = TTF_RenderText_Solid(ourFont, "Peixe IO",padrao);  
    listaSurfaceText[1] = TTF_RenderText_Solid(ourFont, "CoNTINUE",padrao); 
    listaSurfaceText[2] = TTF_RenderText_Solid(ourFont, "Quit",padrao); 
     
    struct SDL_Texture* listaTextureText[3];
	listaTextureText[0] = SDL_CreateTextureFromSurface(ren,listaSurfaceText[0]);
	listaTextureText[1] = SDL_CreateTextureFromSurface(ren,listaSurfaceText[1]);
    listaTextureText[2] = SDL_CreateTextureFromSurface(ren,listaSurfaceText[2]);
    int i = 0;

    bool selecionado = false;
    SDL_Point mouse = {0,0};
    SDL_Rect recNome = {350,130,300,150};
    SDL_Rect recContinue = {350,340,120,40};
    SDL_Rect recQuit = {550,340,100,40};
    SDL_SetRenderDrawColor(ren,0,255,0,255);
    
     // Initialize SDL video and audio systems
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // Initialize SDL mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Volume(1, 4);
    Mix_Music *backgroundSound = Mix_LoadMUS("menu.mp3");
    int count = 0;
    //setVolume(40);
    while(*menu){
			//SDL_RenderClear(ren);
			SDL_RenderCopy(ren, bgmenu, NULL, NULL);		
			SDL_RenderCopy(ren,listaTextureText[0],NULL,&recNome);
			SDL_RenderCopy(ren,listaTextureText[1],NULL,&recContinue);
			SDL_RenderCopy(ren,listaTextureText[2],NULL,&recQuit);
			SDL_RenderPresent(ren);
			SDL_Event event;
			while(SDL_PollEvent(&event)){
				switch(event.type){
					case SDL_QUIT:
						*playing = false;
						*gameIsRunning = false;
						*menu = false;
					break;
					case SDL_MOUSEMOTION:
							SDL_GetMouseState(&mouse.x,&mouse.y);
						   	if(SDL_PointInRect(&mouse,&recContinue)){
						   		mudaCor(ren,listaSurfaceText,listaTextureText,focus,1,"Continue",ourFont);
   		                     	if (count < 1) Mix_PlayMusic(backgroundSound, 1);
   		                     	if(count <= 1) count++;
						   	}
						   	else if(SDL_PointInRect(&mouse,&recQuit)){
						   		mudaCor(ren,listaSurfaceText,listaTextureText,focus,2,"Quit",ourFont);
	   		                     if (count < 1) Mix_PlayMusic(backgroundSound, 1);
	   		                     if(count <= 1) count++;   		                     	
						   	}
						   	else{
						   		mudaCor(ren,listaSurfaceText,listaTextureText,padrao,1,"Continue",ourFont);
						   		mudaCor(ren,listaSurfaceText,listaTextureText,padrao,2,"Quit",ourFont);
								selecionado = false;
								count = 0;
						   	}
					break;
					case SDL_MOUSEBUTTONDOWN:	
						if(event.button.button==SDL_BUTTON_LEFT){
							if(SDL_PointInRect(&mouse,&recQuit)) selecionado = true;
							else if (SDL_PointInRect(&mouse,&recContinue)) selecionado = true;
						}
					case SDL_MOUSEBUTTONUP:	
						if(event.button.button==SDL_BUTTON_LEFT){
							if(event.button.state==SDL_RELEASED){
								if(SDL_PointInRect(&mouse,&recQuit) && selecionado) {						
									*gameIsRunning = false;				
									*menu = false;
									*playing = false;
								}
							}
							else if(SDL_PointInRect(&mouse,&recContinue) && selecionado){
									*menu = false;
									*playing=  true;
							}
						}
					break;
					case SDL_KEYDOWN:	
						switch (event.key.keysym.sym){  
							case SDLK_ESCAPE:
								*playing = true;
								break; 	
						}
					break;
				}
			}
			if(*playing){
				*menu = false;
				//SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
				//SDL_RenderClear(ren);
				SDL_RenderPresent(ren);
				break;
			}
	}
	
    for(i = 0; i <= 2;i++){
		SDL_FreeSurface(listaSurfaceText[i]);
		SDL_DestroyTexture(listaTextureText[i]);
	}
    Mix_FreeMusic(backgroundSound);	
	Mix_CloseAudio();
    TTF_CloseFont(ourFont);
    TTF_Quit();
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
    dadosBarco barco;
    dadosPlayer player;
    //player.rect.x =0; player.rect.y = 460; player.rect.w= 100 ; player.rect.h =80;
    //player.corte.x =0; player.corte.y = 460; player.corte.w= 100 ; player.corte.h =80;
    player.rect = (SDL_Rect) {0,460,100,80};
    player.corte = (SDL_Rect) { 0,0, 48,48 };
    //enum estado {idle = 0,walking,noBarco,remando,fishing};
    player.state = idle;
    player.lugar = onGround;
    // player.state[1] = walking; player.state[2] = noBarco; player.state[3] = remando; player.state[4] = fishing;
	player.texture = IMG_LoadTexture(ren, "imgs/fisherman2.png");
	SDL_Texture* ceu = IMG_LoadTexture(ren, "imgs/bg7.png");
	
	barco.rect = (SDL_Rect) { 564,513, 148,36 };
	barco.corte = (SDL_Rect) { 0,0, 74,18 };
	barco.texture = IMG_LoadTexture(ren, "imgs/Boat.png");
	
    /* EXECUÇÃO */
    while(gameIsRunning){
		//while(menu) chamaMenu(SDL_Renderer* ren,bool* gameIsRunning,bool* playing){	
   		chamaMenu(ren,&menu,&gameIsRunning,&playing);
   		//while(playing) rodaJogo(ren,&menu,&gameIsRunning,&playing,&player,&ceu);
   		rodaJogo(ren,&menu,&gameIsRunning,&playing,&player,&ceu,&barco);
	}
    /* FINALIZACAO */
  	SDL_DestroyTexture(player.texture);
  	SDL_DestroyTexture(barco.texture);
  	SDL_DestroyTexture(ceu);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

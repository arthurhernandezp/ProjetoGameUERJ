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

void mudaCor(SDL_Renderer* ren,SDL_Surface* listaS[],SDL_Texture* listaT[],SDL_Color cor,int i,char* nome,TTF_Font *ourFont){
	listaS[i] = TTF_RenderText_Solid(ourFont, nome,cor);  
	listaT[i] = SDL_CreateTextureFromSurface(ren,listaS[i]);
}

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    SDL_FlushEvent(SDL_MOUSEMOTION);
    if (SDL_WaitEventTimeout(evt, *ms)) {
		*ms = MAX(0, *ms - (int)(SDL_GetTicks() - antes));
		return 1;
    } return 0;
}

void rodaJogo(SDL_Renderer* ren,bool* menu,bool* gameIsRunning,bool* playing){

	bool walking = false;
	int i = 0; int contFundo = 0;
	
    SDL_Texture* playerText = IMG_LoadTexture(ren, "imgs/fisherman2.png");
    SDL_Texture* agua = IMG_LoadTexture(ren, "imgs/Water.png");
    SDL_Texture* fundoTela = IMG_LoadTexture(ren, "imgs/bg7.png");
    SDL_Texture* grama = IMG_LoadTexture(ren, "imgs/grass.png");
	SDL_Texture* cabana = IMG_LoadTexture(ren, "imgs/cabana.png");
	
	struct SDL_Texture* listaDec[5];
	listaDec[0] = IMG_LoadTexture(ren, "imgs/Grass1.png");
	listaDec[1] = IMG_LoadTexture(ren, "imgs/Grass2.png");
	listaDec[2] = IMG_LoadTexture(ren, "imgs/Grass3.png");
	listaDec[3] = IMG_LoadTexture(ren, "imgs/Grass4.png");
	listaDec[4] = IMG_LoadTexture(ren, "imgs/arvores.png");
	
	
	struct SDL_Texture* listaBarrel[4];
	listaBarrel[0] = IMG_LoadTexture(ren, "imgs/Fishbarrel1.png");
	listaBarrel[1] = IMG_LoadTexture(ren, "imgs/Fishbarrel2.png");
	listaBarrel[2] = IMG_LoadTexture(ren, "imgs/Fishbarrel3.png");
	listaBarrel[3] = IMG_LoadTexture(ren, "imgs/Fishbarrel4.png");
	for(i = 0; i <= 3; i++){
		assert(listaDec[i] != NULL);
	}
    assert(playerText != NULL);
    assert(agua != NULL);
    assert(fundoTela != NULL);
    assert(grama != NULL);
    assert(cabana != NULL);
    
    unsigned short int fundoAux = 0;
    short int frame = 1;
    int espera = 0;    
    SDL_Rect gDec = {0,507,32,33};
    SDL_Rect g = {0,536,484,64};
    SDL_Rect w = {444,540,584,64};
    SDL_Rect h = {300,370,384,244};
    SDL_Rect player = { 0,460, 100,80 };
    SDL_Rect arvore = {130,324,179.2,224};
	SDL_Rect cW = (SDL_Rect) {0,0, 584,64 };
	SDL_Rect cG = (SDL_Rect) {0,0, 484,64 };
	SDL_Rect cH = (SDL_Rect) {0,0, 192,122 };
	SDL_Rect cGD = (SDL_Rect) {0,0, 32,33 };
	SDL_Rect cArv = (SDL_Rect) {89.6,0, 89.6,132 };

	SDL_Rect cPlayer =  { 0,0, 48,48 };
	Uint32 antes = 0;
	
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
							if(player.x < 625){
								if(cPlayer.x < 240) cPlayer.x += 48;
								else cPlayer.x = 0;
								if(cPlayer.y != 0) cPlayer.y = 0;
								if(player.x < 280 || player.y <= 417) player.x += 10;
								else if (player.x >= 280 && player.y > 417){
									player.x+=8; 
									player.y-=5;
								} 
								
								walking = true;
							}
						break;
						case SDLK_LEFT:		
							if(cPlayer.x < 240) cPlayer.x +=48;
							else cPlayer.x = 0;
							if(cPlayer.y != 48) cPlayer.y = 48;
							if(player.x >0){	
								if(player.x <=285 || player.x > 360) player.x -= 10;
								else{
									player.x-=8; 
									player.y+=5;
								}
								walking = true;
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
		 		}
			}
		} else {   
  			contFundo += 1;
 			if (contFundo == 20){
				fundoAux++;
				contFundo = 0;
			}
			walking = false;	
			if (cPlayer.x < 240) cPlayer.x +=48;
			else cPlayer.x = 0;
			espera = 500;
		}
		
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, fundoTela, NULL, NULL);		
		SDL_RenderCopy(ren, agua, &cW, &w);
		SDL_RenderCopy(ren, grama, &cG, &g);
		SDL_RenderCopy(ren, cabana, &cH, &h);
		SDL_RenderCopy(ren, listaDec[4], &cArv, &arvore);
		
		for(i = 0; i <= 3;i++){
			SDL_RenderCopy(ren, listaDec[i], &cGD, &gDec);
			gDec.x+=100;
		} gDec.x = 0;
		
		if(!walking) playerText = IMG_LoadTexture(ren, "imgs/Fisherman_idle.png");
		else playerText = IMG_LoadTexture(ren, "imgs/fisherman2.png");
		SDL_RenderCopy(ren, playerText, &cPlayer, &player);	
		if(fundoAux >= 8 ) fundoAux = 0;
		switch(fundoAux){
			case 1:
				fundoTela = IMG_LoadTexture(ren, "imgs/bg2.png");
			break;
			case 2: 
				fundoTela = IMG_LoadTexture(ren, "imgs/bg3.png");
			break;
			case 3:
				fundoTela = IMG_LoadTexture(ren, "imgs/bg4.png");
			break;
			case 4:
				fundoTela = IMG_LoadTexture(ren, "imgs/bg5.png");
			break;
			case 5:
				fundoTela = IMG_LoadTexture(ren, "imgs/bg6.png");
			break;
			case 6:
				fundoTela = IMG_LoadTexture(ren, "imgs/bg7.png");
			break;
			case 7:
				fundoTela = IMG_LoadTexture(ren, "imgs/bg8.png");
			break;
			case 8:
				fundoTela = IMG_LoadTexture(ren, "imgs/bg1.png");
				fundoAux = 0;
			break;
		}
		
		SDL_RenderPresent(ren);
		
	}	
	
	SDL_DestroyTexture(playerText);
	SDL_DestroyTexture(agua);
	SDL_DestroyTexture(fundoTela);
	SDL_DestroyTexture(grama);
	SDL_DestroyTexture(cabana);
	for(i = 0; i < 3; i++)
		SDL_DestroyTexture(listaBarrel[i]);
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
    
    /* EXECUÇÃO */
    while(gameIsRunning){
		//void chamaMenu(SDL_Renderer* ren,bool* gameIsRunning,bool* playing){	
   		chamaMenu(ren,&menu,&gameIsRunning,&playing);
   		//while(playing) rodaJogo(ren,&menu,&gameIsRunning,&playing);
   		rodaJogo(ren,&menu,&gameIsRunning,&playing);
	}
    /* FINALIZACAO */
  
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

void mudaCor(SDL_Renderer* ren,SDL_Surface* listaS[],SDL_Texture* listaT[],SDL_Color cor,int i,char* nome,TTF_Font *ourFont){
	listaS[i] = TTF_RenderText_Solid(ourFont, nome,cor);  
	listaT[i] = SDL_CreateTextureFromSurface(ren,listaS[i]);
}
/*
int AUX_WaitEventTimeoutCount (SDL_Event* evt, Uint32* ms){
	Uint32 antes = SDL_GetTicks();
	Uint32 depois = 0;
	int isevt = SDL_WaitEventTimeout(evt, *ms);
	if(isevt){
		depois = (SDL_GetTicks() - antes);
		if(*ms < depois) depois = *ms;
		*ms -= depois;		
	}
	return isevt;
}
int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    if (SDL_WaitEventTimeout(evt, *ms)) {
    	int temp = *ms - (SDL_GetTicks() - antes);
    	if(0 > temp) *ms = 0;
		//*ms = MAX(0, temp);
		return 1;
    } else return 0;
}


int AUX_WaitEventTimeoutCount(SDL_Event* event, Uint32* wait) {
    Uint32 before = SDL_GetTicks();
    int is_event = SDL_WaitEventTimeout(event, *wait);
    if (is_event) {
        *wait -= (SDL_GetTicks() - before);

        if (*wait >= 300) {
            *wait = 0;
        }
    } else {
        *wait = 300;
    }

    return is_event;
}*/
int AUX_WaitEventTimeoutCount(SDL_Event* event, Uint32* ms)
{
	Uint32 antes, agora = 0;
	int happened = SDL_WaitEventTimeout(event, *ms);
	antes = agora;
	agora = SDL_GetTicks();
	if (happened) {
		// algum evento aconteceu, espera menos da próxima
		if (agora - antes > *ms) *ms = 0;
		else *ms -= agora - antes;
	} else {
		// reseta o temporizador
		*ms = 100;
	}

	return happened;
}

void chamaMenu(SDL_Renderer* ren,bool* menu,bool* gameIsRunning,bool* playing){
    TTF_Init();
    SDL_Color padrao = { 0,0,0,255 };
    SDL_Color focus = { 0,157,231,255 };
    char fonte[23] = "imgs/ArcadeClassic.ttf";
    TTF_Font *ourFont = TTF_OpenFont(fonte,40);
    SDL_Texture* bgmenu = IMG_LoadTexture(ren, "bgmenu.png");
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
						   	}
						   	else if(SDL_PointInRect(&mouse,&recQuit)){
						   		mudaCor(ren,listaSurfaceText,listaTextureText,focus,2,"Quit",ourFont);
						   	}
						   	else{
						   		mudaCor(ren,listaSurfaceText,listaTextureText,padrao,1,"Continue",ourFont);
						   		mudaCor(ren,listaSurfaceText,listaTextureText,padrao,2,"Quit",ourFont);
								selecionado = false;
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
        printf("Janela não pôde ser criada.\nSDL_Error: %s\n", SDL_GetError());
    }

    return win;
}

SDL_Renderer* create_renderer(SDL_Window* win) {
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    if(win==NULL) {
        printf("Janela não pôde ser criada.\nSDL_Error: %s\n", SDL_GetError());
    }

    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    return ren;
}

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);   
    SDL_Window* win = create_window();
    SDL_Renderer* ren = create_renderer(win);
    bool selecionado = false;
    bool gameIsRunning = true;
    bool playing = false;
    bool menu = true;
    bool evento = false;
	int i = 0;
	
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
    

    int fundoAux = 0;
    SDL_Event evt;
    int frame = 1;
    int espera = 500;    
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

	SDL_Rect cPlayer =  {   0,0, 48,48 };
    /* EXECUÇÃO */
    while(gameIsRunning){
		//void chamaMenu(SDL_Renderer* ren,bool* gameIsRunning,bool* playing){	
   		chamaMenu(ren,&menu,&gameIsRunning,&playing);
		while (playing) {
		    SDL_RenderClear(ren);
			SDL_RenderCopy(ren, fundoTela, NULL, NULL);		
			SDL_RenderCopy(ren, agua, &cW, &w);
			SDL_RenderCopy(ren, grama, &cG, &g);
			SDL_RenderCopy(ren, cabana, &cH, &h);
			SDL_RenderCopy(ren, listaDec[4], &cArv, &arvore);
			
			for(i = 0; i <= 3;i++){
				SDL_RenderCopy(ren, listaDec[i], &cGD, &gDec);
				gDec.x+=100;
			}
			gDec.x = 0;
		    int isevt = AUX_WaitEventTimeoutCount(&evt,&espera);              
		    if(isevt){       	
				switch (evt.type ) {
					case SDL_QUIT:
						playing = false;
						menu = false;
						gameIsRunning = false;
						break;	
					case SDL_KEYDOWN:
						switch (evt.key.keysym.sym){  
							case SDLK_RIGHT:
								if(player.x < 625){
									/*frame++;
									if(frame >= 6) frame -= 6;*/
									if(cPlayer.x < 240) cPlayer.x += 48;
									else cPlayer.x = 0;
									if(cPlayer.y != 0) cPlayer.y = 0;
									if(player.x < 280 || player.y <= 417) player.x += 10;
									else if (player.x >= 280 && player.y > 417){
										player.x+=8; 
										player.y-=5;
									} 
									
									evento = true;
								}
							break;
							case SDLK_LEFT:		
								/*if(frame <= 5) frame += 6;
								else if(frame >= 11) frame = 6;
								else frame++;*/
								if(cPlayer.x < 240) cPlayer.x +=48;
								else cPlayer.x = 0;
								if(cPlayer.y != 48) cPlayer.y = 48;
								if(player.x >0){	
									if(player.x <=285 || player.x > 360) player.x -= 10;
									else{
										player.x-=8; 
										player.y+=5;
									}
									evento = true;
								}
							break;
							case SDLK_SPACE:
								fundoAux++;
								break;
							case SDLK_ESCAPE:
								menu = true;
								break;
								
			 		}
				}
			}
			else{   
				espera = 250;
				//frame++;
				evento = false;	
				if(cPlayer.x < 240) cPlayer.x +=48;
				else cPlayer.x = 0;
				/*
				if(frame <= 6){
					if(frame > 5) frame = 0;
				}
				else if(frame >=11){
					 frame = 6;		
				}*/
			}
			if(!evento) playerText = IMG_LoadTexture(ren, "Fisherman_idle.png");
			else playerText = IMG_LoadTexture(ren, "fisherman2.png");
			//SDL_RenderCopy(ren, playerText, &cPlayer[frame], &player);		
			//printf("%d ",c.x);
			SDL_RenderCopy(ren, playerText, &cPlayer, &player);	
			switch(fundoAux){
				case 1:
					fundoTela = IMG_LoadTexture(ren, "bg2.png");
				break;
				case 2: 
					fundoTela = IMG_LoadTexture(ren, "bg3.png");
				break;
				case 3:
					fundoTela = IMG_LoadTexture(ren, "bg4.png");
				break;
				case 4:
					fundoTela = IMG_LoadTexture(ren, "bg5.png");
				break;
				case 5:
					fundoTela = IMG_LoadTexture(ren, "bg6.png");
				break;
				case 6:
					fundoTela = IMG_LoadTexture(ren, "bg7.png");
				break;
				case 7:
					fundoTela = IMG_LoadTexture(ren, "bg8.png");
				break;
				case 8:
					fundoTela = IMG_LoadTexture(ren, "bg1.png");
					fundoAux = 0;
				break;
			}
			if(menu){
				playing = false;
				//SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
				//SDL_RenderClear(ren);
				SDL_RenderPresent(ren);
				break;
			}
			SDL_RenderPresent(ren);
		}

	}
    /* FINALIZACAO */
  	SDL_DestroyTexture(playerText);
    SDL_DestroyTexture(agua);
    SDL_DestroyTexture(fundoTela);
    SDL_DestroyTexture(grama);
    SDL_DestroyTexture(cabana);
    for(i = 0; i < 3; i++){
    	SDL_DestroyTexture(listaBarrel[i]);
    }
    for(i = 0; i < 4; i++){
    	SDL_DestroyTexture(listaDec[i]);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

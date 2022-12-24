#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

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
}/*
int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    if (SDL_WaitEventTimeout(evt, *ms)) {
    	int temp = *ms - (SDL_GetTicks() - antes);
    	if(0 > temp) *ms = 0;
		//*ms = MAX(0, temp);
		return 1;
    } else return 0;
}*/

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("ProjetoP2",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         1000, 600, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    
    SDL_Texture* playerText = IMG_LoadTexture(ren, "fisherman2.png");
    SDL_Texture* agua = IMG_LoadTexture(ren, "Water.png");
    SDL_Texture* fundoTela = IMG_LoadTexture(ren, "bg1.png");
    SDL_Texture* grama = IMG_LoadTexture(ren, "grass.png");
	SDL_Texture* cabana = IMG_LoadTexture(ren, "cabana.png");
	int i;
	
	struct SDL_Texture* listaDec[5];
	listaDec[0] = IMG_LoadTexture(ren, "Grass1.png");
	listaDec[1] = IMG_LoadTexture(ren, "Grass2.png");
	listaDec[2] = IMG_LoadTexture(ren, "Grass3.png");
	listaDec[3] = IMG_LoadTexture(ren, "Grass4.png");
	listaDec[4] = IMG_LoadTexture(ren, "arvores.png");
	
	
	struct SDL_Texture* listaBarrel[4];
	listaBarrel[0] = IMG_LoadTexture(ren, "Fishbarrel1.png");
	listaBarrel[1] = IMG_LoadTexture(ren, "Fishbarrel2.png");
	listaBarrel[2] = IMG_LoadTexture(ren, "Fishbarrel3.png");
	listaBarrel[3] = IMG_LoadTexture(ren, "Fishbarrel4.png");
	
	/*struct SDL_Texture* listaBg[8];
	listaBg[0] = IMG_LoadTexture(ren, "bg1.png");
	listaBg[1] = IMG_LoadTexture(ren, "bg2.png");
	listaBg[2] = IMG_LoadTexture(ren, "bg3.png");
	listaBg[3] = IMG_LoadTexture(ren, "bg4.png");
	listaBg[4] = IMG_LoadTexture(ren, "bg5.png");
	listaBg[5] = IMG_LoadTexture(ren, "bg6.png");
	listaBg[6] = IMG_LoadTexture(ren, "bg7.png");
	listaBg[7] = IMG_LoadTexture(ren, "bg8.png");	
	i = rand() % 8;
	fundoTela = listaBg[i];*/
	
	for(i = 0; i <= 3; i++){
		assert(listaDec[i] != NULL);
	}
    assert(playerText != NULL);
    assert(agua != NULL);
    assert(fundoTela != NULL);
    assert(grama != NULL);
    assert(cabana != NULL);
    int fundoAux = 0;
    bool playing = true;
    bool pause, fimdejogo;
    bool evento = false;
    SDL_Event evt;
    int frame = 1;
    int espera = 100;
    
    SDL_Rect gDec = {0,507,32,33};
    SDL_Rect g = {0,536,484,64};
    SDL_Rect w = {444,540,584,64};
    SDL_Rect h = {300,370,384,244};
    SDL_Rect player = { 0,460, 100,80 };
    SDL_Rect arvore = {130,324,179.2,224};
	SDL_Rect cW;
	SDL_Rect cG;
	SDL_Rect cH;
	SDL_Rect cGD;
	SDL_Rect cArv;
	cGD = (SDL_Rect) {0,0, 32,33 };
	cG = (SDL_Rect) {0,0, 484,64 };
	cW = (SDL_Rect) {0,0, 584,64 };
	cH = (SDL_Rect) {0,0, 192,122 };
	cArv = (SDL_Rect) {89.6,0, 89.6,132 };
	
	struct SDL_Rect c[12];
	//0 < Direita < 5
	c[0] = (SDL_Rect) {   0,0, 48,48 };
	c[1] = (SDL_Rect) { 48,0, 48,48 };
	c[2] = (SDL_Rect) { 96,0, 48,48 };
	c[3] = (SDL_Rect) { 144,0, 48,48 };
	c[4] = (SDL_Rect) { 192,0, 48,48 };
	c[5] = (SDL_Rect) { 240,0, 48,48 };
	//5 < Esquerda < 12
	c[6] = (SDL_Rect) {   0,48, 48,48 };
	c[7] = (SDL_Rect) { 48,48, 48,48 };
	c[8] = (SDL_Rect) { 96,48, 48,48 };
	c[9] = (SDL_Rect) { 144,48, 48,48 };
	c[10] = (SDL_Rect) { 192,48, 48,48 };
	c[11] = (SDL_Rect) { 240,48, 48,48 };
	
    /* EXECUÇÃO */
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
					break;	
				case SDL_KEYDOWN:
					switch (evt.key.keysym.sym){  
						case SDLK_RIGHT:
							if(player.x < 625){
								frame++;
								if(frame >= 6) frame -= 6;
								if(player.x < 280 || player.y <= 417) player.x += 10;
								else if (player.x >= 280 && player.y > 417){
									player.x+=8; 
									player.y-=5;
								} 
								
								evento = true;
							}
						break;
						case SDLK_LEFT:		
							if(frame <= 5) frame += 6;
							else if(frame >= 11) frame = 6;
							else frame++;
							
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
							pause = true;
						break;
		 		}
			}
		}
		else{   
			espera = 250;
			frame++;
			evento = false;	
			if(frame <= 6){
				if(frame > 5) frame = 0;
			}
			else if(frame >=11){
				 frame = 6;
				
			}
		}
		if(!evento){
			/*if(frame <= 5 && frame >= 0){
				if(frame == 5) frame = 0;
			}
			else if(frame >=11 && frame <=6){
				if(frame == 11) frame = 6;
			} */
			playerText = IMG_LoadTexture(ren, "Fisherman_idle.png");
		}

		else playerText = IMG_LoadTexture(ren, "fisherman2.png");

		SDL_RenderCopy(ren, playerText, &c[frame], &player);
		//SDL_RenderPresent(ren);
		//if(frame >= 6) frame = 0;
		//else if(frame <= -6) frame = -1;
		//SDL_RenderCopy(ren, playerText, &c, &player);
		
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
		while(pause){
	        SDL_RenderClear(ren);
			switch (evt.type ) {
				case SDL_QUIT:
					playing = false;
					pause = false;
					break;	
				case SDL_KEYDOWN:
					switch (evt.key.keysym.sym){  
						case SDLK_ESCAPE:
							pause = false;
						break;
		 		}
			}
			
		}
		SDL_RenderPresent(ren);
	
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

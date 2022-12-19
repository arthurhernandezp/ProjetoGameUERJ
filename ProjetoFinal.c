#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

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

void movimenta

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("Recorte",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* img = IMG_LoadTexture(ren, "fisherman2.png");
    SDL_Texture* img2 = IMG_LoadTexture(ren, "Fisherman_idle.png");
    assert(img != NULL);

    /* EXECUÇÃO */
    bool continua = true;
    bool evento = false;
    SDL_Event evt;
    int isup = 1;
    int x = -100;
    int espera = 100;
    while (continua) {
        SDL_SetRenderDrawColor(ren, 255,0,255,0);
        SDL_RenderClear(ren);
        SDL_Rect r = { x,50, 100,80 };
        SDL_Rect c;
      	Uint32 antes = SDL_GetTicks();
        int isevt = AUX_WaitEventTimeoutCount(&evt,&espera);       
        if(isevt){       	
		switch (evt.type ) {
		    case SDL_QUIT:
		    	continua = false;
		    	break;	
		    case SDL_KEYDOWN:
				evento = true;    	
				switch (evt.key.keysym.sym){  
				    case SDLK_RIGHT:
				    	if(r.x < 332 && r.y < 460){   
					    	if(isup < 0) isup *= -1;
							x += 15;
							isup++;
					}
					break;
				    case SDLK_LEFT:
				    	if(isup > 0) isup *= -1;
						x -= 15;
						isup--;
					break;
				
	 		}
		}
	}
	else{   
		espera = 500;
		if(isup < 0) c = (SDL_Rect) {0,48, 48,48 };
		else c = (SDL_Rect) {0,0, 48,48 };
		evento = false;
		
	}
	if(evento){
		switch(isup ){
			case 1:
				c = (SDL_Rect) {   0,0, 48,48 };
			break;
			case 2:
				c = (SDL_Rect) { 48,0, 48,48 };
			break;
			case 3:
				c = (SDL_Rect) { 96,0, 48,48 };
			break;
			case 4:
				c = (SDL_Rect) { 144,0, 48,48 };
			break;
			case 5: 
				c = (SDL_Rect) { 192,0, 48,48 };
			break;
			case 6:
				c = (SDL_Rect) { 240,0, 48,48 };
			break;
			
			case -1:
				c = (SDL_Rect) {   0,48, 48,48 };
			break;
			case -2:
				c = (SDL_Rect) { 48,48, 48,48 };
			break;
			case -3:
				c = (SDL_Rect) { 96,48, 48,48 };
			break;
			case -4:
				c = (SDL_Rect) { 144,48, 48,48 };
			break;
			case -5: 
				c = (SDL_Rect) { 192,48, 48,48 };
			break;
			case -6:
				c = (SDL_Rect) { 240,48, 48,48 };
			break;
		}
		SDL_RenderCopy(ren, img, &c, &r);
	}
	else SDL_RenderCopy(ren, img2, &c, &r);
	SDL_RenderPresent(ren);
	if(isup > 6){
		isup = 1;
	}
	else if(isup < -6) isup = -1;
    }

    /* FINALIZACAO */
    SDL_DestroyTexture(img);
    SDL_DestroyTexture(img2);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

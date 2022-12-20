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

void mudaFundo(SDL_Texture* fundo, int* fundoAux,SDL_Renderer* ren){
	*fundoAux++;
	switch(*fundoAux){
		case 1:
			fundo = IMG_LoadTexture(ren, "bg2.png");
		break;
		case 2: 
			fundo = IMG_LoadTexture(ren, "bg3.png");
		break;
		case 3:
			fundo = IMG_LoadTexture(ren, "bg4.png");
		break;
		case 4:
			fundo = IMG_LoadTexture(ren, "bg5.png");
		break;
		case 5:
			fundo = IMG_LoadTexture(ren, "bg6.png");
		break;
		case 6:
			fundo = IMG_LoadTexture(ren, "bg7.png");
		break;
		case 7:
			fundo = IMG_LoadTexture(ren, "bg8.png");
		break;
		case 8:
			fundo = IMG_LoadTexture(ren, "bg1.png");
			*fundoAux = 0;
		break;
	}
	//SDL_RenderPresent(ren);
	
}

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
    SDL_Texture* img = IMG_LoadTexture(ren, "fisherman2.png");
    SDL_Texture* img2 = IMG_LoadTexture(ren, "Fisherman_idle.png");
    SDL_Texture* img3 = IMG_LoadTexture(ren, "Water.png");
    SDL_Texture* fundoTela = IMG_LoadTexture(ren, "bg1.png");
    SDL_Texture* grama = IMG_LoadTexture(ren, "grass.png");
	SDL_Texture* cabana = IMG_LoadTexture(ren, "cabana.png");
    assert(img != NULL);
    int fundoAux = 0;
    /* EXECUÇÃO */
    bool continua = true;
    bool evento = false;

    SDL_Event evt;
    int isup = 1;
    int espera = 100;
    SDL_Rect g = {0,536,484,64};
    SDL_Rect w = {444,540,584,64};
    SDL_Rect h = {300,370,384,244};
    SDL_Rect player = { 0,460, 100,80 };
    while (continua) {
        SDL_RenderClear(ren);
        SDL_Rect c;
        SDL_Rect cW;
        SDL_Rect cG;
        SDL_Rect cH;
        cG = (SDL_Rect) {   0,0, 484,64 };
        cW = (SDL_Rect) {   0,0, 584,64 };
        cH = (SDL_Rect) {   0,0, 192,122 };
	SDL_RenderCopy(ren, fundoTela, NULL, NULL);	
	SDL_RenderCopy(ren, img3, &cW, &w);
	SDL_RenderCopy(ren, grama, &cG, &g);
	SDL_RenderCopy(ren, cabana, &cH, &h);
      	Uint32 antes = SDL_GetTicks() + 500;
        int isevt = AUX_WaitEventTimeoutCount(&evt,&espera);       
        if(isevt){       	
			switch (evt.type ) {
				case SDL_QUIT:
					continua = false;
					break;	
				case SDL_KEYDOWN:

					switch (evt.key.keysym.sym){  
						case SDLK_RIGHT:
							if(player.x < 625){
								if(isup < 0) isup *= -1;
								if(player.x < 280 || player.y <= 417)  { 
									player.x += 15;

								}
								else if (player.x >= 280 && player.y > 417){

									player.x+=8; 
									player.y-=5;
								} 
								isup++;
								evento = true;
							}
						break;
						case SDLK_LEFT:
							if(isup > 0) isup *= -1;
							if(player.x >0){
								if(player.x <=285 || player.x > 360)  {
									player.x -= 15;
								}
								else{
									player.x-=8; 
									player.y+=5;

								}
								isup--;
								evento = true;
							}
						break;
						case SDLK_SPACE:
							fundoAux++;
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
			SDL_RenderCopy(ren, img, &c, &player);
		}
		else SDL_RenderCopy(ren, img2, &c, &player);
		SDL_RenderPresent(ren);
		if(isup > 6){
			isup = 1;
		}
		else if(isup < -6) isup = -1;
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
	
    }

    /* FINALIZACAO */
    SDL_DestroyTexture(img);
    SDL_DestroyTexture(img2);
    SDL_DestroyTexture(img3);
    SDL_DestroyTexture(fundoTela);
    SDL_DestroyTexture(grama);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

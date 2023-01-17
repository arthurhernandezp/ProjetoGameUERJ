#include <assert.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    //SDL_FlushEvent(SDL_MOUSEMOTION);
    if (SDL_WaitEventTimeout(evt, *ms)) {
		*ms = MAX(0, *ms - (int)(SDL_GetTicks() - antes));
		return 1;
    } return 0;
}

typedef struct dadosItem{
	SDL_Rect r;
	bool state;
	SDL_Texture* img;
}dadosItem;

typedef struct dadosInventario{
	dadosItem matrizItens[6][2];
	int n;//Numeros de itens inseridos
	SDL_Texture* texture;
	SDL_Rect rect;
	unsigned short int state;
	
}dadosInventario;

enum stateInventario {fechado = 0,aberto};

void constroi(dadosInventario* L,int x,int y){
	L->n = 0;
	int aux = x;
	L->rect = (SDL_Rect) {250,100,130,390};
	L->state = fechado;
	for(int i = 0; i<6;i++){
		for(int j = 0;j<2;j++){
			L->matrizItens[i][j].img = NULL;
		 	L->matrizItens[i][j].state = false;
		 	SDL_Rect recAux = {x,y,64,64};
		 	L->matrizItens[i][j].r = recAux;
		 	x+=65;
		}
		x= aux;
    	y+=65;
    }
}

void chamaInventario(SDL_Renderer* ren, dadosInventario inv){
	SDL_RenderCopy(ren, inv.texture, NULL, &inv.rect);
	for(int x = 0; x<=5;x++){
		for(int y = 0;y<=1;y++){
			SDL_RenderCopy(ren, inv.matrizItens[x][y].img, NULL, &inv.matrizItens[x][y].r);
		}
	}

}


int buscaElemento(dadosInventario L,int i, int j){
	return L.matrizItens[i][j].state;
}

int listaVazia(dadosInventario L){
	return L.n == 0;
}

int listaCheia(dadosInventario L){
	return L.n == 12;
}


int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Contando o Tempo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         1000, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
	SDL_Texture* imgInv = IMG_LoadTexture(ren, "inv.png");
    /* EXECUÇÃO */
    enum states {ready=0,cancelled,clicked,dropped,dragging,clicking}; 
	int cur_state = 0;
    SDL_Rect rIsca = { 554,177, 45,60 };
    SDL_Rect rPeixe = { 435,245, 26,19 };
    int espera = 100;
	Uint32 antes = 0;
	int playing = 1;
	int iscaSpeed = 5;
	int peixeSpeed = 0;
	short int aux;
	
	SDL_Texture* isca = IMG_LoadTexture(ren, "imgs/minigameIsca.png");
	SDL_Texture* peixeMG = IMG_LoadTexture(ren, "imgs/minigamePeixe.png");
	SDL_Texture* miniGameBG = IMG_LoadTexture(ren, "imgs/minigamepesca.png");
	SDL_Rect miniGame = { 400,200,308,66};
	assert(isca != NULL);
	assert(peixeMG != NULL);
	struct SDL_Texture* listaItens[7];
	listaItens[0] = IMG_LoadTexture(ren, "imgs/Icons_04.png");
	listaItens[1] = IMG_LoadTexture(ren, "imgs/Icons_05.png");
	listaItens[2] = IMG_LoadTexture(ren, "imgs/Icons_06.png");
	listaItens[3] = IMG_LoadTexture(ren, "imgs/Icons_07.png");
	listaItens[4] = IMG_LoadTexture(ren, "imgs/Icons_08.png");
	listaItens[5] = IMG_LoadTexture(ren, "imgs/Icons_09.png");
	listaItens[6] = IMG_LoadTexture(ren, "imgs/Icons_10.png");
    /* EXECUÇÃO */
    bool continua = true;
    int isup = 1;
    SDL_Rect inventario = {250,100,130,390};
    SDL_Rect r = { 251,101, 64,64 };
    SDL_Rect c;
 	int i = 0;
    int j = 0;
	for(i; i< 7;i++) assert(listaItens[i] != NULL);
    int x, y,dx,dy;
    int xAntes, yAntes;
    //Criação do primeiro inventario
    dadosInventario lista;
    lista.texture = IMG_LoadTexture(ren, "imgs/inv.png");
    constroi(&lista,250,100);
    
    SDL_Point mouse = {0,0};
    int randAux = 0;
    bool selecionado = false;
    bool encontrou = false;
    i = 0;
    SDL_Texture* auxTex;
    bool auxState;
    aux = rand()%701;
	if(aux <= 50) peixeSpeed = 1;
	else if(aux > 50 && aux <= 150) peixeSpeed = 2;
	else peixeSpeed = 3;
	
    while (playing) {    
     	SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);   
       
		espera = MAX(espera - (int)(SDL_GetTicks() - antes), 0);
	  	SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt,&espera);    
	  	antes = SDL_GetTicks();
	  	
        if (isevt) {
            switch (evt.type){
                case SDL_WINDOWEVENT:
                    if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                        playing = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                        if(evt.button.state==SDL_PRESSED) cur_state = clicking;
                        iscaSpeed = rand()%5+10;
				    break;
				case SDL_MOUSEBUTTONUP:
				    if (cur_state == clicking) 
				        cur_state = clicked;
				        iscaSpeed = rand()%5+12;
				   break;
            }
        }
         else {
        	if(cur_state == clicking){
        		rIsca.x += iscaSpeed;
        		rPeixe.x += peixeSpeed;
        	}
        	else rIsca.x -= iscaSpeed;
            espera = 100;   
        }
       if(rPeixe.x >= 655){
			randAux = rand() % 7;
			if(!listaCheia(lista)){
				printf("[%d,%d]INSERINDO\n",i,j);
				lista.matrizItens[i][j].img = listaItens[randAux];
				lista.matrizItens[i][j].state = true;
				(lista.n)++;
				j++;
				if(j >= 2 && i<5){
					j = 0;
					i++;
				}
			}
			else{
				printf("Lista Cheia!!!!\n");
			}
			rPeixe.x = 435; 
		}
		
		if(rIsca.x <= 400 || rIsca.x >= (708-rIsca.w)) {
			rIsca.x = 554;
			rPeixe.x = 435;
		
		}
		SDL_RenderCopy(ren, imgInv, NULL, &lista.rect);
 		
		chamaInventario(ren,lista);

		SDL_RenderCopy(ren, miniGameBG, NULL, &miniGame);
		SDL_RenderCopy(ren, peixeMG, NULL, &rPeixe);
		SDL_RenderCopy(ren, isca, NULL, &rIsca);
		/*SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &rIsca);
        SDL_SetRenderDrawColor(ren, 0x00,0xFF,0x00,0x00);
        SDL_RenderFillRect(ren, &rPeixe);*/
        SDL_RenderPresent(ren);
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

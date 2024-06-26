//Função para mudar a cor do button
void mudaCor(SDL_Renderer* ren,SDL_Surface* listaS[],SDL_Texture* listaT[],SDL_Color cor,int i,char* nome,TTF_Font *ourFont){
	listaS[i] = TTF_RenderText_Solid(ourFont, nome,cor);  
	listaT[i] = SDL_CreateTextureFromSurface(ren,listaS[i]);
}

void chamaMenu(SDL_Renderer* ren,uint8_t * screen,uint8_t * screenAnterior){
	if(*screen == menu){
		#ifdef DEBUG
			printf("\nIniciando Menu");
		#endif
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
		uint8_t i = 0;
		uint32_t espera = 0;    
		Uint32 antes = 0;
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
		uint8_t count = 0;
		#ifdef DEBUG
			printf("\nScreen Atual: %s",nomeScreen(*screen));
			printf("\nScreen Anterior: %s",nomeScreen(*screenAnterior));
		#endif
		while(*screen == menu){
			//desenha o menu	
			SDL_RenderCopy(ren, bgmenu, NULL, NULL);		
			SDL_RenderCopy(ren,listaTextureText[0],NULL,&recNome);
			SDL_RenderCopy(ren,listaTextureText[1],NULL,&recContinue);
			SDL_RenderCopy(ren,listaTextureText[2],NULL,&recQuit);
			SDL_RenderPresent(ren);
			espera = MAX(espera - (int)(SDL_GetTicks() - antes), 0);
		  	SDL_Event event; int isevt = AUX_WaitEventTimeoutCount(&event,&espera);    
		  	antes = SDL_GetTicks();
		  	if(isevt){   
				switch(event.type){
					case SDL_QUIT:
						*screen = fim;
					break;
					case SDL_MOUSEMOTION:
							//muda a cor do button se o mouse passar por cima
							SDL_GetMouseState(&mouse.x,&mouse.y);
						   	if(SDL_PointInRect(&mouse,&recContinue)){
						   		mudaCor(ren,listaSurfaceText,listaTextureText,focus,1,"Continue",ourFont);
			                 	if (count < 1) Mix_PlayMusic(backgroundSound, 1);//Liga o som 
			                 	if(count <= 1) count++;
						   	}
						   	else if(SDL_PointInRect(&mouse,&recQuit)){
						   		mudaCor(ren,listaSurfaceText,listaTextureText,focus,2,"Quit",ourFont);
	   		                     if (count < 1) Mix_PlayMusic(backgroundSound, 1);//Liga o som 
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
								    *screen = fim;
								}
							}
							else if(SDL_PointInRect(&mouse,&recContinue) && selecionado){
								#ifdef DEBUG
									printf("\nScreen Atual: %s",nomeScreen(*screen));
									printf("\nScreen Anterior: %s\n",nomeScreen(*screenAnterior));
								#endif
								if(*screenAnterior == jogo || *screenAnterior == menu){
									 *screen = jogo;
									 #ifdef DEBUG
										printf("\nMudei para Jogo\n");
									#endif
								}
								else if(*screenAnterior == casa){
									*screen = casa;
									 #ifdef DEBUG
										printf("\nMudei para casa\n");
									#endif
								}
							}
						}
					break;
				}
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
}

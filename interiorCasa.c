void interiorCasa(SDL_Renderer* ren,dadosPlayer *personagem,dadosInventario *inventario,dadosCeu *ceu,uint8_t * screen){
	if(*screen == casa){
		Uint32 antes = 0;
		int espera = 0;    
		
		SDL_Rect casaRect = {74,63,852,474};
		SDL_Texture* fundoCasa = IMG_LoadTexture(ren, "imgs/interior_house.jpg");
		
		dadosBotao botao;
		botao.rect = (SDL_Rect) {632,375,35,35};
		botao.texture = IMG_LoadTexture(ren, "imgs/botao.png");
		
		SDL_SetRenderDrawColor(ren,0,0,0,255);
		uint8_t contFundo = 0;
		while(*screen == casa){
			espera = MAX(espera - (int)(SDL_GetTicks() - antes), 0);
		  	SDL_Event evento; int isevt = AUX_WaitEventTimeoutCount(&evento,&espera);    
		  	antes = SDL_GetTicks();	
		  	if(isevt){ 
		  		switch(evento.type){
		  			case SDL_KEYUP:
		  				if(evento.key.keysym.sym == SDLK_e && personagem->rect.x >= 758){
		  					 *screen = jogo;
		  					 personagem->rect.y= 415;
		  					 personagem->rect.x=368;
		  					 break;
		  				}else if(evento.key.keysym.sym == SDLK_i){
			 				if(inventario->state == fechado) inventario->state = aberto;
							else if(inventario->state == aberto) inventario->state = fechado;
			 			}else if(evento.key.keysym.sym == SDLK_ESCAPE){
								*screen = menu;
								#ifdef DEBUG
			                        printf("Estado de Screen mudou para 'menu' usando SDLK_ESCAPE\n");  // Debugging log
								#endif
						}
		  				else{
			 				 personagem->state = idle;
			 			}
			 			
						#ifdef DEBUG
							printf("\nTecla solta: %s\n", nomeTecla(evento.key.keysym.sym));
    						printf("Estado do personagem: %d\n", personagem->state);
                            printf("Posicao x: %d | Posicao y: %d\n", personagem->rect.x,personagem->rect.y);
						#endif
		  				break;
		  			case SDL_QUIT:
		  				*screen = fim;
		  				break;
		  			case SDL_KEYDOWN:
		  				if(evento.key.keysym.sym == SDLK_RIGHT){
							if(personagem->rect.x < 826){
								if(personagem->corte.x < 240){
								 	personagem->corte.x += 48;
								}
								else {
									personagem->corte.x = 0;
								}
								
								if(personagem->corte.y != 0) personagem->corte.y = 0;
								
								personagem->rect.x += 7;
								personagem->state = walking;
							}
								
		  				}else if(evento.key.keysym.sym == SDLK_LEFT){	
							if(personagem->rect.x > 105){
									if(personagem->corte.x < 240) personagem->corte.x +=48;
									else personagem->corte.x = 0;
									if(personagem->corte.y != 48) personagem->corte.y = 48;
									
									personagem->rect.x -= 7;
									personagem->state = walking;
							}
						}
		  				break;
		  			default:
		  				SDL_FlushEvent(evento.type);
		  		}
		  	}else{
		  		espera = 500;
		  		contFundo += 1;
	 			if (contFundo == 15){
					(ceu->fundoAux)++;
					contFundo = 0;
				}
				if(personagem->state == idle){
					if (personagem->corte.x < 240) personagem->corte.x +=48;
					else personagem->corte.x = 0;
				}
			}
			mudaTextura(ren,personagem);
			SDL_RenderClear(ren);
			//Desenha o botao "E"
			
			SDL_RenderCopy(ren, fundoCasa, NULL, &casaRect);					
			SDL_RenderCopy(ren, personagem->texture, &personagem->corte, &personagem->rect);	
			if(personagem->rect.x >= 758){
				botao.rect.x = 800;
				botao.rect.y = 250;
				SDL_RenderCopy(ren, botao.texture, NULL, &botao.rect);
			}
			if(inventario->state == aberto) chamaInventario(ren,*inventario);
			SDL_RenderPresent(ren);		
		}
	}
}
	




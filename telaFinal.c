void rodaTelaFinal(SDL_Renderer* ren,dadosPlayer *personagem,dadosBarco *barco,dadosCeu *ceu,unsigned short int * screen){
	if(*screen == telaFinal){
		TTF_Init();
		SDL_Color padrao = { 255,0,0,255 };
		SDL_Color focus = { 0,157,231,255 };
		char fonte[23] = "imgs/ArcadeClassic.ttf";
		TTF_Font *ourFont = TTF_OpenFont(fonte,40);
		Uint32 antes = 0;
		int espera = 0;    
		SDL_Rect aguaRect1 = {0,540,584,64};
		SDL_Rect aguaRect2 = {454,540,584,64};
		barco->rect = (SDL_Rect) { -100,513, 148,36 };
		personagem->rect.y = 473;
		personagem->rect.x = (barco->rect.w)/2 + barco->rect.x;
		personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_row.png");
		SDL_Texture* agua = IMG_LoadTexture(ren, "imgs/Water.png");
		personagem->corte.y = personagem->corte.x = 0;
		
		SDL_Surface* textoSur = TTF_RenderText_Solid(ourFont, "Aperte   ESC    para sair",padrao);
		SDL_Texture* textoTex = SDL_CreateTextureFromSurface(ren,textoSur);
		SDL_Rect textoRect = {300,-100,600,200};
		SDL_FreeSurface(textoSur);
		int var = 1;
		short int aguaAux = 0;
		while(*screen == telaFinal){
			espera = MAX(espera - (int)(SDL_GetTicks() - antes), 0);
		  	SDL_Event evento; int isevt = AUX_WaitEventTimeoutCount(&evento,&espera);    
		  	antes = SDL_GetTicks();
  			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, ceu->texture, NULL, NULL);				
			SDL_RenderCopy(ren, barco->texture, NULL, &barco->rect);
			SDL_RenderCopy(ren, agua, NULL, &aguaRect1);	
			SDL_RenderCopy(ren, agua, NULL, &aguaRect2);		
			SDL_RenderCopy(ren, personagem->texture, &personagem->corte, &personagem->rect);	
			SDL_RenderCopy(ren,textoTex ,NULL,&textoRect);
			SDL_RenderPresent(ren);			
		  	if(isevt){ 
		  		if(evento.type == SDL_KEYUP){
		  			if(evento.key.keysym.sym == SDLK_ESCAPE) *screen = fim;
		  		}
  				if(evento.type == SDL_QUIT) *screen = fim;
		  	}else{
		  		espera = 100;
		  		if(barco->rect.x <= 1200){
		  			barco->rect.x +=2;
		  			personagem->rect.x += 2;
		  			if(personagem->corte.x < 144) personagem->corte.x +=48;
					else personagem->corte.x = 0;
		  		}
		  		if(textoRect.y <= 150) textoRect.y+= 2;
			}
		}
	}
}
	





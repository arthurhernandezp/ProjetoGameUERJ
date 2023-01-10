void rodaJogo(SDL_Renderer* ren,bool* menu,bool* gameIsRunning,bool* playing,dadosPlayer *personagem,dadosCeu *ceu,dadosBarco *barco,dadosInventario *inventario,char * listaItens[]){

	int i = 0; int contFundo = 0;
	dadosMouse mouse;
	mouse.rect.x = 0; mouse.rect.y = 0; mouse.rect.w = 30; mouse.rect.h = 50;
	mouse.state = 0;
	mouse.texture = IMG_LoadTexture(ren, "imgs/mouse.png");
	
	dadosBotao botao;
	botao.rect = (SDL_Rect) {632,375,35,35};
	botao.texture = IMG_LoadTexture(ren, "imgs/botao.png");
	
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
    assert(mouse.texture != NULL);
    assert(botao.texture != NULL);
    
    unsigned short int fundoAux;
    int espera = 0;    
    SDL_Rect gDec = {0,507,32,33};
    SDL_Rect g = {0,536,484,64};
    SDL_Rect w = {454,540,584,64};
    SDL_Rect h = {300,370,384,244};
    SDL_Rect arvore = {130,324,179.2,224};
	SDL_Rect cArv = (SDL_Rect) {89.6,0, 89.6,132 };
	Uint32 antes = 0;
	int var = 1;
	int randAux = 0;
	
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
									
									if(personagem->rect.x < 280 || personagem->rect.y <= 417) personagem->rect.x += 7;
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
									if((personagem->rect.x <=288 || personagem->rect.x > 360) &&
									(personagem->rect.y == 460 || personagem->rect.y == 415)) personagem->rect.x -= 7;
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
							(ceu->fundoAux)++;
							break;
						case SDLK_ESCAPE:
							*menu = true;
							*playing = false;
							SDL_ShowCursor(true);
							mouse.state = 0;
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
						case SDLK_i:
							if(inventario->state == fechado) inventario->state = aberto;
							else if(inventario->state == aberto) inventario->state = fechado;
							break;
						case SDLK_1:
							if(inventario->state == aberto){
								randAux = rand() % 7;	
								if(!listaCheia(*inventario)){
									if(	!buscaElemento(*inventario,inventario->i,inventario->j) ){
										printf("[%d,%d]INSERINDO\n",inventario->i,inventario->j);
										inventario->matrizItens[inventario->i][inventario->j].img = IMG_LoadTexture(ren, listaItens[randAux]);
										inventario->matrizItens[inventario->i][inventario->j].state = true;
										(inventario->n)++;
										inventario->j++;

										if(inventario->j >= 2 && inventario->i<5){
										inventario->j = 0;
										inventario->i++;
										}
									}
									else{
										printf("Existe um elemento na proxima posição!!!");
									}
								}
								else{
									printf("Lista Cheia!!!!\n");
								}
							}
							break;
						case SDLK_2:
							if(inventario->state == aberto){
								if(!listaVazia(*inventario)){
									inventario->j--;
									if(inventario->j < 0 && inventario->i>0){
										inventario->j = 1;
										inventario->i--;
									}
									inventario->matrizItens[inventario->i][inventario->j].img = NULL;
									inventario->matrizItens[inventario->i][inventario->j].state = false;
									(inventario->n)--;
									printf("[%d,%d] DELETING\n",inventario->i,inventario->j);
								}
								else{
									printf("Lista Vazia!!!!\n");
								}
							}
							break;
						default:
							SDL_FlushEvent(evt.type);
							break;
		 		}
		 		case SDL_MOUSEMOTION:
		 			SDL_GetMouseState(&mouse.point.x,&mouse.point.y);
		 			if(personagem->lugar == onBoat && SDL_PointInRect(&mouse.point,&w) && !*menu){
		 				mouse.state = 1;
		 				mouse.rect.x = mouse.point.x;
		 				mouse.rect.y = mouse.point.y- mouse.rect.h;
		 			}
		 			else mouse.state = 0;
		 		default:
					SDL_FlushEvent(evt.type);
					break;
			}
		} else {   
  			contFundo += 1;
 			if (contFundo == 15){
				(ceu->fundoAux)++;
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
		if(personagem->state == idle && personagem->lugar == onGround) personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_idle.png");
		else if(personagem->state == walking && personagem->lugar == onGround ) personagem->texture = IMG_LoadTexture(ren, "imgs/fisherman2.png");
		else if(personagem->lugar == onBoat ) personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_row.png");
		
		switch(ceu->fundoAux){
			case 1:
				ceu->texture = IMG_LoadTexture(ren, "imgs/bg3.png");
			break;
			case 2: 
				ceu->texture = IMG_LoadTexture(ren, "imgs/bg4.png");
			break;
			case 3:
				ceu->texture = IMG_LoadTexture(ren, "imgs/bg5.png");
			break;
			case 4:
				ceu->texture = IMG_LoadTexture(ren, "imgs/bg6.png");
			break;
			case 5:
				ceu->texture = IMG_LoadTexture(ren, "imgs/bg7.png");
			break;
			case 6:
				ceu->texture = IMG_LoadTexture(ren, "imgs/bg8.png");
			break;
			case 7:
				ceu->texture = IMG_LoadTexture(ren, "imgs/bg1.png");	
			break;
			case 8:
				ceu->texture = IMG_LoadTexture(ren, "imgs/bg2.png");		
			break;
			default: 
				ceu->fundoAux = 1;
			break;
		}
		
		//if(fundoAux >= 9) fundoAux = 1;
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, ceu->texture, NULL, NULL);		
		SDL_RenderCopy(ren, cabana, NULL, &h);
		//SDL_RenderCopy(ren, grama, NULL, &g);
		SDL_RenderCopy(ren, listaDec[4], &cArv, &arvore);
		for(i = 0; i <= 3;i++){
			SDL_RenderCopy(ren, listaDec[i], NULL, &gDec);
			gDec.x+=100;
		} gDec.x = 0;	
		SDL_RenderCopy(ren, barco->texture, NULL, &barco->rect);		
		SDL_RenderCopy(ren, personagem->texture, &personagem->corte, &personagem->rect);
		SDL_RenderCopy(ren, agua, NULL, &w);
		SDL_RenderCopy(ren, grama, NULL, &g);		
		if(mouse.state == 1){
			SDL_ShowCursor(false);
			SDL_RenderCopy(ren, mouse.texture, NULL, &mouse.rect);		
		}
		else if(mouse.state == 0) SDL_ShowCursor(true);
		
		if( (personagem->rect.x >= barco->rect.x && personagem->lugar == onGround) ||
		(personagem->rect.x > 554 && personagem->rect.x < 652 && personagem->lugar == onBoat ) ) {
			SDL_RenderCopy(ren, botao.texture, NULL, &botao.rect);
		}	
		if(inventario->state == aberto) chamaInventario(ren,*inventario);
		SDL_RenderPresent(ren);
		
	}	
	
	SDL_DestroyTexture(agua);
	SDL_DestroyTexture(grama);
	SDL_DestroyTexture(cabana);
	SDL_DestroyTexture(mouse.texture);
	SDL_DestroyTexture(botao.texture);
	for(i = 0; i < 4; i++)
		SDL_DestroyTexture(listaDec[i]);
	
}

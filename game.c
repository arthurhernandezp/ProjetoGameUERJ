void rodaJogo(SDL_Renderer* ren,dadosPlayer *personagem,dadosCeu *ceu,dadosBarco *barco,dadosInventario *inventario,char * listaItens[],unsigned short int * screen){
	//MINIGAME 
	dadosMinigame minigame;
	minigame.state = cancelado;
    SDL_Rect rIsca = { 774,357, 45,60 };
    SDL_Rect rPeixe = { 655,425, 26,19 };
	SDL_Texture* isca = IMG_LoadTexture(ren, "imgs/minigameIsca.png");
	SDL_Texture* peixeMG = IMG_LoadTexture(ren, "imgs/minigamePeixe.png");
	SDL_Texture* miniGameBG = IMG_LoadTexture(ren, "imgs/minigamepesca2.png");
	SDL_Rect miniGame = { 620,380,308,66};
	unsigned short int iscaSpeed = 5;
	unsigned short int peixeSpeed = 0;
	unsigned short int cur_state = 0;
	
	
	//FIM DO MINIGAME
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
	unsigned short int pescaAux = 0;
	while (*screen == jogo) {	
		espera = MAX(espera - (int)(SDL_GetTicks() - antes), 0);
	  	SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt,&espera);    
	  	antes = SDL_GetTicks();
	  	
	  	if(isevt){       
			switch (evt.type) {
				case SDL_WINDOWEVENT:
                	if (SDL_WINDOWEVENT_CLOSE == evt.window.event){
					    *screen = fim;
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
							*screen = menu;
							SDL_ShowCursor(true);
							mouse.state = 0;
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
						default:
							SDL_FlushEvent(evt.type);
							break;
		 		}
		 		case SDL_MOUSEMOTION:
		 			SDL_GetMouseState(&mouse.point.x,&mouse.point.y);
		 			if(personagem->lugar == onBoat && SDL_PointInRect(&mouse.point,&w) && *screen == jogo || personagem->state == fishing || personagem->state == pulling){
		 				mouse.state = 1;
		 				mouse.rect.x = mouse.point.x - mouse.rect.w;
		 				mouse.rect.y = mouse.point.y- mouse.rect.h;
		 			}
		 			else mouse.state = 0;
		 		default:
					SDL_FlushEvent(evt.type);
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(mouse.state == 1 && personagem->state != fishing && personagem->state != pulling){
						personagem->state = fishing;
						personagem->rect.y -= 5;
					}
					if(evt.button.state==SDL_PRESSED) {
					 	cur_state = clicking;
					}
                    if(personagem->state == pulling) iscaSpeed = rand()%5+10;
                break;
                case SDL_MOUSEBUTTONUP:
				   if(cur_state == clicking) cur_state = clicked;
				   if(personagem->state == pulling) iscaSpeed = rand()%5+12;
				   break;
			}
		} else {   
			if(personagem->state != pulling){
	  			contFundo += 1;
	 			if (contFundo == 15){
					(ceu->fundoAux)++;
					contFundo = 0;
				}
				w.y = w.y + 1 * (var);
				var *= -1;
				espera = 500;
			}
			if(personagem->lugar == onGround){
				personagem->state = idle;
				if (personagem->corte.x < 240) personagem->corte.x +=48;
				else personagem->corte.x = 0;
			}
			else if(personagem->lugar == onBoat){
				if(personagem->state == fishing){
					if(personagem->corte.x < 144) personagem->corte.x +=48;
					else personagem->corte.x = 0;
					pescaAux++;
					if(pescaAux == 10) {
						personagem->state = pulling;
						pescaAux = 0;
						personagem->corte.x = 0;
						randAux = rand() % 7;
						switch(randAux){
							case 0:
								peixeSpeed = 1;
							break;
							case 1:
								peixeSpeed = 2;
							break;
							case 2: 
								peixeSpeed = 3;
							break;
							default:
								peixeSpeed = 4;
							break;
						}
					}
				}
				else if(personagem->state == pulling){
					minigame.state = emjogo;
					if(pescaAux == 5){
						if(personagem->corte.x < 96) personagem->corte.x += 48;
						else personagem->corte.x = 0;
						pescaAux = 0;
					}
					if(cur_state == clicking){
        				rIsca.x += iscaSpeed;
						if(rIsca.x < rPeixe.x) rPeixe.x += peixeSpeed;
						else rPeixe.x += 1;
        			}
					if(cur_state == clicking){
						rIsca.x += iscaSpeed;
						if(rIsca.x < rPeixe.x) rPeixe.x += peixeSpeed;
						else rPeixe.x += 1;
					}
					else rIsca.x -= iscaSpeed;
					espera = 100;
					pescaAux++;
				}
			}
		}
		
		if(*screen == menu) {
			mouse.state = 0;
			SDL_ShowCursor(true);
		}
		//trata minigame
		if(personagem->state != pulling && minigame.state == emjogo){
			minigame.state = cancelado;
			personagem->state = remando;
		}
		else{
			if(rPeixe.x >= 875){
				minigame.state == cancelado;
				if(!listaCheia(*inventario)){
					printf("[%d,%d]INSERINDO\n",inventario->i,inventario->j);
					inventario->matrizItens[inventario->i][inventario->j].img =IMG_LoadTexture(ren, listaItens[randAux]); 
					inventario->matrizItens[inventario->i][inventario->j].state = true;
					(inventario->n)++;
					inventario->j++;
					if(inventario->j >= 2 && inventario->i<5){
						inventario->j = 0;
						inventario->i++;
					}
				}
				else{
					printf("Lista Cheia!!!!\n");
				}
				rPeixe.x = 655; 
				rIsca.x = 774;
				personagem->state = remando;
			}
			if(rIsca.x <= 620 || rIsca.x >= (928-rIsca.w)) {
				rIsca.x = 774;
				rPeixe.x = 655;
				minigame.state = cancelado;
				personagem->state = remando;
			}
		}
		
		//MUDA TEXTURA DO PLAYER
		if(personagem->state == idle && personagem->lugar == onGround) personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_idle.png");
		else if(personagem->state == walking && personagem->lugar == onGround ) personagem->texture = IMG_LoadTexture(ren, "imgs/fisherman2.png");
		else if(personagem->lugar == onBoat && personagem->state == remando) {
			personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_row.png");
			personagem->rect.y = 473;
		}
		else if(personagem->lugar == onBoat && personagem->state == fishing){
			personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_fish.png");
			personagem->rect.y = 467;
			personagem->corte.y = 0;
		}
		else if(personagem->lugar == onBoat && personagem->state == pulling){
			personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_hook.png");
		}
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
		
		SDL_RenderClear(ren);
		
		SDL_RenderCopy(ren, ceu->texture, NULL, NULL);		
		SDL_RenderCopy(ren, cabana, NULL, &h);
		SDL_RenderCopy(ren, listaDec[4], &cArv, &arvore);
		for(i = 0; i <= 3;i++){
			SDL_RenderCopy(ren, listaDec[i], NULL, &gDec);
			gDec.x+=100;
		} gDec.x = 0;	
		
		if(personagem->state != fishing && personagem->state != pulling){
			SDL_RenderCopy(ren, barco->texture, NULL, &barco->rect);		
			SDL_RenderCopy(ren, personagem->texture, &personagem->corte, &personagem->rect);
		}
		else{
			SDL_RenderCopy(ren, personagem->texture, &personagem->corte, &personagem->rect);
			SDL_RenderCopy(ren, barco->texture, NULL, &barco->rect);		
		}
		
		
		
		SDL_RenderCopy(ren, agua, NULL, &w);
		SDL_RenderCopy(ren, grama, NULL, &g);	
		
		//Muda textura do mouse	
		if(mouse.state == 1){
			SDL_ShowCursor(false);
			SDL_RenderCopy(ren, mouse.texture, NULL, &mouse.rect);		
		}
		else if(mouse.state == 0) SDL_ShowCursor(true);
		
		if( (personagem->rect.x >= barco->rect.x && personagem->lugar == onGround) ||
		(personagem->rect.x > 554 && personagem->rect.x < 652 && personagem->lugar == onBoat ) && personagem->state !=pulling && personagem->state != fishing) {
			SDL_RenderCopy(ren, botao.texture, NULL, &botao.rect);
		}	
		
		if(inventario->state == aberto) chamaInventario(ren,*inventario);
		if(minigame.state == emjogo && personagem->state == pulling){
			SDL_RenderCopy(ren, miniGameBG, NULL, &miniGame);
			SDL_RenderCopy(ren, peixeMG, NULL, &rPeixe);
			SDL_RenderCopy(ren, isca, NULL, &rIsca);
		}
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

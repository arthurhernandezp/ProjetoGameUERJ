void mudaTextura(SDL_Renderer* ren,dadosPlayer *personagem){
	if(personagem->state == idle && personagem->lugar == onGround) personagem->texture = IMG_LoadTexture(ren, "imgs/Fisherman_idle.png");
	else if(personagem->state == walking && personagem->lugar == onGround ){
		 personagem->texture = IMG_LoadTexture(ren, "imgs/fisherman2.png");
	}
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
}

void rodaJogo(SDL_Renderer* ren,dadosPlayer *personagem,dadosCeu *ceu,dadosBarco *barco,dadosInventario *inventario,char * listaItens[],uint8_t * screen,dadosMinigame *minigame){
	if(*screen == jogo){
		#ifdef DEBUG
			printf("\nIniciando Jogo\n");
			printf("Estado do personagem: %d\n", personagem->state);
			printf("Fundo de tela atual: %d\n", ceu->fundoAux);
			printf("Numero de peixes no inventario: %d\n", inventario->n);
		#endif
		
		uint8_t cur_state = 0;
		uint8_t i = 0; uint8_t contFundo = 0;
		dadosMouse mouse;
		mouse.rect.x = 0; mouse.rect.y = 0; mouse.rect.w = 30; mouse.rect.h = 50;
		mouse.state = 0;
		mouse.texture = IMG_LoadTexture(ren, "imgs/mouse.png");

		dadosBotao botao;
		botao.rect = (SDL_Rect) {632,375,35,35};
		botao.texture = IMG_LoadTexture(ren, "imgs/botao.png");
		SDL_Texture* inv2 = IMG_LoadTexture(ren, "imgs/balde.png");
		SDL_Texture* agua = IMG_LoadTexture(ren, "imgs/Water.png");
		SDL_Texture* grama = IMG_LoadTexture(ren, "imgs/grass.png");
		SDL_Texture* cabana = IMG_LoadTexture(ren, "imgs/cabana.png");
		
		dadosVendedor vendedor;
		vendedor.texture = IMG_LoadTexture(ren, "imgs/market.png");
		vendedor.dialogo = IMG_LoadTexture(ren, "imgs/Dialogo1.png");
		vendedor.dialogoRect =  (SDL_Rect) {30,200,381,134};
		vendedor.rect =  (SDL_Rect) {10,446,110,92};

		SDL_Texture* avatar = IMG_LoadTexture(ren, "imgs/barco.png");
		SDL_Rect avtRect = {20,20,180,75};
		
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
		SDL_Rect inv2r = {600,0,350,405};
		unsigned short int fundoAux;
		int espera = 0;    
		SDL_Rect gDec = {0,507,32,33};
		SDL_Rect gramaRect = {0,536,484,64};
		SDL_Rect aguaRect = {454,540,584,64};
		SDL_Rect h = {300,370,384,244};
		SDL_Rect arvore = {130,324,179.2,224};
		SDL_Rect cArv = (SDL_Rect) {89.6,0, 89.6,132 };
		Uint32 antes = 0;
		int8_t var = 1;
		uint8_t randAux = 0;
		uint8_t pescaAux = 0;

		while (*screen == jogo) {	
			#ifdef DEBUG
				//printf("\nLoop principal rodando, screen: %d\n",*screen);
			#endif
			espera = MAX(espera - (int)(SDL_GetTicks() - antes), 0);
		  	SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt,&espera);    
		  	antes = SDL_GetTicks();
		  	
		  	if(isevt){       
				switch (evt.type) {
					case SDL_WINDOWEVENT:
		            	if (SDL_WINDOWEVENT_CLOSE == evt.window.event){
							*screen = fim;
							#ifdef DEBUG
                            	printf("Estado de Screen mudou para 'fim' ao fechar a janela\n");  // Debugging log
                            #endif

						} 
					break;	
					case SDL_KEYDOWN:
						switch (evt.key.keysym.sym){  
							case SDLK_SPACE:
								*screen =  telaFinal;
								#ifdef DEBUG
									printf("\nScreen mudou para tela final ao apertar Espaço");
								#endif
								minigame->isca = NULL;
								minigame->peixeMG = NULL;
								minigame->texture = NULL;
								for(i = 0; i < 3;i++){
									for(uint8_t j = 0; j < 4;j++){
										inventario->matrizItens[i][j].img = NULL; 
									}
								}
							case SDLK_RIGHT:
								if(personagem->lugar == onGround){
									if(personagem->rect.x < 625){
										//Movimenta o corte na imagem a cada comando e garante que sempre vai estar na parte de cima da imagem quando for pra direita
										if(personagem->corte.x < 240) personagem->corte.x += 48;
										else personagem->corte.x = 0;
										if(personagem->corte.y != 0) personagem->corte.y = 0;
										
										//O personagem ande em qualquer lugar diferente da escada
										if(personagem->rect.x < 280 || personagem->rect.y <= 417) personagem->rect.x += 7;
										else if (personagem->rect.x >= 280 && personagem->rect.y > 417){//Personagem começa a subir a escada
											personagem->rect.x+=8; 
											personagem->rect.y-=5;
										} 
										personagem->state = walking;
									}
								}
								else if(personagem->lugar == onBoat){
									
									if(personagem->rect.x < 852){
										//Movimenta o corte na imagem a cada comando e garante que sempre vai estar na parte de cima da imagem quando for pra direita
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
									//Movimenta o corte na imagem a cada comando e garante que sempre vai estar na parte de cima da imagem quando for pra esquerda
									if(personagem->corte.x < 240) personagem->corte.x +=48;
									else personagem->corte.x = 0;
									if(personagem->corte.y != 48) personagem->corte.y = 48;
									
									if(personagem->rect.x >0){	
										//If para garantir que o personagem ande em qualquer lugar diferente da escada
										if((personagem->rect.x <=288 || personagem->rect.x > 360) &&
										(personagem->rect.y == 460 || personagem->rect.y == 415)) personagem->rect.x -= 7;
										else{//Personagem começa a descer a escada
											personagem->rect.x-=8; 
											personagem->rect.y+=5;
										}
										personagem->state = walking;
									}
								}
								else if(personagem->lugar == onBoat){
									if(personagem->rect.x > 554 ){
										//Movimenta o corte na imagem a cada comando e garante que sempre vai estar na parte de cima da imagem quando for pra esquerda
										if(personagem->corte.x < 144) personagem->corte.x +=48;
										else personagem->corte.x = 0;
										if(personagem->corte.y != 48) personagem->corte.y = 48;		
										personagem->rect.x -= 4;
										barco->rect.x -= 4;
										personagem->state = remando;
									}
								}
							break;
							default:
								if(personagem->state == walking) personagem->state = idle;
								//SDL_FlushEvent(evt.type);
								break;
						
			 		}
			 		case SDL_MOUSEMOTION:
			 			SDL_GetMouseState(&mouse.point.x,&mouse.point.y);
			 			if(personagem->lugar == onBoat && SDL_PointInRect(&mouse.point,&aguaRect) && *screen == jogo || personagem->state == fishing || personagem->state == pulling){
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
		                if(personagem->state == pulling) minigame->iscaSpeed = rand()%5+10;
		            break;
		            case SDL_MOUSEBUTTONUP:
					   if(cur_state == clicking) cur_state = clicked;
					   if(personagem->state == pulling) minigame->iscaSpeed = rand()%5+12;
					break;
				}
				if(evt.type == SDL_KEYUP){
			 			if(evt.key.keysym.sym == SDLK_RIGHT || evt.key.keysym.sym == SDLK_LEFT && personagem->lugar == onGround){
			 				 personagem->state = idle;
			 			}
			 			else if(evt.key.keysym.sym == SDLK_e){
				 			if(personagem->rect.x >= barco->rect.x && personagem->lugar == onGround){
				 						#ifdef DEBUG
				 							printf("Entrou no Barco");
				 						#endif
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
							else if(SDL_HasIntersection(&vendedor.rect, &personagem->rect) && listaCheia(*inventario)){
								*screen = telaFinal;
								#ifdef DEBUG
                           			 printf("Estado da Screen mudou para 'telaFinal' quando apertou 'e' colidindo com o vendendor e com o inventario está cheio\n");  // Debugging log
		                        #endif

								minigame->isca = NULL;
								minigame->peixeMG = NULL;
								minigame->texture = NULL;
								for(i = 0; i < 3;i++){
									for(uint8_t j = 0; j < 4;j++){
										inventario->matrizItens[i][j].img = NULL; 
									}
								}

							}
							else if(personagem->rect.x >= 355 && personagem->rect.x <= 401){
								*screen = casa;
								#ifdef DEBUG
                           			 printf("Estado da Screen mudou para 'interiorcasa' quando apertou 'e' na porta\n");  // Debugging log
		                        #endif
							}
			 			}
			 			else if(evt.key.keysym.sym == SDLK_i){
			 				if(inventario->state == fechado) inventario->state = aberto;
							else if(inventario->state == aberto) inventario->state = fechado;
			 			}
			 			else if(evt.key.keysym.sym == SDLK_ESCAPE){
								*screen = menu;
								#ifdef DEBUG
			                        printf("Estado de Screen mudou para 'menu' usando SDLK_ESCAPE\n");  // Debugging log
								#endif
								SDL_ShowCursor(true);
								mouse.state = 0;
						}
						else{
							if(personagem->state == walking) personagem->state = idle;
						}
						#ifdef DEBUG
							printf("\nTecla solta: %s\n", nomeTecla(evt.key.keysym.sym));
    						printf("Estado do personagem: %d\n", personagem->state);
                            printf("Posicao x: %d | Posicao y: %d\n", personagem->rect.x,personagem->rect.y);
						#endif
				}
			} else {   
				if(personagem->state != pulling){
		  			contFundo += 1;
		 			if (contFundo == 15){
						(ceu->fundoAux)++;
						contFundo = 0;
					}
					aguaRect.y = aguaRect.y + 1 * (var);
					var *= -1;
					espera = 500;
				}
				if(personagem->lugar == onGround){
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
									minigame->peixeSpeed = 1;
								break;
								case 1:
									minigame->peixeSpeed = 2;
								break;
								case 2: 
									minigame->peixeSpeed = 3;
								break;
								default:
									minigame->peixeSpeed = 4;
								break;
							}
						}
					}
					else if(personagem->state == pulling){
						minigame->state = emjogo;
						if(pescaAux == 5){
							if(personagem->corte.x < 96) personagem->corte.x += 48;
							else personagem->corte.x = 0;
							pescaAux = 0;
						}
						if(cur_state == clicking){
		    				minigame->rIsca.x += minigame->iscaSpeed;
							if(minigame->rIsca.x < minigame->rPeixe.x) minigame->rPeixe.x += minigame->peixeSpeed;
							else minigame->rPeixe.x += 1;
		    			}
						if(cur_state == clicking){
							minigame->rIsca.x += minigame->iscaSpeed;
							if(minigame->rIsca.x < minigame->rPeixe.x) minigame->rPeixe.x += minigame->peixeSpeed;
							else minigame->rPeixe.x += 1;
						}
						else minigame->rIsca.x -= minigame->iscaSpeed;
						espera = 100;
						pescaAux++;
					}
				}
			}
			//trata a passagem de tela do jogo para o menu ativando o cursor windowns novamente
			if(*screen == menu) {
				mouse.state = 0;
				SDL_ShowCursor(true);
			}
			
			//trata minigame
			if(personagem->state != pulling && minigame->state == emjogo){
				minigame->state = cancelado;
				personagem->state = remando;
			}
			else{
				if(minigame->rPeixe.x >= 875){
					minigame->state == cancelado;
					if(!listaCheia(*inventario)){
						#ifdef DEBUG
							printf("[%d,%d]INSERINDO\n",inventario->i,inventario->j);
						#endif
						inventario->matrizItens[inventario->i][inventario->j].img =IMG_LoadTexture(ren, listaItens[randAux]); 
						inventario->matrizItens[inventario->i][inventario->j].state = true;
						(inventario->n)++;
						inventario->j++;
						if(inventario->j >= 4 && inventario->i<3){
							inventario->j = 0;
							inventario->i++;
						}
					}
					else{
						printf("Lista Cheia!!!!\n");
					}
					minigame->rPeixe.x = 655; 
					minigame->rIsca.x = 774;
					personagem->state = remando;
				}
				if(minigame->rIsca.x <= 620 || minigame->rIsca.x >= (928-minigame->rIsca.w)) {
					minigame->rIsca.x = 774;
					minigame->rPeixe.x = 655;
					minigame->state = cancelado;
					personagem->state = remando;
				}
			}

			mudaTextura(ren,personagem);

			//Switch para controlar a mudança do fundo de tela
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
			//Desenha grama decoração
			for(i = 0; i <= 3;i++){
				SDL_RenderCopy(ren, listaDec[i], NULL, &gDec);
				gDec.x+=100;
			} gDec.x = 0;	
			SDL_RenderCopy(ren,vendedor.texture, NULL, &vendedor.rect);
			if(personagem->state != fishing && personagem->state != pulling){
				SDL_RenderCopy(ren, barco->texture, NULL, &barco->rect);		
				SDL_RenderCopy(ren, personagem->texture, &personagem->corte, &personagem->rect);
			}
			else{
				SDL_RenderCopy(ren, personagem->texture, &personagem->corte, &personagem->rect);
				SDL_RenderCopy(ren, barco->texture, NULL, &barco->rect);		
			}
			SDL_RenderCopy(ren, agua, NULL, &aguaRect);
			SDL_RenderCopy(ren, grama, NULL, &gramaRect);	
				
			//Desenha o botao "E"
			if( (personagem->rect.x >= barco->rect.x && personagem->lugar == onGround) ||
			(personagem->rect.x > 554 && personagem->rect.x < 652 && personagem->lugar == onBoat ) && personagem->state !=pulling && personagem->state != fishing) {
				botao.rect.x =632;
				botao.rect.y = 375;
				SDL_RenderCopy(ren, botao.texture, NULL, &botao.rect);
			}else if(personagem->rect.x >= 355 && personagem->rect.x <= 401){
                botao.rect.x = 380;
                botao.rect.y = 300;
                SDL_RenderCopy(ren,botao.texture, NULL,&botao.rect);
            }
            
			//DESENHA BOTAO E DIALOGO DO VENDEDOR
			if(SDL_HasIntersection(&vendedor.rect, &personagem->rect)) {
				if(listaCheia(*inventario)){
					vendedor.dialogo = IMG_LoadTexture(ren, "imgs/Dialogo2.png");
					botao.rect.x = 50;
					botao.rect.y = 400;
					SDL_RenderCopy(ren, botao.texture, NULL, &botao.rect);
				}
				SDL_RenderCopy(ren, vendedor.dialogo, NULL, &vendedor.dialogoRect);
			}
			//Desenha o inventario
			if(inventario->state == aberto) chamaInventario(ren,*inventario);
			//Desenha o minigame
			if(minigame->state == emjogo && personagem->state == pulling){
				SDL_RenderCopy(ren, minigame->texture, NULL, &minigame->rect);
				SDL_RenderCopy(ren, minigame->peixeMG, NULL, &minigame->rPeixe);
				SDL_RenderCopy(ren, minigame->isca, NULL, &minigame->rIsca);
			}	
			//Muda textura do mouse	
			if(mouse.state == 1){
				SDL_ShowCursor(false);
				SDL_RenderCopy(ren, mouse.texture, NULL, &mouse.rect);		
			}
			else if(mouse.state == 0) SDL_ShowCursor(true);
			
			SDL_RenderCopy(ren,avatar, NULL, &avtRect);
			SDL_RenderPresent(ren);	

		}		
		SDL_DestroyTexture(agua);
		SDL_DestroyTexture(grama);
		SDL_DestroyTexture(cabana);
		SDL_DestroyTexture(mouse.texture);
		SDL_DestroyTexture(botao.texture);
		SDL_DestroyTexture(vendedor.texture);
		SDL_DestroyTexture(vendedor.dialogo);
		for(i = 0; i < 4; i++) SDL_DestroyTexture(listaDec[i]);	
	}
}

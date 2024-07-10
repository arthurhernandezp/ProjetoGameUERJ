
//int numBytes = read(*serialPort, buffer, sizeof(buffer) - 1);
	   // if (numBytes > 0) {
	        for (int i = 0; i < numBytes; ++i) {
	            if (buffer[i] == '\n') {
	                tempBuffer[tempIndex] = '\0';
	                sscanf(tempBuffer, "%d,%d,%d,%d,%d,%d", &xDirection, &yDirection, &buttonState,&buttonL,&buttonM,&buttonR);
	                printf("X: %d, Y: %d, Button: %d\n", xDirection, yDirection, buttonState);
	                printf("Button Left: %d, Button Middle: %d, Button Right: %d\n", buttonL, buttonM, buttonR);

					//O personagem ande em qualquer lugar diferente da escada
					if(personagem->lugar == onBoat && *screen == jogo || personagem->state == fishing || personagem->state == pulling){
			 				mouse.rect.x += (xDirection * 6);
			 				mouse.rect.y += (yDirection * 6);
	 						mouse.state = 1;
		 			}
					
					if(buttonR == 1){
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
					}
					else if(buttonL == 1){
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
					}else if(buttonL == 0 && lastButtonLState == 1){//Botao Esquerdo apertado
						if(personagem->lugar == onGround){
			 				 personagem->state = idle;
			 			}
					}else if(buttonR == 0 && lastButtonRState == 1){//Botao Direito apertado
						if(personagem->lugar == onGround){
			 				 personagem->state = idle;
			 			}
					}else if(buttonM == 0 && lastButtonMState == 1){//Botao do meio apertado
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
					  			#ifdef DEBUG
			  						printf("\nSaiu do Barco: %d\n",personagem->buff.contador);
			  					#endif
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
								inventario->state = fechado;
								personagem->rect.y = 300;
								personagem->rect.x = 744;
								personagem->corte.y = personagem->corte.x = 0;
								break;
								#ifdef DEBUG
	                       			 printf("Estado da Screen mudou para 'interiorcasa' quando apertou 'e' na porta\n");  // Debugging log
			                    #endif
							}
					}else if(buttonState == 1){//Botao Joystick
			 			if(mouse.state == 1 && personagem->state != fishing && personagem->state != pulling && personagem->lugar != onGround){
							personagem->state = fishing;
							personagem->rect.y -= 5;
						}
					 	cur_state = clicking;
			            if(personagem->state == pulling) {
			            	minigame->iscaSpeed = rand()%5+10;
							Mix_PlayMusic(backgroundSound, 1);
						}
					}else if(buttonState == 0 && lastButtonState == 1){//Botao do joystick apertado
					   if(cur_state == clicking) cur_state = clicked;
					   if(personagem->state == pulling) minigame->iscaSpeed = rand()%5+12;
					   if(personagem->lugar == onGround){
						   if(inventario->state == fechado){
				 					inventario->state = aberto;
						  			#ifdef DEBUG
				  						printf("\nEstado do inventario: %s\n","Aberto");
				  					#endif
				  				}
								else if(inventario->state == aberto){
									inventario->state = fechado;
						  			#ifdef DEBUG
				  						printf("\nEstado do inventario: %s\n","Fechado");
				  					#endif
				  				}
				  		}		
					}
					//Animações do jogo
					animacaoAux++;
					if(animacaoAux == 500) animacaoAux = 5;
					if(animacaoAux % 5 == 0){
						if(personagem->state != pulling){
			  				contFundo += 1;
				 			if (contFundo == 15){
								(ceu->fundoAux)++;
								contFundo = 0;
							}
							aguaRect.y = aguaRect.y + 1 * (var);
							var *= -1;
							//espera = 500;
					  		if(personagem->buff.ativo && personagem->buff.contador >= 1){
					  			personagem->buff.contador -= 1;
					  			if(personagem->buff.contador == 0) {
					  				personagem->buff.ativo = false;
					  				personagem->buff.velocidade = 0;
					  			}
					  			#ifdef DEBUG
					  				printf("\nContador do buff: %d\n",personagem->buff.contador);
					  			#endif
				  			}
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
							
					}
				}
				if(personagem->state == pulling){
						minigame->state = emjogo;

						if(pescaAux == 5){
							if(personagem->corte.x < 96) personagem->corte.x += 48;
							else personagem->corte.x = 0;
							pescaAux = 0;
						}
						if(cur_state == clicking){
							minigame->rIsca.x += minigame->iscaSpeed;
							if(minigame->rIsca.x < minigame->rPeixe.x) minigame->rPeixe.x += minigame->peixeSpeed + personagem->buff.velocidade;
							else minigame->rPeixe.x += 2 + personagem->buff.velocidade;
						}
						else minigame->rIsca.x -= minigame->iscaSpeed;
						//espera = 100;
						pescaAux++;
				}
					
	                lastButtonState = buttonState; // Atualiza o último estado do botão
					lastButtonLState = buttonL;
					lastButtonMState = buttonM;
					lastButtonRState = buttonR;
	                tempIndex = 0; // Reinicia o índice do buffer temporário
	            } else {
	                tempBuffer[tempIndex++] = buffer[i];
	            }
	        }

	    //}


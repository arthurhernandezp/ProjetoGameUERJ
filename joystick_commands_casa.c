#ifdef DEBUG
 	printf("\nEntrando no case casa");
 #endif
 for (int i = 0; i < numBytes; ++i) {
            if (buffer[i] == '\n') {
                tempBuffer[tempIndex] = '\0';
                sscanf(tempBuffer, "%d,%d,%d,%d,%d,%d", &xDirection, &yDirection, &buttonState,&buttonL,&buttonM,&buttonR);
    	  	 	#ifdef DEBUG
		            printf("X: %d, Y: %d, Button: %d\n", xDirection, yDirection, buttonState);
		            printf("Button Left: %d, Button Middle: %d, Button Right: %d\n", buttonL, buttonM, buttonR);
                 #endif
                if(buttonR == 1){//Anda para a direita
					if(personagem->rect.x < 779){
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
				}else if(buttonL == 1){//Anda para a esquerda
					if(personagem->rect.x > 170){
							if(personagem->corte.x < 240) personagem->corte.x +=48;
							else personagem->corte.x = 0;
							if(personagem->corte.y != 48) personagem->corte.y = 48;
							
							personagem->rect.x -= 7;
							personagem->state = walking;
					}
				}else if(buttonState == 0 && lastButtonState == 1 && personagem->state != dormindo){
						personagem->state = dormindo;
						personagem->corte.x = 0;
						personagem->corte.y = 0;
						#ifdef DEBUG
	                        printf("Estado do personagem mudou para 'dormindo' usando SDLK_d\n");  // Debugging log
						#endif
				}else if(buttonM == 0 && lastButtonMState && personagem->rect.x >= 709 && animacaoAux > 1){
  					 *screen = jogo;
  					 personagem->rect.y= 415;
  					 personagem->rect.x=368;
  					 break;
  				}
				
				if((buttonL == 0 && lastButtonLState == 1) || (buttonR == 0 && lastButtonRState == 1) || (buttonM == 0 && lastButtonMState == 1)) personagem->state = idle;
				
				
				//Inicio Animação
				animacaoAux++;
				if(animacaoAux == 500) animacaoAux = 5;
				if(animacaoAux % 5 == 0){
					contFundo += 1;

			  		if(personagem->buff.ativo && personagem->buff.contador >= 1){
			  			personagem->buff.contador -= 1;
			  			if(personagem->buff.contador == 0) {
			  				personagem->buff.ativo = false;
			  				personagem->buff.velocidade = 0;
			  			}
				  		#ifdef DEBUG
				  				printf("\nContador do buff: %d\n",personagem->buff.contador);
				  				printf("\nEstado do buff: %s\n",(personagem->buff.ativo == 1) ? "True" : "False");
			  			#endif
			  		}
		 			if (contFundo == 15){
						(ceu->fundoAux)++;
						contFundo = 0;
					}
					if(personagem->state == idle){
						if (personagem->corte.x < 240) personagem->corte.x +=48;
						else personagem->corte.x = 0;
					}
				}
				if(personagem->state == dormindo && animacaoAux % 5 == 0){
						if (personagem->corte.x < 240) personagem->corte.x +=48;
						else{
							personagem->buff.ativo = true;
							personagem->buff.velocidade = VELOCIDADE_CONTADOR;
							personagem->buff.contador = CONTADOR_DEFAULT;
							personagem->state = idle;
						}
					}
                lastButtonState = buttonState; // Atualiza o último estado do botão
				lastButtonLState = buttonL;
				lastButtonMState = buttonM;
				lastButtonRState = buttonR;
                tempIndex = 0; // Reinicia o índice do buffer temporário
			}else {
                tempBuffer[tempIndex++] = buffer[i];
            }	
}

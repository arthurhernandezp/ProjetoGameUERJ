void constroi(SDL_Renderer *ren,dadosInventario* inv,uint16_t x,uint16_t y){
	inv->n = 0;
	uint16_t aux = x;
	inv->rect = (SDL_Rect) {645,-50,350,450};
	inv->state = fechado;
	inv->i = 0;
	inv->j = 0;
    inv->texture = IMG_LoadTexture(ren, "imgs/balde.png");
	for(uint8_t i = 0; i<3;i++){
		for(uint8_t j = 0;j<4;j++){
			inv->matrizItens[i][j].img = NULL;
		 	inv->matrizItens[i][j].state = false;
		 	SDL_Rect recAux = {x,y,64,64};
		 	inv->matrizItens[i][j].r = recAux;
		 	x+=65;
		}
		x= aux;
    	y+=70;
    }
}

void chamaInventario(SDL_Renderer* ren, dadosInventario inv){
	SDL_RenderCopy(ren, inv.texture, NULL, &inv.rect);
	for(uint8_t i = 0; i<3;i++){
		for(uint8_t j = 0;j<4;j++){
			SDL_RenderCopy(ren, inv.matrizItens[i][j].img, NULL, &inv.matrizItens[i][j].r);
		}
	}

}

int buscaElemento(dadosInventario inv,uint8_t i, uint8_t j){
	return inv.matrizItens[i][j].state;
}

int listaVazia(dadosInventario inv){
	return inv.n == 0;
}

int listaCheia(dadosInventario inv){
	return inv.n == 12;
}

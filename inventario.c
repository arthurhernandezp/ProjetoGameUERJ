void constroi(SDL_Renderer *ren,dadosInventario* inv,int x,int y){
	inv->n = 0;
	int aux = x;
	inv->rect = (SDL_Rect) {850,60,130,390};
	inv->state = fechado;
	inv-> i = 0;
	inv -> j = 0;
    inv->texture = IMG_LoadTexture(ren, "imgs/inv.png");
	for(int i = 0; i<6;i++){
		for(int j = 0;j<2;j++){
			inv->matrizItens[i][j].img = NULL;
		 	inv->matrizItens[i][j].state = false;
		 	SDL_Rect recAux = {x,y,64,64};
		 	inv->matrizItens[i][j].r = recAux;
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

int buscaElemento(dadosInventario inv,int i, int j){
	return inv.matrizItens[i][j].state;
}

int listaVazia(dadosInventario inv){
	return inv.n == 0;
}

int listaCheia(dadosInventario inv){
	return inv.n == 12;
}


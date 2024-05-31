# Projeto-SDL_Game-UERJ Projeto feito para a materia Programação de Jogos / Professor Francisco Figueiredo G. Sant'anna <ul>
  <li> Qual o nome do jogo?</li>
  <ul>
    <li> .Peixe IO</li>
  </ul>
  <li> Descreva o jogo em linhas gerais.</li>
  <ul>
    <li> A ideia do jogo é ambientar uma cabana de pesca em 2d com mini game para conseguir pescar o peixe, com um sistema de inventário para armazenar o peixe e vender para pontuar.</li>
  </ul>
  <li> Poste links ou vídeos relacionados</li>
  <ul>
    <li>https://www.youtube.com/watch?v=sKlcCplUODw&t=33s</li>
    <li>https://free-game-assets.itch.io/free-fishing-pixel-art-pack</li>
  </ul>
  <li> O que você pretende e não pretende implementar.</li>
  <ul>
    <li>Pretendo: Animação de pesca, caminhar. Mini game de pesca. Inventario e/ou um lugar para vender os peixes e pontuar.
  </ul>
  <ul> Qual o link para o repositório com o código fonte? - https://github.com/arthurhernandezp/ProjetoGameUERJ </ul>
</ul>

<h1>Bibliotecas Usadas e como Instalar no Ubuntu</h1>
```batch
#install sdl2
sudo apt install libsdl2-dev libsdl2-2.0-0 -y;

#install sdl image  - Para usar imagens
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y;

#install sdl mixer  - Usos de sons no menu
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;
use
#install sdl true type fonts - Fontes
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;
use 
<h1>roda () { gcc -o c.exe ProjetoFinal.c -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image && ./c.exe && rm c.exe; } </h1>
use
make

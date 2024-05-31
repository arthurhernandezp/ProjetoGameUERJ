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

<h1>Getting Started</h1>
```bash
git clone https://github.com/arthurhernandezp/ProjetoGameUERJ
```
<h2>Bibliotecas Usadas e como Instalar no Ubuntu</h1>
```bash
#install sdl2
sudo apt install libsdl2-dev libsdl2-2.0-0 -y;
#install sdl2_gfx 
sudo apt install libsdl2-gfx-dev
#install sdl image  - Uso de imagens
sudo apt install libsdl2-image-dev libsdl2-image-2.0-0 -y;
#install sdl mixer  - Uso de efeitos sonoros
sudo apt install libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;
#install sdl true type fonts - if you want to use text
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;
```

<h2>Execução dentro do diretorio do Game</h1>
```bash
<h2>roda () { gcc -o c.exe ProjetoFinal.c -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image && ./c.exe && rm c.exe; } </h1>
```

```bash
make
./c.exe
```

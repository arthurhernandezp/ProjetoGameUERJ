# Projeto-SDL_Game-UERJ Projeto feito para a materia Programação de Jogos / Professor Francisco Figueiredo G. Sant'anna 
# Versão 2.0 desenvolvida para a disciplina Estruturas de Linguagens /  Professor Paulo Mann
  <li> Qual o nome do jogo?</li>
  <ul>
    <li> .Peixe IO</li>
  </ul>
  <li> Descreva o jogo em linhas gerais.</li>
  <ul>
    <li> A ideia do jogo é ambientar uma cabana de pesca em 2d com mini game para conseguir pescar o peixe, com um sistema de inventário para armazenar o peixe.</li>
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

```
git clone https://github.com/arthurhernandezp/ProjetoGameUERJ
```

<h2>Bibliotecas Usadas e como Instalar no Ubuntu</h2>

```
sudo apt install libsdl2-dev -y
```

```
sudo apt install libsdl2-gfx-dev -y
```
```
sudo apt install libsdl2-dev -y;
```
```
sudo apt install libsdl2-image-dev -y
```

```
sudo apt install libsdl2-mixer-dev -y
```

```
sudo apt install libsdl2-ttf-dev -y
```

# Execução dentro do diretorio do Game</h1>

```
roda () { gcc -o c.exe ProjetoFinal.c -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image && ./c.exe && rm c.exe; }
```
## OU
```
make
./c.exe
```

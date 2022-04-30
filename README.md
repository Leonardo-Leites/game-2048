# game-2048
Jogo 2048, desenvolvido utilizando a linguagem C. Biblioteca principal ncurses (linux).

Este jogo consiste em um tabuleiro 4×4. O objetivo do jogo é juntar pares de peças de igual valor até ser obtida a peçaa com valor
2048.
O jogo inicia com duas peças com valor 2, que são colocadas em posições aleatórias do tabuleiro. A cada jogada, todas as peças se movem na direção que o jogador informa (pelas teclas ←, →, ↓ e ↑) até o final da linha e uma nova peça no valor de 2 ou 4 é inserida. Caso duas peças com o mesmo valor se encontrem, os valores se somam e ela vira uma peça apenas com o valor novo da soma. O jogo acaba se não puderem ser somadas novas peças ou chegar no valor da peça 2048. 

INFORMAÇÕES IMPORTANTES - RUN
cc -c game.c
cc -c menu.c
cc game.o menu.o -lncurses -o project
./project

TELA DE MENU

![Captura de tela de 2022-04-27 13-49-25](https://user-images.githubusercontent.com/76853394/165577738-133822ae-1c72-4549-b19c-cfa985917a77.png)


TELA DE JOGO

![Captura de tela de 2022-04-27 13-48-33](https://user-images.githubusercontent.com/76853394/165577724-1b9ba79b-f1f2-4075-97e3-ed2085033391.png)

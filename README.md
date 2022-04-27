# game-2048
Jogo 2048, desenvolvido utilizando a linguagem C. Biblioteca principal ncurses (linux).

Este jogo consiste em um tabuleiro 4×4. O objetivo do jogo é juntar pares de peças de igual valor até ser obtida a peçaa com valor
2048.
O jogo inicia com duas peças com valor 2, que são colocadas em posições aleatórias do tabuleiro. A cada jogada, todas as peças se movem na direção que o jogador informa (pelas teclas ←, →, ↓ e ↑) até o final da linha e uma nova peça no valor de 2 ou 4 é inserida. Caso duas peças com o mesmo valor se encontrem, os valores se somam e ela vira uma peça apenas com o valor novo da soma. O jogo acaba se não puderem ser somadas novas peças ou chegar no valor da peça 2048. 

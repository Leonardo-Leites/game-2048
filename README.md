# game-2048
### Descrição
##
Jogo 2048, desenvolvido utilizando a linguagem C. Biblioteca principal  `ncurses` (linux).

Este jogo consiste em um tabuleiro 4×4. O objetivo do jogo é juntar pares de peças de igual valor até ser obtida a peçaa com valor
2048.
O jogo inicia com duas peças com valor 2, que são colocadas em posições aleatórias do tabuleiro. A cada jogada, todas as peças se movem na direção que o jogador informa (pelas teclas ←, →, ↓ e ↑) até o final da linha e uma nova peça no valor de 2 ou 4 é inserida. Caso duas peças com o mesmo valor se encontrem, os valores se somam e ela vira uma peça apenas com o valor novo da soma. O jogo acaba se não puderem ser somadas novas peças ou chegar no valor da peça 2048. 

##
### Instalando biblioteca 
##
 `Abra o terminal`
 
 `Execute`
 ```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
# or
sudo yum install ncurses-devel
```
##
### Sintaxe Import
##
 ```bash
  #include <ncurses.h>
```

## 
#### Mais informações sobre sintaxe e documentação 
<a href="https://terminalroot.com.br/ncurses" target="_blank"><img height="30" width="90" src="https://img.shields.io/badge/-Terminal Root-blue" target="_blank"></a>
##

# Guia de compilação e inicialização 

 ```bash
  < `Criar arquivo .o` >
cc -c game.c
cc -c menu.c
  < `Criar Projeto` >
cc game.o menu.o -lncurses -o project
 < `Executar Projeto` >
./project
```

## 
### Telas de jogo

`Inicio
`

![Captura de tela de![Captura de tela de 2022-05-03 22-02-03](https://user-images.githubusercontent.com/76853394/166861009-a1103792-4af5-4b57-afd2-c3188456e6e4.png)
 2022-04-27 13-49-25](https://user-images.githubusercontent.com/76853394/165577738-133822ae-1c72-4549-b19c-cfa985917a77.png)
 
 `Carregar Jogo salvo
 `
 
![Captura de tela de 2022-05-03 22-00-33](https://user-images.githubusercontent.com/76853394/166860970-2cab60ef-0ad7-4b9f-9569-dc57cb4f6ea2.png)

`Tela de jogo
`

![Captura de tela de 2022-05-03 22-02-03](https://user-images.githubusercontent.com/76853394/166861282-7a37f7f5-70bb-44ab-9931-a1dd64d9885f.png)

`Salvar um Jogo
`
![Captura de tela de 2022-05-05 00-49-04](https://user-images.githubusercontent.com/76853394/166861296-a3017c86-e72d-4d41-8fce-134fa9c67993.png)

`Parabéns, você ganhou
`
![Captura de tela de 2022-05-05 00-49-33](https://user-images.githubusercontent.com/76853394/166861308-0d20b191-25ab-415f-b2b5-1acae3da6884.png)

## 






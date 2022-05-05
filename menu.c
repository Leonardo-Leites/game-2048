#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

#include "defines.h"

WINDOW *menu_wind, *titulo; // criação das janelas utilizadas na imprementação da interface

int menu() {

	char list[NITEMS][20] = {"Novo jogo","Carregar Jogo","Sair"}; // lista de itens para o menu
	int choice, i = 0, inf = 0, xMax, yMax;

	initscr(); // iniciando o ncurses
    getmaxyx(stdscr, yMax, xMax); // pegando os valores maximos da janela

	menu_wind = newwin(8, 20, yMax/2, ((xMax/2)-10)); // criando uma nova janela "menu_wind"
    box(menu_wind, ACS_VLINE, ACS_HLINE ); // imprementação de bordas padrão

    titulo = newwin(3, 20, ((yMax/2)-3), ((xMax/2)-10)); // nova janela "titulo"
    box(titulo, 0, 0 ); // sem bordas
	wattrset(titulo, COLOR_PAIR(6)); // iniciando o set de cores 6

	mvwprintw(titulo, 1, 1, "       2048       "); // printando o título na posição 1,1 da janela "titulo"
	wattroff(titulo, COLOR_PAIR(6));  // finalizando o set de cores 6
    wrefresh(titulo);  // refresh na janela
    
 
	noecho();  // desabibilitando os caracteres digitados
	keypad(menu_wind, TRUE );  // habilitando o teclado para uso na janela "menu_wind"
	curs_set(0);  // deixando o cursor invisivel

	while(1){ 

    for(int i = 0; i < NITEMS; i++ ) {
		if(i == inf) {
			wattron(menu_wind, A_REVERSE ); // setando estilização de mercação do menu
        }
        mvwprintw(menu_wind, i+1, 1, "%s",list[i]);
        wattroff(menu_wind, A_REVERSE);
	}

    wrefresh(menu_wind);

    choice = wgetch(menu_wind); // pegando a entrada do teclado

       	switch(choice){
            case KEY_DOWN:
            inf++;
            if(inf == 3){
                inf = 2;
            }
            break;

            case KEY_UP:
            inf--;
             if(inf == -1){
                inf = 0;
            }
            break;
            
            case 10: //enter
                if(inf == 0){
                    delwin(menu_wind);
                    delwin(titulo);
					endwin();
                    return 0;
                }else if(inf == 1){
                    delwin(menu_wind);
                    delwin(titulo);
					endwin();
                    return 1;
                }else
                    delwin(menu_wind);
                    delwin(titulo);
					endwin();
					return -1;
            break;
            
            default:
            break;
        }
    }
}
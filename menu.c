#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

#include "defines.h"

WINDOW *menu_wind, *titulo;

int menu() {

	char list[NITEMS][20] = {"Novo jogo","Carregar Jogo","Sair"};
	int choice, i = 0, inf = 0, xMax, yMax;

	initscr(); 
    getmaxyx(stdscr, yMax, xMax);

	menu_wind = newwin(8, 20, yMax/2, ((xMax/2)-10)); 
    box(menu_wind, ACS_VLINE, ACS_HLINE ); 

    titulo = newwin(3, 20, ((yMax/2)-3), ((xMax/2)-10));
    box(titulo, 0, 0 ); 
	wattrset(titulo, COLOR_PAIR(6));

	mvwprintw(titulo, 1, 1, "       2048       ");
	wattroff(titulo, COLOR_PAIR(6));
    wrefresh(titulo);
    
 
	noecho(); 
	keypad(menu_wind, TRUE ); 
	curs_set( 0 ); 

	while(1){ 

    for(int i = 0; i < NITEMS; i++ ) {
		if(i == inf) {
			wattron(menu_wind, A_REVERSE ); 
        }
        mvwprintw(menu_wind, i+1, 1, "%s",list[i]);
        wattroff(menu_wind, A_REVERSE);
	}

    wrefresh(menu_wind);

    choice = wgetch(menu_wind);

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
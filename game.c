#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "defines.h"

WINDOW *gamew, *score, *movimentow, *comandosw, *rankingw, *tablew, *blocow, *savew, *load;
void imprime_estrutura(char estrutura[][TAMANHO]){
	for(int i =0; i<TAMANHO; i++){
		for (int k=0; k<TAMANHO; k++){
			printf("%d", *(estrutura[0]+i *TAMANHO +k));
		}
		printf("\n");
	}
}
int save(char estrutura[][TAMANHO], int score){

	keypad(savew, TRUE);
	curs_set(1);

	int xMax, yMax, letra, cont = 0;
    getmaxyx(stdscr, yMax, xMax);
	char name[NAME_TAM], pontuacao[sizeof(int)], estr[sizeof(int)*2];

	FILE *arq = fopen(FILE_NAME, "a");
	if(arq == NULL){
        delwin(gamew);
	 	endwin();
		return 0;
    }
	fseek(arq, 0,SEEK_END);


    savew = newwin(5, 50, (yMax/2), (xMax/4));
	wattrset(savew, COLOR_PAIR(6));
	box(savew, ACS_VLINE, ACS_HLINE);
	wrefresh(savew);

	mvwprintw(savew, 1, 1,"%50s"," ");
	mvwprintw(savew, 1, 22,"Save-Game");
	mvwprintw(savew, 2, 1,"%49s"," ");
	mvwprintw(savew, 3, 1,"%49s"," ");
	wattrset(savew, COLOR_PAIR(2));
	mvwprintw(savew, 3, 1,"Por favor informe seu nick-name: ");

	do {
		letra = wgetch(savew);
		name[cont] = letra;
		
		if(name[cont] >= 'a' && name[cont] <= 'z' || letra == 127){
			if(cont != 0){
				if(letra == 127){
					name[cont-1] = ' ';
					cont --;
				}else{
					cont ++;
				}
			}else{
				cont ++;
			}
		}else if(letra == 10){
			name[cont] = '\0';
		}
		mvwprintw(savew, 3, 1 + strlen("Por favor informe seu nick-name: "),"%s", name);	
	}while(letra != 10 && cont < 10);
	
	wattroff(savew, COLOR_PAIR(2));
	wattroff(savew, COLOR_PAIR(6));

	sprintf(pontuacao, "%d", score);
	fprintf(arq,"\n#%s#",pontuacao);
	fprintf(arq,"%s#",name);

	for(int i =0; i<4; i++){
		for (int j =0; j<4; j++){
			sprintf(estr, "%d", *(estrutura [0]+i *TAMANHO +j));
			fprintf(arq, "*%s", estr);
		}
	}
	fprintf(arq, "%s", "*");
	fclose(arq);

	keypad(savew, FALSE);
	curs_set(0);

	wattrset(savew, COLOR_PAIR(2));
	mvwprintw(savew, 3, 1,"%48s","");
	mvwprintw(savew, 3, 20,"%s","salvo com sucesso");
	wrefresh(savew);
	wattroff(savew, COLOR_PAIR(2));

	usleep(SLEEP*200);
	wclear(savew);
	wrefresh(savew);
	
}
void init_colors() {
	start_color();
	init_color(COLOR_BLACK, 60,60,60);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	init_pair(4, COLOR_BLACK, COLOR_BLUE);
	init_pair(5, COLOR_BLACK, COLOR_RED);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_BLACK, COLOR_YELLOW);
	init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(9, COLOR_BLACK, COLOR_BLACK);

}
void scorew(int pontos){

	int xMax, yMax;
	char point[sizeof(int)];
    getmaxyx(stdscr, yMax, xMax);

	sprintf(point, "%d", pontos);   

	score = newwin(4, 10, (yMax-30), (xMax-60));
	wattrset(score, COLOR_PAIR(6));
	mvwprintw(score, 1, 1, "  score  ");
	wattroff(score, COLOR_PAIR(6));
	wattrset(score, COLOR_PAIR(2));
	mvwprintw(score, 2, 1, "         ");
	mvwprintw(score, 2, 5, "%s",point);
	wattroff(score, COLOR_PAIR(2));
	wrefresh(score);
}
void movimentosw(int mov){

	int xMax, yMax;
	char point[sizeof(int)];
    getmaxyx(stdscr, yMax, xMax);

	sprintf(point, "%d", mov);   

	movimentow = newwin(4, 15, (yMax-30), (xMax-50));
	wattrset(movimentow, COLOR_PAIR(6));
	mvwprintw(movimentow, 1, 1, "  movimentos  ");
	wattroff(movimentow, COLOR_PAIR(6));
	wattrset(movimentow, COLOR_PAIR(2));
	mvwprintw(movimentow, 2, 1, "%14s"," ");
	mvwprintw(movimentow, 2, 7, "%s",point);
	wattroff(movimentow, COLOR_PAIR(2));
	wrefresh(movimentow);
}
void comands(){

	int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
 
	comandosw = newwin(7, 16, (yMax/2)+4, (xMax-60));
	mvwprintw(comandosw, 1, 1, "ESC - SAIR");
	mvwprintw(comandosw, 2, 1, "N - Novo Jogo");
	mvwprintw(comandosw, 3, 1, "S - Salvar Jogo");
	mvwprintw(comandosw, 4, 1, "Setas - Jogar");
	wrefresh(comandosw);
}
void qtdLinhas(int *qtdLinhas){

int caractere, existe_linhas = 0;
int quant_linhas = 0;

FILE *arq = fopen (FILE_NAME, "r");
   
while((caractere = fgetc(arq)) != EOF){
    existe_linhas = 1; 
     
    if(caractere == '\n'){ 
        quant_linhas++;             
    } 
}
if(existe_linhas){
    quant_linhas++;
}
*qtdLinhas = quant_linhas;
}
void rank(){

	FILE *arq = fopen(FILE_NAME, "r");
	if(arq == NULL){
        delwin(gamew);
	 	endwin();
    }

	int xMax, yMax, tamArq;
	qtdLinhas(&tamArq);

	char pontos[sizeof(int)*2];
	char name[NAME_TAM];
	char linha[52];

    getmaxyx(stdscr, yMax, xMax);

	rankingw = newwin(10, 27, (yMax-26), (xMax-60));
	wattrset(rankingw, COLOR_PAIR(6));
	mvwprintw(rankingw, 0, 1, "         ranking        ");
	wattroff(rankingw, COLOR_PAIR(6));
	wattrset(rankingw, COLOR_PAIR(2));

	for (int i =1; i <= tamArq && i <= 5; i++){
		//fscanf(arq, "%d", &pontuacao);
		//sprintf(pontos, "%d", pontuacao);
		//fscanf(arq, "%s", name);

		fgets(linha, 52, arq);
		//printf("%s", linha);
		char *p = strtok(linha, "#");
		int aux = 0;

		do{
			if(aux == 0){
				sprintf(pontos, "%s", p);
			}else if(aux == 1){
				sprintf(name, "%s", p);
			}else{
			}
			aux++;
		}while((p = strtok(NULL, "#")));

		mvwprintw(rankingw, i, 1, "%24s"," ");
        mvwprintw(rankingw, i, 1, "   %s   ",pontos);
		mvwprintw(rankingw, i, 9, "   %s",name);
    }
    fclose(arq);

	wattroff(rankingw, COLOR_PAIR(2));
	wrefresh(rankingw);

}
int colorponto(int ponto){

	if(ponto == 2)
		return 3;
	if(ponto == 4 || ponto == 256)
		return 4;
	if(ponto == 8 || ponto == 32)
		return 5;
	if(ponto == 128 || ponto == 64)
		return 6;
	if(ponto ==  512|| ponto == 2048)
		return 7;
	if(ponto == 1024 || ponto == 16)
		return 8;
}
int returnXY(int j, int i, int *x, int *y){

	if (i == 0){
		*y = 5;
	}else if (i == 1){
		*y = 12;
	}else if (i == 2){
		*y = 19;
	}else{
		*y = 26;
	}

	if (j == 0){
		*x = 16;
	}else if (j == 1){
		*x = 28;
	}else if (j == 2){
		*x = 40;
	}else{
		*x = 52;
	}
}
int returnIJ(int y, int x, int *i, int *j){

	if(y <=5 && y >= 0){
		*i = 0;
	}else if(y <=12 && y >= 6){
		*i = 1;
	}else if(y <= 19 && y >= 13){
		*i = 2;
	}else{
		*i = 3;
	}
		
	if(x <=16 && x >= 0){
		*j = 0;
	}else if(x <=28 && x >= 17){
		*j = 1;
	}else if(x <= 40 && x >= 29){
		*j = 2;
	}else{
		*j = 3;
	}
	return (*i,*j);
}
void desenha_bloco(char estrutura [][TAMANHO]){

	char point[sizeof(int)];
	int y, x,  width = 11, height = 6, num;

		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++){
				if(*(estrutura[0]+i *TAMANHO +j) != 0){
					
					returnXY(j,i, &x, &y);
					num = colorponto(*(estrutura[0]+i *TAMANHO +j));

					blocow = newwin(height, width, y,x);
					wattrset(blocow, COLOR_PAIR(num));
					sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)); 
					mvwprintw(blocow, 0, 0, "               ");
					mvwprintw(blocow, 1, 1, "               ");
					mvwprintw(blocow, 2, 1, "   %s          ",point);
					mvwprintw(blocow, 3, 1, "               ");
					mvwprintw(blocow, 4, 1, "               ");
					mvwprintw(blocow, 5, 1, "               ");
					wattroff(blocow, COLOR_PAIR(num));
					wrefresh(blocow);
				}
			}
		}

}
void desenha_tabela(WINDOW *tablew){

	for(int k = 0; k < 48; k+=12){
        for (int i = 0; i <= 28; i+=7){
            if(k < 36){
                for(int aux = 0; aux <7; aux++){
                    mvwprintw(tablew, i+aux, k, "|");
                }
                    mvwprintw (tablew, i, k, "+-----------+");
            }else{
				for(int aux = 0; aux <7; aux++){
					mvwprintw(tablew, i+aux, k, "|");
				}
					mvwprintw (tablew, i, k, "+-----------+");
			}
        }
    }
	wrefresh(tablew);
}
void anima_bloco(char estrutura [][TAMANHO], int i, int j, int oldi, int oldj, int org){
	
	int y, x,  width = 11, height = 6, num, oldy, oldx;
	char point[sizeof(int)];

	returnXY(j, i, &x, &y);
	returnXY(oldj, oldi, &oldx, &oldy);
	if(org == 1){
		while (oldy < y){

			blocow = newwin(height, width, oldy, x);
			wrefresh(blocow);
			desenha_tabela(tablew);

			blocow = newwin(height, width, ++oldy, x);
			wrefresh(blocow);

			usleep(SLEEP);
		}
	}else if(org == 2){
		while (oldy > y){

			blocow = newwin(height, width, oldy, x);
			wrefresh(blocow);
			desenha_tabela(tablew);

			blocow = newwin(height, width, --oldy, x);
			wrefresh(blocow);

			usleep(SLEEP);
		}
	}else if(org == 3){
		while (oldx > x){

			blocow = newwin(height, width, y, oldx);
			wrefresh(blocow);
			desenha_tabela(tablew);

			blocow = newwin(height, width, y, --oldx);
			wrefresh(blocow);

			usleep(SLEEP);
		}
	}
	else if(org == 4){
		while (oldx < x){

			blocow = newwin(height, width, y, oldx);
			wrefresh(blocow);
			desenha_tabela(tablew);

			blocow = newwin(height, width, y, ++oldx);
			wrefresh(blocow);

			usleep(SLEEP);
		}
	}
		desenha_tabela(tablew);
		desenha_bloco(estrutura);
}
void colide(char estrutura [][TAMANHO], int value, int *score){
	
	char point[sizeof(int)];
	int num, org, aux;

	switch (value){
	case 1:
	org = 1;
		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++){
				if(*(estrutura[0]+i *TAMANHO +j) != 0){
					switch (i){
					case 0:
						if(*(estrutura [0]+1 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+1 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+1 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+1 *TAMANHO +j);
								anima_bloco(estrutura, 1,j, 0, j,org); 
							}
						}else if(*(estrutura [0]+2 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+2 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+2 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+2 *TAMANHO +j);
								anima_bloco(estrutura, 2,j, 0, j,org);  
							}
						}else if(*(estrutura [0]+3 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+3 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+3 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+3 *TAMANHO +j);
								anima_bloco(estrutura, 3,j, 0, j,org); 
							}
						}else{
							*(estrutura [0]+3 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j);
							*(estrutura [0]+i *TAMANHO +j) = 0;
							anima_bloco(estrutura, 3,j, 0, j,org);
						}
						break;
					case 1:
						if(*(estrutura [0]+2 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+2 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+2 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+2 *TAMANHO +j);
								anima_bloco(estrutura, 2,j, 1, j,org); 
							}
						}else if(*(estrutura [0]+3 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+3 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+3 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+3 *TAMANHO +j);
								anima_bloco(estrutura, 3,j, 1, j,org); 
							}
						}else {
							*(estrutura [0]+3 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j);
							*(estrutura [0]+i *TAMANHO +j) = 0;
							anima_bloco(estrutura, 3,j, 1, j,org); 
						}
						break;
					case 2:
						if(*(estrutura [0]+3 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+3 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+3 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+3 *TAMANHO +j);
								anima_bloco(estrutura, 3,j, 2, j,org); 
							}
						}else{
							*(estrutura [0]+3 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j);
							*(estrutura [0]+i *TAMANHO +j) = 0;
							anima_bloco(estrutura, 3,j, 2, j,org); 
						}
						break;
					default:
						break;
					}
				}
			}
		}
		break;
	case 2:
	org = 2;
		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++){
				if(*(estrutura[0]+i *TAMANHO +j) != 0){
					switch (i){
					case 1:
						if(*(estrutura [0]+0 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+0 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+0 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+0 *TAMANHO +j);
								anima_bloco(estrutura, 0,j, 1, j,org); 
							}
						}
						break;
					case 2:
						if(*(estrutura [0]+1 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+1 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+1 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+1 *TAMANHO +j);
								anima_bloco(estrutura, 1,j, 2, j,org); 
							}
						}else if(*(estrutura [0]+0 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+0 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+0 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+0 *TAMANHO +j);
								anima_bloco(estrutura, 0,j, 2, j,org); 
							}
						}
						break;
					case 3:
						if(*(estrutura [0]+2 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+2 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+2 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+2 *TAMANHO +j);
								anima_bloco(estrutura, 2,j, 3, j,org); 
							}
						}else if(*(estrutura [0]+1 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+1 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+1 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+1 *TAMANHO +j);
								anima_bloco(estrutura, 1,j, 3, j,org);  
							}
						}else if(*(estrutura [0]+0 *TAMANHO +j) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+0 *TAMANHO +j)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+0 *TAMANHO +j) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+3 *TAMANHO +j);
								anima_bloco(estrutura, 0,j, 3, j,org); 
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
		break;
	case 3:
	org = 3;
		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++){
				if(*(estrutura[0]+i *TAMANHO +j) != 0){
					switch (j){
					case 1:
						if(*(estrutura [0]+i *TAMANHO +0) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +0)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +0) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +0);
								anima_bloco(estrutura, i,0, i, 1,org); 
							}
						}
						break;
					case 2:
						if(*(estrutura [0]+i *TAMANHO +1) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +1)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +1) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +1);
								anima_bloco(estrutura, i,1, i, 2,org); 
							}
						}else if(*(estrutura [0]+i *TAMANHO +0) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +0)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +0) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +0);
								anima_bloco(estrutura, i,0, i, 2,org); 
							}
						}
						break;
					case 3:
						if(*(estrutura [0]+i *TAMANHO +2) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +2)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +2) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +2);
								anima_bloco(estrutura, i,2, i, 3,org); 
							}
						}else if(*(estrutura [0]+i *TAMANHO +1) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +1)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +1) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +1);
								anima_bloco(estrutura, i,1, i, 3,org); 
							}
						}else if(*(estrutura [0]+i *TAMANHO +0) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +0)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +0) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +0);
								anima_bloco(estrutura, i,0, i, 3,org); 
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
		break;
	case 4:
	org = 4;
		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++){
				if(*(estrutura[0]+i *TAMANHO +j) != 0){
					switch (j){
					case 0:
						if(*(estrutura [0]+i *TAMANHO +1) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +1)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +1) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +1);
								anima_bloco(estrutura, i,1, i, 0,org); 
							}
						}else if(*(estrutura [0]+i *TAMANHO +2) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +2)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +2) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +2);
								anima_bloco(estrutura, i,2, i, 0,org); 
							}
						}else if(*(estrutura [0]+i *TAMANHO +3) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +3)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +3) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +3);
								anima_bloco(estrutura, i,3, i, 0,org); 
							}
						}
						break;
					case 1:
						if(*(estrutura [0]+i *TAMANHO +2) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +2)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +2) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +2);
								anima_bloco(estrutura, i,2, i, 1,org); 
							}
						}else if(*(estrutura [0]+i *TAMANHO +3) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +3)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +3) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +3);
								anima_bloco(estrutura, i,3, i, 1,org); 
							}
						}
						break;
					case 2:
						if(*(estrutura [0]+i *TAMANHO +3) != 0){
							if(*(estrutura [0]+i *TAMANHO +j) == *(estrutura [0]+i *TAMANHO +3)){
								sprintf(point, "%d", *(estrutura[0]+i *TAMANHO +j)*2);
								num = colorponto(*(estrutura[0]+i *TAMANHO +j)*2);
								*(estrutura [0]+i *TAMANHO +3) = *(estrutura[0]+i *TAMANHO +j)*2;
								*(estrutura [0]+i *TAMANHO +j) = 0;
								*score += *(estrutura [0]+i *TAMANHO +3);
								anima_bloco(estrutura, i,3, i, 2,org); 
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
		break;
	
	default:
		break;
	}
	
}
void bloco(char estrutura[][TAMANHO]){


	int ponto, sair = 0, choice;
	int y, x, i, j;

	/*  
	
	y - 5 x - 16	y - 5 x - 28	y - 5 x - 40	y - 5 x - 52
	y - 12 x - 16	y - 12 x - 28	y - 12 x - 40	y - 12 x - 52
	y - 19 x - 16	y - 19 x - 28	y - 19 x - 40	y - 19 x - 52
	y - 26 x - 16	y - 26 x - 28	y - 26 x - 40	y - 26 x - 52

	*/

	srand(time(NULL));
	ponto = rand() % 10;
	if(ponto >= 0 && ponto < 2 ){
		ponto = 4;
	}else
		ponto = 2;

	y = rand() % 26;
	x = rand() % 52;

	while(sair == 0){

		returnIJ(y,x, &i, &j);

		if(*(estrutura[0]+i *TAMANHO +j) != 0){
			y = rand() % 26;
			x = rand() % 52;
		}else{
			*(estrutura[0]+i *TAMANHO +j) = ponto;
			sair = 1;
		}

	}

 desenha_bloco(estrutura);
	
}
int tabela(char estrutura[][TAMANHO], int score){
	
	int choice, movimentos = 0;

	tablew = newwin(29, 49, 4, 15);
	box(tablew, '|', '-'); 

	keypad(tablew, TRUE );

	desenha_tabela(tablew);
	wrefresh(tablew);
	bloco(estrutura);
	bloco(estrutura);

	while(1){
	//imprime_estrutura(estrutura);
	choice = wgetch(tablew);
	switch (choice)
	{
	case KEY_DOWN:
		colide(estrutura, 1, &score);
		usleep(SLEEP*2);
		bloco(estrutura);
		scorew(score);
		movimentos++;
		movimentosw(movimentos);
		break;
	case KEY_UP:
		colide(estrutura, 2, &score);
		usleep(SLEEP*2);
		bloco(estrutura);
		scorew(score);
		movimentos++;
		movimentosw(movimentos);
		break;
	case KEY_LEFT:
		colide(estrutura, 3, &score);
		usleep(SLEEP*2);
		bloco(estrutura);
		scorew(score);
		movimentos++;
		movimentosw(movimentos);
		break;
	case KEY_RIGHT:
		colide(estrutura, 4, &score);
		usleep(SLEEP*2);
		bloco(estrutura);
		scorew(score);
		movimentos++;
		movimentosw(movimentos);
		break;
	case 27:
		printf("esc");
		delwin(gamew);
		endwin();
		return 0;
		break;
	case 110:
		printf("n");
		break;
	case 115:
		save(estrutura, score);
		wclear(gamew);
		wrefresh(gamew);
		return 0;
		break;
	default:
		break;
	}
	}
}
void play(char estrutura[][TAMANHO], int score){

    int xMax, yMax, movimentos = 0;
    getmaxyx(stdscr, yMax, xMax);

		scorew(score);
		movimentosw(movimentos);
		rank();
		comands();
		tabela(estrutura, score);
}
int load_game(){

	keypad(load, TRUE);
	curs_set(1);

	FILE *arq = fopen(FILE_NAME, "r");
	if(arq == NULL){
        delwin(gamew);
	 	endwin();
		return 0;
    }

    int xMax, yMax, letra, cont = 0, tamArq;
	char name[NAME_TAM], estrutura[TAMANHO][TAMANHO], pontuacao[sizeof(int)];
	char pesqname[NAME_TAM];
    getmaxyx(stdscr, yMax, xMax); 
	char linha[52];
	qtdLinhas(&tamArq);

    load = newwin(5, 50, (yMax/2), (xMax/4));
	wattrset(load, COLOR_PAIR(6));
	box(load, ACS_VLINE, ACS_HLINE);
	wrefresh(load);

	mvwprintw(load, 1, 1,"%50s"," ");
	mvwprintw(load, 1, 22,"Load-Game");
	mvwprintw(load, 2, 1,"%49s"," ");
	mvwprintw(load, 3, 1,"%49s"," ");
	wattrset(load, COLOR_PAIR(2));
	mvwprintw(load, 3, 1,"Por favor informe seu nick-name: ");
	
	do {
		letra = wgetch(load);
		name[cont] = letra;
		
		if(name[cont] >= 'a' && name[cont] <= 'z' || letra == 127){
			if(cont != 0){
				if(letra == 127){
					name[cont-1] = ' ';
					cont --;
				}else{
					cont ++;
				}
			}else{
				cont ++;
			}
		}else if(letra == 10){
			name[cont] = '\0';
		}
		mvwprintw(savew, 3, 1 + strlen("Por favor informe seu nick-name: "),"%s", name);	
	}while(letra != 10 && cont < 10);

	wattroff(load, COLOR_PAIR(2));
	wattroff(load, COLOR_PAIR(6));

	for (int i =0; i < tamArq; i++){

	fgets(linha, 52, arq);

	char *infos = strtok(linha, "#");
	char *estr = strtok(linha, "*");
	int aux = 0, i = 0, j = 0;

	do{
		if(aux == 0){
			sprintf(pontuacao, "%s", infos);
		}else if(aux == 1){
			sprintf(pesqname, "%s", infos);
		}else{
			do{	
				//sprintf(estrutura[i][j], "%s", estr);
				i++;
				j++;
			}while((estr = strtok(NULL, "*")) || i == 4);
		}
		aux++;
	}while((infos = strtok(NULL, "#")));
		if(pesqname == name){
			break;
		}
	}
	fclose(arq);
	int score;
	score = atoi(pontuacao);
	keypad(load, false);
	curs_set(0);
	wclear(load);
	wrefresh(load);
	play(estrutura, score);
}
int main() {

	char estrutura[TAMANHO][TAMANHO] = {{0,0,0,0},
						{0,0,0,0},
						{0,0,0,0},
						{0,0,0,0}};
	int  pontos = 0;

	initscr();
	noecho(); // disable echoing of characters on the screen
	keypad(gamew, TRUE ); // enable keyboard input for the window.
	curs_set(0);

    init_colors();
    int play_game = menu();
	//printf("%d", play_game);

    refresh();

	while(1) {

        if(play_game == -1) {
			endwin();
			return 0;
        }
		if(play_game == 1){
			load_game();
		}
		play(estrutura, pontos);

		delwin(gamew);
		endwin();
		return 0;
	}
	delwin(gamew);
	endwin();
}
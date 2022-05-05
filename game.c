#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "defines.h"

WINDOW *gamew, *pontuacaow, *movimentow, *comandosw, *rankingw, *tablew, *blocow, *savew, *load, *win; // criação das janelas utilizadas na imprementação da interface
void imprime_estrutura(char estrutura[][TAMANHO]){ // função meramente auxiliar de visualização da estrutura do tabuleiro
	for(int i =0; i<TAMANHO; i++){
		for (int k=0; k<TAMANHO; k++){
			printf("%d", *(estrutura[0]+i *TAMANHO +k));
		}
		printf("\n");
	}
}
int save(char estrutura[][TAMANHO], int score){ //  salvar os dados do jogo, como a estrutura (posição das peças no tabuleiro) e o score

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


    savew = newwin(5, 50, (yMax/2), (xMax/3));
	wattrset(savew, COLOR_PAIR(6));
	box(savew, ACS_VLINE, ACS_HLINE);
	wrefresh(savew);

	mvwprintw(savew, 1, 1,"%50s"," ");
	mvwprintw(savew, 1, 22,"Save-Game");
	mvwprintw(savew, 2, 1,"%49s"," ");
	mvwprintw(savew, 3, 1, "%49s", " ");
	wattrset(savew, COLOR_PAIR(2));
	mvwprintw(savew, 3, 1,"Por favor informe seu nickname: ");
	wrefresh(savew);
	do {
		letra = wgetch(savew);
		name[cont] = letra;
		
		if(name[cont] >= 'a' && name[cont] <= 'z' || letra == 127 || letra == 27){
			if(letra == 27){
				return 0;
			}
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
		
		mvwprintw(savew, 3, 1 + strlen("Por favor informe seu nickname: "),"%s", name);	
	}while(letra != 10 && cont < 10);
	
	wattroff(savew, COLOR_PAIR(2));
	wattroff(savew, COLOR_PAIR(6));

	sprintf(pontuacao, "%d", score);
	fprintf(arq,"\n#%s#",pontuacao);
	fprintf(arq,"%s#",name);

	for(int i =0; i<4; i++){
		for (int j =0; j<4; j++){
			sprintf(estr, "%d", *(estrutura [0]+i *TAMANHO +j));
			fprintf(arq, "%s#", estr);
		}
	}
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
	delwin(gamew);
	
}
void init_colors() {  // iniciando alguns padrões de cores para usar 
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
void scorew(int pontos){ // printar os dados de score do jogo 

	int xMax, yMax;
	char point[sizeof(int)];
    getmaxyx(stdscr, yMax, xMax);

	sprintf(point, "%d", pontos);   

	pontuacaow = newwin(4, 10, (yMax-30), (xMax-60));
	wattrset(pontuacaow, COLOR_PAIR(6));
	mvwprintw(pontuacaow, 1, 1, "  score  ");
	wattroff(pontuacaow, COLOR_PAIR(6));
	wattrset(pontuacaow, COLOR_PAIR(2));
	mvwprintw(pontuacaow, 2, 1, "         ");
	mvwprintw(pontuacaow, 2, 5, "%s",point);
	wattroff(pontuacaow, COLOR_PAIR(2));
	wrefresh(pontuacaow);
}
void movimentos(int mov){ // printar os dados de movimentos do jogo

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
void comands(){ // printar os comandos possíveis no jogo

	int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
 
	comandosw = newwin(7, 16, (yMax/2)+4, (xMax-60));
	mvwprintw(comandosw, 1, 1, "ESC - SAIR");
	mvwprintw(comandosw, 2, 1, "N - Novo Jogo");
	mvwprintw(comandosw, 3, 1, "S - Salvar Jogo");
	mvwprintw(comandosw, 4, 1, "Setas - Jogar");
	wrefresh(comandosw);
}
void qtdLinhas(int *qtdLinhas){ // verifica a quantidade de linhas do arquivo save.txt

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
void rank(){ // printando o rank de jogadores na tela (ainda não ordenado)

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

	for (int i =1; i <= tamArq && i < 5; i++){

		fgets(linha, 52, arq);
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
int colorponto(int ponto){ // retorna a cor ao bloco dependendo do seu valor

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
int returnXY(int j, int i, int *x, int *y){ // retorna a posição y e x do bloco, pelo i e j passados

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
int returnIJ(int y, int x, int *i, int *j){ // retorna a posição i e j, pelo x e y passados

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
void desenha_bloco(char estrutura [][TAMANHO]){ // responsavel por desenhar os blocos nas posições da "estrutura"

	char point[sizeof(int)*2];
	int y, x,  width = 11, height = 6, num;

		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++){
				if(*(estrutura[0]+i *TAMANHO +j) != 0){
					
					returnXY(j,i, &x, &y);
					num = colorponto(*(estrutura[0]+i *TAMANHO +j));

					blocow = newwin(height, width, y,x);
					wattrset(blocow, COLOR_PAIR(num));
					sprintf(point, "%d ", *(estrutura[0]+i *TAMANHO +j)); 
					mvwprintw(blocow, 0, 0, "               ");
					mvwprintw(blocow, 1, 1, "               ");
					mvwprintw(blocow, 2, 1, "   %s         ",point);
					mvwprintw(blocow, 3, 1, "               ");
					mvwprintw(blocow, 4, 1, "               ");
					mvwprintw(blocow, 5, 1, "               ");
					wattroff(blocow, COLOR_PAIR(num));
					wrefresh(blocow);
				}
			}
		}

}
void desenha_tabela(WINDOW *tablew){ // responsavel por desenhar a tabela de jogo

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
void anima_bloco(char estrutura [][TAMANHO], int i, int j, int oldi, int oldj, int org){ // anima os blocos, dependendo das peças do tabuleiro e escolha de movimento do usuário
	
	int y, x,  width = 11, height = 6, num, oldy, oldx;
	char point[sizeof(int)];

	returnXY(j, i, &x, &y);
	returnXY(oldj, oldi, &oldx, &oldy);
	if(org == 1){
		while (oldy < y){

			blocow = newwin(height, width, oldy, x);
			wrefresh(blocow);
	
			blocow = newwin(height, width, ++oldy, x);
			wrefresh(blocow);
			usleep(SLEEP);
		}
	}else if(org == 2){
		while (oldy > y){

			blocow = newwin(height, width, oldy, x);
			wrefresh(blocow);

			blocow = newwin(height, width, --oldy, x);
			wrefresh(blocow);
			usleep(SLEEP);
		}
	}else if(org == 3){
		while (oldx > x){

			blocow = newwin(height, width, y, oldx);
			wrefresh(blocow);

			blocow = newwin(height, width, y, --oldx);
			wrefresh(blocow);
			usleep(SLEEP);
		}
	}
	else if(org == 4){
		while (oldx < x){

			blocow = newwin(height, width, y, oldx);
			wrefresh(blocow);

			blocow = newwin(height, width, y, ++oldx);
			wrefresh(blocow);
			usleep(SLEEP);
		}
	}
		desenha_tabela(tablew);
		desenha_bloco(estrutura);
}
void ganhou(char estrutura[][TAMANHO], int score){ // caso chegue em 2048, ganhou

	int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);


    win = newwin(5, 50, (yMax/2), (xMax/3));
	wattrset(win, COLOR_PAIR(6));
	box(win, ACS_VLINE, ACS_HLINE);
	wrefresh(win);

	mvwprintw(win, 1, 1,"%50s"," ");
	mvwprintw(win, 2, 1,"%49s"," ");
	mvwprintw(win, 2, 10,"Parabens, voce completou 2048!");
	mvwprintw(win, 3, 1,"%49s"," ");
	wattroff(win, COLOR_PAIR(6));
	wrefresh(win);
	usleep(SLEEP*300);

	save(estrutura, score);
}
int colide(char estrutura [][TAMANHO], int value, int *score){ // realiza a verificação de colisão de blocos com mesmo valor, bem como soma de score e peças
	
	int num, org, aux;

	switch (value){
	case 1:
	org = 1;
		for(int i = 0; i<4; i++){
			for(int j = 0; j<4; j++){
				if(*(estrutura[0]+i *TAMANHO +j) != 0){
					for(int k = i; k <=3; k++){
						if(k+1 <= 3){
							if(*(estrutura [0]+(k+1) *TAMANHO +j) != 0){
								if(*(estrutura [0]+(k+1) *TAMANHO +j) == *(estrutura [0]+k *TAMANHO +j)){
									num = colorponto(*(estrutura[0]+k *TAMANHO +j)*2);
									*(estrutura [0]+(k+1) *TAMANHO +j) = *(estrutura[0]+k *TAMANHO +j)*2;
									*score += *(estrutura [0]+k *TAMANHO +j);
									*(estrutura [0]+k *TAMANHO +j) = 0;
									anima_bloco(estrutura, (k+1),j, k, j,org); 
									if(*(estrutura [0]+(k+1) *TAMANHO +j) == 4){
										int a = *score;
										ganhou(estrutura, a);
										return 0;
									}
								}
							}else{
								*(estrutura [0]+(k+1) *TAMANHO +j) = *(estrutura[0]+k *TAMANHO +j);
								*(estrutura [0]+k *TAMANHO +j) = 0;
								anima_bloco(estrutura, (k+1),j, k, j,org); 
							}
						}
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
					for(int k = i; k >=0; k--){
						if(k-1 >= 0){
							if(*(estrutura [0]+(k-1) *TAMANHO +j) != 0){
								if(*(estrutura [0]+(k-1) *TAMANHO +j) == *(estrutura [0]+k *TAMANHO +j)){
									num = colorponto(*(estrutura[0]+k *TAMANHO +j)*2);
									*(estrutura [0]+(k-1) *TAMANHO +j) = *(estrutura[0]+k *TAMANHO +j)*2;
									*score += *(estrutura [0]+k *TAMANHO +j);
									*(estrutura [0]+k *TAMANHO +j) = 0;
									anima_bloco(estrutura, (k-1),j, k, j,org); 
									if(*(estrutura [0]+(k+1) *TAMANHO +j) == 64){
										int a = *score;
										ganhou(estrutura, a);
										return 0;
									}
								}
							}else{
								*(estrutura [0]+(k-1) *TAMANHO +j) = *(estrutura[0]+k *TAMANHO +j);
								*(estrutura [0]+k *TAMANHO +j) = 0;
								anima_bloco(estrutura, (k-1),j, k, j,org); 
							}
						}
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
					for(int k = j; k >=0; k--){
						if(k-1 >= 0){
							if(*(estrutura [0]+i *TAMANHO +(k-1)) != 0){
								if(*(estrutura [0]+i *TAMANHO +(k-1)) == *(estrutura [0]+i *TAMANHO +k)){
									num = colorponto(*(estrutura[0]+i *TAMANHO +k)*2);
									*(estrutura [0]+i *TAMANHO +(k-1)) = *(estrutura[0]+i *TAMANHO +k)*2;
									*score += *(estrutura [0]+i *TAMANHO +k);
									*(estrutura [0]+i *TAMANHO +k) = 0;
									anima_bloco(estrutura, i,(k-1), i, k,org); 
									if(*(estrutura [0]+(k+1) *TAMANHO +j) == 64){
										int a = *score;
										ganhou(estrutura, a);
										return 0;
									}
								}
							}else{
								*(estrutura [0]+i *TAMANHO +(k-1)) = *(estrutura[0]+i *TAMANHO +k);
								*(estrutura [0]+i *TAMANHO +k) = 0;
								anima_bloco(estrutura, i,(k-1), i, k,org); 
							}
						}
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
					for(int k = j; k <=3; k++){
						if(k+1 <= 3){
							if(*(estrutura [0]+i *TAMANHO +(k+1)) != 0){
								if(*(estrutura [0]+i *TAMANHO +(k+1)) == *(estrutura [0]+i *TAMANHO +k)){
									num = colorponto(*(estrutura[0]+i *TAMANHO +k)*2);
									*(estrutura [0]+i *TAMANHO +(k+1)) = *(estrutura[0]+i *TAMANHO +k)*2;
									*score += *(estrutura [0]+i *TAMANHO +k);
									*(estrutura [0]+i *TAMANHO +k) = 0;
									anima_bloco(estrutura, i,(k+1), i, k,org); 
									if(*(estrutura [0]+(k+1) *TAMANHO +j) == 64){
										int a = *score;
										ganhou(estrutura, a);
										return 0;
									}
								}
							}else{
								*(estrutura [0]+i *TAMANHO +(k+1)) = *(estrutura[0]+i *TAMANHO +k);
								*(estrutura [0]+i *TAMANHO +k) = 0;
								anima_bloco(estrutura, i,(k+1), i, k,org); 
							}
						}
					}
				}
			}
		}
		break;
	
	default:
		break;
	}
	
}
void bloco(char estrutura[][TAMANHO]){ // gera blocos aleatórios no tabuleiro


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
int controle(char estrutura[][TAMANHO], int score){ // controle de movimentação e movimentos
	
	int choice, mov = 0;

	tablew = newwin(29, 49, 4, 15);
	box(tablew, '|', '-'); 

	keypad(tablew, TRUE );

	desenha_tabela(tablew);
	wrefresh(tablew);
	desenha_bloco(estrutura);

	while(1){
	//imprime_estrutura(estrutura);
	choice = wgetch(tablew);
	switch (choice)
	{
	case KEY_DOWN:
		int a = colide(estrutura, 1, &score);
		if(a == 0){
		delwin(gamew);
		endwin();
		return 0;
		}
		usleep(SLEEP*2);
		bloco(estrutura);
		scorew(score);
		mov++;
		movimentos(mov);
		break;
	case KEY_UP:
		int a = colide(estrutura, 2, &score);
		if(a == 0){
		delwin(gamew);
		endwin();
		return 0;
		}
		usleep(SLEEP*2);
		bloco(estrutura);
		scorew(score);
		mov++;
		movimentos(mov);
		break;
	case KEY_LEFT:
		int a = colide(estrutura, 3, &score);
		if(a == 0){
		delwin(gamew);
		endwin();
		return 0;
		}
		usleep(SLEEP*2);
		bloco(estrutura);
		scorew(score);
		mov++;
		movimentos(mov);
		break;
	case KEY_RIGHT:
		int a = colide(estrutura, 4, &score);
		if(a == 0){
		delwin(gamew);
		endwin();
		return 0;
		}
		usleep(SLEEP*2);
		bloco(estrutura);
		scorew(score);
		mov++;
		movimentos(mov);
		break;
	case 27:
		printf("esc");
		delwin(gamew);
		endwin();
		return 0;
		break;
	case 110:
		// wclear(gamew);
		// wclear(tablew);
		// score = 0;
		// mov = 0;
		// scorew(score);
		// movimentos(mov);
		// char estrutura[TAMANHO][TAMANHO] = {{0,0,0,0},
		// 				{0,0,0,0},
		// 				{0,0,0,0},
		// 				{0,0,0,0}};
		// wrefresh(gamew);
		// wrefresh(movimentow);
		// wrefresh(pontuacaow);
		// wrefresh(tablew);
		// controle(estrutura, score);
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
void play(char estrutura[][TAMANHO], int score){ // chama as funções de score, movimentos, rank, comandos e controle. Passando seus parametros quando necessario

    int xMax, yMax, mov = 0;
    getmaxyx(stdscr, yMax, xMax);

		scorew(score);
		movimentos(mov);
		rank();
		comands();
		controle(estrutura, score);
}
int load_game(char estrutura[][TAMANHO]){ // caso opão na tela de menu, carrega um jogo já salvo ou informa que não foi encontrado e fecha o jogo

	keypad(load, TRUE);

	FILE *arq = fopen(FILE_NAME, "r");
	if(arq == NULL){
        delwin(gamew);
	 	endwin();
		return 0;
    }

    int xMax, yMax, letra, cont = 0, tamArq, score;
	getmaxyx(stdscr, yMax, xMax); 

	char name[NAME_TAM], pontos[sizeof(int)*2];
	char pesqname[NAME_TAM];
	char linha[52];
	qtdLinhas(&tamArq);

    load = newwin(5, 50, (yMax/2), (xMax/3));
	wattrset(load, COLOR_PAIR(6));
	box(load, ACS_VLINE, ACS_HLINE);
	wrefresh(load);

	mvwprintw(load, 1, 1,"%50s"," ");
	mvwprintw(load, 1, 22,"Load-Game");
	mvwprintw(load, 2, 1,"%49s"," ");
	mvwprintw(load, 3, 1,"%49s"," ");
	wattrset(load, COLOR_PAIR(2));
	mvwprintw(load, 3, 1,"Por favor informe seu nickname: ");
	
	do {
		letra = wgetch(load);
		pesqname[cont] = letra;
		
		if(pesqname[cont] >= 'a' && pesqname[cont] <= 'z' || letra == 127){
			if(cont != 0){
				if(letra == 127){
					pesqname[cont-1] = ' ';
					cont --;
				}else{
					cont ++;
				}
			}else{
				cont ++;
			}
		}else if(letra == 10){
			pesqname[cont] = '\0';
		}
		mvwprintw(load, 3, 1 + strlen("Por favor informe seu nickname: "),"%s", pesqname);	

	}while(letra != 10 && cont < 10);

	char copy[10];
	strcpy(copy, pesqname);

	wrefresh(load);
	wattroff(load, COLOR_PAIR(2));
	wattroff(load, COLOR_PAIR(6));

	rewind(arq);

	for (int i =1; i <= tamArq; i++){
	
	fgets(linha, 52, arq);

	char *p = strtok(linha, "#");
	int aux = 0, i = 0, j = 0;

		do{
			if(aux == 0){
				sprintf(pontos, "%s", p);
			}else if(aux == 1){
				sprintf(name, "%s", p);
			}else{
				if(j < 4){
					*(estrutura[0]+i *TAMANHO +j) = atoi(p);
					j+=1;
				}else{
					i +=1;
					j = 0;
				}

			}
			aux++;
		}while((p = strtok(NULL, "#")));

		if(strcmp(name, copy) == 0){
			score = atoi(pontos);
			break;
	 	}
	}
	if(strcmp(name,copy) != 0){
				wattrset(load, COLOR_PAIR(2));
				mvwprintw(load, 3, 1,"%49s"," ");
				mvwprintw(load, 3, 18,"Name não encontrado");
				wattrset(load, COLOR_PAIR(2));
				wrefresh(load);
				usleep(SLEEP*200);
				delwin(load);
				delwin(gamew);
				endwin();
				return 0;
	}

	fclose(arq);
	keypad(load, false);
	wclear(load);
	wrefresh(load);
	play(estrutura, score);
}
int main() { // com as informações do menu seleciona o comando, gera a estrutura primária, bem como as duas peças aleatórias de valor 2 

	char estrutura[TAMANHO][TAMANHO] = {{0,0,0,0},
						{0,0,0,0},
						{0,0,0,0},
						{0,0,0,0}};
	int  pontos = 0, y,x,i,j, sair = 0;;

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
			load_game(estrutura);
			return 0;
		}else if(play_game == 0){
			srand(time(NULL));
				for (int k = 0; k<2; k++){
					
					y = rand() % 26;
					x = rand() % 52;
					while(sair == 0){

						returnIJ(y,x, &i, &j);

						if(*(estrutura[0]+i *TAMANHO +j) != 0){
							y = rand() % 26;
							x = rand() % 52;
						}else{
							*(estrutura[0]+i *TAMANHO +j) = 2;
							sair = 1;
						}

					}
					sair =0;
				}
			play(estrutura, pontos);
		}
		delwin(gamew);
		endwin();
		return 0;
	}
	delwin(gamew);
	endwin();
}
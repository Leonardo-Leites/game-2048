#define TAMANHO 4
#define SLEEP 10000
#define NAME_TAM 10

#define FILE_NAME "save.txt"
 
#define NITEMS 3

int menu();
int tabela(char estrutura[][TAMANHO], int score);
int colorponto(int ponto);
int returnXY(int p1, int p2, int *x, int *y);
int returnIJ(int p1, int p2, int *i, int *j);
int save(char estrutura[][TAMANHO], int score);
int load_game();
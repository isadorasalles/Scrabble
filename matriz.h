#ifndef MATRIZ
#define MATRIZ

char **alocar_matriz(int l, int c);
void inicializa_matriz (char **m);
void imprime_matriz (char **m, int l, int c);
void liberar_matriz(char **m, int l);
int inicio_jogo();
int *position(char *vetor, int *points, char **tabuleiro, int *soma, int *quant, int rodada);
void writeWord (char **m, char *vetor, int start, int end, char direction, int pos);
int confer_reuse (char **m, int *quant, int start, int end, char direction, int pos);
int reuse_letter (char *vetor, int *points, char **tabuleiro, int *soma, int start, int end, char direction, int pos);
void return_word (char *palavra, int *points, char **tabuleiro, int *soma, int start, int end, char direction, int pos);
void search_points (char *palavra, int *points, int *soma, int tam);
void print_conditions ();
#endif

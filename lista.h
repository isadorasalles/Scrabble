#ifndef LISTA
#define LISTA

//Structs da lista
typedef struct node{
	struct node *next;
	char value;
	int letter_point;
} node_t;

typedef struct {
	node_t *start;
	node_t *end;
	int num_elements;
} lista_t;

//Struct do jogador
typedef struct {
	char letters[7];
	int letter_point[7];
	int punctuation;
	int used[7];  //para indicar se a letra foi usada
	int dica;
} player;

//funcoes basicas para listas:
lista_t *create_list ();
void insert_list (lista_t *list, char letter, int letter_point);
int *remove_element (lista_t *list, int i);
void clear_list (lista_t *list);
void print_list (lista_t *list);
void swap (lista_t *saco, int n, int m);
//funcoes do jogo e do jogador que usam a lista
void PackageFiller (lista_t *saco, int *pecas, int *points);
void lettersPlayers (lista_t *saco, player *array, int i, int location);
int changeLetters (lista_t *saco, char value, int letter_point);
void inicializa_suporte (lista_t *saco, player *array, int n);
int read_command (lista_t *saco, player *array, char *vetor, int *soma, int i);
int command_swap (lista_t *saco, player *array, int i);
int put_piece (lista_t *saco, player *array, char *vetor, int *soma, int i);
int abastecer_suporte (lista_t *saco, player *array, int i);
//funcoes do jogador que usam apenas a struct do jogador
void print_player (player *array, int player, int n);
void insertion_sort (player *array, int n);
void pontucao_geral (player *array, int n);

#endif 

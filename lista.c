#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"
#include <time.h>

lista_t *create_list (){
	lista_t *list = (lista_t *) malloc (sizeof(lista_t));
	list->start = NULL;
	list->end = NULL;
	list->num_elements = 0;
	return list;
}

void insert_list (lista_t *list, char value, int letter_point){
	node_t *N = (node_t *) malloc (sizeof(node_t));
	N->value = value;
	N->letter_point = letter_point;
	N->next = NULL;
	if (list->start == NULL) list->start = N;
	else list->end->next = N;
	list->end = N;
	list->num_elements++;
}

int *remove_element (lista_t *list, int i){
	int *array= (int *) malloc (2*sizeof(int));
	node_t *toFree = list->start;
	node_t *prev = NULL;
	int j=0;
	while ((j<i)&&(toFree!=NULL)){
		prev = toFree;
		toFree = toFree->next;
		j++;
	}
	array[0] = toFree->value;
	array[1] = toFree->letter_point;
	if (toFree == NULL) return 0;
	if (toFree == list->start) 
		list->start = toFree->next;
	if (toFree == list->end)
		list->end = prev;
	if (prev!= NULL){
		prev->next = toFree->next;
		free(toFree);
	}
	list->num_elements--;
	return array;
}

void clear_list (lista_t *list){
	node_t *toVisit = list->start;
	node_t *toFree;
	while (toVisit != NULL){
		toFree = toVisit;
		toVisit = toVisit->next;
		free(toFree);
	}
	free(list);
}

void print_list (lista_t *list){
	node_t *print = list->start;
	while (print != NULL){
		printf ("%c ", print->value);
		print = print->next;
	}
	printf ("\n");
}

void PackageFiller (lista_t *saco, int *pecas, int *points){
	//esta funcao ira armazenar as pecas de forma aleatoria no saco, que e uma lista encadeada
	int i = 0, j = 0;
	int aux, letter_point;
	int *array= (int *) malloc (2*sizeof(int));
	lista_t *auxiliar = create_list(); 

	for(i=0; i<24; i++){
		for (j=0; j<pecas[i]; j++){
			aux = i;
			if (aux == 22) aux += 3; //letra W vira Z
			if (aux == 10) aux = -65; //letra K vira espaço
			insert_list (auxiliar, aux+97 , points[i]);  //armazena na lista auxiliar as pecas em ordem
		}
	}
	i=0;
	while (i < 118){
		if (auxiliar->num_elements > 1) aux = (rand()%(auxiliar->num_elements-1)); 
		else aux = 0;
		array = remove_element(auxiliar, aux);	//remove a peca da lista auxiliar da posicao "escolhida" aleatoriamente
		insert_list (saco, array[0], array[1]); //insere esta peca no saco
		i++;
	}
	free (array);
	clear_list (auxiliar);
}

void lettersPlayers (lista_t *saco, player *array, int i, int location){
	//coloca pecas no suporte do jogador na posicao selecionada
	int *vector= (int *) malloc (2*sizeof(int));
	vector = remove_element(saco, 0); //retira a primeira peca do saco
	array[i].letters[location] = vector[0];
	array[i].letter_point[location] = vector[1];
	array[i].used[location] = 1;
	free(vector);
}

int changeLetters (lista_t *saco, char value, int letter_point){
	//funcao ira colocar a letra de volta no saco em uma posicao aleatoria
	int i, j;
	if (saco->num_elements > 0){
		insert_list (saco, value, letter_point);  //insere a letra que quer trocar no fim do saco
		j = saco->num_elements - 1;
		i = (rand()%(saco->num_elements-1)); //escolhe uma posicao randomica no saco
		if (j != i){
			swap(saco, i, j);  //troca essa posicao com a ultima
		}
		return 0;
	}
	else {
		printf ("As pecas no saco acabaram.\n");
		return 1;
	}

}
void swap (lista_t *saco, int n, int m){
	//troca os dados de duas posicoes do saco
	int i;
	node_t *pointer1 = saco->start;
	node_t *pointer2 = saco->start;
	char aux_letter;
	int aux_points;
	for (i=0; i<n; i++)
		pointer1 = pointer1->next;
	for (i=0; i<m; i++)
		pointer2 = pointer2->next;
	aux_letter = pointer1->value;
	aux_points = pointer1->letter_point;
	pointer1->value = pointer2->value;
	pointer1->letter_point = pointer2->letter_point;
	pointer2->value = aux_letter;
	pointer2->letter_point = aux_points;
}

void print_player (player *array, int player, int n){
	int i;
	for (i=0; i<n; i++)
		printf("%c ", array[player].letters[i]);
	printf ("\n");
}

void inicializa_suporte (lista_t *saco, player *array, int n) {
	int i, j;
	for (i=0; i<n; i++){
		for (j=0; j<7; j++){
			lettersPlayers (saco, array, i, j);
			array[i].used[j] = 1;
		}
		array[i].punctuation = 0;
		array[i].dica = 3;
	}
}

int read_command (lista_t *saco, player *array, char *vetor, int *soma, int i){
	char move[100];
	int erro = 1;

	while (erro == 1){
		scanf ("%s", move);
		if (strcmp(move, "trocar") == 0){
			erro = 0;
			printf ("\nVoce pode trocar 1 ou 7 as pecas.\n");
			return command_swap (saco, array, i);
		}
		else if (strcmp(move, "colocar") == 0) {
			erro = 0;
			return put_piece (saco, array, vetor, soma, i);
		}
		else if (strcmp(move, "passar") == 0) {
			erro = 0;
			return -2;
		}
		else if (strcmp(move, "dica") == 0){
			erro = 0;
			array[i].dica--;
			if (array[i].dica >= 0)
				return -3;
			printf ("Suas dicas acabaram. Insira um novo comando:\n");
			read_command (saco, array, vetor, soma, i);
		}
		else {
			printf ("Voce deve inserir um desses comandos: \n");
			printf ("trocar, colocar, passar ou dica\n");
		}
	}
}

int command_swap (lista_t *saco, player *array, int i){
	int peca, number, j, cont = 0;
	int erro = 0;
	printf ("Numero de pecas que deseja trocar: ");

	for (j=0; j<7; j++)
		if (array[i].letters[j] != '-') cont++; 

	if (cont != 7) printf ("Voce nao pode trocar pecas, o saco ja esta vazio.\n");

	while (cont == 7){ //caso contrario as pecas no saco acabaram e nao pode haver trocas
		scanf ("%d", &number);
		if ((number != 1)&&(number !=  7))
			printf ("Voce so pode trocar 1 ou 7 as pecas. Insira uma nova quantidade: ");
		else break;
	} 
	if (number == 1){
		printf ("\nQual peca deseja trocar: ");
		scanf ("%d", &peca);
		erro = changeLetters (saco, array[i].letters[peca], array[i].letter_point[peca]); //retorna 1 se as pecas do saco tiverem acabado
		if (erro != 1) 
			lettersPlayers (saco, array, i, peca); //coloca letras nas posicoes vazias do suporte do jogador
	}
	else {
		for (j=0; j<number; j++){
			erro = changeLetters (saco, array[i].letters[j], array[i].letter_point[j]);
			if (erro == 1) break;
			lettersPlayers (saco, array, i, j); 
		}
	}
	if (erro == 0) {
		printf ("\nEssas sao suas novas pecas: \n");
		print_player (array, i, 7);
	}
	return -1;
}

int put_piece (lista_t *saco, player *array, char *vetor, int *soma, int i){
	int j, indice;
	int quant = 0;

	do {
		printf ("\nQuantas letras do seu bloco voce usara: ");
		scanf ("%d", &quant);
		if (quant == 0) 
			printf ("Voce deve colocar uma palavra no tabuleiro.\n");
	} while (quant == 0);
	printf ("\nInsira os indices na ordem que deseja montar a palavra: ");

	for (j = 0; j<quant; j++){
		scanf ("%d", &indice);
		vetor[j] = array[i].letters[indice]; //coloca as pecas dos indices escolhidos no vetor
		array[i].used[indice] = 0;
		*soma += array[i].letter_point[indice]; //coloca na variavel soma a soma dos pontos das pecas que deseja colocar no tabuleiro
	}
	printf("Palavra formada: ");
	for (j=0; j<quant; j++){ 
		printf("%c", vetor[j]); 
	}
	printf ("\n");
	return quant;
}

int abastecer_suporte (lista_t *saco, player *array, int i){
	int j, cont = 0;
	for (j=0; j<7; j++)
		if (array[i].used[j] == 0){
			if (saco->num_elements > 0) lettersPlayers (saco, array, i, j);
			else {
				array[i].letters[j] = '-'; //quando as pedras vao acabando no saco
				array[i].letter_point[j] = 0;
				cont++;
			}
		}
	if (cont == 7) 
		return 1; 
	else 
		return 0;
}
void pontucao_geral (player *array, int n){
	//no final do jogo analisa os suportes dos jogadores e da pontuacao do mesmo sera subtraido os pontos das pecas
	//que sobraram no seu suporte, se algum jogador usar todas as pecas, este ganha os pontos das pecas que sobraram
	//no suporte do restante dos jogadores
	int i, j, k, pontos = 0;
	int usou_tudo[n];
	for (i=0; i<n; i++){
		usou_tudo[i] = 0;
		for (j=0; j<7; j++)
			pontos += array[i].letter_point[j];
		if (pontos == 0) usou_tudo[i] = 1;
		array[i].punctuation -= pontos;
		pontos = 0;
	}
	for (i=0; i<n; i++){
		if (usou_tudo[i] == 1)
			for (j=0; j<n; j++)
				for (k=0; k<7; k++)
					array[i].punctuation += array[j].letter_point[k];
	}
	insertion_sort (array, n);
}

void insertion_sort (player *array, int n){
	int i, j, aux;
	int pontos[n];
	for (i=0; i<n; i++)
		pontos[i] = array[i].punctuation;
	for (i=1; i<n; i++)
		for (j=i; j>0; j--){
			if (pontos[j-1] < pontos[j]) {
				aux = pontos[j];
				pontos[j] = pontos[j-1];
				pontos[j-1] = aux;
			}
			else break;  //quando nao tem mais troca sai do laco interno
		}
	printf ("\n");
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			if (pontos[i] == array[j].punctuation)
				printf ("Jogador %d: %d pontos\n", j+1, pontos[i]);
}

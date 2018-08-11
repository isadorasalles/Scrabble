#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matriz.h"

char **alocar_matriz(int l, int c){
	int i;
	char **m = (char **) malloc (l * sizeof(char *));
	if (m == NULL) {
		printf ("** Erro: Memoria Insuficiente **");
		return (NULL);
    }
  	/* aloca as colunas da matriz */
  	for (i=0; i<l; i++) {
		m[i] = (char*) malloc (c * sizeof(char));
      	if (m[i] == NULL) {
			printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
        }
	}
  return m; 
}

void inicializa_matriz (char **m){
	int i, j;
	for (i=0; i<16; i++){
			m[0][i] = i;
			m[i][0] = i;
		}
	for (i=1; i<16; i++)  //inicializa matriz com "-"
		for (j=1; j<16; j++)
			m[i][j] = '-';
}

void imprime_matriz (char **m, int l, int c){
	int i, j;
	printf("\n");
	for (i=0; i<l; i++) {
		for (j=0; j<c; j++){
			if (i == 0) {
				if (j < 10) printf(" %d ", m[0][j]);
				else printf("%d ", m[0][j]);
			}
			else if (j == 0) {
				if (i <10) printf(" %d ", m[i][0]);
				else  printf("%d ", m[i][0]);
			}
			if ((i != 0)&&(j != 0)) printf(" %c ", m[i][j]);
		}
		printf("\n");
	}
}
void liberar_matriz(char **m, int l){
	int i;
	for (i=0; i<l; i++) 
		free(m[i]);
	free (m);
}

int inicio_jogo(){
	int n;
	printf ("INICIO DO JOGO\n");
	print_conditions();
	printf ("\n");
	do {
		printf ("Diga quantos jogadores estao na partida: ");
		scanf ("%d", &n);
		if ((n>4)||(n<=1)) 
			printf ("O jogo deve ter 2 a 4 jogadores.\n");
	} while ((n>4)||(n<=1));
	return n;
}

int *position(char *vetor, int *points, char **tabuleiro, int *soma, int *quant, int rodada){
	//essa funcao ira retornar a posicao que o jogador deseja colocar a palavra, verificando inicialmente se a mesma e valida
	//a funcao retorara algo diferente caso o jogador decida passar a vez pos escrever posicao errada
	int *posicao = (int *) malloc (sizeof (int));
	int start, end, pos;
	char direction;
	char str_pos[100];
	int valido = 0;
	printf ("\nDigite uma posicao valida: ");
	do {
		scanf ("%s", str_pos);
		if (strcmp (str_pos, "passar") != 0){
			sscanf (str_pos, "%d ", &start);
			scanf ("%d %c %d", &end, &direction, &pos);
		}
		else {
			posicao[0] = -2;
			return posicao;
		}
		if (rodada > 0){//confere se esta reutilizando palavras e se o espaco esta ok
			valido = confer_reuse (tabuleiro, quant, start, end, direction, pos);
			if (valido == 1){
				printf ("Ou o espaco que escolheu nao cabe a palavra ou vc nao esta reutilizando uma palavra.\n");
				printf ("Voce pode escrever uma nova posicao ou o comando passar, para passar a vez: \n");
			}
		}
		else {
			if ((end - start + 1) == *quant) valido = 0;
			else{
				printf ("Palavra nao cabe nesse espaco!!\n");
				printf ("Voce pode escrever uma nova posicao ou passar, para passar a vez: \n");
				valido = 1;
			}
		}
	} while (valido == 1);
	if (rodada > 0)
		*quant = reuse_letter (vetor, points, tabuleiro, soma, start, end, direction, pos);
	posicao[0] = start;
	posicao[1] = end;
	posicao[2] = direction;
	posicao[3] = pos;
	return posicao;
}

void writeWord (char **m, char *vetor, int start, int end, char direction, int pos){
	//essa funcao ira escrever a palavra no tabuleiro
	int i, j=0;
	if (direction == '^') { //direcao de baixo pra cima
		for (i=start; i>end-1; i--){
			m[i][pos] = vetor[j];
			j++;
		}
	}
	if (direction == 'v') { //direcao de cima pra baixo
		for (i=start; i<end+1; i++){
			m[i][pos] = vetor[j];
			j++;
		}
	}
	if (direction == '>') { //direcao da esquerda para a direita
		for (i=start; i<end+1; i++){
			m[pos][i] = vetor[j];
			j++;
		}
	}
	if (direction == '<') { //direcao da direita para a esquerda
		for (i=start; i>end-1; i--){
			m[pos][i] = vetor[j];
			j++;
		}
	}
}
void return_word (char *palavra, int *points, char **tabuleiro, int *soma, int start, int end, char direction, int pos){
	//funcao le a posicao dada pelo jogador, ja verificada anteriormente, colocando as palavras do tabuleiro num vetor "palavra"
	int i;
	int j = 0;
	if (direction == '^') { //direcao de baixo pra cima
		for (i=start; i>end-1; i--){
			palavra[j] = tabuleiro[i][pos];
			j++;
		}
	}
	if (direction == 'v') { //direcao de cima pra baixo
		for (i=start; i<end+1; i++){
			palavra[j] = tabuleiro[i][pos];
			j++;
		}
	}
	if (direction == '>') { //direcao da esquerda para a direita
		for (i=start; i<end+1; i++){
			palavra[j] = tabuleiro[pos][i] ;
			j++;
		}
	}
	if (direction == '<') { //direcao da direita para a esquerda
		for (i=start; i>end-1; i--){
			palavra[j] = tabuleiro[pos][i];
			j++;
		}
	}
	search_points (palavra, points, soma, end-start+1);
	
}

int confer_reuse (char **m, int *quant, int start, int end, char direction, int pos) {
	//funcao para conferir se na posicao dada pelo jogador ha reutilizacao de palavras ou letras do tabuleiro
	//assim como conferir se o espaco solicitado cabe a quantidade de letras que o jogador deseja
	int i, j=0;
	int cont = 0;
	if (direction == '^') { //direcao de baixo pra cima
		for (i=start; i>end-1; i--){
			if (m[i][pos] != '-') cont++;
			j++;
		}
	}
	if (direction == 'v') { //direcao de cima pra baixo
		for (i=start; i<end+1; i++){
			if (m[i][pos] != '-') cont++;
			j++;
		}
	}
	if (direction == '>') { //direcao da esquerda para a direita
		for (i=start; i<end+1; i++){
			if (m[pos][i] != '-') cont++;
			j++;
		}
	}
	if (direction == '<') { //direcao da direita para a esquerda
		for (i=start; i>end-1; i--){
			if (m[pos][i] != '-') cont++;
			j++;
		}
	}
	//confere se o espaco esta ok para inserir a palavra considerando reuso
	if (((end - start + 1 - cont) == *quant)&&(cont > 0)) return 0; 
	else return 1;
}

int reuse_letter (char *vetor, int *points, char **tabuleiro, int *soma, int start, int end, char direction, int pos){
	//essa funcao ira retornar o novo tamanho da palavra, alem de preencher o vetor com as letras do tabueleiro que serao reusadas
	int n, k, j, m = 0;
	int tam = end-start+1;
	char palavra[tam];
	return_word (palavra, points, tabuleiro, soma, start, end, direction, pos); //preenche "palavra" com as letras do tabuleiro
	for (j=0; j<tam; j++) //preenche as posicoes vazias do vetor palavra com as letras que o jogador deseja colocar
		if (palavra[j] == '-') {
			palavra[j] = vetor[m];
			m++;
		}
	printf("Palavra formada: ");
	for (j=0; j<tam; j++){ //copia o "palavra" para o vetor, que sera usado na main
		vetor[j] = palavra[j];
		printf("%c", vetor[j]); 
	}
	printf("\n");
	return tam;
}

void search_points (char *palavra, int *points, int *soma, int tam){
	//essa funcao ira somar os pontos das letras reutilizadas do tabuleiro
	int busca_ponto;
	int i;
	for (i=0; i<tam; i++)
		if (palavra[i] != '-') {
			busca_ponto = palavra[i] - 97;
			if (busca_ponto == 25) busca_ponto = 22; //letra W vira Z
    		if (busca_ponto == -65) busca_ponto = 10; //letra K vira espaço
   			*soma+= points[busca_ponto];
   		}
}

void print_conditions (){
	printf ("INSTRUCOES INICIAIS:\n");
	printf ("\n");
	printf ("A cada rodada cada jogador tera 4 opcoes de comando: \n");
	printf ("1. Para trocar pecas digite: trocar\n");
	printf ("2. Para colocar pecas no tabuleiro digite: colocar\n");
	printf ("3. Para passar a vez digite: passar\n");
	printf ("4. Para pedir uma dica digite: dica\n");
	printf ("\n");
	printf ("Apos a primeira palavra ser colocada no tabuleiro, todas as proximas devem usar uma ou mais letras de palavras anteriores.\n");
	printf ("\n");
	printf ("Para escolher a posicao no tabuleiro:\n");
	printf ("Insira o local que deseja colocar a palavra: o inicio e o fim.\n");
	printf ("Em seguida insira ^ para escrever de baixo para cima.\n");
	printf ("v para escrever de cima para baixo.\n");
	printf ("> para escrever da esquerda para direita.\n");
	printf ("< para escrever da direita para esquerda. Depois a posicao no tabuleiro. \n");
}

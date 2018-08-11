#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "trie.h"
#include "matriz.h"
#include <time.h>

int main(){
	srand(time(NULL));
	int n, i, quant, retorno;
	char vetor[100];
	int soma = 0, cont = 0, fim = 0, isEndOfWord = 0, rodada = 0, valido = 0;
	int *pos = (int *) malloc (4*sizeof (int)); 
	char **tabuleiro = alocar_matriz(16, 16);
	//para usar a tabela ascii coloquei as pecas brancas onde é a letra k e z fica no lugar referente a y
	int pecas[24] = {14, 3, 4, 5, 11, 2, 2, 2, 10, 2, 3, 5, 6, 4, 10, 4, 1, 6, 8, 5, 7, 2, 1, 1};
	//                A, B, C, D,  E, F, G, H,  I, J,  , L, M, N,  O, P, Q, R, S, T, U, V, Z, X 
	int points[24] = {1, 3, 2, 2, 1, 4, 4, 4, 1, 5, 0, 2, 1, 3, 1, 2, 6, 1, 1, 1, 1, 4, 8, 8};

	lista_t *saco = create_list();
	TrieNode *root = create_Node();
	PackageFiller (saco, pecas, points);
	validWords(root);
	inicializa_matriz (tabuleiro);

	n = inicio_jogo();
	int pontuacao[n];
	player array[n]; //cria um array que guarda n structs, que sao os vetores de tamanho 7 para cada jogador

	inicializa_suporte (saco, array, n);
	imprime_matriz (tabuleiro, 16, 16);

	while (fim == 0){ 

		for (i=0; i<n; i++){ 
			printf ("\nJOGADOR %d. Defina seu comando:\n", i+1);
			print_player (array, i, 7);
			soma = 0;
			retorno = read_command (saco, array, vetor, &soma, i);

			if (retorno == -3){  //ocorre esse retorno quando o jogador pede dica
				sugere(root);
				retorno = read_command (saco, array, vetor, &soma, i);
			}

			if (retorno > 0) { //o retorno e maior que 0 quando deseja se colocar o peca no tabuleiro
				quant = retorno;
				pos = position(vetor, points, tabuleiro, &soma, &quant, rodada);
				if (pos[0] != -2){  //ocorre quando o jogador escreve uma posicao errada e depois decide passar a vez
					isEndOfWord = search_word (root, vetor, quant);
					if (isEndOfWord == 1){
						array[i].punctuation += soma;
						writeWord (tabuleiro, vetor, pos[0], pos[1], pos[2], pos[3]);
						if (rodada == 0) rodada++;
						fim = abastecer_suporte (saco, array, i); //retorna 1 quando tem um jogador sem nenhuma peca
						imprime_matriz (tabuleiro, 16, 16);
					}
					else {
						printf ("\nEsta palavra nao existe no dicionario do jogo. Voce passou a vez!\n");
					}
				}
			}

			if ((retorno == -2)||(pos[0] == -2)){  //contagem de passar a vez seguidas
				cont++;
				if (cont == 2 * n) {
					fim = 1;  //quando todos os jogadores passaram a vez duas vezes seguidas o jogo termina
					break;
				}
			}

			if ((retorno != -2)&&(pos[0] != -2)) cont = 0;
		}
	}
	pontucao_geral (array, n);  //ordena a pontuacao dos jogadores

	destroy_trie (root);
	clear_list (saco);
	liberar_matriz(tabuleiro, 16);
	free(pos);
	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

int count = 0;

TrieNode *create_Node (){
	TrieNode *Node = (TrieNode *) malloc(sizeof(TrieNode));
    int i;
    Node->isEndOfWord = 0;
    for (i = 0; i < 25; i++)
        Node->children[i] = NULL;
    return Node;
}

void insert_trie (TrieNode *root, char *word){
    int i;
    int length = strlen(word);
    
    int aux;
 
    TrieNode *start = root;
 
    for (i = 0; i < length; i++){
        aux = word[i] - 97;
        if (aux == 25) aux = 22; //letra W vira Z
        if (aux == -65) aux = 10; //letra K vira espaço
        if (start->children[aux] == NULL)
            start->children[aux] = create_Node();
        start = start->children[aux];
    }
    // mark last node as leaf
    start->isEndOfWord = 1;
}

int search_word(TrieNode *root, char *word, int length){
    int i;
    //int length = strlen(word);
    int aux;
    TrieNode *buscar = root;
 
    for (i = 0; i < length; i++){
        aux = word[i] - 97;
        if (aux == 25) aux = 22; //letra W vira Z
        if (aux == -65) aux = 10; //letra K vira espaço
 
        if (buscar->children[aux] == NULL)
            return 0;
        
 
        buscar = buscar->children[aux];
    }
 
    return buscar->isEndOfWord;
}

void validWords (TrieNode *root){
	FILE *arq;
	char word[100];
	arq = fopen("palavras.txt", "r");
	if (arq == NULL)  // Se houve erro na abertura
	{
		printf("Problemas na abertura do arquivo\n");
		exit(1);
  	}
  	while(fscanf (arq, "%s", word) != EOF) {
        insert_trie (root, word);
	}
  	fclose(arq);
}

void destroy_trie (TrieNode *node){
    int i;
    if (node == NULL)
        return;

    for (i = 0; i < 25; i++)
        destroy_trie (node->children[i]);

    free(node);
}

char *completa (char *prefixo, char part) {
    int length = strlen(prefixo);
    char *str = malloc ((length + 2) * sizeof (char));

    int i = 0;
    for (i=0; i<length; i++){
        str[i] = prefixo[i];
    }
    str[i] = part;
    str[i+1] = '\0';
    return str;
}

void imprimeSugestoes(TrieNode *node, char *palavra) {
    int aux;
    if (node == NULL) {
        return;
    }

    if (node->isEndOfWord == 1) {
        printf("%s ", palavra);
        if (count == 3) {
            return;
        }
        count++;
    }
    for (int i = 0; i < 25; i++){
        if(node->children[i] != NULL){
            if (count == 3) {
                return;
            }
            aux = i;
            if (aux == 22) aux = 25; //letra W vira Z
            if (aux == 10) aux = -65; //letra K vira espaço

            imprimeSugestoes(node->children[i], completa (palavra, aux + 97));
        }
    }
}

void sugere(TrieNode *root) {
    /*a funcao percorre a trie ate o final da palavra, para de
    la poder ver se ha mais palavras para serem impressas a partir do prefixo ou nao */
    char prefix[100];
    printf ("\nInsira o prefixo para sugestao: ");
    scanf ("%s", prefix);
    int aux;
    int len = strlen (prefix);
    TrieNode *node = root;

    for (int i = 0; i < len; i++){
        aux = prefix[i] - 97;
        if (aux == 25) aux = 22; //letra W vira Z
        if (aux == -65) aux = 10; //letra K vira espaco
        node = node->children[aux];
    }
    printf ("\n");
    printf ("Sugestoes: ");
    count = 0;
    imprimeSugestoes(node, prefix);
    printf ("\n");
    printf ("\nEscolha o novo comando: ");
}

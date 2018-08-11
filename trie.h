#ifndef TRIE
#define TRIE

typedef struct Node {
    struct Node *children[25];
    int isEndOfWord;
} TrieNode;

TrieNode *create_Node ();
void insert_trie (TrieNode *root, char *word);
int search_word(TrieNode *root, char *word, int length);
void validWords (TrieNode *root);
void destroy_trie (TrieNode *node);
char *completa (char *prefixo, char part);
void imprimeSugestoes(TrieNode *node, char *palavra);
void sugere(TrieNode *root);
#endif

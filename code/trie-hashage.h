#ifndef TRIE_HACHAGE_H
#define TRIE_HACHAGE_H

#define COEF_H 0.75

struct _list
{
    int startNode,        /* etat de depart de la transition */
        targetNode;       /* cible de la transition */
    unsigned char letter; /* etiquette de la transition */
    struct _list *next;   /* maillon suivant */
    a
};

typedef struct _list *List;

struct _trie
{
    int maxNode;      /* Nombre maximal de noeuds du trie */
    int nextNode;     /* Indice du prochain noeud disponible */
    List *transition; /* listes d'adjacence */
    char *finite;     /* etats terminaux */
};

typedef struct _trie *Trie;

Trie createTrie(int maxNode);
int isInTrie(Trie trie, unsigned char *w);
void insertInTrie(Trie trie, unsigned char *w);
void freeTrie(Trie trie);

#endif // TRIE_HACHAGE_H

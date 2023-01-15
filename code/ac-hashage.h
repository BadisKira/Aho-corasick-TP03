#ifndef AC_HACHAGE_H
#define AC_HACHAGE_H

#include "trie-hashage.h"

/*
    la structure AhoCorasick
*/

struct _ahocorasik
{
    Trie trie;       // Le trie de l'hachage.
    int *suppleance; // le tableau des liens de suppleance
};

typedef struct _ahocorasik *AhoCorasick; // Acorasik

// inisialiser AhoCorasick
AhoCorasick createAhoCorasick(int *donnees_mots);
// Initialiser AhoCorasik
int *AC(unsigned char **X, int *donnees_mots);
// Definir les transitions et les liens de suppleance
int pre_AC(AhoCorasick AhoCorasick, unsigned char **X, int *donees_mots);
// verifier s'il existe une transition de e avec etq comme etiquette
List existTransition(Trie trie, int e, unsigned char etq);
// remplire une liste des noueuds fils de e.
List remplirListTrans(Trie trie, int e);
// Completer les liens de suppleance
void completer(AhoCorasick AhoCorasick, unsigned char **X, int *donnes_mots, int e);
// verifier si e une sortie ou non.
int if_sortie(AhoCorasick AhoCorasick, unsigned char *w, int e);
// Liberer la memoire
void free_AhoCorasick(AhoCorasick AhoCorasick);

#endif // AC-HACHAGE_H

#ifndef GENERE_H
#define GENERE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH_ALPHABET 75

static const unsigned char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ&#{([-|_^@)]=}+*.;!é$è<>";
void mots_genere(int nbr_mots, int longeur_min, int longeur_max, int taille_alph);
void texte_genere(int longeur_text, int taille_alph);
#endif
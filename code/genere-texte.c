#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "genere.h"

#ifndef LENGTH_ALPHABET
#define LENGTH_ALPHABET 75
#endif

int main(int argc, char const *argv[])
{
    // if (argc != 3)
    //     printf("nombre de parametres incorrect : longeur_texte taille_alphabet");
    // else
    // {
    //     if (atoi(argv[1]) <= 0)
    //         printf("  La longeur de texte doit etre > 0");
    //     else if (atoi(argv[2]) <= 0)
    //         printf("  La taille de l'alphabet doit etre > 0");
    //     else if (atoi(argv[2]) > LENGTH_ALPHABET)
    //         printf("La taille de l'alphabet doit etre < taille de l'alphabet");
    // }

    // // la longeur de texte
    // int longeur_texte = (int)atoi(argv[1]);
    // // la taille de l'alphabet pour le mot � generer
    // int taille_alph = (int)atoi(argv[2]);

    // la fonction de generation du texte.
    texte_genere(5000, 25);

    return EXIT_SUCCESS;
}

void texte_genere(int longeur_text, int taille_alph)
{

    for (int i = 0; i < longeur_text; i++)
    {
        int index = rand() % taille_alph;
        printf("%c", alphabet[index]);
    }
    printf("\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "genere.h"

int main(int argc, char const *argv[])
{
    /* if (argc != 5)
         printf("nombre de paramètres incorrect : nbr_mot longeur_min longeur_max taille_alph");
     else
     {
         if (atoi(argv[1]) <= 0)
             printf("Le nombre des mots à generer doit etre > 0");
         else if (atoi(argv[2]) < 0)
             printf("La longeur minimal du mot doit etre >= 0");
         else if (atoi(argv[3]) < 0)
             printf("La longeur maximal du mot doit etre > 0");
         else if (atoi(argv[4]) < 0)
             printf("La taille de l'alphabet doit etre > 0");
         else if (atoi(argv[4]) > LENGTH_ALPHABET)
         {
         }
     }

     int nbr_mot = atoi(argv[1]);
     int longeur_min = atoi(argv[2]);
     int longeur_max = atoi(argv[3]);
     int taille_alph = atoi(argv[4]);

     mots_genere(nbr_mot, longeur_min, longeur_max, taille_alph);*/
    mots_genere(50, 4, 10, 50);

    return EXIT_SUCCESS;
}

void texte_genere2(int longeur_text, int taille_alph)
{

    for (int i = 0; i < longeur_text; i++)
    {
        int index = rand() % taille_alph;
        printf("%c", alphabet[index]);
    }
    printf("\n");
}

void mots_genere(int nbr_mots, int longeur_min, int longeur_max, int taille_alph)
{

    int longeur_mot;
    srand(time(NULL));

    for (int i = 0; i < nbr_mots; i++)
    {
        longeur_mot = (rand() % (longeur_max - longeur_min)) + longeur_min;
        texte_genere2(longeur_mot, taille_alph);
    }
}

#include <stdio.h>
#include <stdlib.h>
#define LENGTH_ALPHABET 75

static const unsigned char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ&#{([-|_^@)]=}+*.;!é$è<>";
void mots_genere(int nbr_mots, int longeur_min, int longeur_max, int taille_alph);

int main(int argc, char const *argv[])
{
    if (argc != 5)
        usage("nombre de paramètres incorrect : nbr_mot longeur_min longeur_max taille_alph");
    else
    {
        if (atoi(argv[1]) <= 0)
            usage("Le nombre des mots à generer doit etre > 0");
        else if (atoi(argv[2]) < 0)
            usage("La longeur minimal du mot doit etre >= 0");
        else if (atoi(argv[3]) < 0)
            usage("La longeur maximal du mot doit etre > 0");
        else if (atoi(argv[4]) < 0)
            usage("La taille de l'alphabet doit etre > 0");
        else if (atoi(argv[4]) > LENGTH_ALPHABET)
            usage("La taille de l'alphabet doit etre < la taille de l'alphabet");
    }

    int nbr_mot = atoi(argv[1]);
    int longeur_min = atoi(argv[2]);
    int longeur_max = atoi(argv[3]);
    int taille_alph = atoi(argv[4]);

    mots_genere(nbr_mot, longeur_min, longeur_max, taille_alph);

    return EXIT_SUCCESS;
}

void mots_genere(int nbr_mots, int longeur_min, int longeur_max, int taille_alph)
{

    int longeur_mot;
    srand(time(NULL));

    for (int i = 0; i < nbr_mots; i++)
    {
        longeur_mot = (rand() % (longeur_max - longeur_min)) + longeur_min;
        texte_genere(longeur_mot, taille_alph);
    }
}

#include <stdio.h>
#include <stdlib.h>
#define LENGTH_ALPHABET 75
static const unsigned char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ&#{([-|_^@)]=}+*.;!é$è<>";
void texte_genere(int longeur_text, int taille_alph);

int main(int argc, char const *argv[])
{
    if (argc != 3)
        usage("nombre de param�tres incorrect : longeur_texte taille_alphabet");
    else
    {
        if (atoi(argv[1]) <= 0)
            usage("  La longeur de texte doit �tre > 0");
        else if (atoi(argv[2]) <= 0)
            usage("  La taille de l'alphabet doit �tre > 0");
        else if (atoi(argv[2]) > LENGTH_ALPHABET)
            usage("La taille de l'alphabet doit �tre < taille de l'alphabet");
    }

    // la longeur de texte
    int longeur_texte = (int)atoi(argv[1]);
    // la taille de l'alphabet pour le mot � generer
    int taille_alph = (int)atoi(argv[2]);

    // la fonction de generation du texte.
    texte_genere(longeur_texte, taille_alph);

    return EXIT_SUCCESS;
}

void texte_genere(int longeur_text, int taille_alph)
{

    for (int i = 0; i < longeur_text; i++)
    {
        // prendre un caractaire al�ratoire de Alphabet
        int index = rand() % taille_alph;
        printf("%c", alphabet[index]);
    }
    printf("\n");
}
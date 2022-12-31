#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerer_file.h"

// créer une file
File creatFile()
{
    // allocation mémoire pour la file
    File f = malloc(sizeof(struct _element));
    f->suivant = NULL;
    return f;
}

// enfiler dans une file
void enfiler(File f, int e)
{

    // allocation m�moire
    File nouveau = malloc(sizeof(struct _element));
    nouveau->etat = e;
    nouveau->suivant = NULL;
    // file temporal
    File fTmp = f;

    // Vérifier si la file est n'est vide
    if (f->suivant != NULL)
    {
        while (fTmp->suivant != NULL)
        {
            fTmp = fTmp->suivant;
        }
        // inserer le  noued dans la file
        fTmp->suivant = nouveau;
    }
    else
    {
        // inserer le noued dans la file
        f->suivant = nouveau;
    }
}

// defiler une file
int defiler(File f)
{

    if (f == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int e = -1;
    if (f->suivant != NULL)
    {
        File fTmp = f->suivant;
        e = fTmp->etat;
        f->suivant = fTmp->suivant;
        free(fTmp);
    }

    // return l'etat défiler
    return e;
}

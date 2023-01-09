#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#include "trie-hashage.h"

static const unsigned char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ&#{([-|_^@)]=}+*.;!é$è<>";

//**********************************************************

Trie createTrie(int maxNode)
{
    Trie trie;
    trie = malloc(sizeof(struct _trie));
    trie->maxNode = maxNode + 1;
    trie->nextNode = 1;
    trie->transition = malloc(((int)(trie->maxNode * COEF_H)) * sizeof(struct _list));
    for (int i = 0; i < (int)(trie->maxNode * COEF_H); i++)
        trie->transition[i] = NULL;
    trie->finite = calloc(trie->maxNode, sizeof(int));
    trie->finite[0] = '0';
    return trie;
}

//**********************************************************
// tester si un mot est contenu dans un trie.
int isInTrie(Trie trie, unsigned char *w)
{
    int etat = 0, find = 1, fin = -1, i = 0;

    while ((etat < trie->maxNode) && (i < strlen((const char *)w)))
    {
        char c = w[i];
        // chercher le mot dans la table d'hachage
        int positionLettre = strchr((char *)alphabet, (char)c) - (char *)alphabet;
        int index = ((etat * 100) + positionLettre) % ((int)(trie->maxNode * COEF_H));

        // si l'index n'existe pas
        if (trie->transition[index] == NULL)
        {

            find = 0; // sortir de la boucle while et retourner 0 (le mot n'existe pas)
            break;
            // sinon
        }
        else
        {
            List listcopy = trie->transition[index];
            // parcourir tous le mot
            while (listcopy != NULL)
            {
                if ((listcopy->letter != c) || (listcopy->startNode != etat))
                {
                    fin = listcopy->targetNode;
                    listcopy = listcopy->next;
                    find = 0; // n'existe pas
                }
                else
                {
                    etat = listcopy->targetNode;
                    fin = listcopy->targetNode;
                    find = 1; // la lettre existe exisete donc on continue
                    break;    // sortir de la deuxieme boucle.
                }
            }
            i++;
        }
    }
    if (find == 1 && (trie->finite[fin] != w[strlen((const char *)w) - 1]))
        find = 0;
    return find;
}

//*********************************************************

void insertInTrie(Trie trie, unsigned char *w)
{
    List nodeListe;
    int etat = 0; // index de lettre.
    int fin = -1, i = 0;

    // si le mot n'existe pas
    if (!isInTrie(trie, w))
    { // verification si le mot complet existe ou non.
        while ((etat < trie->maxNode) && (i < strlen((const char *)w)))
        {
            char c = w[i];

            // fonction de l'hachage.
            int positionLettre = strchr((char *)alphabet, (char)c) - (char *)alphabet;
            int index = ((etat * 100) + positionLettre) % ((int)(trie->maxNode * COEF_H));

            nodeListe = malloc(sizeof(struct _list)); //  creer un noeud de struct  _list

            // verification si (etet, lettre ) existe ou non dans notre trie.
            if (trie->transition[index] == NULL)
            {
                nodeListe->startNode = etat;
                nodeListe->targetNode = trie->nextNode;
                nodeListe->letter = c;
                nodeListe->next = NULL;
                trie->transition[index] = nodeListe;
                etat = trie->nextNode;
                fin = trie->nextNode;
                trie->nextNode++;
                // sinon
            }
            else
            {
                if (trie->transition[index]->next == NULL)
                {
                    // si le n'existe pas, on cree un autre noued
                    if ((trie->transition[index]->letter != c) || (trie->transition[index]->startNode != etat))
                    {
                        nodeListe->letter = c;
                        nodeListe->startNode = etat;
                        nodeListe->targetNode = trie->nextNode;
                        etat = trie->nextNode;
                        fin = trie->nextNode;
                        trie->nextNode++;
                        nodeListe->next = trie->transition[index];
                        trie->transition[index] = nodeListe;
                    }
                    else
                    {
                        // sinon
                        etat = trie->transition[index]->targetNode;
                        fin = trie->transition[index]->targetNode;
                        free(nodeListe);
                    }
                }
                else
                {
                    List listcopy = trie->transition[index];
                    int trouve = 0;

                    while (listcopy != NULL)
                    {
                        if ((listcopy->letter != c) || (listcopy->startNode != etat))
                        {
                            if (listcopy->next != NULL)
                                listcopy = listcopy->next;
                            else
                                break;
                        }
                        else
                        {
                            etat = listcopy->targetNode;
                            fin = listcopy->targetNode;
                            trouve = 1;
                            free(nodeListe);
                            break;
                        }
                    }
                    if (((listcopy->next == NULL) && (trouve == 0)) || (listcopy == NULL))
                    {

                        nodeListe->letter = c;
                        nodeListe->startNode = etat;

                        nodeListe->targetNode = trie->nextNode;
                        etat = trie->nextNode;
                        fin = trie->nextNode;
                        trie->nextNode++;

                        nodeListe->next = trie->transition[index];
                        trie->transition[index] = nodeListe;
                    }
                }
            }
            i++;
        }
        trie->finite[fin] = w[(strlen((const char *)w) - 1)];
        // affichage
        // printf("\n le mot %s est bien ajout�  \n", w);
    } // else printf("\n le mot %s est deja existe !!! \n", w);
}

//********************************************
// Liberer la memoire
void freeTrie(Trie trie)
{

    for (int i = 0; i < ((int)(trie->maxNode * COEF_H)); ++i)
    {
        while (trie->transition[i] != NULL)
        {
            List tmp = trie->transition[i];
            trie->transition[i] = tmp->next;
            free(tmp);
        }
    }
    free(trie->transition);
    free(trie->finite);
    free(trie);
}

/*
int main(int argc, char *argv[])
{
    // la table de nos mots
    unsigned char *tab_mots[NBR_MAX_MOTS];
    //la table pour r�cuperer le nombre des mots et max node.
    int * donnees_mots = malloc(2 * sizeof(int));
    nos_mots(tab_mots, donnees_mots);

    //notre texte
    unsigned char texte[TAILLE_MAX_TEXTE] = "";
    notre_texte(texte);

    Trie trie;
    // on cr�e le trie avec le nombre max des node
    trie = createTrie(donnees_mots[0]);



    //inserer tous les dans le trie
    for(int i = 0; i < donnees_mots[1]; i++){
        insertInTrie(trie, tab_mots[i]);
    }

    //liberer l'espace du trie.
    freeTrie(trie);
    //liberer l'espace m�moire de la table des mots
    for (int i = 0; i < donnees_mots[1]; i++)
    {
        free(tab_mots[i]);
    }

    //liberer l'espace m�moire de la table donne_mots
        free(donnees_mots);

    return EXIT_SUCCESS;
}
*/

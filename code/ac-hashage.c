#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ac-hashage.h"
#include "trie-hashage.c"
#include "gerer_file.c"
#define LENGTH_ALPHABET 75

// inisialiser AhoCorasick
AhoCorasick createAhoCorasick(int *X)
{
    // Allocation mémoire
    AhoCorasick ahoCorasick;
    ahoCorasick = malloc(sizeof(AhoCorasick));
    // Trie de AC
    Trie trie = createTrie(X[0]);
    ahoCorasick->trie = trie;
    // le tableau des suppleance.
    ahoCorasick->suppleance = calloc(X[0], sizeof(int));

    // la suppleance de tous les états == -1.
    for (int i = 0; i < X[0]; i++)
    {
        ahoCorasick->suppleance[i] = -1;
    }
    // le supplience de l'etat 0 == 0
    ahoCorasick->suppleance[0] = 0;
    return ahoCorasick;
}

List existTransition(Trie trie, int e, unsigned char etq)
{
    List nodeList = NULL;
    int positionLettre, index;
    if (e >= 0)
    {
        positionLettre = strchr((char *)alphabet, (char)etq) - (char *)alphabet;
        index = ((e * 100) + positionLettre) % ((int)(trie->maxNode * COEF_H));
    }
    else
        index = -1;

    if ((trie->transition[index] == NULL) || (index == -1))
    {
        return nodeList; // null (la trans n'existe pas)
    }
    else
    {

        List listcopy = trie->transition[index];
        while (listcopy != NULL)
        {
            if ((listcopy->letter != etq) || (listcopy->startNode != e))
            {
                listcopy = listcopy->next;
            }
            else
            {
                // création d'un noued d'une struct _list
                nodeList = malloc(sizeof(struct _list));
                nodeList->startNode = listcopy->startNode;
                nodeList->targetNode = listcopy->targetNode;
                nodeList->letter = listcopy->letter;
                nodeList->next = NULL;
                break;
            }
        }
        return nodeList;
    }
}

int if_sortie(AhoCorasick acorasik, unsigned char *w, int e)
{

    Trie trie = acorasik->trie;
    int etat = 0, find = 1, fin = 0, i = 0;
    while ((etat < trie->maxNode) && (i < strlen((const char *)w)))
    {
        char c = w[i];
        int positionLettre = strchr((char *)alphabet, (char)c) - (char *)alphabet;
        int index = ((etat * 100) + positionLettre) % ((int)(trie->maxNode * COEF_H));

        if (trie->transition[index] == NULL)
        {

            find = 0; // sortir de la boucle while et retourner 0 (le mot n'existe pas)
            break;
        }
        else
        {
            List listcopy = trie->transition[index];
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
    int sup = acorasik->suppleance[e];
    if (((find == 1) && (fin == e)) || ((find == 1) && (fin == sup)))
        find = 1;
    else
        find = 0;
    return find;
}

// Definir les transitions et les liens de suppleance
int pre_AC(AhoCorasick acorasik, unsigned char **X, int *donees_mots)
{

    int q0 = 0;
    // entrer les mots dans le trie
    for (int i = 0; i < donees_mots[1]; i++)
    {

        insertInTrie(acorasik->trie, X[i]);
    }

    // Completer(q0) Ajouter les liens de suppleance
    completer(acorasik, X, donees_mots, q0);
    // retourner q0
    return q0;
}

// Créer une liste à partir d'un etat e
List remplirListTrans(Trie trie, int e)
{

    int i = 0;
    List listtrans = NULL;
    while (i < LENGTH_ALPHABET)
    {
        if (existTransition(trie, e, alphabet[i]) != NULL)
        {
            List listTmptrans = existTransition(trie, e, alphabet[i]);
            if (listtrans == NULL)
            {
                // listtrans = listTmptrans;
                listtrans = malloc(sizeof(struct _list));
                listtrans->letter = listTmptrans->letter;
                listtrans->startNode = listTmptrans->startNode;
                listtrans->targetNode = listTmptrans->targetNode;
            }
            else
            {
                List nouedList = malloc(sizeof(struct _list));
                nouedList->startNode = listTmptrans->startNode;
                nouedList->targetNode = listTmptrans->targetNode;
                nouedList->letter = listTmptrans->letter;
                nouedList->next = NULL;

                List listTmp = listtrans;

                if (listTmp->next != NULL)
                {
                    while (listTmp->next != NULL)
                    {
                        listTmp = listTmp->next;
                    }
                    listTmp->next = nouedList;
                }
                else
                {
                    listTmp->next = nouedList;
                }
            }
        }
        i++;
    }
    return listtrans;
}

// completer les liens de suppleance
void completer(AhoCorasick acorasik, unsigned char **X, int *donnes_mots, int e)
{

    // f← file vide
    File f = creatFile();

    // l← liste des transitions(e, a, p) telles que p!=e
    List l;
    l = remplirListTrans(acorasik->trie, e);

    // tantque l est non vide faire
    while (l != NULL)
    {
        List premierList;
        //(r, a, p)← Premier(l)
        premierList = l;
        // l← Suivant(l)
        l = l->next;
        // Enfiler(f, p)
        enfiler(f, premierList->targetNode);
        // sup(p)←e
        acorasik->suppleance[premierList->targetNode] = e;
    }

    // tantque f est non vide faire
    while (f->suivant != NULL)
    {

        // r←Defiler(f)
        int r = defiler(f);
        // l← liste des transitions(r, a, p)
        l = remplirListTrans(acorasik->trie, r);
        // tantque l est non vide faire
        while (l != NULL)
        {
            List premierList;
            //(r, a, p)← Premier(l)
            premierList = l;
            // l← Suivant(l)
            l = l->next;
            // Enfiler(f, p)
            enfiler(f, premierList->targetNode);
            // s← sup(r)
            int s = acorasik->suppleance[premierList->startNode];

            // pour éviter les boucle infini.
            int cpt;
            // tantque δ(s, a) est non d´efinie faire
            while (existTransition(acorasik->trie, s, premierList->letter) == NULL)
            {
                // s← sup(s)
                s = acorasik->suppleance[s];
                cpt++;
                if (cpt > donnes_mots[0])
                    break;
            }
            // sup(p)←δ(s, a)
            List list_s_p = existTransition(acorasik->trie, s, premierList->letter);
            if (list_s_p != NULL)
                acorasik->suppleance[premierList->targetNode] = list_s_p->targetNode;
        }
    }
    // sortie(p)← sortie(p)∪ sortie(sup(p))
    for (int i = 0; i < donnes_mots[0]; i++)
    {
        int sup = acorasik->suppleance[i];
        if ((sup != -1) && (sup != 0) && (acorasik->trie->finite[sup] != '\0') && (acorasik->trie->finite[i] == '\0'))
        {
            acorasik->trie->finite[i] = 'X';
        }
    }
}

// exécuter l'algo d'Aho-Corasik
int *AC(unsigned char **X, int *donnees_mots)
{
    // la table des occurences
    int *occurence;
    occurence = calloc(donnees_mots[1], sizeof(int));

    // inisialiser Acorasik
    AhoCorasick acorasik = createAhoCorasick(donnees_mots);

    // préparation aho-corasik
    int e = pre_AC(acorasik, X, donnees_mots);
    // int TAILLE_MAX_TEXtE
    unsigned char texte[TAILLE_MAX_TEXTE];
    recuperer_texte(texte);

    int taille_texte = strlen((const char *)texte);
    // pour j ← 0 `a n − 1 faire
    for (int j = 0; j < taille_texte; j++)
    {
        // pour évitier la boucle infini
        int cpt = 0;
        // tantque δ(e, y[j]) est non d´efinie faire
        while (existTransition(acorasik->trie, e, texte[j]) == NULL)
        {
            // e ← sup(e)

            e = acorasik->suppleance[e];
            cpt++;
            if (cpt > donnees_mots[0])
                break;
        }
        List listTmp = existTransition(acorasik->trie, e, texte[j]);
        // e ← δ(e, y[j])
        if (listTmp != NULL)
            e = listTmp->targetNode;

        // si sortie(e)  ∅ alors
        if (acorasik->trie->finite[e] != '\0')
        {
            // reporter une occurrence des ´el´ements de sortie(e)
            // verifier tous les mots fini par
            for (int i = 0; i < donnees_mots[1]; i++)
            {
                unsigned char *mot = X[i];
                if (if_sortie(acorasik, mot, e) == 1)
                {
                    occurence[i] = occurence[i] + 1;
                }
            }
        }
    }
    // liberer l'espace mémoire de l'Aho-Corasik
    free_AhoCorasick(acorasik);
    // return la table d'occurence.
    return occurence;
}

// Liberer la memoire
void free_AhoCorasick(AhoCorasick acorasik)
{

    freeTrie(acorasik->trie);
    free(acorasik->suppleance);
    free(acorasik);
}

int main(int argc, char *argv[])
{

    printf("\nje suis le fichier du texte %s\n", argv[2]);
    printf("je suis le ficheir des mots %s\n", argv[1]);

    if (argc != 3)
        printf("nombre de paramètres incorrect :  mots.txt texte.txt");
    else
    {
        if (strcmp(argv[1], NOM_FICHIER_MOTS) != 0)
            printf(" le fichier des mots est manquant ");
        else if (strcmp(argv[2], NOM_FICHIER_TEXTE) != 0)
            printf("le fichierdu texte est manquant");
    }

    // la table de nos mots
    unsigned char *tab_mots[NBR_MAX_MOTS];
    int *donnees_mots = malloc(2 * sizeof(int));
    recuperer_mots(tab_mots, donnees_mots);

    // notre texte
    unsigned char texte[TAILLE_MAX_TEXTE];
    recuperer_texte(texte);


    printf("je suis toi ")  ;

    /*
            texte
            TAILLE_TEXTE
    */

    // récupere les occurence de chaque mot.
    int *occurence;
    // le nombre total des occurence.
    int total_occurence = 0;

    occurence = AC(tab_mots, donnees_mots);
    for (int i = 0; i < donnees_mots[1]; i++)
    {
        // printf("\n le mot %s a %d occurence dans le texte \n", tab_mots[i], occurence [i]);
        total_occurence = total_occurence + occurence[i];
    }
    printf("\n le nombre total d'occurence dans le texte est %d \n", total_occurence);

    // liberer l'espace des occurences
    free(occurence);
    // liberer l'espace mémoire de la table des mots
    for (int i = 0; i < donnees_mots[1]; i++)
    {
        free(tab_mots[i]);
    }

    // liberer l'espace mémoire de la table donne_mots
    free(donnees_mots);

    return EXIT_SUCCESS;
}

#include <stdio.h>
// #include <limits.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define TAILLE_MAX_TEXTE 500000
// c'est le nombre max des mots.
#define NBR_MAX_MOTS 100
#define TAILLE_MAX_LIGNE 128
#define NOM_FICHIER_MOTS "mots.txt"
#define NOM_FICHIER_TEXTE "texte.txt"

int lireMots(unsigned char **tab_mots, FILE *fichier_mots, int *donnees_mots)
{
    // la nombre des mots
    int taille_tab_mots = 0;
    // le nobre ax des nodes
    int nbr_max_node = 0;

    char ligne[TAILLE_MAX_LIGNE] = ""; // Chaine vide de taille TAILLE_MAX_MOT
    while (fgets(ligne, TAILLE_MAX_LIGNE, fichier_mots) != NULL)
    { // On lit maximum TAILLE_MAX_LIGNE caracteres du fichier, on stocke le tout dans "LIGNE".
        int taille_ligne = strlen(ligne);
        // cette boucle pour recuperer le mot dans la ligne.
        while (ligne[taille_ligne - 1] == '\n')
        {
            ligne[taille_ligne - 1] = '\0';
            taille_ligne--;
        }

        nbr_max_node += taille_ligne;
        // le nombre max des nods

        donnees_mots[0] = nbr_max_node;
        tab_mots[taille_tab_mots] = malloc(128 * sizeof(unsigned char));
        strcpy((char *)tab_mots[taille_tab_mots], ligne);
        taille_tab_mots++;
        // le nombre de mots
        donnees_mots[1] = taille_tab_mots;
    }

    return nbr_max_node;
}

//*******************************************************
// fonction pour lire une texte d'un fichier donne
void lireTexte(unsigned char *texte, FILE *fichier_texte)
{

    int taille_texte = 0;
    fgets((char *)texte, TAILLE_MAX_TEXTE + 1, fichier_texte);
    taille_texte = strlen((const char *)texte);

    printf("THE TEXTE %s", texte) ;

    // on elimune les \n dans le texte recuperer..
    while (texte[taille_texte - 1] == '\n')
    {
        texte[taille_texte - 1] = '\0';
        taille_texte--;
    }
}

//*******************************************************
// recuperer l'ensembles des mots e partir du fichier mots.txt
int recuperer_mots(unsigned char **tab_mots, int *donnee_mots)
{
    int nbr_node_max = 0;
    // la table des mots
    // on recupere la liste ensemble des mots.
    FILE *fichier_mots;

    fichier_mots = fopen(NOM_FICHIER_MOTS, "r"); // ouvrire le fichier mots.txt
    if (fichier_mots == NULL)
        printf("probleme ouverture fichier des mots\n");          
    nbr_node_max = lireMots(tab_mots, fichier_mots, donnee_mots); 
    fclose(fichier_mots);

    return nbr_node_max; // fermer le fichier mots.txt
}

//*******************************************************
// recuperer un texte e partir du fichier texte.txt
void recuperer_texte(unsigned char *texte)
{


    // on recupere le texte.
    FILE *fichier_texte ;
    printf("RECUPERER Texte");

    fichier_texte = fopen(NOM_FICHIER_TEXTE, "r"); // ouvrire le fichier texte.txt 
    printf("je fais quoi a ?");


    
    if (fichier_texte == NULL)
        printf("probleme ouverture fichier de texte \n "); 



    lireTexte(texte, fichier_texte);                       // recupere le texte et la taille de texte.

    fclose(fichier_texte); // fermer le fichier texte.txt

    printf("FIN TEXET");
}

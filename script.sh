# make
# ./genere-texte 50000 3 > texte3.txt
# ./genere-mots 10 5 25 3 > mots3.txt
# ./ac-matrice mots3.txt texte3.txt > res-ac-matrice
# ./ac-hachage mots3.txt texte3.txt > res-ac-hachage
# diff res-ac-matrice res-ac-hachage





# echo "je suis dans le script "
# gcc  ./code/genere-mots.c  -o genere-mots
# genere-mots  15 4 15 26 > mots.txt
# cat mots.txt










echo " je vais eecuter aho - corasick"
gcc ./code/ac-hashage.c -o ach
./ach mots.txt texte.txt

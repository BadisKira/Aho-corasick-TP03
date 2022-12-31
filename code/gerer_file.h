#ifndef FILE_H
#define FILE_H

typedef struct _element *File;
struct _element
{
    int etat;
    struct _element *suivant;
};

File creatFile();
void enfiler(File f, int e);
int defiler(File f);

#endif
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define LINE_LEN 1024
#define WORD_LEN 55

typedef struct _stablo{
    char* ime;
    
    struct _stablo* child;
    struct _stablo* sibling;
}Stablo;

typedef struct _stog{
    Stablo* UpperDirectory;

    struct _stog* next;
    struct _stog* previous;
}Stog;

Stablo* createNewStablo();
 Stablo* findLast(Stablo*);
int Menu(Stablo*, Stog*);
int makeDirectory(Stablo*);


int main()
{
    int status = 0;

    do{
        status = Menu(root, head);
    }while(!status);

    return 0;
}

Stablo* createNewStablo()
{
    Stablo* new = (Stablo*)malloc(sizeof(Stablo));
    new->ime = (char*)malloc(sizeof(char)*WORD_LEN);
    new->child = NULL;
    new->sibling = NULL;

    return new;
}

Stablo* findLast(Stablo* pocetak)
{
    Stablo* temp = pocetak->child;

    if(temp == NULL){
        Stablo* new = createNew();
        pocetak->child = new;
        return new;
    }

    else{
        while(temp->sibling != NULL)
            temp = temp->sibling;
        
        Stablo* new = createNew();
        temp->sibling = new;
        return new;
    }
}

int makeDirectory(Stablo* currentFile)
{
    Stablo* temp;
}
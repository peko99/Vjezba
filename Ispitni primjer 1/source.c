#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define WORD_LEN 55
#define LINE_LEN 1024

typedef struct _stablo{
    char* rijec;
    int duljina;

    struct _stablo* left;
    struct _stablo* right;
}Stablo;

Stablo* procitajDat(Stablo*, FILE*);
Stablo* insertSorted(Stablo*, char*);
int print(Stablo*);

int main()
{
    Stablo* root = NULL;
    char* filename = (char*)malloc(sizeof(char)*WORD_LEN);
    FILE* fp = NULL;

    printf("\nKoju datoteku zelite otvoriti?\n--> ");
    scanf("%s", filename);

    if(strchr(filename, '.') == 0)
        strcat(filename, ".txt");

    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("\nERROR! File could not open!");
        return -1;
    }
    
    root = procitajDat(root, fp);
    print(root);

    return 0;
}

Stablo* procitajDat(Stablo* root, FILE* fp)
{
    char* line = (char*)malloc(sizeof(char)*LINE_LEN);
    int n;
    char* word = (char*)malloc(sizeof(char)*WORD_LEN);

    fgets(line, LINE_LEN, fp);

    while(*line != 0){
        sscanf(line, "%s %n", word, &n);
        line += n;
        root = insertSorted(root, word);
    }

    return root;
}

Stablo* insertSorted(Stablo* root, char* word)
{
    if(root == NULL){
        root = (Stablo*)malloc(sizeof(Stablo));
        root->rijec = (char*)malloc(sizeof(char)*WORD_LEN);
        strcpy(root->rijec, word);
        root->duljina = strlen(root->rijec);
        root->left = NULL;
        root->right = NULL;
        
        return root;
    }

    else if(strcmp(root->rijec, word) > 0)
        root->left = insertSorted(root->left, word);

    else if(strcmp(root->rijec, word) < 0)
        root->right = insertSorted(root->right, word);

    else
        return root;    
}

int print(Stablo* root)
{
    if(root == NULL)
        return 0;

    print(root->left);
    printf("%s\t%d", root->rijec, root->duljina);
    print(root->right);

    return 0;
}
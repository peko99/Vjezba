#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define WORD_LEN 1024

typedef struct _stablo{
    char* word;

    struct _stablo *left;
    struct _stablo *right;
}Stablo;

Stablo* allocateTree();
int readFile(Stablo*);

int main()
{
    Stablo *root = NULL;

    return 0;
}

Stablo* allocateTree()
{
    Stablo* q = (Stablo*)malloc(sizeof(Stablo));
    q->word = (char*)malloc(sizeof(char)*WORD_LEN);
    q->left = NULL;
    q->right = NULL;

    return q;
}

int readFile(Stablo* root)
{
    char* filename = (char*)malloc(sizeof(char)*WORD_LEN);
    FILE* fp = NULL;

    printf("Which file do you want to read rom?\n--> ");
    scanf("%s", filename);
    if(strchr(filename, '.') == 0)
        strcat(filename, ".txt");
    
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("\nERROR! %s could not open!\n");
        return -1;
    }

    

    return 0;
}
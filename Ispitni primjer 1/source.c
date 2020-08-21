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
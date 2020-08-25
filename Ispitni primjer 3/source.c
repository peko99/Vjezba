#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define WORD_LEN 1024

typedef struct _stablo {
    char* word;

    struct _stablo* left;
    struct _stablo* right;
}Stablo;

Stablo* allocateTree();
Stablo* readFile(Stablo*);
Stablo* insertTree(Stablo*, Stablo*);
int inorderPrint(Stablo*);
int treeToFiles(Stablo*);
int pushToFiles(Stablo*, FILE*, FILE*);

int main()
{
    Stablo* root = NULL;

    root = readFile(root);    
    inorderPrint(root);

    treeToFiles(root);

    return 0;
}

Stablo* allocateTree()
{
    Stablo* q = (Stablo*)malloc(sizeof(Stablo));
    q->word = (char*)malloc(sizeof(char) * WORD_LEN);
    q->left = NULL;
    q->right = NULL;

    return q;
}

Stablo* readFile(Stablo* root)
{
    char* filename = (char*)malloc(sizeof(char) * WORD_LEN);
    FILE* fp = NULL;

    printf("Which file do you want to read rom?\n--> ");
    scanf("%s", filename);
    if (strchr(filename, '.') == 0)
        strcat(filename, ".txt");

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("\nERROR! %s could not open!\n");
        return NULL;
    }

    while (!feof(fp)) {
        Stablo* umetni = allocateTree();
        fscanf(fp, "%s", umetni->word);
        root = insertTree(root, umetni);
    }

    fclose(fp);
    return root;
}

Stablo* insertTree(Stablo* root, Stablo* umetni)
{
    if (root == NULL)
        return umetni;

    else if (strcmp(root->word, umetni->word) > 0)
        root->left = insertTree(root->left, umetni);

    else if (strcmp(root->word, umetni->word) < 0)
        root->right = insertTree(root->right, umetni);

    return root;
}

int inorderPrint(Stablo* root)
{
    if (root == NULL)
        return 0;

    inorderPrint(root->left);
    printf("%s ", root->word);
    inorderPrint(root->right);

    return 0;
}

int treeToFiles(Stablo* root)
{
    FILE* fp1 = NULL;
    FILE* fp2 = NULL;

    fp1 = fopen("output1.txt", "w");
    fp2 = fopen("output2.txt", "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("\nERROR Opening output files!\n");
        return -3;
    }

    pushToFiles(root, fp1, fp2);

    fclose(fp1);
    fclose(fp2);
    return 0;
}

int pushToFiles(Stablo* root, FILE* fp1, FILE* fp2)
{
    if (root == NULL)
        return 0;

    pushToFiles(root->left, fp1, fp2);
    if (root->word[0] == 'a' || root->word[0] == 'e' || root->word[0] == 'i' || root->word[0] == 'o' || root->word[0] == 'u')
        fprintf(fp1, "%s\n", root->word);
    else
        fprintf(fp2, "%s\n", root->word);
    pushToFiles(root->right, fp1, fp2);

    return 0;
}
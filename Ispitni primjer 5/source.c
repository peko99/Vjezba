#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct _student {
    char ime[128];
    char prezime[128];
    int broj_bodova;
    float relativni_bodovi;

    struct _student* left;
    struct _student* right;
}Student;

Student* readFile(Student*);
Student* insertInTree(Student*, Student*);
int preorderPrint(Student*);
int findMax(Student*);
int addRelative(Student*, int);

int main()
{
    Student* root = NULL;
    int max;

    root = readFile(root);
    max = findMax(root);
    addRelative(root, max);

    printf("IME         PREZIME          BODOVI     RELATIVNI BODOVI\n");
    preorderPrint(root);

    return 0;
}

Student* readFile(Student* root)
{
    FILE* fp = NULL;
    fp = fopen("popis.txt", "r");
    if (fp == NULL) {
        printf("\nERROR! File could not open!\n");
        return NULL;
    }

    while (!feof(fp)) {
        Student* q = (Student*)malloc(sizeof(Student));
        q->left = NULL;
        q->right = NULL;
        fscanf(fp, "%s %s %d", q->ime, q->prezime, &q->broj_bodova);
        root = insertInTree(root, q);
    }

    return root;
}

Student* insertInTree(Student* root, Student* q)
{
    if (root == NULL)
        return q;

    else if (root->broj_bodova > q->broj_bodova)
        root->left = insertInTree(root->left, q);

    else
        root->right = insertInTree(root->right, q);

    return root;
}

int preorderPrint(Student* root)
{
    if (root == NULL)
        return 0;

    printf("%-12s%-12s\t%d\t%lf\n", root->ime, root->prezime, root->broj_bodova, root->relativni_bodovi);
    preorderPrint(root->left);
    preorderPrint(root->right);

    return 0;
}

int findMax(Student* root)
{
    if (root->right == NULL)
        return root->broj_bodova;

    findMax(root->right);
}

int addRelative(Student* root, int max)
{
    if (root == NULL)
        return 0;

    root->relativni_bodovi = (float)root->broj_bodova / max;

    addRelative(root->left, max);
    addRelative(root->right, max );

    return 0;
}
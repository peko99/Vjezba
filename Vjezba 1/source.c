#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define WORD_LEN 55
#define LINE_LEN 1024

typedef struct _student{
    char ime[WORD_LEN];
    char prezime[WORD_LEN];
    int bodovi_aps;
    float bodovi_rel;

}Student;

int countRows(char*);
int readFile(char*, Student*, int);
int printList(Student*, int);
int findMax(Student*, int);
int relative(Student*, int, int);

int main()
{
    Student* s;
    int n, max;
    char* filename;
    filename = (char*)malloc(sizeof(char) * WORD_LEN);

    printf("\nUnesite ime vase datoteke:\n--> ");
    scanf("%s", filename);

    n = countRows(filename);

    s = (Student*)malloc(sizeof(Student) * n);

    readFile(filename, s, n);
    max = findMax(s, n);
    relative(s, n, max);
    printList(s, n);

    return 0;
}

int countRows(char* filename)
{
    int n = 0;
    char* line = (char*)malloc(sizeof(char) * LINE_LEN);

    FILE* fp = NULL;
    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("\nFATAL ERROR! File %s could not open!\n", filename);
        return -1;
    }

    while(!feof(fp)){
        fgets(line, LINE_LEN, fp);
        n++;
    }

    fclose(fp);
    return n;
}

int readFile(char* filename, Student* s, int n)
{
    int i = 0, k;
    char* line, *buffer;
    line = (char*)malloc(sizeof(char) * LINE_LEN);
    buffer = (char*)malloc(sizeof(char) * LINE_LEN);
    FILE* fp = NULL;

    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("\nFATAL ERROR! File could not open!");
        return -1;
    }

    while(!feof(fp)){
        fgets(buffer, LINE_LEN, fp);
        line = buffer;

        while(*line != 0){
            sscanf(line, "%d %n", &s[i].bodovi_aps, &k);
            line += k;
            sscanf(line, "%s %n", s[i].ime, &k);
            line += k;
            sscanf(line, "%s %n", s[i].prezime, &k);
            line += k;
            i++;
        }

    }

    return 0;
}

int printList(Student* s, int n)
{
    int i;

    printf("IME\t\tPREZIME\t\tBODOVI APS\t\tBODOVI REL\n");
    for(i=0; i<n; i++){
        printf("%-13s\t%-17s\t%-10d\t%-10lf\n", s[i].ime, s[i].prezime, s[i].bodovi_aps, s[i].bodovi_rel);
    }

    return 0;
}

int findMax(Student* s, int n)
{
    int i, max;

    max = s[0].bodovi_aps;

    for(i = 1; i < n; i++){
        if(s[i].bodovi_aps > max)
            max = s[i].bodovi_aps;
    }

    return max;
}

int relative(Student* s, int n, int max)
{
    int i;

    for(i = 0; i < n; i++){
        s[i].bodovi_rel = (float)s[i].bodovi_aps/max*100;
    }

    return 0;
}
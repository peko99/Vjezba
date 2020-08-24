#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define WORD_LEN 1024

typedef struct _element {
    char* rijec;
    int priority;

    struct _element* next;
}Element;

Element* createNew();
Element* readFile(Element*);
int getPriority(char*);
Element* sortByPriority(Element*, Element*);
int printList(Element*);
int listToFiles(Element*);
Element* createList(Element*, Element*);
int createFile(Element*, FILE*);

int main()
{
    Element* head = createNew();

    head = readFile(head);

    printList(head);

    listToFiles(head);

    return 0;
}

Element* createNew()
{
    Element* new = (Element*)malloc(sizeof(Element));
    new->rijec = (char*)malloc(sizeof(char) * WORD_LEN);
    new->next = NULL;

    return new;
}

Element* readFile(Element* head)
{
    FILE* fp = NULL;
    char* filename = (char*)malloc(sizeof(char) * WORD_LEN);

    printf("Which file do you want to open?\n--> ");
    scanf("%s", filename);

    if (strchr(filename, '.') == 0)
      strcat(filename, ".txt");

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("\nERROR! File %s could not open!\n", filename);
        return NULL;
    }

    while (!feof(fp)) {
        Element* new = createNew();
        fscanf(fp, "%s", new->rijec);
        new->priority = getPriority(new->rijec);
        head = sortByPriority(head, new);
    }

    fclose(fp);
    return head;
}

int getPriority(char* word)
{
    char letter;
    letter = toupper(word[0]);

    if (letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U')
        return 1;

    else
        return 2;
}

Element* sortByPriority(Element* head, Element* new)
{

    if (head->next == NULL) {
        head->next = new;
        return head;
    }

    else {
        if (new->priority == 1) {
            new->next = head->next;
            head->next = new;
            return head;
        }

        else {
            Element* temp;
            temp = head->next;

            while (temp->next != NULL && temp->next->priority == 1)
                temp = temp->next;

            new->next = temp->next;
            temp->next = new;

            return head;
        }
    }
}

int printList(Element* head)
{
    if (head->next == NULL) {
        printf("\nPrazna lista.\n");
        return -1;
    }

    Element* temp = head->next;
    while (temp != NULL) {
        printf("%-15s\t", temp->rijec);
        temp = temp->next;
    }

    return 0;
}

int listToFiles(Element* head)
{
    FILE* fp1 = NULL;
    FILE* fp2 = NULL;

    Element* head1 = createNew();
    Element* head2 = createNew();

    fp1 = fopen("output1.txt", "w");
    fp2 = fopen("output2.txt", "w");

    if (fp1 == NULL) {
        printf("\nERROR! Could not open output1.txt");
        return -3;
    }
    if (fp2 == NULL) {
        printf("\nERROR! Could not open output2.txt");
        return -3;
    }

    Element* temp = head->next;
    while (temp->priority == 1) {
        head1 = createList(head1, temp);
        temp = temp->next;
    }
    while (temp != NULL) {
        head2 = createList(head2, temp);
        temp = temp->next;
    }

    createFile(head1, fp1);
    createFile(head2, fp2);

    fclose(fp1);
    fclose(fp2);

    return 0;
}

Element* createList(Element* head, Element* new)
{
    if (head->next == NULL) {
        Element* novi = createNew();
        strcpy(novi->rijec, new->rijec);
        novi->priority = new->priority;
        head->next = novi;
        return head;
    }

    Element* temp = head->next;

    if (temp->rijec[0] > new->rijec[0]) {
        Element* novi = createNew();
        strcpy(novi->rijec, new->rijec);
        novi->priority = new->priority;
        novi->next = head->next;
        head->next = novi;
        return head;
    }

    else if(temp->rijec[0] < new->rijec[0]){
        Element* previous = head;
        while (temp != NULL && temp->rijec[0] < new->rijec[0]) {
            previous = previous->next;
            temp = temp->next;
        }
        
        if (temp != NULL && temp->rijec[0] == new->rijec[0]) {
            int i = 1;
            while (i < WORD_LEN) {
                if (temp->rijec[i] > new->rijec[i]) {
                    Element* novi = createNew();
                    strcpy(novi->rijec, new->rijec);
                    novi->priority = new->priority;
                    previous->next = novi;
                    novi->next = temp;
                    return head;
                }
                else if (temp->rijec[i] < new->rijec[i]) {
                    Element* novi = createNew();
                    strcpy(novi->rijec, new->rijec);
                    novi->priority = new->priority;
                    novi->next = temp->next;
                    temp->next = novi;
                    return head;
                }
                else
                    i++;
            }
        }

        else {
            Element* novi = createNew();
            strcpy(novi->rijec, new->rijec);
            novi->priority = new->priority;
            previous->next = novi;
            novi->next = temp;

            return head;
        }
    }

    else {
        int i = 1;
        while (i < WORD_LEN) {
            if (temp->rijec[i] > new->rijec[i]) {
                Element* novi = createNew();
                strcpy(novi->rijec, new->rijec);
                novi->priority = new->priority;
                head->next = novi;
                novi->next = temp;
                return head;
            }
            else if (temp->rijec[i] < new->rijec[i]) {
                while (temp ->next != NULL && temp->rijec[i] == temp->next->rijec[i])
                    temp = temp->next;
                Element* novi = createNew();
                strcpy(novi->rijec, new->rijec);
                novi->priority = new->priority;
                novi->next = temp->next;
                temp->next = novi;
                return head;
            }
            else
                i++;
        }
    }

    return head;
}

int createFile(Element* head, FILE* fp)
{
    if (head->next == NULL) {
        printf("\nERROR! Empty list!");
        return -3;
    }
    Element* temp = head->next;

    fprintf(fp, "Abecedna lista\n");

    while (temp != NULL) {
        fprintf(fp, "%-15s\t%d\n", temp->rijec, temp->priority);
        temp = temp->next;
    }
    
    return 0;
}
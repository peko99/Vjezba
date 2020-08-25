#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define WORD_LEN 55
#define LINE_LEN 1024

typedef struct _student {
    char* sifra_studenta;
    char* ime;
    char* prezime;
    char* sifra_ispita;
    struct _student* next;
}Student;

typedef struct _ispit {
    char* sifra_ispita;
    char* naziv;

    struct _ispit* next;
}Ispit;

Student* allocateStudent();
Ispit* allocateIspit();
int readFiles(Student*, Ispit*);
Student* insertStudent(Student*, Student*);
Ispit* insertIspit(Ispit*, Ispit*);
int printStudents(Student*);
int printIspiti(Ispit*);
Student* poloziliIspit(Student*, Ispit*, char*);
Student* createList(Student*, Student*, char*);
int deleteList(Student*);

int main()
{
    Student* Shead = allocateStudent();
    Student* pomocna = allocateStudent();
    Ispit* Ihead = allocateIspit();
    char* kolegij = (char*)malloc(sizeof(char) * WORD_LEN);

    readFiles(Shead, Ihead);

    do {
        printf("\nUnesite naziv kolegija\n--> ");
        scanf("%s", kolegij);
        pomocna = poloziliIspit(Shead, Ihead, kolegij);
        printf("\nStudenti koji su polozili ispit %s\n", kolegij);
        printStudents(pomocna);
        deleteList(pomocna);
    } while (strcmp(kolegij, "izlaz") != 0);

    return 0;
}

Student* allocateStudent()
{
    Student* q = (Student*)malloc(sizeof(Student));
    q->sifra_studenta = (char*)malloc(sizeof(char) * WORD_LEN);
    q->ime = (char*)malloc(sizeof(char) * WORD_LEN);
    q->prezime = (char*)malloc(sizeof(char) * WORD_LEN);
    q->sifra_ispita = (char*)malloc(sizeof(char) * WORD_LEN);
    q->next = NULL;

    return q;
}

Ispit* allocateIspit()
{
    Ispit* q = (Ispit*)malloc(sizeof(Ispit));
    q->sifra_ispita = (char*)malloc(sizeof(char) * WORD_LEN);
    q->naziv = (char*)malloc(sizeof(char) * WORD_LEN);
    q->next = NULL;

    return q;
}

int readFiles(Student* Shead, Ispit* Ihead)
{
    FILE* fp1 = NULL;
    FILE* fp2 = NULL;

    fp1 = fopen("studenti.txt", "r");
    fp2 = fopen("ispiti.txt", "r");

    if (fp1 == NULL || fp2 == NULL) {
        printf("ERROR!\nFiles could not open!\n");
        return -3;
    }

    while (!feof(fp1)) {
        Student* q = allocateStudent();
        fscanf(fp1, "%s %s %s %s", q->sifra_studenta, q->ime, q->prezime, q->sifra_ispita);
        Shead = insertStudent(Shead, q);
    }

    while (!feof(fp2)) {
        Ispit* q = allocateIspit();
        fscanf(fp2, "%s %s", q->sifra_ispita, q->naziv);
        Ihead = insertIspit(Ihead, q);
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}

Student* insertStudent(Student* head, Student* q)
{
    q->next = head->next;
    head->next = q;

    return head;
}

Ispit* insertIspit(Ispit* head, Ispit* q)
{
    q->next = head->next;
    head->next = q;

    return head;
}

int printStudents(Student* head) {
    if (head == NULL) {
        printf("\nKrivi naziv kolegija!\n");
        return 2;
    }

    if (head->next == NULL) {
        printf("Prazna lista!\n");
        return -1;
    }

    printf("IME       PREZIME   SIFRA STUDENTA\tSIFRA ISPITA\n");
    Student* temp = head->next;
    while (temp != NULL) {
        printf("%-10s%-10s%-10s\t\t%-10s\n", temp->ime, temp->prezime, temp->sifra_studenta, temp->sifra_ispita);
        temp = temp->next;
    }

    return 0;
}

int printIspiti(Ispit* head)
{
    if (head == NULL) {
        printf("\nERROR! Krivi naziv kolegija!\n");
        return 2;
    }

    if (head->next == NULL) {
        printf("Prazna lista!\n");
        return -1;
    }

    printf("NAZIV\t\tSIFRA ISPITA\n");
    Ispit* temp = head->next;
    while (temp != NULL) {
        printf("%-10s\t%-10s\n", temp->naziv, temp->sifra_ispita);
        temp = temp->next;
    }

    return 0;
}

Student* poloziliIspit(Student* Shead, Ispit* Ihead, char* kolegij)
{
    Student* head = allocateStudent();
    Ispit *temp;
    char* sifra = (char*)malloc(sizeof(char) * WORD_LEN);
    if (Ihead->next == NULL) {
        printf("\nERROR Emty list!\n");
        return NULL;
    }
    temp = Ihead->next;
    while (temp != NULL && (strcmp(temp->naziv, kolegij) != 0)) {
        temp = temp->next;
    }
    if (temp == NULL) {
        return NULL;
    }

    strcpy(sifra, temp->sifra_ispita);
    head = createList(head, Shead, sifra);

    return head;
}

Student* createList(Student* head, Student* Shead, char* sifra)
{
    if (Shead->next == NULL) {
        printf("\nERROR Empty list!");
        return NULL;
    }
    Student* temp = Shead->next;

    while (temp != NULL) {
        if (strcmp(temp->sifra_ispita, sifra) == 0) {
            Student* q = allocateStudent();
            strcpy(q->ime, temp->ime);
            strcpy(q->prezime, temp->prezime);
            strcpy(q->sifra_ispita, temp->sifra_ispita);
            strcpy(q->sifra_studenta, temp->sifra_studenta);
            q->next = head->next;
            head->next = q;

            temp = temp->next;
        }
        else
            temp = temp->next;
    }

    return head;
}

int deleteList(Student* head)
{
    if (head == NULL)
        return 0;

    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    Student* temp = head->next;
    Student* brisi = head;

    while (temp != NULL) {
        free(brisi);
        brisi = temp;
        temp = temp->next;
    }
    free(brisi);

    return 0;
}

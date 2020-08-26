#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define WORD_LEN 55

typedef struct _student {
	char* name;
	char* lastname;
	int grade;

	struct _student* next;
}Student;

Student* allocateStudent();
Student* readFile(Student*, char*);
int printList(Student*);
Student* passedAll(Student*, Student*, Student*, Student*);
Student* deleteDuplicates(Student*);

int main()
{
	Student* head1 = allocateStudent();
	Student* head2 = allocateStudent();
	Student* head3 = allocateStudent();
	Student* temp = allocateStudent();

	head1 = readFile(head1, "predmet1.txt");
	head2 = readFile(head2, "predmet2.txt");
	head3 = readFile(head3, "predmet3.txt");

	printf("Lista 1:\nIME            PREZIME        OCJENA\n\n");
	printList(head1);
	printf("\n\nLista 2:\nIME            PREZIME        OCJENA\n\n");
	printList(head2);
	printf("\n\nLista 3:\nIME            PREZIME        OCJENA\n\n");
	printList(head3);
	


	return 0;
}

Student* allocateStudent()
{
	Student* q = (Student*)malloc(sizeof(Student));
	q->name = (char*)malloc(sizeof(char) * WORD_LEN);
	q->lastname = (char*)malloc(sizeof(char) * WORD_LEN);
	q->next = NULL;

	return q;
}

Student* readFile(Student* head, char* filename)
{
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("ERROR! File %s could not open!\n", filename);
		return NULL;
	}

	while (!feof(fp)) {
		Student* new = allocateStudent();
		fscanf(fp, "%s %s %d", new->name, new->lastname, &new->grade);
		new->next = head->next;
		head->next = new;
	}

	fclose(fp);
	return head;
}

int printList(Student* head)
{
	if (head->next == NULL) {
		printf("\nERROR! Empty list!\n");
		return -1;
	}

	Student* temp = head->next;
	while (temp != NULL) {
		printf("%-15s%-15s\t%d\n", temp->name, temp->lastname, temp->grade);
		temp = temp->next;
	}

	return 0;
}
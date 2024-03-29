#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct  MusicalComposition{
	char name[80];
	char author[80];
	int year;
	struct MusicalComposition* next;
	struct MusicalComposition* last;
}MusicalComposition;

// Описание структуры MusicalComposition


// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* autor,int year);

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n);

void push(MusicalComposition* head, MusicalComposition* element);

void removeEl(MusicalComposition* head, char* name_for_remove);

int count(MusicalComposition* head);

void print_names(MusicalComposition* head);


int main(){
	int length;
	scanf("%d\n", &length);

	char** names = (char**)malloc(sizeof(char*)*length);
	char** authors = (char**)malloc(sizeof(char*)*length);
	int* years = (int*)malloc(sizeof(int)*length);

	for (int i=0;i<length;i++)
	{
		char name[80];
		char author[80];

		fgets(name, 80, stdin);
		fgets(author, 80, stdin);
		fscanf(stdin, "%d\n", &years[i]);

		(*strstr(name,"\n"))=0;
		(*strstr(author,"\n"))=0;

		names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
		authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

		strcpy(names[i], name);
		strcpy(authors[i], author);

	}
	MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
	char name_for_push[80];
	char author_for_push[80];
	int year_for_push;

	char name_for_remove[80];

	fgets(name_for_push, 80, stdin);
	fgets(author_for_push, 80, stdin);
	fscanf(stdin, "%d\n", &year_for_push);
	(*strstr(name_for_push,"\n"))=0;
	(*strstr(author_for_push,"\n"))=0;

	MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

	fgets(name_for_remove, 80, stdin);
	(*strstr(name_for_remove,"\n"))=0;

	printf("%s %s %d\n", head->name, head->author, head->year);
	int k = count(head);

	printf("%d\n", k);
	push(head, element_for_push);

	k = count(head);
	printf("%d\n", k);

	removeEl(head, name_for_remove);
	print_names(head);

	k = count(head);
	printf("%d\n", k);

	for (int i=0;i<length;i++){
		free(names[i]);
		free(authors[i]);
	}
	free(names);
	free(authors);
	free(years);

	return 0;

}
MusicalComposition* createMusicalComposition(char* name, char* author, int year){
	MusicalComposition* new_music =malloc(sizeof(MusicalComposition));
	strcpy(new_music->name,name);
	strcpy(new_music->author,author);
	new_music->year=year;
	new_music->next=NULL;
	new_music->last=NULL;
	return new_music;
}
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
	MusicalComposition *head = createMusicalComposition(array_names[0],array_authors[0],array_years[0]);
	head->last = NULL;
	for (int i = 1; i < n; i++) {
		MusicalComposition* tmp = createMusicalComposition(array_names[i],array_authors[i],array_years[i]);
		push(head,tmp);
	}
	return head;
}

int count(MusicalComposition*  head){
	int count=0;
	for (MusicalComposition* i = head; i!=NULL ; i=i->next) {
		count++;
	}
	return count;
}

void push(MusicalComposition*  head, MusicalComposition* element){
	while(head->next!=NULL){
		head=head->next;
	}
	head->next=element;
	element->next=NULL;
	element->last=head;

}
void print_names(MusicalComposition*  head){
	//int c = count(head);
	for (MusicalComposition* i = head; i!=NULL ; i=i->next) {
		printf("%s\n",i->name);
	}
}
void removeEl (MusicalComposition*  head, char* name_for_remove){
	for (MusicalComposition* i = head; i!=NULL ; i=i->next) {
		if(strcmp(i->name,name_for_remove)==0){
			i->last->next=i->next;
			i->next->last=i->last;
		}

	}
}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define BUFFER_SIZE 100

//функция считывания предложения, сделали буфер, изначально выделили память и считываем предложение посимвольно.
char *read_sentence() {
	int buffer = BUFFER_SIZE;
	char* sentence = malloc(buffer * sizeof(char));
	int len_of_sentence = 0;
	char symbol;
	int nachalo = 1;
	do {
		symbol = (char)getchar();//считали текст посимвольно, затем проверили, хватает ли памяти для считывания инфы, перевыделили, приведение getchar к типу char для избежания варнинга
		if (nachalo == 1) {
			if (symbol == ' '||symbol=='.'||symbol==',') {
				continue;
			} else {
				nachalo = 0;
			}
		}
		sentence[len_of_sentence++] = symbol;
		if (len_of_sentence == buffer) {
			buffer += BUFFER_SIZE;
			sentence = realloc(sentence, buffer);
		}
	} while (symbol != '.' && symbol !='\n');
	sentence[len_of_sentence] = '\0';
	return sentence;
}

//Функция, которая собирает полученные предложения в один текст, пока не встретит enter на вводе.
char **collect_text(int *count_of_sentence) {
	int buffer = BUFFER_SIZE;
	char **text = malloc(buffer * sizeof(char *));
	int count = 0;
	char *sentence;
	while (1) {
		sentence = read_sentence();
		if (sentence[0] == '\n') {
			break;
		}
		text[count++] = sentence;

		if (count == buffer) {
			buffer += BUFFER_SIZE;
			text = realloc(text, buffer * sizeof(char *));
		}
	}
	*count_of_sentence = count;
	return text;
}
char** null_repeat(char** text, int* count){//функция, удаляющая предложения, если они равны null
	for (int i = 0; i < *count; i++) {
		if (text[i]==NULL){
			memmove(text+i, text+i+1, (*count-i)*sizeof (char*));
			i--;
			(*count)--;

		}

	}
	return text;
}
void delete_repeats(char **text, int *count) {//принимаем текст на вход, если предложения равны, то делаем равным NULL и удаляем предложения.
	char* snt1;
	char* snt2;
	for(int i = 0; i < *count; i++) {
		for(int j = i+1; j < *count; j++) {
			snt1 = text[i];
			snt2 = text[j];
			if(snt1!=NULL && snt2!=NULL) {
				if(strcasecmp(snt1,snt2)==0) {
					free(text[j]);
					text[j] = NULL;
				}
			}
		}
	}
	text = null_repeat(text,count);

}

int is_separator(char x) {//функция, которая проверяет, разделитель ли символ
	return x == ' ' || x == '.' || x == ',';
}

void replace_bomb(char **text,int size) {
	char *bomb = "bomb";
	char *def = "defused";
	char *p;
	unsigned int len; //беззнаковое, т.к. strlen возвращает беззнаковый тип
	for (int i = 0; i < size; i++) {
		p = strstr(text[i], bomb);
		while (p) {
			if (is_separator(*(p + 4)) && (is_separator(*(p - 1)) || p == text[i])) {
				len = strlen(text[i]);
				memmove(p + strlen(def), p + strlen(bomb), strlen(text[i])-(p-text[i])-strlen(bomb));
				memmove(p, def, strlen(def));
				text[i][len + 3] = '\0';
			}
			p = strstr(p+1 , bomb);
		}
	}
}

void delete_enemy_sentence(char **text, int *size) {
	char* enemy1 = "enemy";
	char* enemy2 = "enemy.";
	char* snt;
	char* istr;
	char* sep = "., ";
	int count;
	int index = 0;
	for(int i = 0; i < *size; i++) {
		count = 0;
		snt = malloc((strlen(text[i])+1)*sizeof(char));
		strcpy(snt,text[i]);
		istr = strtok(snt,sep);
		while(istr!=NULL) {
			if(strcmp(istr,enemy1)==0 || strcmp(istr,enemy2)==0) {
				count++;
			}
			istr = strtok(NULL,sep);
		}
		if(count>1) {
			free(text[i]);
			text[i] = NULL;
		}
	}

	text = null_repeat(text, size);
}
void count_students(char **text, int count) {
	int count_stud;
	char *stud = "student";
	char* start = "\x1b[31m";
	char* end = "\x1b[0m";
	for (int i = 0; i < count; i++) {
		count_stud = 0;
		char *prev = text[i];
		char *p = strstr(text[i], stud);
		while (p != NULL) {
			if (is_separator(*(p + 7)) && (p == text[i] || is_separator(*(p - 1)))) {
				count_stud++;
				for (char *j = prev; j < p; j++) {//посимвольно выводим текст, если встречаем отдельное слово student, то ставим перед ним и после код для окрашивания текста в консоли.
					printf("%c", j[0]);
				}
				printf("%sstudent%s",start,end);
				prev = p + 7;
				p = strstr(prev, stud);
			}
			else {
				for (char *j = prev; j < p; j++) {
					printf("%c", j[0]);
				}
				printf("student");
				prev = p + 7;
				p = strstr(prev, stud);
			}
		}
		p = text[i] + strlen(text[i]);
		for (char *j = prev; j < p; j++) {
			printf("%c", j[0]);
		}


		printf(" Count of words - %d\n", count_stud);
	}
}

int len_number(int x) {//функция для подсчета количиства симвловов для записи числа.
	int count = 0;
	if (x < 0) {
		count++;
	}
	while (x) {
		x = x / 10;
		count++;
	}
	return count;
}

int max_number(char *sentence) {//находим максимальное число в предложении
	int max = INT_MIN;
	char *str_copy = malloc(sizeof(char) * strlen(sentence));
	strncpy(str_copy, sentence, strlen(sentence));
	char *pch = strtok(str_copy, " ,.");
	while (pch != NULL) {
		int val = atoi(pch);
		if (strlen(pch) == len_number(val)) {
			if (val > max) {
				max = val;
			}
		}
		pch = strtok(NULL, " ,.");
	}
	if (max == INT_MIN) {
		max = 0;
	}
	return max;
}

int comp(const void *text1, const void *text2) {
	return max_number(*(char **) text2) - max_number(*(char **) text1);
}

void sort_text(char **text, int count) {//функция сортировки текста по уменьшению максимального числа.
	qsort(text, count, sizeof(char *), comp);
}

int main() {
	int count_of_sentence;
	char **new_text;
	printf("Hello! Enter your text for processing.\n");
	new_text = collect_text(&count_of_sentence);
	delete_repeats(new_text, &count_of_sentence);
	printf("Your text with deleted duplicate sentences:\n");
	for (int i = 0; i < count_of_sentence; i++) {
		puts(new_text[i]);
	}
	printf("\nSelect a number to perform the function:\n");
	printf("1. In each sentence, replace all the words <bomb> with “defused”.\n");
	printf("2. For each sentence, count the number of words “student” and display the number of counted words and the sentence itself by highlighting the words “student” in red.\n");
	printf("3. Delete all sentences in which the word “enemy” occurs more than once.\n");
	printf("4. Sort suggestions to reduce the maximum number in a row. A number is a word consisting only of digits. If there is no number in the sentence, then for such a number, the value of the maximum number is 0.\n");
	printf("0. Exit the program.\n");
	int x = getchar();
	switch (x) {
		case '0':
			printf("End of programm!");
			break;
		case '1':
			replace_bomb(new_text, count_of_sentence);
			for (int i = 0; i < count_of_sentence; i++) {
				puts(new_text[i]);
			}
			break;
		case '2':
			count_students(new_text, count_of_sentence);
			break;
		case '3':
			delete_enemy_sentence(new_text, &count_of_sentence);
			for (int i = 0; i < count_of_sentence; i++) {
				puts(new_text[i]);
			}
			break;
		case '4':
			sort_text(new_text, count_of_sentence);
			for (int i = 0; i < count_of_sentence; i++) {
				puts(new_text[i]);
			}
			break;
		default:
			printf("Enter the correct value!\n");
	}
	for (int i = 0; i < count_of_sentence; i++) {
		free(new_text[i]);
	}
	free(new_text);
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#define TEXT_SIZE 100
//чтение предложения
char* read_sentence(){
    int size = TEXT_SIZE;
    char *sentence = malloc(size*sizeof(char));
    int sentence_len = 0;
    int symbol = getchar();
    if (symbol == '\n' || symbol=='\t'||symbol==' ');
    else{
        sentence[sentence_len++]=symbol;
    }



    do{
        symbol = getchar();
        sentence[sentence_len++]=symbol;
        if(sentence_len==size){
            size+=TEXT_SIZE;
            sentence= realloc(sentence,size);
        }
    }while(symbol!='!'&& symbol!='.' &&symbol!=';'&& symbol!='?');
    sentence[sentence_len]='\0';
    return sentence;
}

//количество заглавных символов в предложении, больше 1 - false, меньше - true
int count_upper_cymbols(char *sentence){
    int count = 0;
    for(int i=0; i< strlen(sentence); i++){
        if(isupper(sentence[i])){
            count++;
        }
    }
    if (count>1){
        return 0;
    }else{
        return 1;
    }
}

int main(){
    int text_size= TEXT_SIZE;
    char** text = malloc(text_size*sizeof(char*));
    char* end_of_text = "Dragon flew away!";
    char* sentence;
    int count_sentence = 0;
    int count_deleaded_sentences = 0;


    do {
        sentence= read_sentence();
        if(count_upper_cymbols(sentence)){
            text[count_sentence++]=sentence;

        }else{
            count_deleaded_sentences+=1;

        }
        if(count_sentence==text_size){
            text_size+=TEXT_SIZE;
            text =realloc(text,text_size*sizeof (char*));

        }
    } while (strcmp(sentence,end_of_text)!=0);

    for (int i = 0; i < count_sentence; i++) {
        puts(text[i]);
        free(text[i]);
    }
    free(text);
    printf("Количество предложений до %d и количество предложений после %d",count_sentence+count_deleaded_sentences-1,count_sentence-1);

    return 0;
}
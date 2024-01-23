#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include  <string.h>


typedef struct file_array{
    char** text;
    int count;
    int buffer;
} file_array;

void check_directory(file_array* array, char* path){
    DIR *dir = opendir(path);
    if(dir){
        struct dirent * de = readdir(dir);
        while(de){
            if(strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0){
                char path_to_file[200];
                snprintf(path_to_file,200,"%s%s",path,de->d_name);
                if(strstr(de->d_name,".txt")!=NULL){
                    FILE *file = fopen(path_to_file,"r");
                    if(file){
                        char info[30];
                        fgets(info,30,file);
                        char * pos;
                        if((pos= strchr(info,'\n'))!=NULL){
                            *pos = '\0';
                        }
                        array->text[array->count]= malloc(sizeof (char)*(strlen(info)+1));
                        strncpy(array->text[array->count], info, strlen(info)+1);
                        array->count++;
                        if(array->count>=array->buffer){
                            array->buffer+=10;
                            array->text= realloc(array->text,array->buffer*sizeof (char*));
                        }
                        fclose(file);
                    }
                }
                else{
                    strcat(path_to_file,"/");
                    check_directory(array,path_to_file);
                }
            }
            de = readdir(dir);
        }

    }
    closedir(dir);
}
int comp(const void* s1, const void* s2){
    s1 = *(char** )s1;
    s2 = *(char **)s2;

    int num1 = atoi(s1);
    int num2 = atoi(s2);
    if(num1>num2){
        return 1;
    }
    else if(num1<num2){
        return -1;
    }
    else{
        return 0;
    }
}
void sort(file_array *array){
    qsort(array->text, array->count,sizeof(char*), comp);
}
void print_in_file(file_array * array){
    FILE * fl = fopen("result.txt","w");
    for (int i = 0; i < array->count; i++) {
        fprintf(fl,"%s\n",array->text[i]);
        free(array->text[i]);
    }
    fclose(fl);
}
int main(){
    int count =0;
    int buffer = 1;
    file_array *array = malloc(sizeof(file_array*));
    array->count=count;
    array->buffer=buffer;
    array->text = malloc(array->buffer*sizeof (char*));
    check_directory(array,"./");
    sort(array);
    print_in_file(array);
    return 0;
}
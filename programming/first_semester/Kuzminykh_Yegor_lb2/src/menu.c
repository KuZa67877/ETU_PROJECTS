#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
#define Array_length 100
int main(){
    int array[Array_length]; //Обозначим массив, куда будем сохранять числа, переменные, отвечающие за кол-во элементов и последний элемент.
    int count_elements =0;
    char last_symbol;
    int operation;
    scanf("%d", &operation); //Принимаем от пользователя число, отвечающее за выполняемую операцию.

    do //Считываем массив чисел
    {
        scanf("%d%c", &array[count_elements], &last_symbol);
        count_elements++;
    } while (last_symbol!='\n' && count_elements<Array_length);

    switch (operation) //Вызываем различные функции в зависимости от числа, которое ввел пользователь.
    {
        case 0:
            printf("%d\n",index_first_zero(count_elements,array));
            break;

        case 1:
            printf("%d\n",index_last_zero(count_elements,array));
            break;
        case 2:
            printf("%d\n",sum_between(count_elements,array));
            break;

        case 3:
            printf("%d\n",sum_before_and_after(count_elements,array));
            break;
        default:
            printf("Данные некорректны");
    }

    return 0;
}

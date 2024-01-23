#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
int sum_between(int count_elements, int array[]){//Фунция, возвращающая сумму модулей чисел, расположенных между первым и последним нулем.
    int zero_first_index = index_first_zero(count_elements,array);
    int zero_last_index= index_last_zero(count_elements,array);// Используем предыдущие функции для нахождения индексов нулей.
    int sum = 0;
    if (zero_first_index!=-1 && zero_last_index!=-1&& zero_first_index!=zero_last_index)//Проверка корректных данных.
    {
        for (int i =zero_first_index; i < zero_last_index; i++)
        {
            sum+=abs(array[i]);

        }
        return sum;
    }   if (zero_first_index==zero_last_index) // Возвращаем сумму модулей при верных данных, в противном случае возвращаем 0  -> если 0 в массиве 1,
    {                                           // -1 -> при некорректных данных.
        return 0;
    }   else{
        return -100;
    }

}
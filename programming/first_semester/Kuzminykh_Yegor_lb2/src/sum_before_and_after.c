#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_before_and_after(int count_elements, int array[]){//Функция, возвращающая сумму модулей чисел, расположенных до первого нуля и после последнего.
    int zero_first_index = index_first_zero(count_elements,array);
    int zero_last_index= index_last_zero(count_elements,array);

    int sum=0;
    if (zero_first_index!=-1 && zero_last_index!=-1)//Аналогично sum_between используем функции для нахождения индекса нулей, проверяем корректность данных
    {                                               //И с помощью двух циклов for считываем сумму модулей.
        for (int i = 0; i < zero_first_index; i++)
        {
            sum+=abs(array[i]);
        }
        for (int i =zero_last_index; i < count_elements; i++)
        {
            sum+=abs(array[i]);
        }
        return sum;
    }else{
        return -100;
    }

}
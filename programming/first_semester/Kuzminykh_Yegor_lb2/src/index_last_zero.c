#include <stdio.h>
#include "index_last_zero.h"

int index_last_zero(int count_elements, int array[]){ //Функция, возвращающая индекс последнего элемента, равного нулю.
    int last_index = 0;
    for (int t = 0; t < count_elements; t++)
    {
        if (array[t]==0)
        {
            last_index = t;


        }


    }

    return last_index;
}

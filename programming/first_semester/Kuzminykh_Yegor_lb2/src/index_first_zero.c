#include <stdio.h>
#include "index_first_zero.h"
int index_first_zero( int count_elements, int array[]) //Функция, возвращающая индекс первого элемента, равного нулю.
{
    int first_index = 0;
    for (int i = 0; i < count_elements; i++)
    {
        if (array[i]==0)
        {

            first_index = i;
            return first_index;

        }
    }
    return -100;
}
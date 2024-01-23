#include <stdio.h>
#include <stdlib.h>
#define Array_length 100 // Подключение библиотек, объявление константы на размер массива.
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

int index_last_zero(int count_elements, int array[]){ // Функция, возвращающая индекс последнего элемента, равного нулю.
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

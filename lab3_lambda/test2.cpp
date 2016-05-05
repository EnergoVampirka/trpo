#include "stdafx.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <list>


void fill_list(std::list<int>& list)  //Заполнение списка
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, 700);  //границы значений в списке

	for (std::list<int>::iterator cit = list.begin();
        cit != list.end(); ++cit)
	{
		*cit = dist(mt);
    }
}

struct found_class   //непараметризованный класс
{
    explicit found_class( int& sum):m_sum(sum){}  //конструктор, принимающий в качестве аргумента текущее значение суммы

    void operator() (int a)  //вызываемая функция
    {
		int last_val = 1;   //значение предыдущего проверяемого числа фибоначчи
		int cur_val = 1;	//значение текущего проверяемого числа фибоначчи
		while (1)
		{
			if (a == cur_val)  //проверка - является ли параметр числом фибоначчи
				m_sum += a;	   // если является - увеличиваем суммуж

			if (a<=cur_val)		//если проверяемое значение превысило параметр, то он не является числом фибоначчи
			{break;}
			else
			{
				int temp = last_val+cur_val;	//следующее число фибоначчи, с которм будет сравнение
				last_val = cur_val;				// делаем текущее число предыдущим
				cur_val = temp;					// делаем следующее число текущим для проверки
			}
		}
    }

private:
	int& m_sum;
};

template<typename T>
struct found_template_class  //параметризованный класс
{
    found_template_class( T& sum)  : m_sum(sum)   {}//конструктор, принимающий в качестве аргумента текущее значение суммы

    void operator() (T a)		//вызываемая функция
    {
		T last_val = 1;			//значение предыдущего проверяемого числа фибоначчи
		T cur_val = 1;			//значение текущего проверяемого числа фибоначчи
		while (1)
		{
			if (a == cur_val)	//проверка - является ли параметр числом фибоначчи
				m_sum += a;		// если является - увеличиваем суммуж

			if (a<=cur_val)		//если проверяемое значение превысило параметр, то он не является числом фибоначчи
			{break;}
			else
			{
				T temp = last_val+cur_val;	//следующее число фибоначчи, с которм будет сравнение
				last_val = cur_val;			// делаем текущее число предыдущим
				cur_val = temp;				// делаем следующее число текущим для проверки
			}
		}
    }

private:
	T& m_sum;
};

int main()
{
    std::list <int> input;		// список элементов
    input.resize(999);			// задается размер списка
	fill_list(input);			// заполнение списка
	

    auto sum_output = [&](int sum, std::string method)  //функция вывода на экран
        {
            std::cout << "Sum of fibonachi elements (" << method << "): " << sum << std::endl;

         }    ;



	//////////// поиск суммы с помощью лямбда функции
	int found_sum1 = 0;				
    std::for_each(input.begin(), input.end(),		//for_each
	[ &found_sum1](int a)		//на входе текущая сумма
    {
        int last_val = 1;		//предыдущее число фибоначчи
		int cur_val = 1;		//текущее число фибоначчи
		while (1)
		{			
			if (a == cur_val)		//сравнение с текущим числом
				found_sum1 += a;	//увеличение суммы

			if (a<=cur_val)			//условие выхода, если число превысило входной параметр, то он не является числом фибоначчи
			{break;}
			else
			{	// вычисление следующего числа фибоначчи для проверки
				int temp = last_val+cur_val;
				last_val = cur_val;
				cur_val = temp;
			}
		}
    });
    sum_output(found_sum1, "inline");		//вывод 1 результата на экран

	/////////поиск суммы с помощью непараметризованного класса
	int found_sum2 = 0;
    found_class cl(found_sum2);	//объявление класса
    std::for_each(input.begin(), input.end(), cl) ;		//for_each
    sum_output(found_sum2, "class");		//DSDJL

	/////////поиск суммы с помощью параметризованного класса
	int found_sum3 = 0;
    found_template_class<int> cl_template(found_sum3);	//объявление
    std::for_each(input.begin(), input.end(), cl_template) ;	//for_each
    sum_output(found_sum3, "class template");		//вывод
    
	///////////лямбда функция, объявленная заранее (то же самое что и в 1 случае)
	int found_sum4 = 0;
    auto func= [ &found_sum4]( int a) -> void {
            int last_val = 1;
			int cur_val = 1;
			while (1)
			{
				if (a == cur_val)
					found_sum4 += a;

				if (a<=cur_val)
				{break;}
				else
				{
					int temp = last_val+cur_val;
					last_val = cur_val;
					cur_val = temp;
				}
			}
        } ;

    std::for_each(input.begin(), input.end(), func) ;
    sum_output(found_sum4, "function object");
    
	system("PAUSE");
    return 0;
}

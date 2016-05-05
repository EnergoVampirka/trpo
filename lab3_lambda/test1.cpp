#include "stdafx.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <list>

#define MAX_FIBONACHI   610		//максимальное проверяемое число фибоначчи
using namespace std;



void fill_list(std::list<int>& list)		//заполнение списка
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, MAX_FIBONACHI);		//границы значений в списке

	for (std::list<int>::iterator cit = list.begin();
        cit != list.end(); ++cit)
	{
		*cit = dist(mt);
    }
}

void fill_fibonachi_list(std::list<int>& list, int N)		//заполнение N элементов списка числами фибоначчи
{
	int last_val = 1;
    int cur_val = 0;

	std::list<int>::iterator cit = list.begin();
	for (int i=0;i<N; i++, ++cit)		//вычисление чисел фибоначчи
	{
		*cit = last_val+cur_val;	
		int temp = last_val+cur_val;
		last_val = cur_val;
		cur_val = temp;
    }
}


struct found_class		//непараметризованный класс
{
    explicit found_class(std::list <int> in, int& sum):m_sum(sum)		//конструктор, на входе ряд фибоначчи и текущая сумма
				{fibonachi = in;}

    void operator() (int a)			//вызываемая функция
    {
		if (std::find(fibonachi.begin(),fibonachi.end(),a) != fibonachi.end()) //проверка, находится ли входной параметр в ряду фибоначчи
		{
			m_sum += a;		//если находится - прибавляем его к сумме
		}
    }

private:
    std::list <int> fibonachi;
	int& m_sum;
};

template<typename T>
struct found_template_class		//параметризованный класс
{
    found_template_class(std::list <T> in, T& sum)  :		//конструктор, на входе ряд фибоначчи и текущая сумма
	m_sum(sum)
    {
        fibonachi = in;
    }

    void operator() (T a)  //вызываемая функция
    {
        if (std::find(fibonachi.begin(),fibonachi.end(),a) != fibonachi.end())//проверка, находится ли входной параметр в ряду фибоначчи
		{
			m_sum += a;//если находится - прибавляем его к сумме
		}
    }

private:
    std::list <T> fibonachi;
	T& m_sum;
};

int main()
{
	std::list <int> fibonachi;		//список с числами фибоначчи
	fibonachi.resize(15);			//размер списка 15 элементов - значит последний элемент будет числом 610
	fill_fibonachi_list(fibonachi, 15);		//заполняем эти 15 элементов

    std::list <int> input;		//входной список
    input.resize(999);			// размер входного списка
	fill_list(input);			//заполняем список значениями
	

    auto sum_output = [&](int sum, std::string method)	//функция вывода
        {
            std::cout << "Sum of fibonachi elements (" << method << "): " << sum << std::endl;

         }    ;



	//////////поиск с помощью лямбда функции
	int found_sum1 = 0;
    std::for_each(input.begin(), input.end(),	//for_each
	[fibonachi, &found_sum1](int a)		//входной параметр а, ряд фибоначчи и текущая сумма
    {
        if (std::find(fibonachi.begin(),fibonachi.end(),a) != fibonachi.end())		//поиск параметра а в ряду фибоначчи
			{
				found_sum1 += a; //увеличиваем сумму если параметр в списке
			}
    });
    sum_output(found_sum1, "inline");		//вывод

	////////непараметризованный класс
	int found_sum2 = 0;
    found_class cl(fibonachi, found_sum2);		//объявление + конструктор, на входе ряд фибоначчи и сумма
    std::for_each(input.begin(), input.end(), cl) ;			//for_each
    sum_output(found_sum2, "class");		//вывод
		
	/////////параметризованный класс
	int found_sum3 = 0;
    found_template_class<int> cl_template(fibonachi, found_sum3);		//конструктор
    std::for_each(input.begin(), input.end(), cl_template) ;		//for_each
    sum_output(found_sum3, "class template");		//вывод
    
	//////////лямбда функция задана объектом, в остальном аналогично 1 случаю
	int found_sum4 = 0;
    auto func= [fibonachi, &found_sum4]( int a) -> void {
            if (std::find(fibonachi.begin(),fibonachi.end(),a) != fibonachi.end())
			{
				found_sum4 += a;
			}
        } ;

    std::for_each(input.begin(), input.end(), func) ;	//for_each
    sum_output(found_sum4, "function object");		//вывод
    
	system("PAUSE");
    return 0;
}

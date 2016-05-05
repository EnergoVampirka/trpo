#include "stdafx.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <list>

#define MAX_FIBONACHI   610		//������������ ����������� ����� ���������
using namespace std;



void fill_list(std::list<int>& list)		//���������� ������
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, MAX_FIBONACHI);		//������� �������� � ������

	for (std::list<int>::iterator cit = list.begin();
        cit != list.end(); ++cit)
	{
		*cit = dist(mt);
    }
}

void fill_fibonachi_list(std::list<int>& list, int N)		//���������� N ��������� ������ ������� ���������
{
	int last_val = 1;
    int cur_val = 0;

	std::list<int>::iterator cit = list.begin();
	for (int i=0;i<N; i++, ++cit)		//���������� ����� ���������
	{
		*cit = last_val+cur_val;	
		int temp = last_val+cur_val;
		last_val = cur_val;
		cur_val = temp;
    }
}


struct found_class		//������������������� �����
{
    explicit found_class(std::list <int> in, int& sum):m_sum(sum)		//�����������, �� ����� ��� ��������� � ������� �����
				{fibonachi = in;}

    void operator() (int a)			//���������� �������
    {
		if (std::find(fibonachi.begin(),fibonachi.end(),a) != fibonachi.end()) //��������, ��������� �� ������� �������� � ���� ���������
		{
			m_sum += a;		//���� ��������� - ���������� ��� � �����
		}
    }

private:
    std::list <int> fibonachi;
	int& m_sum;
};

template<typename T>
struct found_template_class		//����������������� �����
{
    found_template_class(std::list <T> in, T& sum)  :		//�����������, �� ����� ��� ��������� � ������� �����
	m_sum(sum)
    {
        fibonachi = in;
    }

    void operator() (T a)  //���������� �������
    {
        if (std::find(fibonachi.begin(),fibonachi.end(),a) != fibonachi.end())//��������, ��������� �� ������� �������� � ���� ���������
		{
			m_sum += a;//���� ��������� - ���������� ��� � �����
		}
    }

private:
    std::list <T> fibonachi;
	T& m_sum;
};

int main()
{
	std::list <int> fibonachi;		//������ � ������� ���������
	fibonachi.resize(15);			//������ ������ 15 ��������� - ������ ��������� ������� ����� ������ 610
	fill_fibonachi_list(fibonachi, 15);		//��������� ��� 15 ���������

    std::list <int> input;		//������� ������
    input.resize(999);			// ������ �������� ������
	fill_list(input);			//��������� ������ ����������
	

    auto sum_output = [&](int sum, std::string method)	//������� ������
        {
            std::cout << "Sum of fibonachi elements (" << method << "): " << sum << std::endl;

         }    ;



	//////////����� � ������� ������ �������
	int found_sum1 = 0;
    std::for_each(input.begin(), input.end(),	//for_each
	[fibonachi, &found_sum1](int a)		//������� �������� �, ��� ��������� � ������� �����
    {
        if (std::find(fibonachi.begin(),fibonachi.end(),a) != fibonachi.end())		//����� ��������� � � ���� ���������
			{
				found_sum1 += a; //����������� ����� ���� �������� � ������
			}
    });
    sum_output(found_sum1, "inline");		//�����

	////////������������������� �����
	int found_sum2 = 0;
    found_class cl(fibonachi, found_sum2);		//���������� + �����������, �� ����� ��� ��������� � �����
    std::for_each(input.begin(), input.end(), cl) ;			//for_each
    sum_output(found_sum2, "class");		//�����
		
	/////////����������������� �����
	int found_sum3 = 0;
    found_template_class<int> cl_template(fibonachi, found_sum3);		//�����������
    std::for_each(input.begin(), input.end(), cl_template) ;		//for_each
    sum_output(found_sum3, "class template");		//�����
    
	//////////������ ������� ������ ��������, � ��������� ���������� 1 ������
	int found_sum4 = 0;
    auto func= [fibonachi, &found_sum4]( int a) -> void {
            if (std::find(fibonachi.begin(),fibonachi.end(),a) != fibonachi.end())
			{
				found_sum4 += a;
			}
        } ;

    std::for_each(input.begin(), input.end(), func) ;	//for_each
    sum_output(found_sum4, "function object");		//�����
    
	system("PAUSE");
    return 0;
}

#include "stdafx.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <list>


void fill_list(std::list<int>& list)  //���������� ������
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, 700);  //������� �������� � ������

	for (std::list<int>::iterator cit = list.begin();
        cit != list.end(); ++cit)
	{
		*cit = dist(mt);
    }
}

struct found_class   //������������������� �����
{
    explicit found_class( int& sum):m_sum(sum){}  //�����������, ����������� � �������� ��������� ������� �������� �����

    void operator() (int a)  //���������� �������
    {
		int last_val = 1;   //�������� ����������� ������������ ����� ���������
		int cur_val = 1;	//�������� �������� ������������ ����� ���������
		while (1)
		{
			if (a == cur_val)  //�������� - �������� �� �������� ������ ���������
				m_sum += a;	   // ���� �������� - ����������� ������

			if (a<=cur_val)		//���� ����������� �������� ��������� ��������, �� �� �� �������� ������ ���������
			{break;}
			else
			{
				int temp = last_val+cur_val;	//��������� ����� ���������, � ������ ����� ���������
				last_val = cur_val;				// ������ ������� ����� ����������
				cur_val = temp;					// ������ ��������� ����� ������� ��� ��������
			}
		}
    }

private:
	int& m_sum;
};

template<typename T>
struct found_template_class  //����������������� �����
{
    found_template_class( T& sum)  : m_sum(sum)   {}//�����������, ����������� � �������� ��������� ������� �������� �����

    void operator() (T a)		//���������� �������
    {
		T last_val = 1;			//�������� ����������� ������������ ����� ���������
		T cur_val = 1;			//�������� �������� ������������ ����� ���������
		while (1)
		{
			if (a == cur_val)	//�������� - �������� �� �������� ������ ���������
				m_sum += a;		// ���� �������� - ����������� ������

			if (a<=cur_val)		//���� ����������� �������� ��������� ��������, �� �� �� �������� ������ ���������
			{break;}
			else
			{
				T temp = last_val+cur_val;	//��������� ����� ���������, � ������ ����� ���������
				last_val = cur_val;			// ������ ������� ����� ����������
				cur_val = temp;				// ������ ��������� ����� ������� ��� ��������
			}
		}
    }

private:
	T& m_sum;
};

int main()
{
    std::list <int> input;		// ������ ���������
    input.resize(999);			// �������� ������ ������
	fill_list(input);			// ���������� ������
	

    auto sum_output = [&](int sum, std::string method)  //������� ������ �� �����
        {
            std::cout << "Sum of fibonachi elements (" << method << "): " << sum << std::endl;

         }    ;



	//////////// ����� ����� � ������� ������ �������
	int found_sum1 = 0;				
    std::for_each(input.begin(), input.end(),		//for_each
	[ &found_sum1](int a)		//�� ����� ������� �����
    {
        int last_val = 1;		//���������� ����� ���������
		int cur_val = 1;		//������� ����� ���������
		while (1)
		{			
			if (a == cur_val)		//��������� � ������� ������
				found_sum1 += a;	//���������� �����

			if (a<=cur_val)			//������� ������, ���� ����� ��������� ������� ��������, �� �� �� �������� ������ ���������
			{break;}
			else
			{	// ���������� ���������� ����� ��������� ��� ��������
				int temp = last_val+cur_val;
				last_val = cur_val;
				cur_val = temp;
			}
		}
    });
    sum_output(found_sum1, "inline");		//����� 1 ���������� �� �����

	/////////����� ����� � ������� �������������������� ������
	int found_sum2 = 0;
    found_class cl(found_sum2);	//���������� ������
    std::for_each(input.begin(), input.end(), cl) ;		//for_each
    sum_output(found_sum2, "class");		//DSDJL

	/////////����� ����� � ������� ������������������ ������
	int found_sum3 = 0;
    found_template_class<int> cl_template(found_sum3);	//����������
    std::for_each(input.begin(), input.end(), cl_template) ;	//for_each
    sum_output(found_sum3, "class template");		//�����
    
	///////////������ �������, ����������� ������� (�� �� ����� ��� � � 1 ������)
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

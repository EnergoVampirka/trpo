#include <iostream>
#include <stdlib.h>
using namespace std;
#define DEFAULT_SIZE 10

// создание шаблона класса stack
template <class StackType> class stack
{
StackType *stck; // массив, содержащий стек
int tos; // индекс вершины стека
int size; // максимальный размер стека
public:
stack(); // конструктор по умолчанию
stack(int value); // параметризованный конструктор
~stack() {delete [] stck;} // деструктор

void init() { tos = 0; } // инициализация стека
void push(StackType ob); // поместить объект в стек
StackType pop(); // извлечь объект из стека
};

template <class StackType> stack <StackType>::stack()
{
stck = new StackType[DEFAULT_SIZE ]; //создали массив в динамической памяти
if(!stck)
{
cout << "ERROR! \n";
exit (1);
}
size = DEFAULT_SIZE; //длина по умолчанию
tos=0;
}

template <class StackType> stack <StackType>::stack(int value)
{
stck = new StackType[value]; //создали массив в динамической памяти
if(!stck)
{
cout << "ERROR! \n";
exit (1);
}
size = value; //длина массива на единицу больше чем длина очереди;сохранить в length
tos=0;
}

template <class StackType> void stack < StackType>:: push(StackType ob)
{
if (tos == size)
{
cout << "Stack is full" << endl;
return;
}
stck[tos] = ob;
tos++;
}

template <class StackType> StackType stack < StackType>:: pop()
{
if (tos == 0)
{
cout << "Stack is empty"<< endl;
return 0;
}
tos--;
return stck[tos];
}

int main ()
{
  stack<int> myStack(3);
  myStack.push(1);
  myStack.push(2);
  myStack.push(3);
  myStack.push(4);
  
  cout << "Popout elements: " << myStack.pop() << endl;
  cout << "Popout elements: " << myStack.pop() << endl;
  cout << "Popout elements: " << myStack.pop() << endl;
  cout << "Popout elements: " << myStack.pop() << endl;
  
  return 0;
}
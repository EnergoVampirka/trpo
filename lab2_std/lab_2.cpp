#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

int main ()
{
  const int N = 10;
  std::vector<int> temp(N);
  srand(time(NULL));
  for(int i =0; i<N; i++)
  {
    temp[i] = rand()%100;
  }

  int minv = temp[0];
  int maxv = minv;
  // вместо std::vector<int>::iterator буду использовать auto
  
  std::cout << "Initial vector:" << std::endl;
  for (std::vector<int>::iterator iter = temp.begin(); iter != temp.end(); iter++)
  { 
    std::cout << *iter << "\t";
  }
   std::cout  << std::endl;
 
  for (std::vector<int>::iterator iter = temp.begin(); iter != temp.end(); iter++)
  {
    if ( *iter > maxv )
    {
      maxv = *iter;
    }

    if ( *iter < minv )
    {
      minv = *iter;
    }
  }
  temp.insert(temp.begin(), minv);
  int size = temp.size() / 2;
  if (2*size< temp.size())
  {
    size += 1;
  }
  temp.insert(temp.begin()+size, maxv);
  
  std::cout << "Rezult vector:" << std::endl;
  int cur_index = 0;
  for (std::vector<int>::iterator iter = temp.begin(); iter != temp.end(); iter++)
  { 
    cur_index = iter - temp.begin();
    if(cur_index == 0 || cur_index == size)
      std::cout << "\"" <<  *iter << "\"" << "\t";
    else
      std::cout << *iter << "\t";
  }

   std::cout << std::endl;
   std::cout << "min:" << minv << std::endl;
   std::cout << "max:" << maxv << std::endl;
  
   
  
  
  return 0;
}
#include <iostream>
#include "../vector/vector.hpp"
#include <vector>

template <typename T>
bool check_ft_with_std(const ft::vector<T>& ft_con, const std::vector<T>& std_con)
{
  typename ft::vector<T>::const_iterator it1;
  typename std::vector<T>::const_iterator it2;

  it1 = ft_con.begin();
  it2 = std_con.end();
  while ()
}

/** 1.Constructor
 ** https://www.cplusplus.com/reference/vector/vector/vector/ **/
void test_constructor()
{
  ft::vector<int> ft_first;                                // empty vector of ints
  ft::vector<int> ft_second (4,100);                       // four ints with value 100
  ft::vector<int> ft_third (ft_second.begin(),ft_second.end());  // iterating through second
  ft::vector<int> ft_fourth (ft_third);                       // a copy of third
  
  std::vector<int> std_first;                                // empty vector of ints
  std::vector<int> std_second (4,100);                       // four ints with value 100
  std::vector<int> std_third (std_second.begin(),std_second.end());  // iterating through second
  std::vector<int> std_fourth (std_third);                       // a copy of third

  check_ft_with_std(ft_first, std_first);
  check_ft_with_std(ft_second, std_second);
  check_ft_with_std(ft_third, std_third);
  check_ft_with_std(ft_fourth, std_fourth);
}


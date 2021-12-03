#include <iostream>
#include "../vector/vector.hpp"
#include <vector>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

template <typename T>
bool check_ft_with_std(const ft::vector<T>& ft_con, const std::vector<T>& std_con)
{
  typename ft::vector<T>::const_iterator it1;
  typename std::vector<T>::const_iterator it2;

  it1 = ft_con.begin();
  it2 = std_con.begin();
  while (it1 != ft_con.end())
  {
    if (*it1 != *it2)
      return false;
    it1++; it2++;
  }
  return true;
}

template <typename T>
bool check_ft_with_std_rev(const ft::vector<T>& ft_con, const std::vector<T>& std_con)
{
  typename ft::vector<T>::const_reverse_iterator it1;
  typename std::vector<T>::const_reverse_iterator it2;

  it1 = ft_con.rbegin();
  it2 = std_con.rbegin();
  while (it1 != ft_con.rend())
  {
    if (*it1 != *it2)
      return false;
    it1--; it2--;
  }
  return true;
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

  if (check_ft_with_std(ft_first, std_first) &&
      check_ft_with_std(ft_second, std_second) &&
      check_ft_with_std(ft_third, std_third) &&
      check_ft_with_std(ft_fourth, std_fourth))
    std::cout << GREEN << "Contstruct OK" << RESET << std::endl;
  else
    std::cout << RED << "Contstruct X" << RESET << std::endl;
}

/** 2.::operator=, size
 **/
void test_size()
{
  ft::vector<int> ft_foo (3,0);
  ft::vector<int> ft_bar (5,0);

  ft_bar = ft_foo;
  ft_foo = ft::vector<int>();

  std::vector<int> std_foo (3,0);
  std::vector<int> std_bar (5,0);

  std_bar = std_foo;
  std_foo = std::vector<int>();

  std::cout << "Size of foo: " << int(std_foo.size()) << '\n';
  std::cout << "Size of bar: " << int(std_bar.size()) << '\n';

  if ((ft_foo.size() == std_foo.size()) &&
      (ft_bar.size() == std_bar.size()))
    std::cout << GREEN << "::operator=, size OK" << RESET << std::endl;
  else
    std::cout << RED << "::operator=, size X" << RESET << std::endl;
}

/** 3. reverse_iterator
 **/
void test_reverse_iterator()
{
  ft::vector<int> ft_first;                                // empty vector of ints
  ft::vector<int> ft_second (4,100);                       // four ints with value 100
  ft::vector<int> ft_third (ft_second.begin(),ft_second.end());  // iterating through second
  ft::vector<int> ft_fourth (ft_third);                       // a copy of third

  std::vector<int> std_first;                                // empty vector of ints
  std::vector<int> std_second (4,100);                       // four ints with value 100
  std::vector<int> std_third (std_second.begin(),std_second.end());  // iterating through second
  std::vector<int> std_fourth (std_third);                       // a copy of third

  if (check_ft_with_std_rev(ft_first, std_first) &&
      check_ft_with_std_rev(ft_second, std_second) &&
      check_ft_with_std_rev(ft_third, std_third) &&
      check_ft_with_std_rev(ft_fourth, std_fourth))
    std::cout << GREEN << "reverse iterator OK" << RESET << std::endl;
  else
    std::cout << RED << "reverse iterator X" << RESET << std::endl;
}
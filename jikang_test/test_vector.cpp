#include "test.hpp"
#include <vector>
#include "../vector/vector.hpp"


namespace vector_test
{
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
      it1++; it2++;
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
      std::cout << REDCOLOR << "Contstruct X" << RESET << std::endl;
  }

  /** 2.::operator=, size
   **/
  void test_size()
  {
    ft::vector<char> ft_empty;
    std::vector<char> std_empty;

    if (ft_empty.empty() == std_empty.empty())
      std::cout << GREEN << "empty OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "empty X" << RESET << std::endl;

    ft::vector<int> ft_foo (3,0);
    ft::vector<int> ft_bar (5,0);
    std::vector<int> std_foo (3,0);
    std::vector<int> std_bar (5,0);

    if ((ft_foo.size() == std_foo.size()) &&
        (ft_bar.size() == std_bar.size()))
      std::cout << GREEN << "size OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "size X" << RESET << std::endl;

    ft_bar = ft_foo;
    ft_foo = ft::vector<int>();
    std_bar = std_foo;
    std_foo = std::vector<int>();

    if ((ft_foo.size() == std_foo.size()) &&
        (ft_bar.size() == std_bar.size()))
      std::cout << GREEN << "::operator=, size OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "::operator=, size X" << RESET << std::endl;

    ft::vector<int> ft_zoo;
    std::vector<int> std_zoo;

    for (int i=1; i<10; i++) ft_zoo.push_back(i);
    for (int i=1; i<10; i++) std_zoo.push_back(i);

    ft_zoo.resize(5);
    std_zoo.resize(5);

    if ((ft_zoo.size() == std_zoo.size()))
      std::cout << GREEN << "resize OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "resize X" << RESET << std::endl;

    if (ft_zoo.capacity() == std_zoo.capacity())
      std::cout << GREEN << "capacity OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "capacity X" << RESET << std::endl;

    if (ft_zoo.max_size() == std_zoo.max_size())
      std::cout << GREEN << "max_size OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "max_size X" << RESET << std::endl;
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
      std::cout << REDCOLOR << "reverse iterator X" << RESET << std::endl;
  }

  /** 4. [], at 
   **/
  void test_at()
  {
    ft::vector<int> ft_myvector (10);
    ft::vector<int>::size_type ft_sz = ft_myvector.size();

    std::vector<int> std_myvector (10);
    std::vector<int>::size_type std_sz = std_myvector.size();

    for (unsigned i=0; i<ft_sz; i++) ft_myvector[i]=i;
    for (unsigned i=0; i<std_sz; i++) std_myvector[i]=i;

    if (check_ft_with_std(ft_myvector, std_myvector))
      std::cout << GREEN << "[] OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "[] X" << RESET << std::endl;

    for (unsigned i=0; i<ft_sz; i++) ft_myvector.at(i)=2*i;
    for (unsigned i=0; i<std_sz; i++) std_myvector.at(i)=2*i;

    if (check_ft_with_std(ft_myvector, std_myvector))
      std::cout << GREEN << "at OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "at X" << RESET << std::endl;

    ft_myvector.front() -= ft_myvector.back();
    std_myvector.front() -= std_myvector.back();
    
    if (check_ft_with_std(ft_myvector, std_myvector))
      std::cout << GREEN << "front, back OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "front, back X" << RESET << std::endl;
  }

  /** 5.modifier
   **/
  void test_modifier()
  {
    ft::vector<int> ft_first;
    ft::vector<int> ft_second;
    ft::vector<int> ft_third;
    ft::vector<int> ft_fourth;
    ft::vector<int> ft_fifth;

    std::vector<int> std_first;
    std::vector<int> std_second;
    std::vector<int> std_third;
    std::vector<int> std_fourth;
    std::vector<int> std_fifth;

    ft_fifth.assign (7,100);             // 7 ints with a value of 100
    std_fifth.assign (7,100);             // 7 ints with a value of 100

    ft_fifth.clear();
    std_fifth.clear();

    if (ft_fifth.empty() == std_fifth.empty())
      std::cout << GREEN << "clear OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "clear X" << RESET << std::endl;

    ft_first.assign (7,100);             // 7 ints with a value of 100
    std_first.assign (7,100);             // 7 ints with a value of 100

    ft::vector<int>::iterator ft_it = ft_first.begin();
    ft_first.insert(ft_it, 50);
    ft::vector<int>::iterator ft_itz = ft_first.begin();
    ft_first.erase(ft_itz);

    std::vector<int>::iterator std_it = std_first.begin();
    std_first.insert(std_it, 50);
    std::vector<int>::iterator std_itz = std_first.begin();
    std_first.erase(std_itz);


    if (check_ft_with_std(ft_first, std_first))
      std::cout << GREEN << "assign, insert, erase OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "assign, insert, erase X" << RESET << std::endl;

    ft_third.push_back(100);
    ft_third.push_back(200);
    ft_third.push_back(300);

    std_third.push_back(100);
    std_third.push_back(200);
    std_third.push_back(300);

    if (check_ft_with_std(ft_third, std_third))
      std::cout << GREEN << "push_back OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "push_back X" << RESET << std::endl;
    
    int ft_sum = 0;
    int std_sum = 0;

    while (!ft_third.empty())
    {
      ft_sum += ft_third.back();
      ft_third.pop_back();  
    }
    while (!std_third.empty())
    {
      std_sum += std_third.back();
      std_third.pop_back();  
    }

    if (check_ft_with_std(ft_third, std_third))
      std::cout << GREEN << "pop_back OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "pop_back X" << RESET << std::endl;

    ft_fourth.reserve(10);
    std_fourth.reserve(10);
    if (ft_fourth.capacity() == std_fourth.capacity())
      std::cout << GREEN << "capacity OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "capacity X" << RESET << std::endl;
  }
}

void test_vector_all()
{
  vector_test::test_constructor();
  vector_test::test_size();
  vector_test::test_reverse_iterator();
  vector_test::test_at();
  vector_test::test_modifier();
}
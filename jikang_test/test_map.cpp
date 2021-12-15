#include "test.hpp"
#include <map>
#include "../map/map.hpp"

namespace map_test
{
  template <typename T1, typename T2>
  bool check_ft_with_std(const ft::map<T1, T2>& ft_con, const std::map<T1, T2>& std_con)
  {
    typename ft::map<T1, T2>::const_iterator it1;
    typename std::map<T1, T2>::const_iterator it2;

    if (ft_con.size() != std_con.size())
      return false;
    it1 = ft_con.begin();
    it2 = std_con.begin();
    while (it1 != ft_con.end())
    {
      if (it1->first != it2->first || it1->second != it2->second)
        return false;
      it1++; it2++;
    }
    return true;
  }

  /** 1.map
   **/
  bool fncomp (char lhs, char rhs) {return lhs < rhs;}

  struct classcomp
  {
    bool operator() (const char& lhs, const char& rhs) const
    { return lhs<rhs; }
  };

  void test_map()
  {
    ft::map<char,int> ft_first;
    std::map<char,int> std_first;

    if (ft_first.empty() == std_first.empty())
      std::cout << GREEN << "empty OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "empty X" << RESET << std::endl;

    ft_first['a']=10;
    ft_first['b']=30;
    ft_first['c']=50;
    ft_first['d']=70;

    std_first['a']=10;
    std_first['b']=30;
    std_first['c']=50;
    std_first['d']=70;

    if ((ft_first.lower_bound('b')->first == std_first.lower_bound('b')->first) &&
        (ft_first.lower_bound('b')->second == std_first.lower_bound('b')->second))
      std::cout << GREEN << "lower_bound OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "lower_bound X" << RESET << std::endl;

    if ((ft_first.upper_bound('b')->first == std_first.upper_bound('b')->first) &&
        (ft_first.upper_bound('b')->second == std_first.upper_bound('b')->second))
      std::cout << GREEN << "upper_bound OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "upper_bound X" << RESET << std::endl;

    if ((ft_first.equal_range('c').first->first == std_first.equal_range('c').first->first) &&
        (ft_first.equal_range('c').first->second == std_first.equal_range('c').first->second) &&
        (ft_first.equal_range('c').second->first == std_first.equal_range('c').second->first) &&
        (ft_first.equal_range('c').second->second == std_first.equal_range('c').second->second))
      std::cout << GREEN << "equal_range OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "equal_range X" << RESET << std::endl;


    if (ft_first.size() == std_first.size())
      std::cout << GREEN << "empty OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "empty X" << RESET << std::endl;

    if (ft_first['b'] == std_first['b'])
      std::cout << GREEN << "[] OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "[] X" << RESET << std::endl;

    ft::map<char,int> ft_second (ft_first.begin(),ft_first.end());
    std::map<char,int> std_second (std_first.begin(),std_first.end());

    ft::map<char,int> ft_third (ft_second);
    std::map<char,int> std_third (std_second);

    if (check_ft_with_std(ft_first, std_first) &&
        check_ft_with_std(ft_second, std_second) &&
        check_ft_with_std(ft_third, std_third))
      std::cout << GREEN << "Contstruct OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "Contstruct X" << RESET << std::endl;

    ft_first.insert(ft_first.begin(), ft::pair<char, int>('s', 99));
    std_first.insert(std_first.begin(), std::pair<char, int>('s', 99));

    if (ft_first.find('s')->first == std_first.find('s')->first &&
        ft_first.find('s')->second == std_first.find('s')->second)
    {
      std::cout << GREEN << "find OK" << RESET << std::endl;
      std::cout << GREEN << "insert OK" << RESET << std::endl;
    }
    else
    {
      std::cout << REDCOLOR << "find X" << RESET << std::endl;
      std::cout << REDCOLOR << "insert X" << RESET << std::endl;
    }

    if (ft_first.count('s') == std_first.count('s') &&
        ft_first.count('s') == std_first.count('s'))
      std::cout << GREEN << "count OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "count X" << RESET << std::endl;

    ft_first.erase('s');
    std_first.erase('s');

    if (check_ft_with_std(ft_first, std_first))
      std::cout << GREEN << "erase OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "erase X" << RESET << std::endl;

    ft_first.swap(ft_second);
    std_first.swap(std_second);

    if (check_ft_with_std(ft_first, std_first))
      std::cout << GREEN << "swap OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "swap X" << RESET << std::endl;

    ft_first.clear();
    std_first.clear();

    if (ft_first.size() == std_first.size())
      std::cout << GREEN << "clear OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "clear X" << RESET << std::endl;
  }

  void get_allocator_test()
  {
    ft::map<char, int> ft_map;
    std::map<char, int> std_map;
    ft::pair<const char, int>* ft_p;
    std::pair<const char, int>* std_p;
    
    bool success = 1;

    ft_p = ft_map.get_allocator().allocate(5);
    std_p = std_map.get_allocator().allocate(5);

    for (int i = 0; i < 5; i++)
    {
      ft_map.get_allocator().construct(&ft_p[i], ft::pair<int, int>(i, i));
      std_map.get_allocator().construct(&std_p[i], std::pair<int, int>(i, i));
    }

    for (int i = 0; i < 5; i++)
    {
      if (ft_p[i].first != std_p[i].first &&
          ft_p[i].second != std_p[i].second)
      {
        std::cout << REDCOLOR << "get_allocator X" << RESET << std::endl;
        success = 0;
      }
    }
    if (success)
      std::cout << GREEN << "get_allocator OK" << RESET << std::endl;

    ft_map.get_allocator().deallocate(ft_p, 5);
    std_map.get_allocator().deallocate(std_p, 5);
  }
}

void test_map_all()
{
  map_test::test_map();
  map_test::get_allocator_test();
}
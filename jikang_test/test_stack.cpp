#include "test.hpp"
#include <stack>
#include "../stack/stack.hpp"


namespace stack_test
{
  /** 1.Constructor
   ** https://www.cplusplus.com/reference/stack/stack/stack/ **/
  void test_constructor()
  {
    ft::vector<int> ft_first(4,100);                       // four ints with value 100
    ft::stack<int> ft_second (ft_first);  // iterating through second

    std::deque<int> std_first(4,100);                       // four ints with value 100
    std::stack<int> std_second (std_first);  // iterating through second

    if (ft_first.size() == std_first.size() ||
        ft_second.size() == std_second.size())
      std::cout << GREEN << "Contstruct OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "Contstruct X" << RESET << std::endl;
  }

  /** 2. Member function
   **/
  void test_member_function()
  {
    ft::stack<int> ft_mystack;
    std::stack<int> std_mystack;
    
    int ft_sum (0);
    int std_sum (0);

    for (int i=1;i<=10;i++) ft_mystack.push(i);
    for (int i=1;i<=10;i++) std_mystack.push(i);

    if (ft_mystack.empty() == std_mystack.empty())
      std::cout << GREEN << "empty OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "empty X" << RESET << std::endl;
    
    if (ft_mystack.size() == std_mystack.size())
      std::cout << GREEN << "push OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "push X" << RESET << std::endl;

    if (ft_mystack.size() == std_mystack.size())
      std::cout << GREEN << "szie OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "size X" << RESET << std::endl;

    ft_mystack.top() -= 5;
    std_mystack.top() -= 5;

    if (ft_mystack.top() == std_mystack.top())
      std::cout << GREEN << "top OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "top X" << RESET << std::endl;

    while (!ft_mystack.empty())
    {
      ft_sum += ft_mystack.top();
      ft_mystack.pop();
    }
    while (!std_mystack.empty())
    {
      std_sum += std_mystack.top();
      std_mystack.pop();
    }

    if (ft_mystack.size() == std_mystack.size())
      std::cout << GREEN << "pop OK" << RESET << std::endl;
    else
      std::cout << REDCOLOR << "pop X" << RESET << std::endl;
  }
}

void test_stack_all()
{
  stack_test::test_constructor();
  stack_test::test_member_function();
}
#include "stack/stack.hpp"
#include <iostream>
#include <stack>
#include <string>
#include "include/iterator.hpp"
#include <deque>          // std::deque
#include <vector>

int main ()
{
  std::deque<int> mydeque (3,100);          // deque with 3 elements
  std::vector<int> myvector (2,200);        // vector with 2 elements

  ft::stack<int> first;                    // empty stack
  ft::stack<int> second (mydeque);         // stack initialized to copy of deque

  ft::stack<int,std::vector<int> > third;  // empty stack using vector
  ft::stack<int,std::vector<int> > fourth (myvector);

  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';

  return 0;
}
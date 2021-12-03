#include <iostream>
#include "../map/map.hpp"
#include "../stack/stack.hpp"
#include "../vector/vector.hpp"

void print_title(std::string title)
{
  std::cout << "==============================================" << std::endl;
  std::cout << "=============   " << title << "   ============" << std::endl;
  std::cout << "==============================================" << std::endl;
}

int main(void)
{
  print_title("Vector");

  return 0;
}
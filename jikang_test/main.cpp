#include "test.hpp"

void print_title(std::string title)
{
  std::cout << "==============================================" << std::endl;
  std::cout << "   =============   " << title << "   ============" << std::endl;
  std::cout << "==============================================" << std::endl;
}

int main(void)
{
  print_title("Vector");  
  test_vector_all();
  print_title("Stack");  
  test_stack_all();
  print_title("Map");  
  test_map_all();
  
  return 0;
}
#include "test.hpp"
#include "unistd.h"

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
  

  system("leaks jikang_test_program > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
  return 0;
}
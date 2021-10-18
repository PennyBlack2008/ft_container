/*
헷갈렸던 이유는 iterator의 end가 NULL값인지 몰랐었고, 그래서 reverse_iterator의 경우에 begin이 NULL값일 지 몰랐다.
&*( reverse_iterator ( i )) = = &* ( i -1). 이 의미를 이해하려면 i값이 무엇인지를 알아야하는 데, i가 정방향 until이면,
reverse_iterator는 역방향 from이 되고, i가 정방향 from이 되면 reverse_iterator는 역방향 until이 된다. 이 때 iterator를
한자리 씩 왼쪽으로 옮겨줘야 계산이 된다. 왜냐하면 역방향 iterator는 정방향 iterator와 다르게 NULL로 시작해서 끝값으로 끝나기 때문이다.
*/

// reverse_iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::reverse_iterator
#include <vector>       // std::vector

int main () {
  std::vector<int> myvector;
  for (int i=1; i<11; i++) myvector.push_back(i);

  typedef std::vector<int>::iterator iter_type;

  for (auto it = std::begin(myvector); it != std::end(myvector); ++it)
      std::cout << ' ' << *it;
   std::cout << std::endl;   
                                                         // ? 1 2 3 4 5 6 7 8 9 10 ?
  iter_type from (myvector.begin());                     //   ^
                                                         //         ------>
  iter_type until (myvector.end());                      //                        ^
                                                         //
  std::reverse_iterator<iter_type> rev_until (from);     // ^               !        // 지금은 8이 나오지만, null값이 들어가서 무작위 수가 나오는 거다.
                                                         //         <------
  std::reverse_iterator<iter_type> rev_from (until);     //                      ^   
                                                         //
                                    // rev_from.until()  //   ^
                                    // rev_from.base()   //                        ^
   // std::cout << "*myvector.begin() is" << *myvector.begin() << std::endl;
  std::cout << "*from is" << *from << std::endl;
  std::cout << "*until is" << *until << std::endl;
  std::cout << "*(until - 1) is" << *(until - 1) << std::endl;
  std::cout << "*rev_until is" << *rev_until << std::endl; // 8이 나오지만 사실 ?의 NULL값을 참조한 것이다.
  std::cout << "*rev_from is" << *rev_from << std::endl; // 10
  std::cout << "*rev_until.base() is" << *rev_until.base() << std::endl; // 1
  std::cout << "*rev_from.base() is" << *rev_from.base() << std::endl; // 0
  std::cout << "*(rev_from + 1).base()+1 is" << *(rev_from + 1).base() << std::endl; // 10
  std::cout << "myvector:";
  while (rev_from != rev_until) {
    std::cout << ' ' << *rev_from++;
   // *rev_from++;
   //  std::cout << "*rev_until is" << *rev_until << std::endl;
  }
  std::cout << '\n';

  return 0;
}
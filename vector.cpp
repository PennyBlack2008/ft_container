#include <iostream>
#include <list>
// #include <vector>
#include "vector.hpp"
using namespace std;

int		main(void) {
	  std::list<int> i;
  	i.push_back(3);
  	i.push_back(4);
  	i.push_back(5);
	ft::vector<int>	a;
	int				b[10] = {0,1,2,3,4,5,6,7,8,9};
	cout << a.size() << endl;
	int	cnt = 0;
	for (int j=0;j<10;j++) {
		a.push_back(j);
		cout << "a.capacity(): " << a.capacity() << endl;
	}
	for (ft::vector<int>::iterator it=a.begin();it !=a.end();++it) {
		cout << *it;
	}
	cout << endl;
	ft::vector<int> c(i.begin(), i.end());
	for (ft::vector<int>::iterator it=c.begin();it !=c.end();++it) {
		cout << *it;
	}
	cout << endl;
	return (0);
}

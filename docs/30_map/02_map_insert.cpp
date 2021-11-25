#include <map>
#include <iostream>

using namespace std;

int main()
{
  map<char, int> mymap;

  mymap.insert(pair<char, int>('a', 100));
  mymap.insert(pair<char, int>('c', 200));
  mymap.insert(pair<char, int>('z', 300));
  mymap.insert(pair<char, int>('b', 400));
  mymap.insert(pair<char, int>('c', 500));

  map<char, int> another;
  another.insert(mymap.begin(), mymap.find('z'));

  for (pair<char, int> p : another)
    cout << p.first << ": " << p.second << endl;

  return 0;
}
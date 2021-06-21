// https://docs.microsoft.com/ko-kr/cpp/standard-library/random-access-iterator-tag-struct?view=msvc-160

#include <iterator>
#include <vector>
#include <iostream>
#include <list>

using namespace std;

int main()
{
    vector<int> vi;
    vector<char> vc;
    list<char> lc;
    iterator_traits<vector<int>::iterator>::iterator_category cati;
    iterator_traits<vector<char>::iterator>::iterator_category catc;
    iterator_traits<list<char>::iterator>::iterator_category catlc;

    //These are both random-access iterators
    cout << "Thre type of iterator for vector<int> is "
        << "identified by the tag:\n "
        << typeid(cati).name() << endl;
    cout << "The type of iterator for vector<char> is "
        << "identified by the tag:\n "
        << typeid(catc).name() << endl;
    if (typeid(cati)==typeid(catc))
        cout << "The iterators are the same." << endl << endl;
    else
        cout << "The iteratros are not the same." << endl << endl;

    // But the list iterator is bidirectional, not random access
    cout << "The type of iterator for list<char> is "
        << "identified by the tag:\n"
        << typeid (catlc).name() << endl;

    // cout << (typeid(vi.begin()) == typeid(vc.begin())) << endl;
    if (typeid(vi.begin()) == typeid(vc.begin()))
        cout << "The iterators are the same." << endl;
    else
        cout << "The iterators are not the same." <<endl;
    // A random-access iterator is a bidirectional iterator.
    cout << (void*)dynamic_cast<iterator_traits<list<char>::iterator>::iterator_category* > (&catc) << endl;
    
    return (0);
}
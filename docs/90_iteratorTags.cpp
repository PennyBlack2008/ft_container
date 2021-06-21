// https://en.cppreference.com/w/cpp/iterator/iterator_tags
#include <iostream>
#include <vector>
#include <list>
#include <iterator>

// quite foten implementation details are hidden in a dedicated namepsace
namespace implementation_details
{
    template<class BDIter>
    void alg(BDIter, BDIter, std::bidirectional_iterator_tag)
    {
        std::cout << "alg() called for bidirectional iterator\n";
    }

    template<class RAIter>
    void alg(RAIter, RAIter, std::random_access_iterator_tag)
    {
        std::cout << "alg() called for random-access iterator\n";
    } // namespace implementation_details

    template<class Iter>
    void alg(Iter first, Iter last)
    {
        implementation_details::alg(first, last, typename std::iterator_traits<Iter>::iterator_category());
    }

    int main()
    {
        std::vector<int> v; // random access iterator
        alg(v.begin(), v.end());

        std::list<int> l; // bidirectional iterator
        alg(l.begin(), l.end());
    }
}
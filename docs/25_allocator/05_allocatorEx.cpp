#include <memory>
#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    vector<int> v1;
    vector<int>::iterator v1Iter;
    vector<int>::allocator_type v1Alloc;

    int i;
    for (i = 1; i <= 7; i++)
        v1.push_back(i * 2);
    
    cout << "The original vector v1 is:\n ( ";
    for (v1Iter = v1.begin(); v1Iter != v1.end(); v1Iter++)
        cout << *v1Iter << " ";
    cout << ")." << endl;

    allocator<int>::const_pointer v1Ptr;
    const int k = 10;
    v1Ptr = v1Alloc.address(k);

    cout << "The integer's address found has a value of: "
            << *v1Ptr << "." << endl;
    return (0);
}
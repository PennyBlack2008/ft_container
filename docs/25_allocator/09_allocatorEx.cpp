#include <memory>
#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    vector<int> v1;
    vector<int>::iterator v1Iter;
    vector<int>::allocator_type v1Alloc;

    int i ;
    for (i = 0; i <= 7; i++)
        v1.push_back(i * 2);

    cout << "The original vector v1 is:\n ( ";
    for (v1Iter = v1.begin(); v1Iter != v1.end(); v1Iter++)
        cout << *v1Iter << " ";
    cout << ")." << endl;

    allocator<int>::const_pointer v1PtrA, v1PtrB;
    const int kA = 4, kB = 12;
    v1PtrA = v1Alloc.address(kA);
    v1PtrB = v1Alloc.address(kB);
    allocator<int>::difference_type v1diff = *v1PtrB - *v1PtrA;

    cout << "Pointer v1PtrA addresses " << *v1PtrA << "." << endl;
    cout << "Pointer v1PtrB addresses " << *v1PtrB << "." << endl;
    cout << "The difference between the integer's addresses is: "
            << v1diff << "." << endl;

    return (0);
}
#include <memory>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
    vector<int> v1;
    vector<int>::iterator v1Iter;
    vector<int>::allocator_type v1Alloc;

    int i;
    for (i = 1; i <= 7; i++)
        v1.push_back(2 * i);

    cout << "The original vector v1 is:\n ( ";
    for (v1Iter = v1.begin(); v1Iter != v1.end(); v1Iter++)
        cout << *v1Iter << " ";
    cout << ")." << endl;

    allocator<int>::pointer v1PtrA;
    int kA = 12, kB = -99;
    v1PtrA = v1Alloc.address(*find(v1.begin(), v1.end(), kA));
    v1Alloc.destroy(v1PtrA);
    v1Alloc.construct(v1PtrA, kB);

    cout << "The modified vector v1 is:\n ( ";
    for (v1Iter = v1.begin(); v1Iter != v1.end(); v1Iter++)
        cout << *v1Iter << " ";
    cout << ")." << endl;
}
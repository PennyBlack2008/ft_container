// allocator_address.cpp
// compile with : /EHsc
/*
무슨 예제인지 모르겠다.
그냥 const allocator 인 v1Ptr 의 값을 확인하려면, 
allocator type 을 미리 선언해서 이 선언된 변수를 활용해서 주소를 확인해야하는 구나,
라고 생각했다. 그런데, 굳이 왜 이렇게 만들어져있는 지, 왜 하나를 알려고 2개나 선언해야되는 지
이해가 안간다.
*/
#include <memory>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
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

    allocator<int>::const_pointer v1Ptr;
    const int k = 8;
    v1Ptr = v1Alloc.address(*find(v1.begin(), v1.end(), k));
    // v1Ptr = v1Alloc.address(k);
    cout << "The integer addressed by v1Ptr has a value of: "
            << "*v1Ptr = " << *v1Ptr << "." << endl;
}
// allocator_allocate.cpp
// compile with: /EHsc

#include <memory>
#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    allocator<int> v1Alloc;
    allocator<int>::pointer v1aPtr;
    v1aPtr = v1Alloc.allocate(10);
    
    int i;
    for (i = 0; i < 10; i++)
        v1aPtr[i] = i;
    for (i = 0; i < 10; i++)
        cout << v1aPtr[i] << " ";
    cout << endl;
    v1Alloc.deallocate(v1aPtr, 10);
    return (0);
}
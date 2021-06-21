#include <memory>
#include <iostream>
#include <vector>

using namespace std;

class Int
{
public:
    Int(int i)
    {
        cout << "Constructing " << (void*)this << endl;
        x = i;
        bIsConstructed = true;
    };
    ~Int()
    {
        cout << "Destructing " << (void*)this << endl;
        bIsConstructed = false;
    };
    Int& operator++()
    {
        x++;
        return (*this);
    };
    int x;
private:
    bool bIsConstructed;
};

int main(void)
{
    allocator<double> Alloc;
    vector<Int>::allocator_type v1Alloc;

    allocator<double> cAlloc(Alloc);
    allocator<Int> cv1Alloc(v1Alloc);

    if (cv1Alloc == v1Alloc)
        cout << "The allocator objects cv1Alloc & v1Alloc are equal." << endl;
    else
        cout << "The allocator objects cv1Alloc & v1Alloc are not equal" << endl;
    
    if (cAlloc == Alloc)
        cout << "The allocator objects cAlloc & Alloc are equal." << endl;
    else
        cout << "The allocator objects cAlloc & Alloc are not equal." << endl;
    return (0);
}
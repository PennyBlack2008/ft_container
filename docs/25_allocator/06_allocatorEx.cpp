#include <memory>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<double> v;
    vector<double>::iterator vIter, vfIter;
    vector<double>::allocator_type vAlloc;

    int j;
    for (j = 1; j <= 7; j++)
        v.push_back(100.0 * j);

    cout << "The original vector v is:\n ( ";
    for (vIter = v.begin(); vIter != v.end(); vIter++)
        cout << *vIter << " ";
    cout << ")." << endl;

    vfIter = v.begin();
    allocator<double>::const_reference vcref = *vfIter;
    cout << "The value of the element referred to by vref is: "
            << vcref << ",\n the first element in the vector." << endl;

    // const references can have their elements modified,
    // so the following woould generate an error:
    // vcref = 150;
    // but the value of the first element could be modified through
    // its nonconst iterator and the const reference would remain valid
    *vfIter = 175;
    cout << "The value of the element referred to by vcref, "
            << "\n after nofication through its nonconst iterator, is: "
            << vcref << "." << endl;
    return (0);
}
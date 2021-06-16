// template_name_resolution10.cpp
// compile with: /EHsc
#include <iostream>

using namespace std;

void f(int, int) { cout << "f(int, int)" << endl; }

template <typename T1, typename T2>
void f(T1, T2)
{
    cout << "void f(T1, T2)" << endl;
};

int main(void)
{
    long l = 0;
    int i = 0;
    int j = 1;
    f(l, i);
    f(0, 0);
    f(i, j);
    return (0);
}
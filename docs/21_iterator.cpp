#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    vector<int> v;
    for (int i = 0; i < 7; i++)
        v.push_back(10 * i);

    vector<int>::iterator iter;
    // vecotr 반복자 iter는 v의 시작점을 가리킴
    iter = v.begin();

    cout << &iter << endl; // 0x7ffee08db870
    cout << *iter << endl; // 0

    // 임의 접근
    cout << iter[1] << endl;

    iter += 2;
    cout << &iter << endl; // 0x7ffee08db870 iter 에 +2 해도 주소값은 그대로지만,
    cout << *iter << endl; // 20 iter 에 +2 하면 참조하는 값은 달라짐.

    for (iter = v.begin(); iter != v.end(); iter++)
        cout << *iter << endl;

    return (0);
}
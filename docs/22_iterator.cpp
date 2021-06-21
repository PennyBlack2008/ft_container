#include <iostream>
#include <vector>

using namespace std;
int main()
{
    // 벡터 생성
    vector<int> vt;

    for(int i = 1; i < 6; i++)
        vt.push_back(i);

    vector<int>::iterator iter;

    for (iter = vt.begin(); iter != vt.end(); iter++)
        cout << "vector : " << *iter << endl;

    iter = vt.begin();

    for (int i = 0; i < 5; i++)
        cout << iter[i] << endl;

    iter += 2;
    cout << *iter << endl;

    return (0);
}
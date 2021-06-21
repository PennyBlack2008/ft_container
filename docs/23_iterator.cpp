/*
begin() 은 첫 원소를 가리킨다.

그런데, end() 은 마지막 원소의 다음 번째 를 가리킨다.

쉽게 생각하려면

for (iter = STL.begin(); iter < STL.end(); iterator++)
*/

#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
    vector<int> ar = { 1, 2, 3, 4, 5};

    vector<int>::iterator ptr;

    cout << "The vector elements are : ";
    for (ptr = ar.begin(); ptr < ar.end(); ptr++)
        cout << *ptr  << " ";
    return (0);
}
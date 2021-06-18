// http://cplusplus.com/reference/vector/vector/insert/
/*
리턴 값이 참 특이하다.

벡터.insert 는 이제 첫 element 가 된 iterator 를 반환한다.
*/
#include <iostream>
#include <vector>

int main(void)
{
    std::vector<int> myvector(3, 100); // 100 100 100
    std::vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert(it, 200); // 200

    myvector.insert(it, 2, 300); // 300 300

    // "it" no longer valid, get a new one:
    it = myvector.begin();

    std::vector<int> anothervector(2, 400); // 400 400
    myvector.insert(it + 2, anothervector.begin(), anothervector.end());

    int myarray[] = { 501, 502, 503 };
    myvector.insert(myvector.begin(), myarray, myarray + 3);

    std::cout << "myvector contains: ";
    for (it = myvector.begin(); it < myvector.end(); it++)
        std::cout << ' ' << *it;
    std::cout << '\n';
    
    return (0);
}
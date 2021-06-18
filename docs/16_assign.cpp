// Vector Assign
// http://cplusplus.com/reference/vector/vector/assign/

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> first;
    std::vector<int> second;
    std::vector<int> third;

    first.assign(7, 100); // 빈 벡터 first 에 100 이 7개
    
    std::vector<int>::iterator it;
    it = first.begin() + 1; // first 의 begin 하나 뒤로 it 설정

    second.assign(it, first.end() - 1); // 빈 vector 인 second 에 it 부터 ~ first 의 끝의 하나 앞까지

    int myints[] = { 1776, 7, 4 };
    third.assign(myints, myints + 3); // assigning from array

    std::cout << "Size of first: " << int (first.size()) << '\n';
    std::cout << "Size of second: " << int (second.size()) << '\n';
    std::cout << "Size of third: " << int (third.size()) << '\n';
    return 0;

}
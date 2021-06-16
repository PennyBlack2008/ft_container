// https://github.com/Glagan/42-ft_containers/commit/bf285b00f70768ddd2b0a23c2bf1d8688d2bd720
#include <iostream>
#include "vector.hpp"

int main(void)
{
    ft::vector<int> vector;
    std::cout << "Empty vector: " << std::endl;
    ft::vector<int>::iterator it = vector.begin();
    ft::vector<int>::iterator ite = vector.end();
    while (it != ite)
    {
        std::cout << *it << std::endl;
        it++;
    }

    // 2 elements
    vector.push_back(5);
    vector.push_back(42);

    std::cout << "2 elements in vector (index): " << std::endl;
    for (size_t i = 0; i < 2; i++)
    {
        std::cout << vector[i] << " (" << vector.at(i) << ")" << std::endl;
        // at(숫자) 는 idx 번째 원소를 참조한다. v[idx] 보다 속도는 느리지만 범위 점검해서 안전하다
    }
    
    std::cout << "2 elements in vector(iterator): " << std::endl;
    it = vector.begin();
    ite = vector.end();
    while (it != ite)
    {
        std::cout << *it << std::endl;
        it++;
    }

    // A lot of elements
    for (size_t i = 0; i < 500; i++)
        vector.push_back(i);

    std::cout << "502 elements in vector(index): " << std::endl;
    it = vector.begin();
    ite = vector.end();
    while (it != ite)
    {
        std::cout << *it;
        it++;
        if (it == ite)
            std::cout << std::endl;
        else
            std::cout << ", ";
    }

    // Reverse
    std::cout << "502 elements in vector(reverse_iterator): " << std::endl;
    ft::vector<int>::reverse_iterator rit = vector.rbegin();
    ft::vector<int>::reverse_iterator rite = vector.rend();
    while (rit != rite)
    {
        std::cout << *rit;
        rit++;
        if (rit == rite)
            std::cout << std::endl;
        else
            std::cout << ", ";
    }

    // system("leaks ft_containters");
}
#include <iostream>
#include <string>

template <typename T>
T sum(T a, T b)
{
    return (a + b);
}

template <typename T>
T sub(T a, T b)
{
    return (a - b);
}

int main(void)
{
    int a = 1, b = 2;

    double d1 = 2.2, d2 = 3.3;

    std::string s1 = "Show me ";
    std::string s2 = "The Money 6";

    std::cout << "int 합: " << sum<int>(a, b) << std::endl;
    std::cout << "double 합: " << sum<double>(d1, d2) << std::endl;
    std::cout << "string 합: " << sum<std::string>(s1, s2) << std::endl;

    std::cout << "int 차: " << sub<int>(a, b) << std::endl;
    std::cout << "double 차: " << sub<double>(d1, d2) << std::endl;

    return (0);
}
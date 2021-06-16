#include <iostream>
#include <string>

template <typename T>
class Person
{
public:
    Person(std::string name, T height);
    void printAll(void);
    void setNumber(T height);
private:
    std::string mName;
    T mHeight;
};

template <typename T>
Person<T>::Person(std::string name, T height)
    : mName(name)
    , mHeight(height)
{
}

template <typename T>
void Person<T>::printAll(void)
{
    std::cout << "name : " << mName << std::endl;
    std::cout << "number : " << mHeight << std::endl;
};

template <typename T>
void Person<T>::setNumber(T height)
{
    mHeight = height;
}

int main(void)
{
    // main 함수는 동일
    Person<int> p1("Mr.Dev C++", 173);
    Person<std::string> p2("Ms.Unix", "155cm");

    p1.printAll();
    p2.printAll();
    std::cout << std::endl;

    p1.setNumber(188);
    p2.setNumber("2m 10cm");
    std::cout << std::endl;

    p1.printAll();
    p2.printAll();
    return (0);
}
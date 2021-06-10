// https://www.youtube.com/watch?v=GutCygNRi-I&t=0s
// https://velog.io/@kjh3865/CC-R-value-%EC%B0%B8%EC%A1%B0%EC%9E%90%EB%A3%8C

#include <string>

void storeByValue(std::string s)
{
    std::string b = s;
}

void storeByLRef(std::string& s)
{
    std::string b = s;
}

void storeByRRef(std::string&& s) // 임시 값 rvalue 가 변수처럼 argument로 들어간다.
{
    // std::string b = s; // 잘못된 선언, 이렇게 선언하면  s 가 lvalue 로 바뀐다.
    std::string b = std::move(s);
}

int main(void)
{
    std::string a = "abc";
    storeByValue(a);
    storeByLRef(a);
    // storeByRRef(a); // wrong
    storeByRRef("abcd");
    storeByRRef(std::move(a));
}
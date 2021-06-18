// https://cutemoomin.tistory.com/entry/rvalue-%EC%B0%B8%EC%A1%B0
// https://m.blog.naver.com/zxwnstn/221683580396
// https://popawaw.tistory.com/56 익명 객체
// 익명 함수는 Lvalue 가 아닌 Rvalue 처럼 작동한다.

#include <iostream>
using namespace std;

class Cents
{
private:
    int m_cents;
public:
    Cents(int cents) { m_cents = cents; }
    int getCents() const { return m_cents; }
};

// Cents 를 리턴하는 함수
Cents add(const Cents& c1, const Cents& c2)
{
    return Cents(c1.getCents() + c2.getCents());
}

int main()
{
    cout << add(Cents(7), Cents(9)).getCents() << endl;
    return (0);
}
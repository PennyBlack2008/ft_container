// https://cutemoomin.tistory.com/entry/rvalue-%EC%B0%B8%EC%A1%B0

/*
Q. Lvalue 인지 Rvalue 인지 헷갈린다면?
주소 연산자 & 를 붙여서 에러가 나면 Rvalue

&(++x);
&(x++); // error, '&' requires l-value

lvalue : 표현식이 종료된 이후에도 없어지지 않고 지속되는 개체(예. 모든 변수)
rvalue : 표현식이 종료되면 더 이상 존재하지 않는 임시적인 개체(예. 상수, 임시객체)
*/

int rvalue()
{
    return (10);
}

int main(void)
{
    int lvalue = 10;
    int& a = lvalue;
    int& b = rvalue();
    int&& c = lvalue;
    int&& d = rvalue();

    return (0);
}
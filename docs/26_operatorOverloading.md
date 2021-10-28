# Operator Overloading

[참고 링크](https://www.learncpp.com/cpp-tutorial/overloading-operators-using-member-functions/)

연산자 오버로딩에서 friend를 붙여줄 때와 붙여주지 않을 때가 궁금해서 4시간 정도를 소비했다. 한글 문서로 사전 학습을 하고 긴 영문을 읽어서 공부했다.

이 세가지가 member function으로 연산자 오버로딩할 때 조건이다. 이에 해당하지 않으면 frined로 선언해야한다.

- The overloaded operator must be added as a member function of the left operand.
- The left operand becomes the implicit *this object
- All other operands become function parameters.

왼쪽 피연산자가 *this를 암시해야되니깐, friend function으로 이렇게

```
friend Cents operator+(const Cents &cents, int value);
```

~~할 것을, member function으로 하면,~~

```
// friend function <--- freind function이라고 명시되어있는 데 멤버 함수라고 하고 있는 내 실수
Cents operator+ (int value);
```

~~이렇게 안 예쁘게 된다.~~



----------------
!!밑은 잘못된 해석일 가능성이 매우 높음.

friend를 붙여줄 때와 그대로 member function으로 하는 2가지 경우가 있다.

일단, member function으로 반드시 선언해서 사용해야하는 경우가 있다.

- '=, [], (), ->'를 overloading 할 때
    - 이유는 언어적 특성 때문
- 단항연산자를 사용할 경우, '+(양수 표기), -(음수 표기), ++, --, !, (type), ~'


~~member function이 아닌 friend로 반드시 선언해서 사용해야하는 경우가 있다.~~

~~-피연산자가 해당 class의 멤버가 아닌 것이 하나라도 있을 경우~~

----------------
위에도 잘못된 결론이다. ykoh가 바로잡아줬다.

```
#include <iostream>

class Cents
{
private:
    int m_cents {};

public:
    Cents(int cents)
        : m_cents { cents } { }

    // Overload Cents + int
    friend Cents operator+(const Cents &cents, int value);

    int getCents() const { return m_cents; }
};

// note: this function is not a member function!
Cents operator+(const Cents &cents, int value)
{
    return Cents(cents.m_cents + value);
}

int main()
{
	Cents cents1 { 6 };
	Cents cents2 { cents1 + 2 };
	std::cout << "I have " << cents2.getCents() << " cents.\n";

	return 0;
}
```
링크에서 가져온 링크인데
10:26
여기 코드에서 보면
10:26
```
// note: this function is not a member function!
Cents operator+(const Cents &cents, int value)
{
    return Cents(cents.m_cents + value);
}
```
이거는 멤버 함수가 아니라
10:26
Cents 클래스에서 사용하지 못하는 함수라서
10:26
friend 키워드 넣어서 Cents 클래스에서 사용할수 있게 하는거
10:26
딱 요정도 역할로 생각하면될듯
10:26
원래 멤버함수가 아니면 못쓰는데 이걸 멤버함수가 아님에도 쓸수있게 해주는 테크닉임
10:28
stack에서 이렇게 nonmemberfunction으로 구분되어있어서
stack 클래스 자체가 연산자를 쓸수없으니
10:30
첫번째 사진처럼 friend 키워드 붙여줘서 두번째 사진과 같은 연산자를 사용하게 해주는거


내가 집에 가면서 예시코드를 검토를 별로 안하고 보내서 이런 사태가 발생한 것같다.

일단, ykoh의 이야기가 맞는 얘기고 원래 내가 가져왔어야할 예시는 

충격 받아서, 내가 왜 저렇게 말했을 까? 생각해보니깐 내가 마지막 예시 코드를 잘못들인 것같아.
내 원래 의도 -->
friend를 써주는 이유는 이것이 아닐까?
friend function으로 이렇게
```
friend Cents operator+(const Cents &cents, int value);
할 것을, member function으로 하면,
Cents Cents::operator+ (int value)
{
    return Cents { m_cents + value };
}
```
이렇게 안 예쁘게 되니깐! (링크)
그리고 너가 답장으로 알려준 이유가 맞는 것같음 ㅎㅎ

였다.
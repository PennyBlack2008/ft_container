# Rvalue Reference

## Rvalue Reference 알아보기
Rvalue reference 는 C 11 표준에서 추가된 기능이다.

Rvalue reference 를 이용하면 argument 에서 생기는 값과 변수에 rvalue를 대입할 때 복사를 줄일 수 있다. 

[유튜브강의링크](https://www.youtube.com/watch?v=GutCygNRi-I&t=0s)

![reference사진](https://media.vlpt.us/images/kjh3865/post/7ce14002-ce86-42c3-8d66-983c01166c4a/R-value2.png)

**1. 가장 오른쪽 그림**

첫 번째 함수 storByValue 가 작동한 것을 그림으로 그린 것이다.

(i) 원본 a, rvalue "abc" 가 있다.

(ii) storeByValue 에 들어갈 argument 로 "abc"가 복사된다.

(iii) std::string b 로 "abc" 가 복사된다.

그래서 rvalue "abc" 가 총 3번 쌓이게 된다.

**2. 가운데 그림**

두 번째 함수 storeByRef 가 작동한 것을 그림으로 그린 것이다.

(i) 원본 a, rvalue "abc" 가 있다.

(복사없음) storeByRef 에 rvalue "abc" 가 그대로 들어간다.

(ii) std::string b 로 "abc" 가 복사되어 들어간다.

그래서 rvalue "abc" 가 총 2번 쌓이게 된다.

**3. 가장 왼쪽 그림**

세 번째 함수 storeByRRef 가 작동한 것을 그림으로 그린 것이다.

(i) 원본 a, rvalue "abc" 가 있다.

(복사없음) storeByRRef 에 rvalue "abc" 가 그대로 들어간다.

(복사없음) std::string b 로 rvalue "abc" 가 그대로 들어간다.

그래서 rvalue "abc" 가 총 1번 쌓이게 된다.

주의할 점은 std::move 를 써줘야한다. 이동생성자를 구현할 때 std::move 를 제대로 써주지 않는 다면, rvalue 를 복제하여 복사생성자가 실행된다.

## 이동생성자 알아보기

Rvalue reference 를 활용한 이동생성자를 알아보자.

다음의 코드에서 a 객체에 담긴 동적할당된 변수 가리키는 포인터 멤버 포함 모든 멤버들을 완벽하게 v[0] 에 넣어놓는다. b 도 마찬가지다.

이 때, 원본인 a 객체의 data 는 nullptr 를 가리키게 되어 더이상 원본이 아니게된다.

```
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class A {
public:
    A() {}
    A(string s) : s(s), data(new char[100])
    { cout << " constructor" << endl; }
    // A(const A& ref)
    // {
    //     this->s = ref.s;
    //     this->data = new char[10000];
    //     cout << s << " copy constructor" << endl;
    // }
    A(A&& ref) noexcept
    {
        this->s = ref.s;
        this->data = ref.data;
        ref.data = nullptr;
        cout << s << " move constructor" << endl;
    }
    ~A()
    {
        delete[] data;
        cout << " ~constructor" << endl;
    }
    void print() { printf("v[?].data 변수의 주소 값: %x\n", (this->data)); }

    string s;
    char* data;
};

int main(void)
{
    vector<A> v;

    A a("a");
    A b("b");

    printf("a.data 변수의 주소 값: %x\n", a.data);
    v.push_back(move(a)); // 벡터에 값(a) 입력
    v[0].print(); // v[0] 에 있는 data 가 가리키는 주소 값 출력

    printf("b.data 변수의 주소 값: %x\n", b.data);
    v.push_back(move(b)); // 벡터에 값(b) 입력 <-- 무조건 move(b) 를 해줘야한다. 안그러면 복사생성자가 생성된다.
    v[1].print();

    cout << "/////////// cut ///////////" << endl;
    return (0);
}
```

결과 예시로는 객체의 data 가 가리키는 주소와 vector 에 들어간 data 가 가리키는 주소가 같다는 것을 알 수 있다.

```
jikang@c1r9s5 docs % ./a.out             constructor
 constructor
a.data 변수의 주소 값: 18405880
a move constructor
v[?].data 변수의 주소 값: 18405880
b.data 변수의 주소 값: 184058f0
b move constructor
a move constructor
 ~constructor
v[?].data 변수의 주소 값: 184058f0
/////////// cut ///////////
 ~constructor
 ~constructor
 ~constructor
 ~constructor
```

## 혼란스러운 점

rvalue 는 어짜피 컴파일러가 컴파일 시간에 계산을 하기 때문에 바이너리 파일은 똑같을 것같다는 생각이 들었다. 그래서, 이런식으로 짜는 것이 의미가 있을 까? 라는 의문을 갖게 되었다. 

-> 고민 해결! 그림을 자세히 보면 "abc" 를 담은 변수가 가장 적기 때문에 변수 복사도 가장 덜 일어난다. 그래서 좀 더 빠를 것이다. 근데 이 해석이 틀리면 어떡하지?
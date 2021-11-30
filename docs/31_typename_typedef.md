[여기가 짱임](https://wikidocs.net/419)


## 왜 컨테이너에 typename, typedef를 많이 쓸까?

### typedef을 왜 사용할 까?

typedef는 길고 긴 type을 쉽게 표현하기 위해 사용된다.

### typename을 왜 사용할 까?

```
template <class T>
void func(const T& obj)
{
  typename T::size_type _size;
}
```

위 코드는 아래와 같이 컴파일 에러를 발생시킨다.

``C7510 'size_type': use of dependent type name must be prefixed with 'typename'``

그런데, class를 쓰지 않고 typename으로 바꿔주면, 정상 작동한다.

왜냐하면 예를 들어, string 타입을 인자로 전달할 경우 string::size_type 타입을 사용하려는 의도이지만 T의 타입은 컴파일 과정에서 해당 함수 호출 시점에서 정해지기 때문에 미리 컴파일러에게 T::size_type이 타입이라는 것을 알려주어야한다.

이렇게 타입 안에 타입의 객체를 호출된 것을 중첩 의존 타입 이름이라고 하고 이 때 typename을 명시해줘야한다.

```
template <typenmae T>
void func(const T& obj)
{
  typename T::size_type _size;
}
```

대부분의 경우에 class 대신 typename을 써도 되지만, 상속 관계를 나타낼 때(기반 클래스 지정자, base-specifier)나 멤버 초기화식(mem-initializer) 할 때는 typename을 써주지 않는다.

### 부분 특수화
  - ``MyClass<int*, int*>``가 ``MyClass<T, T>``와 ``MyClass<T1*, T2*>``로 모두 가능하기 때문에 모호해진다.
  - 그래서 이렇게 표현하는 게 좋다.

  ```
  template <typename T>
  class MyClass<T*, T*>
  {
    ...
  };
  ```

예시

```
template <class T>
void func(const T& obj)
{
  T::size_type _size;
}
```
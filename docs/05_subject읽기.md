# Subject 해석

## Mandatory part

- 컨테이너를 구현하고 필요한 파일을 <continer>.hpp 에 넣는다.
    - !정확한 표현 파악필요하다

- 테스트 하는 main.cpp 준비해라.

- member functions, Non-member and overloads are expected.
    - 무슨 말인지 애매한 것같다.
        - 멤버 함수, 비멤버 함수와 오버로딩이 가능해야한다.
            - 뭐가 가능해야하는 지 모르겠다.

- 멤버 함수 get_allocator가 예상되지 않는 경우 std::allocator를 사용할 수 있습니다.
    - 무슨 말인지 모르겠다.
        - 어떤 상황에서 get_allocator 가 예상되지 못할 까?
        - std::allocator 에 대한 지식 부재

- 지도에 대한 간단한 배열을 사용하여 각 컨테이너의 내부 데이터 구조를 정당화해야합니다.

- 컨테이너에 반복자 시스템이있는 경우 이를 단순화해야합니다.
    - 무슨 말인지 모르겠다.

- https://www.cplusplus.com/ 로 c++98 버전을 체크하면서 보기가 편할 것이다.

- https://cppreference.com/ 는 최신 버전을 참고하는 데 좋다.

- 표준 컨테이너에서 제공하는 것만 하세요. 각 공용 함수 /-변수는 정당화되어야합니다.

- non-member 오버로드의 경우 friend 키워드가 허용됩니다. 친구의 각 사용은 정당화되어야하며 평가 중에 확인됩니다.

다음을 구현하시오.

- List
    - LL
- Vector
    - ?
- Map
    - red black tree
- Stack
- Queue

물론 STL은 금지되어 있습니다. 그러나 STD 라이브러리를 사용할 수 있습니다.
    - 어디 까지가 std 라이브러리로 치부하는 지 모르겠다.

## Bonus Part

필수 부분을 완전히 완료했다면 보너스를 시도하고 제출할 수 있습니다.

보너스로 다음 컨테이너 및 관련 기능을 제출할 수 있습니다.

- Deque
- Set
- Multiset
- Multimap
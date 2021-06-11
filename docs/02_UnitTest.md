# 구글 테스트

[슬라이드 링크](https://www.slideshare.net/jinhwason/ss-69528881)
[예시 링크1](https://github.com/dmonopoly/gtest-cmake-example)
[예시 링크2](https://github.com/kaizouman/gtest-cmake-example)
## 개념정리

- 단위 테스트(unit test)
    - 소스코드의 특정 모듈이 의도된 대로 정확히 작동하는 지 검증하는 절차
    - 모든 함수와 메소드에 대한 테스트 케이스를 작성한다.
    - 장점
        - 문제점 발견이 쉽다.
        - 변경이 쉽다.
        - 통합이 간단함.
    - 테스트 도구
        - Cpp Unit
        - Google test

- 통합 테스트
    - 단위 테스트에서 확장된 것
    - 둘 이상의 모듈을 하나의 그룹으로 테스트하는 것

- Google Test 를 사용한 이유
    - 하나의 test 는 다른 test 와 독립되어 있고 반복 가능
    - 테스트 케이스 그룹을 만들 수 있어서 코드 파악에 도움이 된다.
    - 플랫폼 중립적이어서 재사용이 용이
    - 하나의 테스트 케이스를 실패해도 전체 테스트를 계속 진행할 수 있다.

## 사용법

### 테스트 케이스

```
TEST(테스트 그룹 이름, 그룹 내 하위 테스트 이름)
{
    // 테스트 수행 내용
}
```

이렇게 선언하면 자동으로 프로그램 수행 시 실행될 테스트로 등록된다.

**특징**

- 테스트가 수행되는 순서는 랜덤
- 테스트를 사용하지 않을 경우 앞에 DISABLED_ 키워드를 붙인다.
- 필터로 원하는 테스트만 수행 가능 -gtest_filter

**사용법 - Assertions**

- 결과가 참인지 확인한다.
- 결과는 성공, 심각하지 않은 실패, 심각한 실패로 3가지이다.
- 매크로처럼 사용

- ASSERT_*
    - 조건문이 참이 아닐 경우, 실패를 출력하고 현재 테스트를 종료.
    - ASSERT_TRUE(condition);
    - ASSERT_EQ(val1, val2);
    - ASSERT_STREQ(str1, str2);
    - 
        ```
        TEST(FactorialTest, HandlesZeroInput)
        {
            EXPECT_EQ(1, Factorial(0));
        }
        ```
- EXPECT_*
    - 조건문이 참이 아닐 경우, 실패를 출력하고 다음 테스트를 계속 진행

**사용법 - Test Fixtures**

- 여러 테스트에서 공통으로 사용하는 객체설정을 정의
- ::testing::Test 를 상속 받아서 사용한다.
- Setup()
    - 테스트에 필요한 설정을 세팅한다.
    - 각각의 테스트 케이스가 시작되기 전에 호출된다.
- TearDown()
    - 테스트에 사용한 자원들을 해제할 때 사용.
    - 각각의 테스트 케이스가 끝날 때 호출.
    - 
        ```
        Class MyFixture : public testing::Test
        {
        Public:
            User m_pUser*;
            MyFixture();
            ~MyFixture();
            virtual void SetUp();
            virtual void TearDown();
        }

        void MyFixture::SetUp()
        {
            InitializeUser();
        }

        void MyFixture::TearDown()
        {
            m_pUser->CleanUp();
        }

        TEST_F(MyFixture, 사용테스트)
        {
            m_pUser->SetMoney(100);
            EXPECT_EQ(100, m_pUser->GetMoney());
            m_pUser->ConsumeMoney(5);
            EXPECT_EQ(95, m_pUser->GetMoney());
        }

        TEST_F(MyFixture, 획득 테스트)
        {
            m_pUser->GetMoney(50);
            EXPECT_EQ(50, m_pUser->GetMoney());
        }
        ```
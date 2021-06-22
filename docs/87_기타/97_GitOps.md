# GitOps

데브 옵스의 확장 모델

> "개발과 운영의 벽을 허물어 더 빨리 더 자주 배포하자"

## 깃 옵스란?

**무슨 그림인지는 모르겠지만, 아무튼 크흠**
![](https://image.samsungsds.com/kr/insights/gitops_img01.jpg?queryString=20210621120951)

애플리케이션의 배포와 운영에 관련된 모든 요소를 코드화하여 깃(git) 에서 관리(Ops)하는 것이 깃 옵스의 핵심이다.

핵심 아이디어
- 배포와 관련된 모든 것을 "선언형 기술서" 형태에 작성해서 Repository 에서 관리함
- Config Repository 의 "선언형 기술서" 와 운영 환경 간 상태 차이가 없도록 유지 시켜주는 자동화 시스템을 구성

## 선언형 기술서???

1) 선언형 모델 (Declarative Model)

만약 애플리케이션 배포를 할 때 여러 OS 가 섞여 있다면, 아래코드 처럼만 작성하면, OS 에 따라 관련 없이 잘 작동한다.

```
- name: Create a directory if it does not exist
file:
path: /etc/some_directory
state: directory
(https://docs.ansible.com/ansible/latest/collections/ansible/builtin/file_module.html)
```

2) 단일 진실 공급원 (Single Source Of Truth, SSOT)

데이터 정규화 작업에 이용된다. 만약, 데이터가 수정된다면 그 데이터를 사용하는 테이블 모두 데이터를 수정해야한다. 실수로 프로그래머가 수정된 데이터의 테이블을 수정하지 않는 다면, 문제가 생긴다.

## 깃옵스 구현

1) 저장소 전략

애플리케이션 저장소, 배포 환경 구성 저장소 이렇게 2개를 둔다.

2) 배포 전략

Push Type, Pull Type 두 가지의 배포 전략

1, 2 가 정확히 뭐가 중요하고 왜 이렇게 하는 지 이해하지 못함.

## 깃옵스 장점

1) 정보의 신뢰성

 깃 이력을 보면 현재 상태는 물론 누가, 언제, 왜, 어느 곳을 수정했는 지 쉽게 알 수 있다.

 에러 복구의 편리함: git revert 만 사용하면 배포환경이 이전 버전으로 롤백된다.

2) 익숙한 절차

 git commit -> push -> merge request -> review -> merge

 리뷰 절차를 통해 휴먼 에러를 조기에 발견하고 책임을 나눌 수 있음.
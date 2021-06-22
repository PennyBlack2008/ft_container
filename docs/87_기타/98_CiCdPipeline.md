# CI/CD Pipeline

DevOps 핵심 업무. 이것을 잘하면 고객에게 안정감 있는 서비스를 배포하여 운영할 수 있음.
- Jenkins
- Travis CI
- Bamboo

CI(Continuous Intergration) 는 개발자를 위한 자동화 프로세스인 지속적인 통합을 의미

CD(Continuous Delivery, Deployment) 는 지속적인 서비스 제공 및 지속적인 배포

## CI/CD 파이프라인의 요소

OpenShift Pipelines는 Tekton에 구축된 Red Hat OpenShift 기능 중 하나입니다. 

![CI/CD](https://www.redhat.com/cms/managed-files/styles/wysiwyg_full_width/s3/ci-cd-flow-desktop_0.png?itok=QgBYmjA2)

- Build
- Test
- Release
- Deploy
- Validation & compliance

## CI

![CI png](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbGXdIT%2FbtqI9GkH3wP%2F5Qx2zLKYRxsYWLSoS6KH3K%2Fimg.png)

CI 의 핵심 목표는 버그를 신속하게 찾아 해결하고, 소프트웨어 품질을 개선, 새로운 업데이트의 검증 및 릴리즈의 시간을 단축시키는 것.

## CD

![CD png](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FeeSLmu%2FbtqI9pXqCN8%2FiIopSPh3KSK1SwhRjkWPf1%2Fimg.png)

Continuous Delivery 는 공유 레포지토리로 자동으로 Release 하는 것,
Continuous Deployment 는 Production 레벨까지 자동으로 deploy 하는 것을 의미.

즉 CD 는 개발자의 변경 사항이 레포지토리를 넘어, 고객의 프로덕션 환경까지 릴리즈되는 것을 의미.
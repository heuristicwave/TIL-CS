## Background Knowledge on DevOps

### ITS : Issue Tracking System

애자일 개발에 대응 가능하도록 백로그 및 버그 관리 기능

- JIRA
- Redmine
- Trac
- PagerDuty

문서화 도구

- 레드마인 - Wiki
- Confluence



### Continuous Integration

코드의 build 및 정적, 동적 테스트를 빈번하게 계속적 실시

장점 : 코드로 인하여 발생하는 문제를 조기에 발견하고 Build, 테스트에 관계된 작업 비용의 낮춤, 테스트 상황의 가시화, 딜리버리 타임의 단축

- Jenkins
- Travis CI
- Circle CI



#### Continuous Delivery

구축부터 시험까지의 JOB이 성공하면, 운영 환경으로 Release 준비까지 완료



### 모니터링

PDCA 사이클에서 Check을 하기 위한 기반

CPU 사용률 및 메모리 사용량, 디스크 I/O의 리소스 소비 비율 등 매트릭스를 모니터링

로그의 양이 많아 각 분야에서 미들웨어 조합

Elasticsearch(로그 검색), Logstash(로그 수집), Kibana(로그 가시화)



##### 각종 감시 장비

- Zabbix
- Munin
- JP1
- Hinemos

- Grafana - 모니터링 인터페이스
- Fluentd - 로그 수집



### 가상 환경 구축 도구

Infrastructure as Code : Vagrant



### 인프라 구성 관리 도구

- Ansible
- Chef
- Puppet

---

위 내용은 `IT 운용 체베 변화를 위한 DevOps ` 보고 요약한 내용입니다.


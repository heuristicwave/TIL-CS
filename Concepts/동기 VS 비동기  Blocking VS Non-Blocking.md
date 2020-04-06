## 동기 VS 비동기 / Blocking VS Non-Blocking

Blocking I/O : System Call이 끝날때까지 프로그램 대기, System Call이 완료가 되면 그 때 Return ex) scanf



### Non-Blocking Vs ASynchronous 차이점

*System Call이 즉시 Return될 때 데이터의 포함 유무*

- Asynchronous은 **요청에 처리 완료와 관계없이 응답 이후 운영체제에서 응답할 준비가 되면 응답**
- Non-Blocking은 **요청에 처리할 수 있으면 바로 응답하고 아니면 Error를 반환**

### Blocking Vs Synchronous 차이점

*Wait Queue 유무*

- Blocking은 **System Call의 Return을 기다리는 동안 필수로 Wait Queue에 머문다**
- Synchronous은 **System Call의 Return을 기다리는 동안 Wait Queue에 머물 수도 아닐 수도 있다**



[참고자료](https://nesoy.github.io/articles/2017-01/Synchronized)
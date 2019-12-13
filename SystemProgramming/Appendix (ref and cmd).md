## References

[Blocking & Non-blocking](https://tech.peoplefund.co.kr/2017/08/02/non-blocking-asynchronous-concurrency.html)

[fcntl 파일_제어](https://www.joinc.co.kr/w/Site/system_programing/File/Fcntl)

[I/O Multiplexing](https://dbehdrhs.tistory.com/98)

[Processor Affinity](https://jeep-shoes.tistory.com/64)



### 개념체크

[void 포인터 반환하기](https://dojang.io/mod/page/view.php?id=530)



#### 명령어 수행 상태확인

```shell
echo $?
```



#### pid로 kill 수행

`!ps` 명령어로 pid를 확인하여 kill 할 수 있지만 아래와 같은 명령어 가능

```shell
kill -TERM `pidof signal`
killall -TERM signal
```



#### sigaction send & recv

```shell
# after run sigaction_recv

kill -USR1 `pidof sigaction_recv` # print sigaction_recv msg

./sigaction_send `pidof sigaction_recv` data # print sigaction_recv data
```


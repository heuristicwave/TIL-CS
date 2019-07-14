### setuid - 4000

setuid가 설정된 파일을 실행하면 파일의 소유자 권한으로 실행

>  /etc/passwd의 경우 매번 root에게 요청하면 root가 힘드니까 각각의 user가 pw를 바꿀 수 있도록 root권한을 부여받는다

```shell
chmod 4755 [File Name]
```



### setgid - 2000

파일의 소유그룹 권한을 가짐



### stickyBit - 1000

공유디렉토리를 의미, 생성한 사람의 소유



### [find 명령어](https://recipes4dev.tistory.com/156)

```shell
find . -name [FILE]		// 현제 디렉토리 아래 모든 파일 및 하위 디렉토리에서 검색
find / -name [FILE]		// 루트 디렉토리 아래 모든 파일 검색 (전체 시스템)

find / -perm 4000	// 4000과 같은 퍼미션을 검색
// (-4000 : 4000포함 권한 검색 / +4000 : 4000이 일부라도 포함된 권한 검색)

// 6000 : setuid & setgid
// 2> /dev/null 에러제거 옵션
find / -perm +6000 -user [File] 2> /dev/null
```



### VI 와 쉘 명령어

:!{shell command} – 쉘 명령를 vi 안에서 실행
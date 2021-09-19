# Shell Script

- 리눅스 command 들을 모아 놓은 ASCII text 파일
- 실행 권한을 할당해야 실행 가능 : `chmod +x sample.sh`
- top-down 방식으로 해설해서 실행
- Sub shell
  - `#!/bin/bash` shebang(hashbang) 스크립트를 실행할 sub shell 이름

<br>

## LAB

### Quiz 1. 현재 디렉토리의 모든 파일 목록을 특정 위치에 저장하기

현재 디렉토리의 모든 파일 목록을 현재 위치에 저장하는 script를 작성하시오.

**Example Result**

```shell
$ cat quiz01.txt
quiz01.txt
file1
file2
```

<details>
  <summary>💡 Hint</summary>

```shell
ls > $(pwd)/quiz01.txt
```

</details>

<br>

[💯 Answer](./LAB/quiz01.sh)

<br>

---

[강의 동영상 : 따배셸](https://youtube.com/playlist?list=PLApuRlvrZKog2XlvGJQh9KY8ePCvUG7Je)

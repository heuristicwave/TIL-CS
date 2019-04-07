## 2019학년도 1학기 컴퓨터 프로그래밍 튜터링에 진행관련 내용입니다.

## 구름 IDE 사용법

파일 만들기 

```shell
touch 파일이름.c
```



실행파일 만들기

```shell
gcc -o 실행파일이름 파일이름.c

// 예시
// helloworld.c로 실행파일을 만드려면
// gcc -o myprogram helloworld.c
```



생성된 실행파일 실행시키기

```shell
./실행파일이름

// 예시
// 위에서 만든 myprogram을 실행시키려면
// ./myprogram
```

<br>




## 추천 교재 및 레퍼런스

[C발라먹기](http://www.realhanbit.co.kr/books/149)

구글아이디로 가입하고 구매하기를 누르면 끝!

[씹어먹는 C언어 - 개념 및 c언어 레퍼런스](https://modoocode.com/notice/15)

<br>



## Visual Studio 활용

### [생산성을 향상](<https://blogs.msdn.microsoft.com/visualstudio/2018/08/30/improving-your-productivity-in-the-visual-studio-editor/> ) 시켜주는 단축키

**IntelliSense**  : Tab



전체 주석 : Ctrl + k + c

전체 주석 해제 : Ctrl + k + u

코드정렬 : (Ctrl + A) 전체지정 한 후, => Alt + F8

빌드& 실행 : ctrl + F5



여러 행 선택 후 편집 : Alt + Shift + 화살표

```c
// 예시
// 아래 3개의 %f를 %d로 바꿀때
printf("섭씨온도는 %f입니다", c_temp);
printf("섭씨온도는 %f입니다", c_temp);
printf("섭씨온도는 %f입니다", c_temp);
```


[Visual Studio scanf 에러 해결](https://security-nanglam.tistory.com/116)

<br>

## 도움이 되는 사이트
[인프런](https://www.inflearn.com)
추천강좌 : [c로배우는 자료구조](https://www.inflearn.com/course/c%EB%A1%9C-%EB%B0%B0%EC%9A%B0%EB%8A%94-%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0-%EB%B0%8F-%EC%97%AC%EB%9F%AC%EA%B0%80%EC%A7%80-%EC%98%88%EC%A0%9C-%EC%8B%A4%EC%8A%B5)

[다른학교는 어떻게 공부할까? - kocw](http://www.kocw.net/home/index.do)
추천강좌 : [3학년 이상, 운영체제](http://www.kocw.net/home/search/kemView.do?kemId=1046323)

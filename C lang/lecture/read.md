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




## 추천 교재

[C발라먹기](http://www.realhanbit.co.kr/books/149)

구글아이디로 가입하고 구매하기를 누르면 끝!

<br>



## Visual Studio 활용

### [생산성을 향상](<https://blogs.msdn.microsoft.com/visualstudio/2018/08/30/improving-your-productivity-in-the-visual-studio-editor/> ) 시켜주는 단축키

**IntelliSense**  : Tab



전체 주석 : Ctrl + k + c

전체 주석 해제 : Ctrl + k + u



빌드& 실행 : ctrl + F5



여러 행 선택 후 편집 : Alt + Shift + 화살표

```c
// 예시
// 아래 3개의 %f를 %d로 바꿀때
printf("섭씨온도는 %f입니다", c_temp);
printf("섭씨온도는 %f입니다", c_temp);
printf("섭씨온도는 %f입니다", c_temp);
```

<br>


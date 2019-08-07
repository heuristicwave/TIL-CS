

192.168.10.1 - string

c0a80a01  - bin



```c
char *inet_ntoa(struct in_addr in);

char *inet_ntoa(struct in_addr in){
    char* buf = malloc(16);
    return buf;
    
    // stack 보호가 안됨
    /*char buf[16];
    ...
    return buf;*/
}
```



```c
char *inet_ntoa(uint_32t in){
    //char buf[16];
    //char* buf = malloc(16);
    static char buf[16];
    
    return buf;
}

// 함수가 호출 될 시 전에 호출된 값도 같이 바뀜
char* str1 = inet_ntoa(0xc0a80a01);
char* str2 = inet_ntoa(0xc0a80a02);

=> 스레드로 개선

char *inet_ntoa(uint_32t in){
    thread static char buf[16];
    
    return buf;
}
```

[개선 inet_ntop](http://man7.org/linux/man-pages/man3/inet_ntop.3.html)



### short circuit evaluation

https://codedragon.tistory.com/5429

```
if (p! = nullptr && p=>a ...)
```


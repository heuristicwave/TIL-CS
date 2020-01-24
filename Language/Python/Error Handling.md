## Error Handling

16진수 문자열 10진수 정수형 바꾸기

```python
str1 = "0xf"
str2 = "f"

print( int("0xf", 0) ) #prefix(0x)가 있는 경우 - 2번째 인자가 0이면 자동으로 형을 찾아줌
print( int("f", 16) )  #prefix가 없는 경우 - 명시해줘야 함
```


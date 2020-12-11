### 클래스

클래스 - 주형 / 객체 - 피조물

```python
class Calculator:
    def __init__(self):
        self.result = 0

    def add(self, num):
        self.result += num
        return self.result

cal1 = Calculator()
cal2 = Calculator()

print(cal1.add(3))
print(cal1.add(4))
print(cal2.add(3))
print(cal2.add(7))
```

>**[객체와 인스턴스의 차이]**
>
>클래스로 만든 객체를 인스턴스라고도 한다. 
>
>a = Cookie() 이렇게 만든 a는 객체이다. 그리고 a 객체는 Cookie의 인스턴스이다.
>
>즉 인스턴스라는 말은 특정 객체(a)가 어떤 클래스(Cookie)의 객체인지를 관계 위주로 설명할 때 사용한다. 

<br>

### 메서드

[클래스 안에 있는 함수](https://www.tutorialspoint.com/difference-between-method-and-function-in-python)

```python
def setdata(self, first, second):   # ① 메서드의 매개변수
    self.first = first              # ② 메서드의 수행문
    self.second = second            # ② 메서드의 수행문
    
>>> a = FourCal()
>>> a.setdata(4, 2)

>>> a = FourCal()
>>> FourCal.setdata(a, 4, 2)

# 객체변수 생성 : 객체에 생성되는 객체만의 변수
a.first = 4
a.second = 2
```

파이썬은 method를 호출할 때, 그 method의 instance를 첫번째 argument로 사용함

```python
class Car():
    wheels = 4
    seats = 4
    
	def start(kimchi)
    	print("Engine Start")
        
sonata = Car()
sonata.start()
```

<br>

<br>

---

본 내용은 [위키독스](https://wikidocs.net/28)를 참고하여 정리하였습니다.
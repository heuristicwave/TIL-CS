## Class Basic Usage

```python
class FlightClass:	# Naming Convetion : CamelCase
    def number(self):
        return 'SN060'
    

f = FlightClass()	# 클래스 객체 생성자(constructor)
f.number()			# 인스턴스 메소드 사용
```

<br>

### 생성자와 초기화자

```python
class Flight:

    def __init__(self):		# 초기화자, 생성자 아님
        print('init')
        super().__init__()

    def __new__(cls):		# 원천적인 접근을 막기위해 __ 사용
        print('new')
        return super().__new__(cls)

    def number(self):
        return 'SN060'
```

생성자로 객체생성을 호출받으면 `__new__` 메소드가 `__init__`호출하여 초기값 초기화

```python
>>> from airtravel import Flight
>>> f = Flight()
new
init
```

<br>

### 상속

```python
class Parent:			# Super Class

    name = '이름'

    def show(self):
        print('부모 클래스의 메소드입니다.')


class Child(Parent):	# Sub Class

    def __init__(self, name):
        self.name = name

    def show(self):		# 메소드 오버라이딩, 자식 클래스에서 재정의
        print('이름은 : ', self.name)
    
    def show_name(self):
        super().show()	# 부모 클래스 호출
```

<br>

>  파이썬은 오버로딩이 없지만, 다중 상속이 가능하다.
>
> ```python
> class Child(ParentOne, ParentTwo):
>     pass
> ```

<br>

<br>

----

위 내용은 https://suwoni-codelab.com/ 을 읽고 정리한 내용입니다.
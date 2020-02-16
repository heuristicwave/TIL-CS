## 객체지향 디자인의 기본 원칙



### The Open/Close Principle

클래스와 객체, 메소드 모구 확장엔 개방적이고 수정엔 폐쇄적



### The Inversion of Control Principle

상위 모듈은 하위 모듈에 의존적이지 않아야 한다. 세부 구현이 추상화에 의존해야 한다.

의존적인 모듈 사이에 추상화 계층을 둬 분리해야 한다.



### The Interface Segregation Principle

클라이언트는 불필요한 인터페이스에 의존하지 않아야 한다.

개발자는 반드시 해당 기능과 관련 있는 메소드만을 작성해야 한다.



### The Single Resposibility Principle

클래스는 하나의 책임만을 가져야 한다.



### The Subsitution Principle

상속받는 클래스는 기본 클래스의 역할을 완전히 치환할 수 있어야 한다.



## 동적 언어 패턴

파이썬은 동적언어로 다음과 같은 특성이 있다.

- 자료형과 클래스는 런타임 객체이다.
- 변수형은 런타임에 변경 될 수 있다.
- 동적 언어는 클래스 제한 측면에서 더 유동적인다.
- 파이썬은 다형성이 언어에 구현되어 있고, 접근지정자가 없으며 모든 변수는 기본적으로 public이다.
- 동적 언어를 사용해 쉽게 디자인 패턴을 구현 할 수 있다.



## 디자인 패턴의 분류

### 생성 패턴

- 객체가 생성되는 방식을 중시한다.
- 객체 생성 관련 상세 로직을 숨긴다.
- 코드는 생성하려는 객체형과는 독립적이다.

>  예) Singleton Pattern



### 구조 패턴

- 클래스와 객체를 더 큰 결과물로 합칠 수 있는 구조로 설계한다.
- 구조를 간결화하고 클래스와 객체 간의 상호관계를 파악할 수 있다.
- 클래스 상속과 컴포지션을 중시한다.

> 예) Adapter Pattern

> **Composition**
>
> 컴포지션을 통해 특정 객체는 다른 모듈의 함수를 호출 할 수 있다. 즉, 상속 없이 외부 기능 사용이 가능하다.
>
> ```python
> class A(object):
>     def a1(self):
> 		print("a")
> # A 클래스를 B클래스에 포함시킴        
> class B(object):
>     def b(self):
> 		print("b")
>         A().a1()
>         
> objectB = B()
> objectB.b()
> ```



### 행위 패턴

- 객체 간의 상호작용와 책임을 중시한다.
- 객체는 상호작용하지만 느슨하게 결합돼야 한다.

> 예) Observer Pattern





---

위 내용은 `Learning python design patterns 2e - Chetan Giridhar`을 읽고 정리한 내용입니다.
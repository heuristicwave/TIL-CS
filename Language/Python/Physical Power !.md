## Physical Power !

#### [리스트 컴프리헨션](https://wikidocs.net/22805)



#### 집합 자료형의 연산

```python
a = set([1, 2, 3, 4, 5])
b = set([3, 4, 5, 6, 7])

print(a | b)	# 합집합 >> {1, 2, 3, 4, 5, 6, 7}
print(a & b)	# 교집합 >> {3, 4, 5}
print(a - b)	# 차집합 >> {1, 2}

data = set([1, 2, 3])

# 원소 추가
data.add(4)			#	>> {1, 2, 3, 4}
data.update([5, 6])	#	>> {1, 2, 3, 4, 5, 6}
data.remove(3)		# 	>> {1, 2, 4, 5, 6}
```



### [내장함수](https://wikidocs.net/32)

```python
# sum
a = [1, 2, 3]
print(sum(a))	# >> 6

# eval
print(eval("1+2"))	# >> 3

# chr & ord
# filter
```



### collections

```python
from collections import Counter

counter = Counter(['red', 'blue', 'red', 'green', 'blue', 'blue'])

print(counter['blue'])	# >> 3
print(dict(counter))	# >> {'red': 2, 'blue': 3, 'green':1}
```



### math

```python
import math

print(math.factorial(1))	# >> 1
print(math.gcd(21, 14))		# >> 7
```



#### 조건부 표현식

정의 : 조건문이 참인 경우` if `조건문` else `조건문이 거짓인 경우

```python
message = "success" if score >= 60 else "failure"
```



`in` 과 `not in` 



#### readline()

```python
import sys
sys.stdin.readline().rstrip()	# rstrip()은 개행 제거
```


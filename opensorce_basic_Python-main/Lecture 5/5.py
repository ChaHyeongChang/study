'''
##함수 기본###


def 함수이름(매개변수):
    실행할 코드
    return 반환값
    
ex)
def greet(name):
    print("안녕하세요,", name)

greet("민수")

매개변수와 반환값이 없는 함수
def say_hi():
    print("안녕!")

say_hi()

매개변수가 있는 함수
def greet(name):
    print(f"{name}님, 안녕하세요!")

greet("지훈")


반환값이 있는 함수
def square(x):
    return x * x

result = square(4)
print(result)  # 16



파이썬에서는 return의 자료형을 명시적으로 지정할 필요가 없어요.
즉, 함수가 어떤 자료형을 반환하든 자유롭고, return도 없어도 돼요.

문자열 반환
def get_name():
    return "철수"
    
print(get_name())


숫자 반환
def add(a, b):
    return a+b

print(add(2,3)) # 5


아무것도 반환 안하는 함수
def say_hello():
    print("안녕!") ##return 없음
    
retsult = say_hello()
print(result)


자료형 섞어서 반환 가능
def mixed():
    return "문자", 123, True

a, b, c = mixed()
print(a, b, c)  # 문자 123 True

'''





'''
✅ 지역변수(Local Variable)
    -함수 안에서만 사용하는 변수
    -함수가 끝나면 사라짐
    
def greet():
    name = "민수"  # 지역변수
    print("안녕,", name)

greet()
print(name)  # ❌ 오류! 함수 밖에선 name이 없음


✅ 전역변수(Global Variable)
    -함수 밖에서 정의된 변수
    -프로그램 전체에서 사용 가능
    
name = "지훈"  # 전역변수

def greet():
    print("안녕,", name)

greet()        # 안녕, 지훈
print(name)    # 지훈



##헷갈리는 예제

x = 10

def func():
    x = 5  # 지역변수 (전역 x와는 다름)
    print("함수 안:", x)

func()
print("함수 밖:", x)

##함수 안: 5
##함수 밖: 10


'''





'''
✅ pass 명령어란?
"아무 일도 하지 마라" 라는 뜻의 빈 문장(placeholder) 이자 자리 채움용 명령어예요.

✅ 언제 쓰는가?
pass는 문법적으로 코드가 있어야 할 자리인데,
아직 구현할 코드를 안 썼거나,
일부러 비워두고 싶을 때 사용해요.

코드가 비어 있으면 파이썬은 에러를 내기 때문에
pass를 써서 에러 없이 "일단 넘어가기" 하는 거예요.



✅ 예제
🔹 1. 함수 틀만 잡아두기
def future_function():
    pass  # 나중에 구현할 예정

🔹 2. 조건문 안 비워두기
x = 10

if x > 0:
    pass  # 아직 아무 것도 안 함
else:
    print("0 이하입니다.")


🔹 3. 클래스 뼈대만 만들기
class MyClass:
    pass


✅ 왜 필요한가?
파이썬은 빈 블록(if문, 함수, 클래스 등)에
아무 코드도 없으면 에러가 나요.

def my_func():
    # 아무 코드도 없음 → ❌ SyntaxError 발생


'''




'''
✅ global 예약어란?
    함수 내부에서 **전역 변수(global variable)**를 사용해서 값을 변경하려고 할 때 사용하는 키워드예요.

파이썬은 기본적으로 함수 안에서 변수에 값을 할당하면 지역변수로 처리해요.
그런데 global을 붙이면, **"이건 전역변수야!"**라고 알려주는 거죠.



## global 없이 전역변수 수정 시 오류
x = 10

def change():
    x = x + 1  # ❌ 오류 발생! (UnboundLocalError)

change()


##global로 해결

x = 10

def change():
    gloal x
    x = x + 1
    
change()
print(x) #11


##global 없이 전역변수 읽기만 할 경우

x = 100

def show():
    print(x)  # 읽는 건 문제없음

show()  # 100

✔ **읽기(read)**만 하는 건 괜찮고,
❌ 쓰기(write) 하려면 global이 필요해요.
'''





'''
✅ 여러 개의 값을 반환하는 방법
파이썬 함수는 여러 값을 ,로 구분해서 return하면, **자동으로 튜플(tuple)**로 반환해줘요.

#여러 값 반환
def get_info():
    name = "지훈"
    age = 25
    return name, age  # 튜플 반환

result = get_info()
print(result)        # ('지훈', 25)


✅ 반환값 분해해서 받기 (튜플 언패킹)
#여러 변수에 각각 저장
def get_position():
    x = 10
    y = 20
    return x, y

x_val, y_val = get_position()
print("x:", x_val)  # x: 10
print("y:", y_val)  # y: 20


✅ 다양한 자료형도 섞어서 반환 가능
def get_data():
    return "철수", [1, 2, 3], True

name, scores, passed = get_data()
print(name)    # 철수
print(scores)  # [1, 2, 3]
print(passed)  # True


✅ 반환값을 리스트나 딕셔너리로 넘기는 것도 가능
def get_student():
    return ["지민", 23, "컴퓨터공학과"]

def get_student_dict():
    return {"name": "지민", "age": 23, "major": "컴퓨터공학과"}

'''



'''
✅ 매개변수 개수 제한 없이 받기
## *args (여러 개 인자를 튜플로 받음)

def show_scores(*args):
    for score in args:
        print("점수:", score)

show_scores(90, 85, 70)

점수: 90
점수: 85
점수: 70


## **kwargs (여러 개 인자를 딕셔너리로 받음)

def show_info(**kwargs):
    for key, value in kwargs.items():
        print(f"{key}: {value}")

show_info(name="지훈", age=22, major="컴공")

name: 지훈
age: 22
major: 컴공


✅ 딕셔너리로 함수에 전달
--딕셔너리를 함수에 전달할 때는 **를 써서 풀어줘야 해요

def user_info(name, age):
    print(f"{name}은 {age}살입니다.")

data = {"name": "정우", "age": 24}
user_info(**data)  # 딕셔너리를 풀어서 전달

'''




'''
✅ 모듈이란?
파이썬 파일(.py) 하나가 곧 모듈이에요.
즉, 다른 파이썬 파일에서 불러와서(import) 사용할 수 있는 기능 묶음이에요.


✅ 모듈의 예
예를 들어 math.py라는 파일에 아래와 같은 코드가 있다고 해볼게요.

# math_utils.py

def add(a, b):
    return a + b

def subtract(a, b):
    return a - b


이걸 다른 파일에서 불러올 수 있음



✅ 모듈 사용 방법
🔹 1. import로 모듈 불러오기

import math_utils

result = math_utils.add(3, 4)
print(result)  # 7



🔹 2. 모듈 안에서 특정 함수만 가져오기

from math_utils import subtract

print(subtract(10, 5))  # 5



🔹 3. 별명(alias) 붙이기

import math_utils as mu

print(mu.add(2, 3))  # 5



✅ 정리
개념	설명
모듈	.py 파일 하나
import	모듈 전체 가져오기
from ~ import	특정 함수만 가져오기
별칭 사용	import 모듈명 as 별명
표준 모듈	math, random, os, datetime 등


'''






'''
✅ 람다 함수란?
lambda 키워드를 사용해서 만드는 익명 함수 (이름 없는 함수)
주로 짧은 함수나 임시로 쓸 함수를 만들 때 사용돼요.


✅ 기본 문법

lambda 매개변수: 표현식



✅ 예제: 두 수 더하기
add = lambda a, b: a + b
print(add(3, 5))  # 8


##예제 비교

# 일반 함수
def square(x):
    return x * x

# 람다 함수
square = lambda x: x * x

print(square(4))  # 16



✅ 자주 쓰이는 상황
🔸 1. map()과 함께 사용

nums = [1, 2, 3, 4]
squared = list(map(lambda x: x**2, nums))
print(squared)  # [1, 4, 9, 16]



✅ map() 함수란?
여러 개의 값에 함수 하나를 적용해서
그 결과를 **새로운 map 객체(이터레이터)**로 돌려주는 함수야.



✅ 기본 문법
map(함수, 반복가능한 자료)

🔹 예제: 리스트의 모든 숫자를 제곱
nums = [1, 2, 3, 4]
squared = map(lambda x: x**2, nums)

print(list(squared))  # [1, 4, 9, 16]



##✅ 설명 흐름
lambda x: x**2 → 각각의 요소를 제곱하는 함수

nums 리스트의 요소에 이 함수를 하나씩 적용

결과는 map 객체 → list()로 감싸서 리스트로 변환



✅ 일반 함수도 사용 가능
def double(n):
    return n * 2

result = map(double, [1, 2, 3])
print(list(result))  # [2, 4, 6]




✅ 여러 개의 리스트에 동시에 적용 가능
a = [1, 2, 3]
b = [4, 5, 6]

result = map(lambda x, y: x + y, a, b)
print(list(result))  # [5, 7, 9]



✅ map vs for문 비교
# 일반 for문
nums = [1, 2, 3]
doubled = []
for n in nums:
    doubled.append(n * 2)

# map 사용
doubled = list(map(lambda x: x * 2, nums))

'''
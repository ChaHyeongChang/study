'''
파이썬에서 **클래스(class)**는 객체지향 프로그래밍(OOP, Object-Oriented Programming)의 핵심 개념 중 하나로, **데이터(속성)**와 **함수(메서드)**를 하나로 묶는 틀


class 클래스명:
    # 이 부분에 관련 코드 구현
    
    
class Person:
    def __init__(self, name, age): ##매서드 라고 함(함수가 아니라라)
        self.name = name
        self.age = age

    def greet(self):
        print("안녕하세요, 저는 %s이고, %d살입니다." % (self.name, self.age))

'''



'''
**클래스를 사용해서 만든 실제 객체(변수)**를 인스턴스
클래스 : 붕어빵 틀
인스턴스 : 틀로 찍어낸 붕어빵
속성/메서드 : 붕어빵의 속 내용, 기능 등
class Dog:
    def __init__(self, name):
        self.name = name

    def bark(self):
        print(f"{self.name}가 짖어요! 멍멍!")



#인스턴스 생성
dog1 = Dog("초코")  # dog1은 Dog 클래스의 인스턴스
dog2 = Dog("바둑이")  # 또 다른 인스턴스

#각각 bark() 메서드 사용가능
dog1.bark()  # 초코가 짖어요! 멍멍!
dog2.bark()  # 바둑이가 짖어요! 멍멍!

'''



'''
**생성자(constructor)**
파이썬에서 클래스의 생성자는 객체(인스턴스)가 처음 만들어질 때 자동으로 호출되는 특별한 메서드

class Person:
    def __init__(self, name, age):  # 이게 생성자!
        self.name = name
        self.age = age
        
#__init__()은 클래스에서 객체를 생성할 때 자동으로 호출됨
#self는 생성될 객체 자신을 의미
#생성자 안에서 객체의 **초기 상태(속성)**를 지정할 수 있다.


ex)
class Person:
    def __init__(self, name):
        print("생성자가 호출되었습니다!")
        self.name = name

p = Person("철수")  # 객체 생성 시 자동으로 __init__ 호출

'''



'''
#클래스를 기반으로 인스턴스를 생성하는 개념!

인스턴스 변수 vs 클래스 변수

#인스턴스 변수: self.로 시작 → "나만의 값"
#클래스 변수: 그냥 클래스 안에 선언 → "모두의 값"

구분	    인스턴스 변수	                    클래스 변수
선언 위치	__init__() 안에서 self.로 선언	    클래스 내부, 메서드 밖에서 선언
소속	각각의 인스턴스에 속함	                클래스 전체에 속함
저장 위치	인스턴스마다 따로 저장	            클래스에 한 번만 저장
용도	객체마다 다른 데이터를 저장할 때 사용	모든 객체가 공유하는 값을 저장할 때 사용



class Dog:
    species = "포유류"  # 클래스 변수

    def __init__(self, name):
        self.name = name  # 인스턴스 변수
        
dog1 = Dog("초코")
dog2 = Dog("바둑이")

dog1.name, dog2.name은 서로 다를 수 있음 → 인스턴스 변수
dog1.species, dog2.species는 똑같이 "포유류" → 클래스 변수

'''


'''
? 클래스 상속이란? : 기존 클래스(부모)의 속성과 메서드를 새로운 클래스(자식)가 물려받는 것!

#기본 문법
class 부모클래스:
    ...

class 자식클래스(부모클래스):
    ...

ex)
class Animal:
    def __init__(self, name):
        self.name = name

    def speak(self):
        print(f"{self.name}이(가) 소리를 낸다.")

class Dog(Animal):  # Animal을 상속받음
    def bark(self):
        print(f"{self.name}이(가) 멍멍 짖는다.")
        
d = Dog("초코")

d.speak()  # Animal에서 상속받은 메서드
d.bark()   # Dog만의 메서드

#결과
#초코이(가) 소리를 낸다.
#초코이(가) 멍멍 짖는다.

'''



'''
#메서드 오버라이딩 (덮어쓰기) : 부모 메서드를 자식 클래스에서 다르게 구현할 수 있음
class Cat(Animal):
    def speak(self):  # 부모의 speak()를 덮어씀
        print(f"{self.name}이(가) 야옹~")

#상속 : 부모 클래스의 기능을 자식이 물려받음
#오버라이딩 : 부모 메서드를 자식이 다시 정의 //자식 클래스에서 오버라이딩해도 부모 클래스의 메서드는 그대로 유지됨됨
#super() : 부모 클래스의 메서드를 명시적으로 호출할 때 사용
'''


'''
? 추상 메서드란? : 자식 클래스에서 반드시 구현해야 하는 메서드의 틀만 정해놓는 것!

#부모 클래스에서 함수 이름만 선언하고
#자식 클래스에서 실제 내용을 구현하게 강제함

#공통 구조만 정하고 구체적인 동작은 자식 클래스에게 맡기기 위해서
#->즉, "이건 꼭 오버라이딩해서 써라!" 라고 강제하고 싶을 때

#기본구조
from abc import ABC, abstractmethod

class Animal(ABC):  # ABC를 상속받아 추상 클래스 생성
    @abstractmethod
    def speak(self):  # 추상 메서드
        pass

#자식 클래스는 반드시 구현해야함
class Dog(Animal):
    def speak(self):
        print("멍멍!")

class Cat(Animal):
    def speak(self):
        print("야옹~")

#추상 메서드 : 이름만 있는 메서드(내용 없음)
#목적 : 자식 클래스가 반드시 오버라이딩 하도록 강제
#@abstractmethod : 데코레이터로 지정
#ABC : 추상 클래스 만들려면 상속해야 함

class Shape(ABC):
    @abstractmethod
    def draw(self):
        pass

class Circle(Shape):
    def draw(self):
        print("원을 그립니다.")
        
→ Shape는 도형의 공통된 틀, Circle은 구체적인 구현

'''




'''
GUI란? : **GUI (Graphical User Interface)**는 그래픽을 이용해서 사용자가 컴퓨터와 상호작용할 수 있게 해주는 "화면 인터페이스"

? tkinter란? : 파이썬에 기본 내장된 GUI 라이브러리(간단한 창, 버튼, 입력창, 라벨 등 만들 수 있음)
#import tkinter as tk

? Button이란? : 버튼을 만들어주는 tkinter 위젯 중 하나
#tk.Button(부모창, text="버튼에 보일 글자", command=클릭시_실행할_함수)
'''
'''
import tkinter as tk

def say_hello():
    print("안녕하세요!")

window = tk.Tk()
window.title("버튼 예제")

button = tk.Button(window, text="눌러보세요!", command=say_hello)
button.pack()

window.mainloop()

'''
'''
? pack()이란? : 위젯을 창(window)에 배치하는 메서드(pack()을 써야 화면에 보임임)

#label = tk.Label(window, text="안녕하세요!")
label.pack()

#pack() : 위에서 아래로 차곡차곡 정렬
#place() : 좌표로 위치 지정
#grid() : 행, 열로 정렬
'''
'''
import tkinter as tk

window = tk.Tk()
window.title("간단한 GUI")

label = tk.Label(window, text="안녕, GUI 세계!")
label.pack()

button = tk.Button(window, text="눌러보세요!", command=lambda: print("버튼 눌림!"))
button.pack()

window.mainloop()

'''

'''
import tkinter as tk

def show_message():
    print("버튼이 눌렸어요!")

window = tk.Tk()
window.title("간단 GUI")

label = tk.Label(window, text="환영합니다!")
label.pack()

btn = tk.Button(window, text="눌러봐요", command=show_message)
btn.pack()

window.mainloop()


'''




'''
? place()란? : 위젯(Button, Label 등)을 **픽셀 좌표(x, y)**로 배치하는 방식(place()는 말 그대로 **"위치 고정"**)

#place()는 정해진 좌표(x, y)에 위젯을 정확히 배치해서
창 크기가 바뀌어도 그 위치에 그대로 고정됨

import tkinter as tk

window = tk.Tk()
window.geometry("300x200")

btn = tk.Button(window, text="여기 고정!")
btn.place(x=100, y=50)  # 창의 (100, 50)에 고정

window.mainloop()


'''





'''
### 키보드, 마우스 이벤트 처리###

#기본구조
#widget.bind("이벤트명", 이벤트_처리함수)
#이벤트 처리 함수는 매개변수로 이벤트 객체(event)를 받아야 함.

? 키보드 이벤트 처리
import tkinter as tk

def on_key(event):
    print(f"눌린 키: {event.keysym}")

window = tk.Tk()
window.bind("<Key>", on_key)  # 어떤 키든 누르면 호출됨

window.mainloop()



?? 마우스 이벤트 처리
def on_click(event):
    print(f"마우스 클릭 좌표: ({event.x}, {event.y})")

window.bind("<Button-1>", on_click)  # 왼쪽 클릭

'''


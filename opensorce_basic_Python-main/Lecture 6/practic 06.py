'''
���̽㿡�� **Ŭ����(class)**�� ��ü���� ���α׷���(OOP, Object-Oriented Programming)�� �ٽ� ���� �� �ϳ���, **������(�Ӽ�)**�� **�Լ�(�޼���)**�� �ϳ��� ���� Ʋ


class Ŭ������:
    # �� �κп� ���� �ڵ� ����
    
    
class Person:
    def __init__(self, name, age): ##�ż��� ��� ��(�Լ��� �ƴ϶��)
        self.name = name
        self.age = age

    def greet(self):
        print("�ȳ��ϼ���, ���� %s�̰�, %d���Դϴ�." % (self.name, self.age))

'''



'''
**Ŭ������ ����ؼ� ���� ���� ��ü(����)**�� �ν��Ͻ�
Ŭ���� : �ؾ Ʋ
�ν��Ͻ� : Ʋ�� �� �ؾ
�Ӽ�/�޼��� : �ؾ�� �� ����, ��� ��
class Dog:
    def __init__(self, name):
        self.name = name

    def bark(self):
        print(f"{self.name}�� ¢���! �۸�!")



#�ν��Ͻ� ����
dog1 = Dog("����")  # dog1�� Dog Ŭ������ �ν��Ͻ�
dog2 = Dog("�ٵ���")  # �� �ٸ� �ν��Ͻ�

#���� bark() �޼��� ��밡��
dog1.bark()  # ���ڰ� ¢���! �۸�!
dog2.bark()  # �ٵ��̰� ¢���! �۸�!

'''



'''
**������(constructor)**
���̽㿡�� Ŭ������ �����ڴ� ��ü(�ν��Ͻ�)�� ó�� ������� �� �ڵ����� ȣ��Ǵ� Ư���� �޼���

class Person:
    def __init__(self, name, age):  # �̰� ������!
        self.name = name
        self.age = age
        
#__init__()�� Ŭ�������� ��ü�� ������ �� �ڵ����� ȣ���
#self�� ������ ��ü �ڽ��� �ǹ�
#������ �ȿ��� ��ü�� **�ʱ� ����(�Ӽ�)**�� ������ �� �ִ�.


ex)
class Person:
    def __init__(self, name):
        print("�����ڰ� ȣ��Ǿ����ϴ�!")
        self.name = name

p = Person("ö��")  # ��ü ���� �� �ڵ����� __init__ ȣ��

'''



'''
#Ŭ������ ������� �ν��Ͻ��� �����ϴ� ����!

�ν��Ͻ� ���� vs Ŭ���� ����

#�ν��Ͻ� ����: self.�� ���� �� "������ ��"
#Ŭ���� ����: �׳� Ŭ���� �ȿ� ���� �� "����� ��"

����	    �ν��Ͻ� ����	                    Ŭ���� ����
���� ��ġ	__init__() �ȿ��� self.�� ����	    Ŭ���� ����, �޼��� �ۿ��� ����
�Ҽ�	������ �ν��Ͻ��� ����	                Ŭ���� ��ü�� ����
���� ��ġ	�ν��Ͻ����� ���� ����	            Ŭ������ �� ���� ����
�뵵	��ü���� �ٸ� �����͸� ������ �� ���	��� ��ü�� �����ϴ� ���� ������ �� ���



class Dog:
    species = "������"  # Ŭ���� ����

    def __init__(self, name):
        self.name = name  # �ν��Ͻ� ����
        
dog1 = Dog("����")
dog2 = Dog("�ٵ���")

dog1.name, dog2.name�� ���� �ٸ� �� ���� �� �ν��Ͻ� ����
dog1.species, dog2.species�� �Ȱ��� "������" �� Ŭ���� ����

'''


'''
? Ŭ���� ����̶�? : ���� Ŭ����(�θ�)�� �Ӽ��� �޼��带 ���ο� Ŭ����(�ڽ�)�� �����޴� ��!

#�⺻ ����
class �θ�Ŭ����:
    ...

class �ڽ�Ŭ����(�θ�Ŭ����):
    ...

ex)
class Animal:
    def __init__(self, name):
        self.name = name

    def speak(self):
        print(f"{self.name}��(��) �Ҹ��� ����.")

class Dog(Animal):  # Animal�� ��ӹ���
    def bark(self):
        print(f"{self.name}��(��) �۸� ¢�´�.")
        
d = Dog("����")

d.speak()  # Animal���� ��ӹ��� �޼���
d.bark()   # Dog���� �޼���

#���
#������(��) �Ҹ��� ����.
#������(��) �۸� ¢�´�.

'''



'''
#�޼��� �������̵� (�����) : �θ� �޼��带 �ڽ� Ŭ�������� �ٸ��� ������ �� ����
class Cat(Animal):
    def speak(self):  # �θ��� speak()�� ���
        print(f"{self.name}��(��) �߿�~")

#��� : �θ� Ŭ������ ����� �ڽ��� ��������
#�������̵� : �θ� �޼��带 �ڽ��� �ٽ� ���� //�ڽ� Ŭ�������� �������̵��ص� �θ� Ŭ������ �޼���� �״�� �����ʵ�
#super() : �θ� Ŭ������ �޼��带 ��������� ȣ���� �� ���
'''


'''
? �߻� �޼����? : �ڽ� Ŭ�������� �ݵ�� �����ؾ� �ϴ� �޼����� Ʋ�� ���س��� ��!

#�θ� Ŭ�������� �Լ� �̸��� �����ϰ�
#�ڽ� Ŭ�������� ���� ������ �����ϰ� ������

#���� ������ ���ϰ� ��ü���� ������ �ڽ� Ŭ�������� �ñ�� ���ؼ�
#->��, "�̰� �� �������̵��ؼ� ���!" ��� �����ϰ� ���� ��

#�⺻����
from abc import ABC, abstractmethod

class Animal(ABC):  # ABC�� ��ӹ޾� �߻� Ŭ���� ����
    @abstractmethod
    def speak(self):  # �߻� �޼���
        pass

#�ڽ� Ŭ������ �ݵ�� �����ؾ���
class Dog(Animal):
    def speak(self):
        print("�۸�!")

class Cat(Animal):
    def speak(self):
        print("�߿�~")

#�߻� �޼��� : �̸��� �ִ� �޼���(���� ����)
#���� : �ڽ� Ŭ������ �ݵ�� �������̵� �ϵ��� ����
#@abstractmethod : ���ڷ����ͷ� ����
#ABC : �߻� Ŭ���� ������� ����ؾ� ��

class Shape(ABC):
    @abstractmethod
    def draw(self):
        pass

class Circle(Shape):
    def draw(self):
        print("���� �׸��ϴ�.")
        
�� Shape�� ������ ����� Ʋ, Circle�� ��ü���� ����

'''




'''
GUI��? : **GUI (Graphical User Interface)**�� �׷����� �̿��ؼ� ����ڰ� ��ǻ�Ϳ� ��ȣ�ۿ��� �� �ְ� ���ִ� "ȭ�� �������̽�"

? tkinter��? : ���̽㿡 �⺻ ����� GUI ���̺귯��(������ â, ��ư, �Է�â, �� �� ���� �� ����)
#import tkinter as tk

? Button�̶�? : ��ư�� ������ִ� tkinter ���� �� �ϳ�
#tk.Button(�θ�â, text="��ư�� ���� ����", command=Ŭ����_������_�Լ�)
'''
'''
import tkinter as tk

def say_hello():
    print("�ȳ��ϼ���!")

window = tk.Tk()
window.title("��ư ����")

button = tk.Button(window, text="����������!", command=say_hello)
button.pack()

window.mainloop()

'''
'''
? pack()�̶�? : ������ â(window)�� ��ġ�ϴ� �޼���(pack()�� ��� ȭ�鿡 ������)

#label = tk.Label(window, text="�ȳ��ϼ���!")
label.pack()

#pack() : ������ �Ʒ��� �������� ����
#place() : ��ǥ�� ��ġ ����
#grid() : ��, ���� ����
'''
'''
import tkinter as tk

window = tk.Tk()
window.title("������ GUI")

label = tk.Label(window, text="�ȳ�, GUI ����!")
label.pack()

button = tk.Button(window, text="����������!", command=lambda: print("��ư ����!"))
button.pack()

window.mainloop()

'''

'''
import tkinter as tk

def show_message():
    print("��ư�� ���Ⱦ��!")

window = tk.Tk()
window.title("���� GUI")

label = tk.Label(window, text="ȯ���մϴ�!")
label.pack()

btn = tk.Button(window, text="��������", command=show_message)
btn.pack()

window.mainloop()


'''




'''
? place()��? : ����(Button, Label ��)�� **�ȼ� ��ǥ(x, y)**�� ��ġ�ϴ� ���(place()�� �� �״�� **"��ġ ����"**)

#place()�� ������ ��ǥ(x, y)�� ������ ��Ȯ�� ��ġ�ؼ�
â ũ�Ⱑ �ٲ� �� ��ġ�� �״�� ������

import tkinter as tk

window = tk.Tk()
window.geometry("300x200")

btn = tk.Button(window, text="���� ����!")
btn.place(x=100, y=50)  # â�� (100, 50)�� ����

window.mainloop()


'''





'''
### Ű����, ���콺 �̺�Ʈ ó��###

#�⺻����
#widget.bind("�̺�Ʈ��", �̺�Ʈ_ó���Լ�)
#�̺�Ʈ ó�� �Լ��� �Ű������� �̺�Ʈ ��ü(event)�� �޾ƾ� ��.

? Ű���� �̺�Ʈ ó��
import tkinter as tk

def on_key(event):
    print(f"���� Ű: {event.keysym}")

window = tk.Tk()
window.bind("<Key>", on_key)  # � Ű�� ������ ȣ���

window.mainloop()



?? ���콺 �̺�Ʈ ó��
def on_click(event):
    print(f"���콺 Ŭ�� ��ǥ: ({event.x}, {event.y})")

window.bind("<Button-1>", on_click)  # ���� Ŭ��

'''


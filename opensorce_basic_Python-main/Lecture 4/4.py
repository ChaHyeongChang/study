'''
배열 : 동일한 데이터 묶음

aa = [10 ,20, 30, 40]

aa[0] 사용
aa[1] 사용
aa[2] 사용
aa[3] 사용

aa = []
for i in range(0, 100):
    aa.appenc(0)
print(00)
print(len(aa))


리스트의 첨자가 순서대로 변할 수 있도록 반복문과 함께 활용

aa = []

for i in range(0, 100):
    aa.append(0)
hap = 0

for i in range(0, 4):
    aa[i] = int(input)
    
    
    
aa = []
bb = [10, 20, 30]
cc = ['파이썬', '자바']
dd
'''
'''
p11

for i in range(0, 100):
    aa.append(value)
    

리스트 음수값 접근
print("aa[-1]은 %d, aa[-2]는 %d" % (aa(-1), aa(-2)))


p13
리스트끼리 연산을 수행하면 요소들이 합쳐져 결과로 '하나의 리스트'로 반환됨

aa = [10, 20, 30]

aa[1] = 200
print(aa) #[10, 200, 30]

aa = [10, 20, 30]
aa[1:2] = [200, 201]
'''
'''
2. aa[1:2] = [200, 201]
여기서 aa[1:2]는 index 1부터 2 직전까지, 즉 [20] 하나의 요소를 가리킵니다.

이 자리에 [200, 201]을 넣으면,

기존의 20이 사라지고,

그 자리에 200, 201이 삽입됩니다.
'''

'''
p17
copy() # 새리스트=리스트명.copy()


2차원 리스트 개념
list1 = []
list2 = []

p21 -> a[1][1]임임

2차원 리스트 불규칙 할 때
aa = [[1,2,3,4],
        [5,6],
        [7,8,9]]



 튜플이란?
여러 값을 묶어서 저장할 수 있는 자료형

리스트([])와 비슷하지만, **소괄호(())**를 사용

한 번 생성하면 값 변경 불가 (immutable)



튜플도 리스트와 같이 덧셈 및 곱셈 등의 연산 가느ㅏㅇ
리스트처럼 뒤에 추가됨

튜플과 리스트는 서로 변환이 가능함
튜플은 직접 값을 수저하지 못하기 때문에!!
myTuple = (10, 20, 30)
myList = list(myTuple)

딕셔너리 : 두개의 값을 {}로 묶어서 구성
키와 값을 반대로도 입력 가능

딕셔너리에는 순서가 없기 때문에 생성한 순서대로 딕셔너리가 구성된다는 보장이 없다

동일한 키를 갖는 딕셔너리를 생성하는 것이 아니라 마지막에 있는 키가 적용

딕셔너리명.get(키) 함수를 사용할수도 있음

딕셔너리명[키]는 없는키를 호출하면 오류발생
딕셔너리명.get(키)는 없는키를 호출해도 오류발생X

딕셔너리 안에 해당 키가 있는지를 in을 사용해 확인가능
 ex) 딕셔너리에 키가 있다면 True 반환, 없다면 False반환



세트: 키만 모아 놓은 딕셔너리의 특수한 형태, 중괄호{}를 사용하지만 콜론(:) 없이 입력

컴프리헨션 : 한 줄로 간단하고 빠르게 리스트, 딕셔너리, 집합을 만드는 방법!
 리스트 = [수식 for 항목 i in range( , )]
 
 
zip() 함수를 사용해 동시에 여러 리스트 접근 가능
두개의 리스트를 튜플이나 딕셔너리로 짝지을때도 zip()사용 가능


리스트의 복사
    얕은 복사 :
    
    깊은 복사 :
'''

'''
문자열 기본

더하기 곱하기 등 기호사용 문자열 반복

ss = "파이썬abcd"

print(len(ss))

for i in ragne(0, len(ss)):
    print(ss[i] + "$", end = "")


p49
앞에가 괄호로 되어있지 않다면 괄호추가

뒤에가 괄호로 되어있지 않다면 괄호 추가

p50
strip(), rstrip(), lstrip(), replace()


p55
split(), splitlines(), join()


p57
center(), ljust(), rjust(), zfill()

p58
전부True False로 반환함

'''

'''
변수 = 시작값값
while 변수 < 끝값:
    변수 = 변수 + 증가값
'''
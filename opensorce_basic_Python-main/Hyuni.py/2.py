
'''
print("100") #문자열 100
print("%d" % 100) #숫자 100

print("100 + 100") #  100 + 100
print("%d" %(100+100)) #200

print("%d" % 123) #123
print("%5d" % 123) #  123
print("%05d" % 123)#00123

print("%d %5d %05d" % (123, 123, 123))
print("{0:d} {1:5d} {2:05d}".format(123, 123, 123)) #.fromat을 사용해서 출력 순서도 지정 가능
print("{2:d} {1:d} {0:d}".format(100, 200, 300)) #300 200 100
print("한 행입니다. 또 한 행입니다.")
print("한 행입니다. \n또 한 행입니다.")

print("줄바꿈\n연습")
print("\t탭키\t연습")
print("글자가 \"강조\"되는 효과1") # 글자가 "강조"되는 효과1
print("글자가 \'강조\'되는 효과2") # 글자가 '강조'되는 효과2
print("\\\\\\ 역슬래시 세 개 출력")
print(r"\n \t \"\\를 그대로 출력")
'''


'''
boolvar = True
print(type(boolvar))

intvar = 0
print(type(intvar))

floatvar = 0.0
print(type(floatvar))

strvar = ""
print(type(strvar))

var2 = 200
var1 = var2
print(var1)

var1=var2=var3=var4=100 #변수는 오른쪽에서 왼쪽으로 대입

str2 = '45.89'
re2 = float(str2) + 10 #형변환 float(  ), int(  )
print(re2)

a = 123; type(a)
a = 100 ** 50; print(a, type(a))

connect = int('123') + int('456') + int('789') #문자열을 int형으로 형 변환
print(connect)

str1 = "Hello World"
##문자열의 길이
print(len(str1))
print(len("tim;asdjkf;lak"))

# *연산: 문자열을 반복
print('a' * 100)

aa = [10, 20, 30, 40]
print("aa[-1]은 %d, aa[-2]는 %d" % (aa[-1], aa[-2]))
print(aa[0:3])
print(aa[2:4])

num = "031012-3325111"
#문자열의 인덱스는 0부터 시작한다
year = num[0] + num[1]
month = num[2] + num[3]
day = num[4] + num[5]

print("당신이 태어난 해는 %s년 입니다" % year)
print("당신이 태어난 월은 %s년 입니다" % month)
print("당신이 태어난 일은 %s년 입니다" % day)


n1, n2 = map(int, input("정수 2개 입력(공백 구분): ").split())
f1, f2 = map(float, input("실수 2개 입력(공백 구분): ").split())

nAvg = (n1 + n2) /2
fAvg = (f1 + f2) / 2

print("정수 평균 : %d, 실수 평균 : %f" % (nAvg, fAvg))
'''

'''
n = int(input("정수 입력: "))

if n % 3 == 0 and n % 4 == 0:
    print("%d은(는) 3의 배수 이면서, 4의 배수입니다." % n)
elif n % 3 == 0:
    print("%d은(는) 3의 배수입니다." % n)
elif n % 4 == 0:
    print("%d은(는) 4의 배수입니다.")
else:
    print("%d은(는) 3의 배수도 4의 배수도 아닙니다.")
    
    
    
'''

'''
##3과목 전부 다 60점이 넘어야함

kor, eng, mat = map(int, input("국어 영어 수학 점수를 연속으로 입력: ").split())
avg = (kor + eng + mat) / 3

if avg >= 60:
    if kor >= 60 and eng >= 60 and mat >= 60:
        print("합격입니다")
    else:
        if kor < 60:
            print("국어")
        if eng < 60:
            print("영어", end = " ")
        if mat < 60:
            print("수학", end = " ")
        print("과락으로 탈락입니다.")
else:
    print("불합격입니다.")
    
'''

'''
str = "Life is too short, you need python"

search_str = input("검색 문자열을 입력: ")

'''
'''
if search_str in str: #str내에 search_str이 존재하는 경우 True
    print("검색 문자열은 존재합니다.")
else:
    print("검색한 문자열은 없습니다.")
    
'''
'''
if search_str not in str: #str에 search_str이 존재하지 않는 경우 True
    print("검색 문자열은 존재하지 않습니다")
else:
    print("검색문자열은 존재합니다.")
    
'''


for i in range(0, 100, 1):
    print("%d" % (i+1), end = " ")
print()


for i in range(0, 91, 10):
    print("%d" % i, end = " ")
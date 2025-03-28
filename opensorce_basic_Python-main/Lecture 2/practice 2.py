#2주차 ppt 2-1, 2-2, 2-3 실습

##### 2-1 ####
#print("    *\n   ***\n  *****\n *******\n*********\n *******\n  *****\n   ***\n    *")


##### 2-2 #####
'''
base = input("입력 진수 결정(16/10/8/2) : ")
base = int(base)
#base = int(input("입력 진수 결정(16/10/8/2) : ))

n = input("값 입력 : ")

if base == 16:
    n = int(n, 16)
elif base == 10:
    n = int(n)
elif base == 8:
    n = int(n, 8)
elif base == 2:
    n = int(n, 2)
else:
    print("다른값을 입력했습니다.")

print("16진수 ==> %s" % hex(n))
print("10진수 ==> %d" % n)
print(" 8진수 ==> %s" % oct(n))
print(" 2진수 ==> %s" % bin(n))

#print(f"16진수 ==> {hex(n)}") ## f-문자열(Python 3.6 이상) 가독성이 좋아 f"문자열 {값}" 방식을 많이 사용
#print(f"10진수 ==> {n}")
#print(f" 8진수 ==> {oct(n)}")
#print(f" 2진수 ==> {bin(n)}")

'''

##### 2-3 #####

money = int(input("교환할 돈은 얼마 ? "))

num_500 = money // 500 # //연산자는 나머지의 값을 정수 개수로 표현, num_500 = money / 500은 나눗셈 연산자로 결과로 실수(float)형태가 저장됨
print(" 500원짜리 ==> %d개" % num_500)
money %= 500

num_100 = money // 100
print(" 100원짜리  ==> %d개" % num_100)
money %= 100

num_50 = money // 50
print(" 50원짜리 ==> %d개" % num_50)
money %= 50

num_10 = money // 10
print(" 10원짜리  ==> %d개" % num_10)
money %= 10

print(" 바꾸지 못한 잔돈 ==> %d원" % money)

'''
money = input("교환할 돈은 얼마 ? ")
money = int(money)
#money = int(input("교환할 돈은 얼마 ? "))

print(" 500원짜리 ==> %d개" % (money/500))
print(" 100원짜리   ==> %d개" % ((money%500)/100))
print(" 50원짜리 ==> %d개" % (((money%500)%100)/50))
print(" 10원짜리   ==> %d개" % ((((money%500)%100)%50)/10))
print(" 바꾸지 못한 잔돈 ==> %d원" % (((((money%500)%100)%50)%10)%10))
'''
'''
✅ 아래 코드가 더 정확하며, 정수 나눗셈(//)을 사용하여 정확한 개수를 계산하는 방식이므로 실수 연산으로 인한 오류가 없음.
❌ 위의 코드에서는 money/500 등으로 인해 실수(float) 결과가 나올 가능성이 있으므로 부정확한 결과가 발생할 수 있음.

즉, 위의 코드가 올바른 코드이고, 아래 코드는 잘못된 코드입니다.
'''
# vs코드에서 실행했을 때 동일한 결과가 나오는 이유는 원래 money / 500 의 결과는 실수(float) 값이지만, %d를 사용하여 출력하면서 정수로 변환됨

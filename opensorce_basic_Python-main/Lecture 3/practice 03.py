### 3-1 ###

n = input("1. 입력한 수식 계산  2. 두 수 사이의 합계 : ")
i, answer1, answer2 = 0, 0, 0
num1, num2, num3 = 0, 0, 0
if n == '1':
    res = (input("수식을 입력하세요 : "))
    answer1 = eval(res)
    print("%s의 결과는  %s입니다." % (res, answer1))
elif n == '2':
    num1 = int(input("*** 첫 번째 숫자를 입력하세요 : "))
    num2 = int(input("*** 두 번째 숫자를 입려가세요 : "))

    for i in range(num1, num2+1, 1):
        answer2 += i
    print("%d+...+%d는 %d입니다" % (num1, num2, answer2))
else:
    print("다른값을 입력했습니다.")


'''
#첫번째 숫자가 큰 경우
n = input("1. 입력한 수식 계산  2. 두 수 사이의 합계 : ")

i, answer1, answer2 = 0, 0, 0
num1, num2, num3 = 0, 0, 0
if n == '1':
    res = (input("수식을 입력하세요 : "))
    answer1 = eval(res)
    print("%s의 결과는  %s입니다." % (res, answer1))
elif n == '2':
    num1 = int(input("*** 첫 번째 숫자를 입력하세요 : "))
    num2 = int(input("*** 두 번째 숫자를 입려가세요 : "))

    if num1>num2:
        for i in range(num1, num2-1, -1):
            answer2 += i
        print("%d+...+%d는 %d입니다" % (num1, num2, answer2))
else:
    print("다른값을 입력했습니다.")


#열린국회 opne api활용
'''
    

### 3-2 ###
'''
print("#   2단   #\t#   3단   #\t#   4단   #\t#   5단   #\t#   6단   #\t#   7단   #\t#   8단  #\t#  9단  #")

i, k = 0, 0

for i in range(1, 10, 1):
    for k in range(2, 10, 1):
        print("%d X %d = %2d\t" % (k, i, i*k), end = "")
    print()

'''

##팀 프로젝트 1차##

#열린국회 opne api활용

#api명칭    api주소URL) 출력명  출력설명    api 출력데이터 예시 ##합쳐서 만들고 어떤 변수를 사용할지

#기존데이터 시트(E열)
#신규데이터 시트(J열) 약 5개?

#열린국회정보 https://open.assembly.go.kr/portal/mainPage.do (opneapi)최대한 원본에서 api데이터를 사용 아래의 파생되는 사이트가 아니라

#거의 다 열린국회정보 openApi를 통해 만들어짐
#ex) https://assembly101.kr/ (국회 101)사이트 참고 
#ex) https://www.openwatch.kr/explore/local-council-members 참고(오픈와치) api확인가능
#ex) https://thecodit.com/kr-ko (코딧)
#ex) https://likms.assembly.go.kr/bill/main.do (의안정보시스템)
#ex) https://1.monologue-of-money.com/18
#ex) https://www.bing.com/search?q=%EC%97%B4%EB%A0%A4%EB%9D%BC+%EA%B5%AD%ED%9A%8C&form=ANNTH1&refig=23da37e9c2604a15ae49852c6c0ec9bf&pc=NMTS (열려라 국회회)
#날짜
#투표결과 찬/반
#불참
#무기명 투표

#출석,청가,출장,결석

#개인 정보




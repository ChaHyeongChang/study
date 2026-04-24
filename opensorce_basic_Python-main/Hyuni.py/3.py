'''
from random import randrange

n = randrange(1, 101) #1~100


is_correct = False
for i in range(0, 5, 1):
    selct_n = int(input("%d번째 기회 : " % (i+1)))
    if n == selct_n:
        print("정답을 맞췄습니다")
        is_correct = True
        break
    elif selct_n > n:
        print("정답은 %d보다 작은 수" % selct_n)
    else:
        print("정답은 %d보다 큰 수" % selct_n)
        
if not is_correct: #is_correct가 True가 아니라면
    print("5번의 기회를 모두 마치고 정답은 %d입니다." % n)

'''


str = "Life is too short, You need Python"

if str[0].isupper(): #대문자야? True, 아니라면 False
    print("대문자 입니다.")
else:
    print("대문자가 아닙니다.")
    
    
if str[0:4].isupper(): #인덱스 0번부터 3번까지 대문자야? True, 아니라면 False
    print("0~4사이의 문자는 대문자 입니다.")
else:
    print("0~4사이의 문자는 대문자가 아닙니다.")

lower_str = str.lower() #대문자를 소문자로 변환 #기능을 담당하는 애는 무조건 ()소괄호 사용, 소괄호가 없으면 기능을 실행안하고 변수로 작용
upper_str = str.upper() #소문자를 대문자로 변환
swapcase_str = str.swapcase() #소문자는 대문자로, 대문자는 소문자로 변환환

print("oiriginal str = %s" % str)
print("lower str = %s" % lower_str)
print("upper str = %s" % upper_str)

print("문자열의 길이는 %d입니다" % len(str)) #len()함수는 문자열의 길이를 확인가능
print("swapcase str = %s" % swapcase_str) #swapcase()함수는 대,소문자를 상호 변환함
print("title str = %s" % str.title()) #title()함수는 각 단어의 첫 번째 글자만 대문자로 변환함
print("'o'문자의 개수는 %d개 입니다." % str.count('o')) #특정 문자의 개수가 몇개인지 확인 ##count('찾을 문자열')함수는 '찾을 문자열'이 몇 개 들어 있는지 개수를 셈
print("'o'문자의 위치는 %d입니다." % str.find('o')) #특장 문자의 위치가 어디인지 확인 ##find('찾을문자열')함수는 '찾을 문자열'이 몇 번째 위치하는지 찾음


buf = "        a   p   p  l  e                      "

remove_space_buf = buf.strip() # 앞 뒤 공백을 제거(중간 공백이 아님) ##strip()함수는 문자열의 앞 뒤 공백 제거
print("앞 뒤 공백을 제거한 문자열은 %s입니다" % remove_space_buf)


remove_lspace_buf = buf.lstrip() #왼쪽 공백을 제거(중간 공백 아님) ## lstrip()함수는 문자열의 왼쪽 공백 제거
print("왼쪽 공백을 제거한 문자열은 %s입니다." % remove_lspace_buf)

remove_rspace_buf = buf.rstrip() #오른쪽 공백을 제거(중간 공백 아님) ## rstrip()함수는 문자열의 오른쪽 공백 제거
print("오른쪽 공백을 제거한 문자열은 %s입니다." % remove_rspace_buf)

new_str = str.replace('short', 'long') #문자열 변경 replace('예전 문자열', '바꿀 문자열')
print("새로운 문자열은 %s입니다" % new_str)



saying = "Time and tide wait for no man"
saying.split() #공백이나 다른 문자를 기준으로 문자열을 분리해 리스트를 반환함
print(saying.split())

phone = "010-4886-5013"
phone.split('-') # -를 기준으로 문자열을 분리해 리스트를 반환함
print(phone.split('-'))


#문자열의 공백을 제거함
in_str = input("문자열 입력: ")
space_str = in_str.replace(' ', '') #공백을 없는거로 대체함
print("공백 제거 문자열: %s" % space_str)

#특수 문자가 제거 된 연락처를 저장
in_number = input("전화번호 입력(-는 빼고 숫자만 입력하세요.): ")

real_number = ''
for i in range(0, len(in_number), 1):
    if in_number[i] in '012346789': #문자열에서 문자가 포함되어 있다면 True
        real_number += in_number[i]

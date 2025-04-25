import random

def import_random():
    print("추첨된 로또 번호 ==> ", end = " ")
    
    number = []
    
    while len(number) < 6:  ###중복이 나오면 다시 뽑도록 만듬,, for문으로는 구현이 안됨(for문은 i가 자동으로 1씩 증가해서 중복이 나오면 나온만큼 변수가 하나씩 적게 저장됨)
        ##중복된 숫자가 나왔을 때는 append()가 안 되므로 길이가 유지되고 따라서 반복이 멈추지 않고 다음 숫자를 다시 뽑게 됨.
        num = random.randrange(1, 46)
        if num not in number:
            number.append(num)
        
    sort_number = sorted(number)
    
    for j in sort_number:
        print(j, end = " ")
    
    
print("** 로또 추첨을 시작합니다 **")
import_random()

'''
##중복이 안나오게 하는 간단한 방법

import random

number = sorted(random.sample(range(1, 46), 6))
print("로또 번호:", numbers)

'''

def dic_func(**para):
    for k in para.keys():
        print("%s : %s 명입니다." % (k, para[k]))
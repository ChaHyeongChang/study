import random

def import_random():
    print("추첨된 로또 번호 ==> ", end = " ")
    
    number = []
    
    while len(number) < 6:
        
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
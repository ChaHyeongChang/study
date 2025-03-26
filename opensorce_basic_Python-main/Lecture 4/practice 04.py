
'''
foods = {
    "떡볶이": "오뎅", "짜장면": "단무지", "라면": "김치", "피자": "", "맥주": "", "치킨": "", "삼겹살": ""}

while True:
    choice = input("%s 중 좋아하는 음식은 ? " % foods.keys())

    if choice in foods:
        print("<%s>궁합 음식은 <%s>입니다." % (choice, foods.get(choice))) #(choice, foods[choice])
    elif choice == '끝':
        print("프로그램 종료")
        break
    else:
        print("그런 음식이 없습니다. 확인해보세요.")

'''

'''
s = input("문자열을 입력하세요 : ")
print("내용을 거꾸로 출력 : ", end = "")

for i in range(len(s)-1, -1, -1):
    print(s[i], end = "")
'''

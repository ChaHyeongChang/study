
s = input("문자열을 입력하세요 : ")
print("내용을 거꾸로 출력 : ", end = "")

for i in range(len(s)-1, -1, -1):
    print(s[i], end = "")

